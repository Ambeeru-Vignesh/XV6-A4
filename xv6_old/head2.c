// head.c
#include "types.h"
#include "stat.h"
#include "user.h"

#define DL 14

void h(int fd, int l) {
    char b[512];
    int n, c = 0;

    while ((n = read(fd, b, sizeof(b))) > 0 && c < l) {
        for (int i = 0; i < n && c < l; i++) {
            if (write(1, &b[i], 1) != 1) {
                printf(2, "he: w error\n");
                exit();
            }
            if (b[i] == '\n')
                c++;
        }
    }
}

int main(int a, char *v[]) {
    int fd;
    int l = DL;

    if (a > 1 && v[1][0] == '-') {
        l = atoi(&v[1][1]);
        a--;
        v++;
    }

    if (a <= 1) {
        h(0, l);
    } else {
        for (int i = 1; i < a; i++) {
            if ((fd = open(v[i], 0)) < 0) {
                printf(2, "he: c open %s\n", v[i]);
                exit();
            }
            if (a > 2)
                printf(1, "==> %s <==\n", v[i]);
            h(fd, l);
            close(fd);
        }
    }

    exit();
}

