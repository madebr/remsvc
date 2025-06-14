#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#include "portable.h"

static int run_link_exe(int argc, char *argv[], const char *command);

// FUNCTION: LIB 0x00401000
int main(int argc, char *argv[])
{
    run_link_exe(argc, argv, "-lib");
    return 0;
}

// FUNCTION: LIB 0x00401020
int run_link_exe(int argc, char *argv[], const char *command)
{
    char program_drive[4];
    char program_dir[256];
    char path_link_exe[260];
    const char *program_path;
    int result;
    int i;

#ifdef _MSC_VER
    program_path = *__p__pgmptr();
#else
    program_path = argv[0];
#endif
    _splitpath(program_path, program_drive, program_dir, NULL, NULL);
    _makepath(path_link_exe, program_drive, program_dir, "link", ".exe");
    if (command != NULL) {
        char **new_argv;

        new_argv = malloc((argc + 2) * sizeof(char *));
        if (new_argv == NULL) {
            printf("%s : error : out of memory\n", argv[0]);
            exit(1);
        }
        for (i = 0; i < argc; i++) {
            size_t len;
            char *new_arg;

            len = strlen(argv[i]);
            new_arg = malloc(len + 3);
            new_argv[i == 0 ? 0 : i + 1] = new_arg;
            if (new_arg == NULL) {
                printf("%s : error : out of memory\n", argv[0]);
                exit(1);
            }
            new_arg[0] = '"';
            memcpy(&new_arg[1], argv[i], len);
            new_arg[len + 1] = '"';
            new_arg[len + 2] = '\0';
        }
        argv = new_argv;
        new_argv[1] = (char *) command;
        new_argv[argc + 1] = NULL;
    }
    result = (int) _spawnv(_P_WAIT, path_link_exe, (const char *const *) argv);
    if (result == -1) {
        result = _spawnvp(_P_WAIT, "link.exe", (const char *const *) argv);
    }
    for (i = 1; i < argc; i++) {
        free(argv[i + 1]);
    }
    free(argv);
    if (result == -1) {
        // FIXME: Use after free
        printf("%s : error : cannot execute LINK.EXE\n", argv[0]);
    }
    exit(result);
}
