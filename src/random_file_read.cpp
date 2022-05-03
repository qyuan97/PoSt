//
// Created by qy on 29/4/2022.
//
#include<assert.h>
#include<fcntl.h>
#include<stdint.h>
#include<toolkit.h>
#include<math.h>
#include<getopt.h>

#define BYTES_UNDER_P (7)
#define CHUNK_ALIGN (56)
#define ROW_SIZE_BYTES (4194304) // 4MB

void usage(const char* arg0) {
    fprintf(stderr, "usage: %s [OPTIONS] <filePath> <fileSize>\n"
                                  "\t -h --help show this help menu\n"
                                  "<fileSize> should be a positive integer, followed by optionally by one of\n"
                                  "K:KB\nM:MB\nG:GB\nT:TB\n"
                                  , arg0);
}

int main(int argc, char* argv[]) {

    struct option longopts[] = {
            {"help", no_argument, NULL, 'h'},
            {NULL, 0, NULL, 0}
    };

    while (true) {
        switch (getopt_long(argc, argv, "h", longopts, NULL)) {
            case -1:
                goto done_opts;
            case 'h':
                usage(argv[0]);
                exit(1);
            default:
                fprintf(stderr, "unexpected getopt return value\n");
                exit(2);
        }
    }

    done_opts:

    if (optind != argc - 2) {
        usage(argv[0]);
        exit(1);
    }

    int fd;
    const char* filePath = argv[optind];
    if ((fd = open(filePath, O_RDONLY)) < 0) {
        fprintf(stderr, "cannot open the file %s\n", filePath);
        return 2;
    }

    uint64_t fileSize;
    {
        const char* conv_str = argv[optind+1];
        char* end;
        fileSize = strtoul(argv[optind+1], &end, 10);
        printf("argv[0]: %s\nargv[1]: %s\nargv[2]: %c\n", filePath, conv_str, *end);
        if (end == conv_str || !(*end == '\0' || *(end+1) == '\0')) {
            fprintf(stderr, "invalid size specification '%s'n", conv_str);
            return 2;
        }
        switch (*end) {
            case '\0': break;
            case 'k': case 'K': fileSize *= 1024ul; break;
            case 'm': case 'M': fileSize *= 1048576ul; break;
            case 'g': case 'G': fileSize *= 1073741824ul; break;
            case 't': case 'T': fileSize *= 1099511627776ul; break;
            default: fprintf(stderr, "invalid size specification '%s'\n", conv_str); return 2;
        }
    }

    uint64_t n_rows = 1 + (fileSize - 1) / ROW_SIZE_BYTES;
    const static uint64_t ROW_SIZE_64 = ROW_SIZE_BYTES / 8;

    uint64_t *raw_row = (uint64_t *)malloc(ROW_SIZE_BYTES);
    assert (raw_row);

    for (size_t i = 0; i < n_rows; ++i) {
        my_pread(fd, raw_row, ROW_SIZE_BYTES, ROW_SIZE_BYTES * i);
        for (size_t j = 0; j < ROW_SIZE_64; ++j) {
            printf("current block: %lu\n", raw_row[j]);
        }
    }

    free(raw_row);
    close(fd);
    return 0;
}
