#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "types.h"

extern void OnbAOption(tParsed_option *option);
extern void OnbaOption(tParsed_option *option);
extern void OnbcOption(tParsed_option *option);
extern void OnbdOption(tParsed_option *option);
extern void OnboOption(tParsed_option *option);
extern void OnbpOption(tParsed_option *option);
extern void OnbUOption(tParsed_option *option);
extern void OnbuOption(tParsed_option *option);
extern void OnArgumentLDorLDd(tParsed_option *option);

extern int OnDCallback(const char **args, int *index);
extern int OnLinkCallback(const char **args, int *index);
extern int OnTcCallback(const char **args, int *index);
extern int OnTpCallback(const char **args, int *index);
extern int OnToCallback(const char **args, int *index);

#endif
