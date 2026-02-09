#ifndef CL_COMPILE_H
#define CL_COMPILE_H

#include "types.h"

extern void acquire_pass(context_s *ctx);
extern void response_file(const char *path);
extern void compile(context_s *ctx);
extern worklist_s *build_full_worklist(context_s *ctx);
extern worklist_s *new_worklist_item(source_s *parsed_file);
extern worklist_s *init_minrebuild(context_s *ctx, worklist_s *inputs, CAList *mr_state);
extern worklist_s *iterate_minrebuild(context_s *ctx, CAList *mr_state);
extern char *get_minrebuild_options(context_s *ctx);
#ifdef WITH_MSPDB
extern int strcmp_proxy(const void *lhs, const void *rhs);
extern worklist_s *rethread_worklist_by_srctargs(SRCTARG *srctarg);
extern SRCTARG *rethread_srctargs_by_worklist(worklist_s worklist);
#endif
extern unsigned int compile_worklist(context_s *ctx, worklist_s *input_file);
extern worklist_s *reverse_worklist(worklist_s *input_file);
extern int passes(passinfo_s *passes, context_s *ctx, int (*exec)(context_s *));
extern int dopass(context_s *ctx);
extern int link_(context_s *ctx);
extern void OmfResponseFile(context_s *ctx);
extern void CoffResponseFile(context_s *ctx);
extern const char *mapfile(char *buffer, const char *exePath);
extern char *replaca(char *buffer, const char *format, context_s *ctx);
extern size_t replaca_strlen(const char *text, context_s *ctx);

#endif
