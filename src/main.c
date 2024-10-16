#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mem.h"
#include "stb_ds.h"

static const char *_copy_arg_str(const char *str) {
    size_t str_size = strlen(str);
    char *new_str = malloc_with_check((sizeof(char) * str_size) + 1);
    strncpy(new_str, str, str_size);
    return new_str;
}

static void _debug_print_dir_list(char **list) {
    for (int i = 0; i < arrlen(list); i++) {
        printf("Dir: %s\n", list[i]);
    }
}
static void _free_dir_list(char **list) {
    for (int i = 0; i < arrlen(list); i++) {
        free(list[i]);
    }
}

// common arguments
typedef enum {
    INDEX = 1
} SubCommand;

typedef struct {
    int debug;
    int verbose;
    SubCommand sub;
} RunOptions;

#define COMMON_OPTIONS \
    {"debug", no_argument, 0, 1000}, {"verbose", no_argument, 0, 1001},

// looks stupid, but works
#define PARSE_COMMON_OPTIONS  \
    case 1000: {              \
        run_opts.debug = 1;   \
        break;                \
    }                         \
    case 1001: {              \
        run_opts.verbose = 1; \
        break;                \
    }

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s <subcommand> args\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // TODO: print help, version number, license

    // common argparse stuff
    int c;
    RunOptions run_opts = {0};

    // ========================================================
    // index subcommand
    struct option index_long_options[] = {
        {"dir", required_argument, 0, 'd'},

        COMMON_OPTIONS

        // TODO: implement ignore files
        {0, 0, 0, 0},
    };

    char **dir_list = NULL;

    if (strncmp(argv[1], "index", 5) == 0) {
        while ((c = getopt_long(argc, argv, "d:", index_long_options, NULL)) != -1) {
            switch (c) {
                case 'd': {
                    arrpush(dir_list, _copy_arg_str(optarg));
                    break;
                }

                    PARSE_COMMON_OPTIONS

                case '?': {
                    // TODO: better error messages
                    fprintf(stderr, "Unknown argument\n");
                    break;
                }
            }
        }
    }

    if (run_opts.debug == 1) {
        _debug_print_dir_list(dir_list);
    }

    // Perform the indexing

    _free_dir_list(dir_list);

    arrfree(dir_list);
    // Index command end
    // ========================================================

    printf("Verbose: %d Debug: %d\n", run_opts.verbose, run_opts.debug);
}
