#include "compile.h"

#include "main.h"
#include "util.h"

#ifdef _WIN32
#include <mbstring.h>
#endif
#include <stdbool.h>

#include "portable.h"

// FUNCTION: CL 0x0040330d
void acquire_pass(context_s *ctx)
{
    passinfo_s *stage_spec = ctx->compiler_stage_spec;
    source_type filetype = ctx->current_source->type;
    int stage = ctx->current_pass;

    if (ctx->exepaths[filetype][stage] == NULL) {
        char *compiler_path = findpass(ctx->exedir, stage_spec->pass_filename);

        ctx->exepaths[filetype][stage] = compiler_path;
        if (stage_spec->error_filename != NULL) {
            ctx->errorpaths[filetype][stage] =
                    findpass(extract_path(compiler_path), stage_spec->error_filename);
        }
    }
}

// FUNCTION: CL 0x0040336e
void response_file(const char *path)
{
    FILE *f;
    char *line;

    // GLOBAL: CL 0x0040a06c
    static bool32 first = TRUE;

    // GLOBAL: CL 0x0040a068
    int nesting = 0;

    nesting += 1;
    if (nesting > 13) {
        cmderr(2035, path);
    }
    f = fopen(path, "r");
    if (f == NULL) {
        cmderr(2022, path);
    }
    line = xnew(1024);
    while (fgets(line, sizeof(line) - 1, f) != NULL) {
        size_t len_line = strlen(line);
        char **args;

        if (line[len_line - 1] == '\n') {
            line[len_line - 1] = '\0';
        }
        if (!Nologo) {
            print(STDERR_FILENO, first ? "cl " : "   ");
            print(STDERR_FILENO, "%s\n", line);
            first = FALSE;
            RespEcho = TRUE;
        }
        args = sztoszv(line, TRUE);
        if (args != NULL) {
            size_t args_count = argcount((const char **) args);
            templates((const char **) args, args_count);
            xfree(args[0]);
            xfree(args);
        }
    }
    if (!feof(f)) {
        cmderr(2034, path);
    }
    fclose(f);
    xfree(line);
    nesting -= 1;
}

// FUNCTION: CL 0x004034c2
void compile(context_s *ctx)
{
    unsigned int mre_result = 0;
    CAList mr_state;
    worklist_s *remaining_inputs;
    source_s *next_linker_output;

    remaining_inputs = build_full_worklist(ctx);
    remaining_inputs = init_minrebuild(ctx, remaining_inputs, &mr_state);
    for (;;) {
        if (remaining_inputs != NULL) {
            for (;;) {
                while (remaining_inputs != NULL) {
                    passinfo_s *filetype_compiler_spec;
                    worklist_s *next_input;
                    worklist_s *current_input;

                    filetype_compiler_spec = Sourceinfo[remaining_inputs->parsed_file->type].passes;
                    remaining_inputs->parsed_file->batch_id = 0;
                    next_input = remaining_inputs->next;
                    current_input = remaining_inputs;
                    while (next_input != NULL &&
                           Sourceinfo[next_input->parsed_file->type].passes ==
                           filetype_compiler_spec &&
                           current_input->parsed_file->batch_id < 259) {
                        next_input->parsed_file->batch_id = current_input->parsed_file->batch_id + 1;
                        current_input = next_input;
                        next_input = next_input->next;
                    }
                    current_input->next = NULL;
                    mre_result |= compile_worklist(ctx, remaining_inputs);
                    remaining_inputs = next_input;
                }
                remaining_inputs = iterate_minrebuild(ctx, &mr_state);
                if (remaining_inputs == NULL) {
                    break;
                }
            }
        }
        remaining_inputs = iterate_minrebuild(ctx, &mr_state);
        if (remaining_inputs == NULL) {
            break;
        }
    }
    if (ctx->skiplist != NULL) {
        print(STDERR_FILENO, get_message(330));
        NOT_IMPLEMENTED();
#if 0
        item_0x18 = ctx->field_0x18;
        while (item_0x18 != NULL) {
            char buffer[1024];
            next_0x18 = NULL;
            if (item_0x18 != NULL) {
                next_0x18 = item_0x18->next;;
            }
            print(STDERR_FILENO, "%s\n", filename(buffer, GET_HEAD(item_0x18)->path));
            item_0x18->next = mr_state.field_0x0c;
            mr_state.field_0x0c = item_0x18;
            item_0x18 = next_0x18;
        }
#endif
    }
    if (mre_result != 0) {
        Nerrors = mre_result;
        return;
    }

    ctx->current_source = ctx->field_0x10;
    if (ctx->field_0x10 != NULL) {
        source_s *parsed_filepath = ctx->field_0x10;
        while (parsed_filepath != NULL) {
            if (parsed_filepath->type == SOURCE_OBJ) {
                break;
            }
            parsed_filepath = parsed_filepath->next;
        }
        if (parsed_filepath != NULL) {
            ctx->current_source = parsed_filepath;
        }
    }
    cc_switches(ctx);
    Nerrors = passes(Link_passes, ctx, link_);
    if (Nerrors) {
        return;
    }
    if (Exefilename != NULL) {
        source_s *exe_path = newsource(Exefilename, SOURCE_EXE);
        exe_path->next = ctx->field_0x10->next;
        ctx->field_0x10->next = exe_path;
    }
    next_linker_output = ctx->field_0x10;
    for (;;) {
        source_s *linker_output;
        for (;;) {
            linker_output = next_linker_output;
            if (linker_output == NULL) {
                return;
            }
            next_linker_output = linker_output->next;
            if (Sourceinfo[linker_output->type].phase == PHASE_POSTPROCESS) {
                break;
            }
        }
        ctx->current_source = linker_output;
        Nerrors = passes(Sourceinfo[linker_output->type].passes, ctx, dopass);
        if (Nerrors) {
            return;
        }
    }
}

// FUNCTION: CL 0x004036b5
worklist_s *build_full_worklist(context_s *ctx)
{
    worklist_s *result = NULL;
    worklist_s *last_input = NULL;
    source_s *parsed_filepath;
    for (parsed_filepath = ctx->field_0x10; parsed_filepath != NULL; parsed_filepath = parsed_filepath->next) {
        if (Sourceinfo[parsed_filepath->type].phase == PHASE_COMPILE) {
            worklist_s *compiler_input = new_worklist_item(parsed_filepath);
            if (result != NULL) {
                last_input->next = compiler_input;
            } else {
                result = compiler_input;
            }
            last_input = compiler_input;
        }
    }
    if (last_input == result) {
        BatchPassOK = FALSE;
    }
    return result;
}

// FUNCTION: CL 0x00403705
worklist_s *new_worklist_item(source_s *parsed_file)
{
    worklist_s *result = xnew(sizeof(worklist_s));
    result->next = NULL;
    result->parsed_file = parsed_file;
    result->had_error = 0;
    return result;
}

// FUNCTION: CL 0x0040371e
worklist_s *init_minrebuild(context_s *ctx, worklist_s *inputs, CAList *mr_state)
{
#ifdef WITH_MSPDB
    MREngine *engine;
    MREDriver *driver;
    int result_code;
    worklist_s *input;
    SRCTARG *unk;
    char *arg_string;
#endif

    if (!MinimalRebuild || !MinRebuildOK) {
        MinRebuildOK = FALSE;
        return inputs;
    }
#ifdef WITH_MSPDB
    if (!MREFOpenByName(&engine, IdbFileName, &result_code, Bigbuf, Reproducable, TRUE)) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
        return inputs;
    }
    unk = NULL;
    MREQueryMreDrv(engine, &driver);
    MREDrvOneTimeInit(driver);
    mr_state->pstDoCompile = NULL;
    mr_state->pstMaybeCompile = NULL;
    mr_state->pstDontCompile = NULL;
    mr_state->pstDone = NULL;
    mr_state->pstError = NULL;
    ctx->skiplist = NULL;
    ctx->skiplistend = &ctx->skiplist;
    arg_string = get_minrebuild_options(ctx);
    for (input = inputs; input != NULL; input = input->next) {
        source_s *parsed_file = input->parsed_file;
        SRCTARG* srctarg;

        ctx->current_source = parsed_file;
        cc_switches(ctx);
        srctarg = &input->srctarg;
        srctarg->psrctargNext = NULL;
        if (unk != NULL) {
            unk->psrctargNext = srctarg;
        } else {
            mr_state->pstMaybeCompile = srctarg;
        }
        srctarg->fCpp = parsed_file->type == SOURCE_CPP || parsed_file->type == SOURCE_CXX;
        srctarg->szSrc = parsed_file->path;
        srctarg->szTarg = Object;
        srctarg->szOptions = arg_string;
        input->sbrfile = SbrFileName;
        unk = srctarg;
    }
    if (MinRebuildOK && MREDrvFFilesOutOfDate(driver, mr_state)) {
        inputs = rethread_worklist_by_srctargs(mr_state->pstDoCompile);
    } else if (MinRebuildOK) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
    }
    if (!MREDrvFRelease(driver) && MinRebuildOK) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
    }
    if (!MREFClose(engine, MinRebuildOK) && MinRebuildOK) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
    }
    return inputs;
#else
    (void) ctx;
    (void) mr_state;
    cmdwarn(4028);
    MinRebuildOK = FALSE;
    return inputs;
#endif
}

// FUNCTION: CL 0x004038f0
worklist_s *iterate_minrebuild(context_s *ctx, CAList *mr_state)
{
#ifdef WITH_MSPDB
    int result_code;
    MREngine *engine;
    MREDriver *driver;
#endif

    if (!MinimalRebuild || !MinRebuildOK) {
        return NULL;
    }
#ifdef WITH_MSPDB
    if (mr_state->pstDoCompile == NULL && mr_state->pstMaybeCompile == NULL && mr_state->pstDontCompile == NULL) {
        return NULL;
    }
    if (!MREFOpenByName(&engine, IdbFileName, &result_code, Bigbuf, Reproducable, TRUE)) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
        return rethread_worklist_by_srctargs(mr_state->pstMaybeCompile);
    }
    MREQueryMreDrv(engine, &driver);
    if (mr_state->pstDoCompile != NULL) {
        NOT_IMPLEMENTED();
    }
    (void) ctx;
    NOT_IMPLEMENTED();
#else
    (void) ctx;
    (void) mr_state;
    cmdwarn(4028);
    MinRebuildOK = FALSE;
    return NULL;
#endif
}

#ifdef WITH_MSPDB

// FUNCTION: CL 0x00403b70
char *get_minrebuild_options(context_s *ctx)
{
    char *buffer1 = xnew(1024);
    char *buffer2 = xnew(1024);
    char **argv;
    int arg_i;
    flag_s *option;
    char *arg_string;
    char *arg_ptr;
    int count_arguments;
    size_t len;

    count_arguments = 0;
    if (ctx->include != NULL && DefInclude) {
        count_arguments += 1;
    }
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_these_pass_ids(option, "Mm") != '\0') {
            count_arguments += 1;
        }
    }
    len = 0;
    argv = xnew(count_arguments * sizeof(char *));
    arg_i = 0;
    for (option = ctx->flags; option != NULL; option = option->next) {
        char c = flag_these_pass_ids(option, "Mm");
        if (c != '\0') {
            char *arg_ptr;
            char *arg_value_ptr;

            Bigbuf[0] = '-';
            arg_ptr = append(&Bigbuf[1], option->base);
            arg_value_ptr = option->arg;
            if (arg_value_ptr != NULL) {
                if (c == 'm') {
                    if (_fullpath(buffer2, arg_value_ptr, 1024) == NULL) {
                        strcpy(buffer2, option->arg);
                    }
                    _mbslwr((unsigned char *) buffer2);
                    arg_value_ptr = buffer2;
                }
                strqcpy(buffer1, arg_value_ptr);
                append(arg_ptr, buffer1);
            }
            argv[arg_i++] = xstrdup(Bigbuf);
            len += strlen(Bigbuf) + 1;
        }
    }
    if (ctx->include != NULL && DefInclude) {
        size_t lenInclude = strqlen(ctx->include);
        char *incString = xnew(lenInclude + 6);
        strcpy(incString, "-inc=");
        strqcpy(&incString[5], ctx->include);
        _mbslwr((unsigned char *) incString);
        len += lenInclude + 6;
        argv[arg_i] = incString;
    }
    qsort(argv, count_arguments, sizeof(char *), strcmp_proxy);
    arg_string = xnew(len + 1);
    arg_ptr = arg_string;
    for (arg_i = 0; arg_i < count_arguments; arg_i++) {
        arg_ptr = append(arg_ptr, argv[arg_i]);
        *arg_ptr++ = ' ';
    }
#ifdef REMSVC_RECCMP
    arg_ptr[-1] = '\0';
#else
    arg_string[len] = '\0';
#endif
    for (arg_i = 0; arg_i < count_arguments; arg_i++) {
        xfree(argv[arg_i]);
    }
    xfree(argv);
    xfree(buffer2);
    xfree(buffer1);
    return arg_string;
}

// FUNCTION: CL 0x00403db1
int strcmp_proxy(const void *lhs, const void *rhs)
{
    return strcmp(*(char **) lhs, *(char **) rhs);
}

// FUNCTION: CL 0x00403dc6
worklist_s *rethread_worklist_by_srctargs(SRCTARG *srctarg)
{
    (void) srctarg;
    NOT_IMPLEMENTED();
}

// FUNCTION: CL 0x00403dfa
SRCTARG *rethread_srctargs_by_worklist(worklist_s worklist)
{
    (void) worklist;
    NOT_IMPLEMENTED();
}

#endif

// FUNCTION: CL 0x00403e26
unsigned int compile_worklist(context_s *ctx, worklist_s *input_file)
{
    char buffer[1024];
    int count_failed = 0;
    passinfo_s *input_compiler_spec = Sourceinfo[input_file->parsed_file->type].passes;
    int count_stages = 0;
    int stage;
    int message_stage;
    bool do_stage_per_stage;

    // GLOBAL: CL 0x0040a1bc
    bool32 first = TRUE;

    for (stage = 0; input_compiler_spec[stage].pass_filename != NULL; stage++) {
        if (input_compiler_spec[stage].is_active) {
            count_stages += 1;
        }
    }
    if (BatchPasses && BatchPassOK && count_stages >= 2) {
        do_stage_per_stage = true;
        ctx->batchlist = input_file;
    } else {
        do_stage_per_stage = false;
        ctx->batchlist = NULL;
    }
    message_stage = 0;
    for (stage = 0;; stage++) {
        passinfo_s *stage_compiler_spec = &input_compiler_spec[stage];
        bool run_on_file = false;
        if (do_stage_per_stage) {
            if (stage_compiler_spec->is_active) {
                if (message_stage > 0) {
                    input_file = reverse_worklist(input_file);
                    ctx->batchlist = input_file;
                }
                message_stage += 1;
                ctx->current_pass = stage;
                ctx->compiler_stage_spec = stage_compiler_spec;
                ctx->current_source = input_file->parsed_file;
                if (message_stage == 1) {
                    if (first) {
                        first = FALSE;
                    } else {
                        print(STDERR_FILENO, get_message(331));
                    }
                } else if (message_stage == 2 && count_stages > 2) {
                    print(STDERR_FILENO, get_message(332));
                } else {
                    if (message_stage == count_stages) {
                        print(STDERR_FILENO, get_message(333));
                    }
                }
                run_on_file = true;
            }
        }
        if (!do_stage_per_stage || run_on_file) {
            worklist_s *current_input_file;
            for (current_input_file = input_file; current_input_file != NULL;
                 current_input_file = current_input_file->next) {
                if (!do_stage_per_stage || !current_input_file->had_error) {
                    source_s *current_parsed_filepath = current_input_file->parsed_file;
                    ctx->current_source = current_parsed_filepath;
                    cc_switches(ctx);
                    if (!do_stage_per_stage || message_stage < 2) {
                        print(STDERR_FILENO, "%s\n", filename(buffer, current_parsed_filepath->path));
                    }
                    if (do_stage_per_stage) {
                        acquire_pass(ctx);
                        Nerrors = dopass(ctx);
                    } else {
                        Nerrors = passes(input_compiler_spec, ctx, dopass);
                    }
                    if (Nerrors) {
                        count_failed += 1;
                        current_input_file->had_error = 1;
                        if (do_stage_per_stage) {
                            rm_il(TRUE);
                            if (do_stage_per_stage && message_stage != count_stages) {
                                continue;
                            }
                        }
                    } else if (do_stage_per_stage && message_stage != count_stages) {
                        continue;
                    }
                    if (Object != NULL) {
                        source_s *obj_parsed_path = newsource(Object, SOURCE_OBJ);
                        obj_parsed_path->next = current_parsed_filepath->next;
                        current_input_file->parsed_file->next = obj_parsed_path;
                    }
                    rm_il(TRUE);
                }
            }
            if (!do_stage_per_stage) {
                ctx->batchlist = NULL;
                return count_failed;
            }
        }
        if (!do_stage_per_stage || stage_compiler_spec->pass_filename == NULL) {
            ctx->batchlist = NULL;
            return count_failed;
        }
    }
}

// FUNCTION: CL 0x00404069
worklist_s *reverse_worklist(worklist_s *input_file)
{
    worklist_s *new_head;
    worklist_s *new_next;

    new_next = new_head = NULL;
    while (input_file != NULL) {
        new_head = input_file;
        input_file = new_head->next;
        new_head->next = new_next;
        new_next = new_head;
    }
    return new_head;
}

// FUNCTION: CL 0x00404080
int passes(passinfo_s *passes, context_s *ctx, int (*exec)(context_s *))
{
    int i;

    for (i = 0; passes[i].pass_filename != NULL; i++) {
        passinfo_s *pass = &passes[i];
        if (pass->is_active) {
            ctx->current_pass = i;
            ctx->compiler_stage_spec = pass;
            acquire_pass(ctx);
            Nerrors = exec(ctx);
            if (Nerrors) {
                return Nerrors;
            }
        }
    }
    return Nerrors;
}

// FUNCTION: CL 0x004040c9
int dopass(context_s *ctx)
{
    char *buffer1;
    char *buffer2;
    const char *exe_filepath;
    size_t len;
    int argc;
    flag_s *option;
    char **argv;
    char *arg_string;
    char **argv_ptr;
    char *arg_ptr;
    passinfo_s *compiler_stage_spec;
    source_s *current_filepath;
    int result;

    Action = TRUE;
    buffer1 = xnew(1024);
    buffer2 = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    current_filepath = ctx->current_source;
    exe_filepath = ctx->exepaths[current_filepath->type][ctx->current_pass];
    len = strqlen(exe_filepath);
    argc = 0;
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            len += replaca_strlen(option->base, ctx) + 2;
            argc += 1;
            if (option->arg != NULL) {
                len += replaca_strlen(option->arg, ctx) + 2;
                argc += 1;
            }
        }
    }
    if (ctx->include != NULL && DefInclude) {
        const char *ptr_include;
        len += strqlen(ctx->include) + 6;
        ptr_include = ctx->include;
        for (;;) {
            argc += 2;
            ptr_include = (char *) _mbschr((unsigned char *) ptr_include, ';');
            if (ptr_include == NULL) {
                break;
            }
            len += 6;
            ptr_include += 1;
        }
    }
    argv = xnew((argc + 2) * sizeof(char *));
    arg_string = xnew(len);
    argv_ptr = argv;
    *argv_ptr++ = arg_string;
    strqcpy(buffer1, exe_filepath);
    arg_ptr = append(arg_string, buffer1);
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            arg_ptr++;
            *argv_ptr++ = arg_ptr;
            if (!(option->info & 0x8)) {
                *arg_ptr++ = compiler_stage_spec->swchar;
            }
            arg_ptr = append(arg_ptr, replaca(buffer1, option->base, ctx));
            if (option->arg != NULL) {
                if (!(option->info & 0x4)) {
                    arg_ptr++;
                    *argv_ptr++ = arg_ptr;
                }
                strqcpy(buffer1, replaca(buffer2, option->arg, ctx));
                arg_ptr = append(arg_ptr, buffer1);
            }
        }
    }
    if (ctx->include != NULL && DefInclude && strchr("1P", compiler_stage_spec->id) != NULL) {
        const char *ptr_include = ctx->include;
        size_t pos_non_whitespace;

        for (;;) {
            char *ptr_end;

            ptr_end = (char *) _mbschr((unsigned char *) ptr_include, ';');
            if (ptr_end == NULL) {
                break;
            }
            if (ptr_include != ptr_end) {
                int pos_non_whitespace = (int) _mbsspn((unsigned char *) ptr_include, (unsigned char *) " \t");
                if (pos_non_whitespace < ptr_end - ptr_include) {
                    *argv_ptr++ = &arg_ptr[1];
                    arg_ptr = append(&arg_ptr[1], "-I");
                    *argv_ptr++ = &arg_ptr[1];
                    *ptr_end = '\0';
                    strqcpy(buffer1, ptr_include);
                    *ptr_end = ';';
                    arg_ptr = append(&arg_ptr[1], buffer1);
                }
            }
            ptr_include = &ptr_end[1];
        }
        pos_non_whitespace = _mbsspn((unsigned char *) ptr_include, (unsigned char *) " \t");
        if (pos_non_whitespace < strlen(ptr_include)) {
            *argv_ptr++ = &arg_ptr[1];
            arg_ptr = append(&arg_ptr[1], "-I");
            *argv_ptr++ = &arg_ptr[1];
            strqcpy(buffer1, ptr_include);
            append(&arg_ptr[1], buffer1);
        }
    }
    *argv_ptr = NULL;
    if (Verbose) {
        char **ptr;

        print(STDERR_FILENO, "`%s", exe_filepath);
        for (ptr = &argv[1]; *ptr != NULL; ptr++) {
            print(STDERR_FILENO, " %s", *ptr);
        }
        print(STDERR_FILENO, "'\n");
    }
    result = 0;
    if (!Nospawn) {
        int inheritEnv;

        if (Time) {
            starttiming();
        }
        if (current_filepath->type == SOURCE_EXE) {
            inheritEnv = 2;
        } else {
            inheritEnv = 0;
        }
        result = execute(inheritEnv, exe_filepath, compiler_stage_spec->environment_variable, argv);
        if (Time) {
            endtiming(exe_filepath);
        }
    }
    xfree(argv);
    xfree(arg_string);
    xfree(buffer2);
    xfree(buffer1);
    return result;
}

// FUNCTION: CL 0x00404471
int link_(context_s *ctx)
{
    char buffer[2048];
    char *argument_string;
    const char *program_exe;
    char *arguments_ptr;
    passinfo_s *compiler_stage_spec;
    char **argv;
    int result;

    Action = TRUE;
    argument_string = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    program_exe = ctx->exepaths[ctx->current_source->type][ctx->current_pass];
    strqcpy(argument_string, program_exe);
    arguments_ptr = append(buffer, argument_string);
    if (Coff) {
        CoffResponseFile(ctx);
        arguments_ptr = append(arguments_ptr, " -link");
    } else {
        OmfResponseFile(ctx);
    }
    arguments_ptr[0] = ' ';
    arguments_ptr[1] = '\0';
    arguments_ptr = append(&arguments_ptr[1], "@");
    arguments_ptr = append(arguments_ptr, ctx->tempPath);
    append(arguments_ptr, "lk");
    if (strlen(buffer) > sizeof(buffer) - 1) {
        cmderr(0);
    }
    argv = sztoszv(buffer, 0);
    if (Verbose) {
        print(STDERR_FILENO, "`%s'\n", buffer);
    }
    result = 0;
    if (!Nospawn) {
        if (Time) {
            starttiming();
        }
        result = execute(1, program_exe, compiler_stage_spec->environment_variable, argv);
        if (Time) {
            endtiming(program_exe);
        }
    }
    xfree(argv);
    xfree(argument_string);
    return result;
}

// FUNCTION: CL 0x004045d8
void OmfResponseFile(context_s *ctx)
{
    char *buffer1;
    char *buffer2;
    FILE *f;
    const passinfo_s *compiler_stage_spec;
    source_s *filepath;
    flag_s *option;
    bool first;
    char *exePath;

    buffer1 = xnew(1024);
    buffer2 = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    strcpy(buffer1, ctx->tempPath);
    strcat(buffer1, "lk");
    if (!Nospawn) {
        f = fopen(buffer1, "w");
        if (f == NULL) {
            cmderr(2018);
        }
    } else {
        f = NULL;
    }
    first = true;
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_OBJ || filepath->type == SOURCE_UNKNOWN) {
            if (!first) {
                echoprintf(f, "+\n");
            }
            echoprintf(f, "\"%s\"", filepath->path);
            first = false;
        }
    }
    replaca(buffer1, Exefilename, ctx);
    exePath = xstrdup(buffer1);
    echoprintf(f, "\n\"%s\"", exePath);
    echoprintf(f, "\n\"%s\"", mapfile(buffer1, exePath));
    first = true;
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_LIB) {
            if (!first) {
                echoprintf(f, "+");
            }
            echoprintf(f, "\n\"%s\"", filepath->path);
            first = false;
        }
    }
    if (first) {
        echoprintf(f, "\n");
    }
    first = true;
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            if (!first) {
                echoprintf(f, " ");
            } else {
                first = false;
            }
            if (!(option->info & 0x8)) {
                echoprintf(f, "%c", compiler_stage_spec->swchar);
            }
            echoprintf(f, "%s", replaca(buffer1, option->base, ctx));
            if (option->arg != NULL) {
                if (!(option->info & 0x4)) {
                    echoprintf(f, " ");
                }
                strqcpy(buffer1, replaca(buffer2, option->arg, ctx));
                echoprintf(f, "%s", buffer1);
            }
        }
    }
    if (first) {
        echoprintf(f, "\n");
    }
    first = true;
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_DEF) {
            if (!first) {
                echoprintf(f, "+\n");
            }
            echoprintf(f, "\n\"%s\"", filepath->path);
            first = false;
        }
    }
    echoprintf(f, ";\n");
    if (f != NULL) {
        fclose(f);
    }
    xfree(exePath);
    xfree(buffer2);
    xfree(buffer1);
}

// FUNCTION: CL 0x00404897
void CoffResponseFile(context_s *ctx)
{
    char *buffer1;
    char *buffer2;
    FILE *f;
    const passinfo_s *compiler_stage_spec;
    flag_s *option;
    source_s *filepath;

    buffer1 = xnew(1024);
    buffer2 = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    strcpy(buffer1, ctx->tempPath);
    strcat(buffer1, "lk");
    if (!Nospawn) {
        f = fopen(buffer1, "w");
        if (f == NULL) {
            cmderr(2018);
        }
    } else {
        f = NULL;
    }
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            if (!(option->info & 0x8)) {
                echoprintf(f, "%c", compiler_stage_spec->swchar);
            }
            echoprintf(f, "%s", replaca(buffer1, option->base, ctx));
            if (option->arg != NULL) {
                if (!(option->info & 0x4)) {
                    echoprintf(f, " ");
                }
                strqcpy(buffer1, replaca(buffer2, option->arg, ctx));
                echoprintf(f, "%s", buffer1);
            }
            echoprintf(f, "\n");
        }
    }
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_DEF) {
            strqcpy(buffer1, filepath->path);
            echoprintf(f, "%cdef:%s\n", compiler_stage_spec->swchar, buffer1);
        }
    }
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (Sourceinfo[filepath->type].phase == PHASE_LINK && filepath->type != SOURCE_DEF) {
            strqcpy(buffer1, filepath->path);
            echoprintf(f, "%s\n", buffer1);
        }
    }
    if (f != NULL) {
        fclose(f);
    }
    xfree(buffer2);
    xfree(buffer1);
}

// FUNCTION: CL 0x00404a64
const char *mapfile(char *buffer, const char *exePath)
{
    char drive[4];
    char dir[256];
    char filename[256];
    char extension[256];

    if (!Mapfile) {
        return "nul.map";
    }
    if (!Mapfilename) {
        _splitpath(exePath, drive, dir, filename, NULL);
        _makepath(buffer, drive, dir, filename, "map");
        return buffer;
    }
    _splitpath(exePath, drive, dir, filename, extension);
    if (filename[0] == '\0') {
        basename(filename, exePath);
    }
    _makepath(buffer, drive, dir, filename, extension[0] != '\0' ? extension : "map");
    return buffer;
}

// FUNCTION: CL 0x00404b29
char *replaca(char *buffer, const char *format, context_s *ctx)
{
    char path_buffer[256];
    char *dest = buffer;
    char *ptr;
    const char *filepath;
    source_type filetype;
    short batch_id;

    if (ctx->current_source != NULL) {
        filepath = ctx->current_source->path;
        filetype = ctx->current_source->type;
        batch_id = ctx->current_source->batch_id;
    } else {
        filepath = "";
        filetype = SOURCE_UNKNOWN;
        batch_id = -1;
    }
    while (*format != '\0') {
        if (*format == '%') {
            *dest = '\0';
            switch (format[1]) {
            case '%':
                *dest++ = format[1];
                break;
            case 'b':
                basename(path_buffer, filepath);
                dest = concat(dest, path_buffer);
                break;
            case 'B':
                basename(path_buffer, filepath);
                _mbsupr((unsigned char *) path_buffer);
                dest = concat(dest, path_buffer);
                break;
            case 'e':
                ptr = ctx->errorpaths[filetype][ctx->current_pass];
                if (dest == NULL) {
                    dest = "";
                }
                dest = concat(dest, ptr);
                break;
            case 'f':
                dest = concat(dest, filepath);
                break;
            case 'X':
                if (DllFlg) {
                    dest = concat(dest, "dll");
                } else {
                    dest = concat(dest, "exe");
                }
                break;
            case 'x':
                pathname(path_buffer, Exefilename);
                dest = concat(dest, path_buffer);
                break;
            case 't':
                dest = concat(dest, ctx->tempPath);
                if (ctx->batchlist && batch_id != -1) {
                    dest[-6] = 'a' + batch_id / 10;
                    dest[-5] = '0' + batch_id % 10;
                }
                break;
            case 'm':
            {
                char *exe_buffer = xnew(1024);
                replaca(exe_buffer, Exefilename, ctx);
                mapfile(dest, exe_buffer);
                dest += strlen(dest);
                xfree(exe_buffer);
                break;
            }
            }
            format += 2;
        } else {
            *dest++ = *format++;
        }
    }
    *dest = '\0';
    return buffer;
}

// FUNCTION: CL 0x00404d26
size_t replaca_strlen(const char *text, context_s *ctx)
{
    char buffer[256];
    size_t len = 0;
    const char *current_file;
    source_type current_filetype;
    if (ctx->current_source == NULL) {
        current_file = "";
        current_filetype = SOURCE_UNKNOWN;
    } else {
        current_file = ctx->current_source->path;
        current_filetype = ctx->current_source->type;
    }
    while (*text != '\0') {
        switch (*text) {
        case '"':
        case '\\':
            len += 2;
            text++;
            break;
        case '%':
            switch (text[1]) {
            case '%':
                len += 1;
                break;
            case 'X':
                len += 3;
                break;
            case 'e':
                if (ctx->errorpaths[current_filetype][ctx->current_pass] != NULL) {
                    len += strqlen(ctx->errorpaths[current_filetype][ctx->current_pass]);
                }
                break;
            case 'f':
                len += strqlen(current_file);
                break;
            case 'b':
            case 'B':
                basename(buffer, current_file);
                len += strqlen(buffer);
                break;
            case 'm':
                len += 1024;
                break;
            case 't':
                len += strqlen(ctx->tempPath);
                break;
            case 'x':
                pathname(buffer, Exefilename);
                len += strqlen(buffer);
                break;
            }
            text += 2;
            break;
        default:
            len += 1;
            text++;
            break;
        }
    }
    return len;
}

