#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "types.h"

extern void configure_asmlist(flag_s *option);
extern void activate_pass(flag_s *option);
extern void copy_active_pass(flag_s *option);
extern void deactivate_passes(flag_s *option);
extern void check_compile_collide(flag_s *option);
extern void alternate_pass(flag_s *option);
extern void undef_one_stddef(flag_s *option);
extern void undef_stddefs(flag_s *option);
extern void link_dll(flag_s *option);

extern int Dargs(const char **args, int *index);
extern int ldargs(const char **args, int *index);
extern int tcargs(const char **args, int *index);
extern int tpargs(const char **args, int *index);
extern int toargs(const char **args, int *index);

#endif
