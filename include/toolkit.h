//
// Created by qy on 21/4/2022.
//

#ifndef POST_TOOLKIT_H
#define POST_TOOLKIT_H
#include<memory.h>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>

static inline void my_pread(int fd, void* buf, size_t count, off_t offset) {
    ssize_t res = pread(fd, buf, count, offset);
    if (res == (ssize_t)count)
        return;
    size_t got = 0;
    while (1) {
        if (res > 0) {
            got += res;
            if (got >= count)
                return;
        }
        else if (res == 0) {
            // EOF; zero out the rest
            memset(buf + got, 0, count - got);
            return;
        }
        else {
            perror("pread in my_pread");
            exit(10);
        }
        res = pread(fd, buf + got, count - got, offset + got);
    };
}

static inline void my_pwrite(int fd, const void * buf, size_t count, off_t offset) {
    ssize_t res = pwrite(fd, buf, count, offset);
    if (res == (ssize_t)count)
        return;
    size_t gave = 0;
    while (1) {
        if (res > 0) {
            gave += res;
            if (gave >= count)
                return;
        }
        else if (res == 0) {
            // strange
            fprintf(stderr, "ERROR: pwrite couldn't write any more bytes\n");
            exit(10);
        }
        else {
            perror("pwrite in my_pwrite");
            exit(10);
        }
        res = pwrite(fd, buf + gave, count - gave, offset + gave);
    };
}

#endif //POST_TOOLKIT_H
