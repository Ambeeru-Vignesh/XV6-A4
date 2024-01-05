#include "types.h"
#include "stat.h"
#include "user.h"

#define DEFAULT_LINES 14

void head(int fd, int lines) {
    char buf[512];
    int n, count = 0;

    while ((n = read(fd, buf, sizeof(buf))) > 0 && count < lines) {
        for (int i = 0; i < n && count < lines; i++) {
            if (write(1, &buf[i], 1) != 1) {
                printf(2, "head: write error\n");
                exit();
            }
            if (buf[i] == '\n')
                count++;
        }
    }
}

int main(int argc, char *argv[]) {
    int fd;
    int lines = DEFAULT_LINES;

    if (argc > 1 && strcmp(argv[1], "-n") == 0 && argc > 2) {
        // Handle the case where the first argument is "-n"
        lines = atoi(argv[2]);
        argc -= 2;
        argv += 2;
    }

    if (argc <= 1) {
        // No filename provided, read from standard input
        head(0, lines);
    } else {
        for (int i = 1; i < argc; i++) {
            if ((fd = open(argv[i], 0)) < 0) {
                printf(2, "head: cannot open %s\n", argv[i]);
                exit();
            }
            if (argc > 2)
                printf(1, "==> %s <==\n", argv[i]);
            head(fd, lines);
            close(fd);
        }
    }

    exit();
}

