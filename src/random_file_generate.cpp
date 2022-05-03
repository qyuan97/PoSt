#include<stdint.h>
#include<fcntl.h>
#include<sys/random.h>
#include<getopt.h>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<assert.h>
#include<tinymt64.h>
#include<omp.h>
#include<toolkit.h>

#define ROW_SIZE_BYTES (4194304) // 4MB

void usage(const char* arg0) {
    fprintf(stderr, "usage: %s [OPTIONS] <output_datafile> <size>\n"
                                  "\t -s --seed<number> \t specify random seed\n"
                                  "\t -h --help \t show the help menu\n"
                                  "<size> should be a positive integer, followed optionally by one of:\n"
                                  "K:KB(2^10 bytes)\nM:MB(2^20 bytes)\nG:GB(2^30 bytes)\nT:TB(2^40 bytes)\n"
                                  , arg0);
}

int main(int argc, char* argv[]) {
    int datafd;
    uint64_t nbytes;

    int seeded = 0;
    uint64_t seed;

    struct option longopts[] = {
            {"seed", required_argument, NULL, 's'},
            {"help", no_argument, NULL, 'h'},
            {NULL, 0, NULL, 0}
    };

    while (true) {
        switch (getopt_long(argc, argv, "s:h", longopts, NULL)){
            case -1:
                goto done_opts;
            case 's':
                seed = strtoul(optarg, NULL, 10);
                seeded = 1;
                break;
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

    const char* fname = argv[optind];
    if ((datafd = open(fname, O_WRONLY|O_CREAT, 0644)) < 0) {
        perror("count not open output file.");
        return 2;
    }

    {
        const char* conv_str = argv[optind+1];
        char* end;
        nbytes = strtoul(argv[optind+1], &end, 10);
        printf("argv[0]: %s\nargv[1]: %s\nargv[2]: %c\n", fname, conv_str, *end);
        if (end == conv_str || !(*end == '\0' || *(end+1) == '\0')) {
            fprintf(stderr, "invalid size specification '%s'n", conv_str);
            return 2;
        }
        switch (*end) {
            case '\0': break;
            case 'k': case 'K': nbytes *= 1024ul; break;
            case 'm': case 'M': nbytes *= 1048576ul; break;
            case 'g': case 'G': nbytes *= 1073741824ul; break;
            case 't': case 'T': nbytes *= 1099511627776ul; break;
            default: fprintf(stderr, "invalid size specification '%s'\n", conv_str); return 2;
        }
    }

    fprintf(stderr, "setting file length with ftruncate...");
    if (ftruncate(datafd, nbytes)) {
        perror("could not set file length as specified");
        return 2;
    }
    fprintf(stderr, "done\n");

    if (!seeded) {
        if (getentropy(&seed, sizeof seed) == -1) {
			fprintf(stderr, "getentropy failed\n");
			exit(6);
		}
        if (getrandom(&seed, sizeof seed, 0) != sizeof(seed)) {
            fprintf(stderr, "getrandom failed\n");
            exit(7);
        }
    }

    uint64_t n_rows = 1 + (nbytes - 1) / ROW_SIZE_BYTES;
    const static uint64_t ROW_SIZE_64 = ROW_SIZE_BYTES / 8;

    printf("n_rows: %d\nROW_SIZE_64:%lu\n", n_rows, ROW_SIZE_64);

    #pragma omp parallel
    {
        fprintf(stderr, "thread %d starting parallel writes\n", omp_get_thread_num());
        uint64_t *raw_row = (uint64_t *)malloc(ROW_SIZE_BYTES);
        assert (raw_row);
        #pragma omp for nowait
        for (uint64_t i = 0; i < n_rows; ++i) {
            tinymt64_t state = {0};
            tinymt64_init(&state, seed + i);

            for (size_t j = 0; j < ROW_SIZE_64; ++j) {
                raw_row[j] = tinymt64_generate_uint64(&state);
                if(j == 1){
                    printf("current block: %lu\n", raw_row[j]);
                }
            }

            uint64_t offset = i * ROW_SIZE_BYTES;
            if (i == n_rows - 1) {
                my_pwrite(datafd, raw_row, nbytes - offset, offset);
            }
            else {
                my_pwrite(datafd, raw_row, ROW_SIZE_BYTES, offset);
            }
        }

        fprintf(stderr, "thread %d finished\n", omp_get_thread_num());
    }

    close(datafd);

    printf("successfully wrote %lu bytes to %s\n", nbytes, fname);

    return 0;
}
