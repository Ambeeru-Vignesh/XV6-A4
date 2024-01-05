#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_LINE_LEN 256

// Custom string comparison function
int strcmpr(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(2, "Usage: %s <filename>\n", argv[0]);
        exit();
    }

    char *filename = argv[1];
    int fd = open(filename, 0);
    if (fd < 0) {
        printf(2, "Error: Cannot open %s\n", filename);
        exit();
    }

    char prevLine[MAX_LINE_LEN] = "";
    char currLine[MAX_LINE_LEN] = "";
    int bytesRead;
    int isPrevLineDuplicate = 0;

    while ((bytesRead = read(fd, currLine, sizeof(currLine))) > 0) {
        if (strcmpr(currLine, prevLine) == 0) {
            isPrevLineDuplicate = 1;
        } else {
            if (!isPrevLineDuplicate) {
                printf(2, "%s", prevLine); // Print the line if it's not a duplicate
            }
            strcpy(prevLine, currLine);
            isPrevLineDuplicate = 0;
        }
    }

    // Print the last line if it's not a duplicate
    if (!isPrevLineDuplicate) {
        printf(1, "%s", prevLine);
    }

    close(fd);
    exit();
}

