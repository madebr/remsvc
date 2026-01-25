#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "portable.h"

void dumpbin_main(int argc, char *argv[], char *dump_opt);

// FUNCTION: DUMPBIN 0x401000
int main(int argc, char *argv[])
{
    dumpbin_main(argc, argv, "-dump");
    return 0;
}

// FUNCTION: DUMPBIN 0x401020
void dumpbin_main(int argc, char *argv[], char *dump_opt)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char link_path[_MAX_PATH];
    char **new_argv;
    int i, j;
    int len;
    int code;

    // Assume link.exe is in the same directory as dumpbin.
    _splitpath(_pgmptr, drive, dir, NULL, NULL);
    _makepath(link_path, drive, dir, "link", ".exe");

    if (dump_opt != NULL) {
        // Make a copy of argv to the following specifications:
        // new_argv[0]   = argv[0] wrapped in double quotes
        // new_argv[1]   = dump_opt (i.e. "-dump")
        // new_argv[2..] = argv[1..] wrapped in double quotes

        // argc +2 because we will add one new argument and a nullptr.
        new_argv = malloc((argc + 2) * sizeof(*new_argv));
        if (new_argv == NULL) {
            printf("%s : error : out of memory\n", argv[0]);
            exit(1);
        }

        for (i = 0; i < argc; i++) {
            len = strlen(argv[i]);

            // Leave a gap at new_argv[1].
            // (i, j) values are (0, 0), (1, 2), (2, 3)...
            j = i == 0 ? i : i + 1;

            // +3 to make room for the double quotes and a new null-terminator.
            new_argv[j] = malloc(len + 3);
            if (new_argv[j] == NULL) {
                printf("%s : error : out of memory\n", argv[0]);
                exit(1);
            }

            // Wrap the input argv in double quotes
            new_argv[j][0] = '"';
            memcpy(&new_argv[j][1], argv[i], len);
            new_argv[j][len + 1] = '"';
            new_argv[j][len + 2] = '\0';
        }

        argv = new_argv;
        argv[1] = dump_opt;
        argv[argc + 1] = NULL;
    }

    code = (int) _spawnv(_P_WAIT, link_path, (const char *const *)argv);
    if (code == -1) {
        // Try again with link.exe in the cwd.
        code = (int) _spawnvp(_P_WAIT, "link.exe", (const char *const *) argv);
    }

    // Free each quote-wrapped copy of the input args.
    for (i = 1; i < argc; i++) {
        // Add one here to start at argv[2], skipping over "-dump"
        free(argv[i + 1]);
    }

    // We replaced argv with our malloc'd array.
    free(argv);

    if (code == -1) {
        printf("%s : error : cannot execute LINK.EXE\n", argv[0]);
        exit(1);
    }

    exit(code);
}
