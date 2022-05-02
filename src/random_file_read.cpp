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

void usage(const char* arg0){
    fprintf(stderr, "usage: %s [OPTIONS] <filePath> <fileSize>\n"
                    "-h --help show this help menu\n"
            ,arg0);
}

int main(int argc, char* argv[]){

    struct option longOpts[] = {
            {"help", no_argument, NULL, 'h'},
            {NULL, 0, NULL, 0}
    };

    while(true) {
        switch(getopt_long(argc, argv, "h", longOpts, NULL)) {
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

    if(optind != argc - 2){
        usage(argv[0]);
        exit(1);
    }

    int fd;
    const char* filePath = argv[optind];
    if((fd = open(filePath, O_RDONLY) < 0)){
        fprintf(stderr, "cannot open the file %s\n", filePath);
        return 2;
    }

    uint64_t fileSize;
    {
        const char* conv_str = argv[optind+1];
        char* end;
        fileSize = strtoul(argv[optind+1], &end, 10);
        if(end == conv_str || !(*end == '\0' || *(end+1) == '\0')){
            fprintf(stderr, "invalid size specification '%s'n", conv_str);
            return 2;
        }
        switch(*end){
            case '\0': break;
            case 'k': case 'K': fileSize *= 1024ul;
            case 'm': case 'M': fileSize *= 1048576ul;
            case 'g': case 'G': fileSize *= 1073741824ul;
            case 't': case 'T': fileSize *= 1099511627776ul;
            default: fprintf(stderr, "invalid size specification '%s'\n", conv_str); return 2;
        }
    }

    uint64_t num_chunks = 1 + (fileSize - 1) / BYTES_UNDER_P;
    uint64_t n = ceil(sqrt((double)num_chunks) / CHUNK_ALIGN) * CHUNK_ALIGN;
    uint64_t m = 1 + (num_chunks - 1) / n;

    uint64_t bytes_per_row = BYTES_UNDER_P * n;

    uint64_t *raw_row = (uint64_t *) malloc(bytes_per_row);
    assert(raw_row);

    for (size_t i = 0; i < m; i++){
        my_pread(fd, raw_row, bytes_per_row, bytes_per_row * i);
    }

    free(raw_row);
    close(fd);
}
