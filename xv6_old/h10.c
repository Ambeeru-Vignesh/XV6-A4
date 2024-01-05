// head.c
#include "types.h"
#include "stat.h"
#include "user.h"
#include "stddef.h"

#define DEFAULT_LINES 14

void head(int fd, int lines) {
    char buf[1024];
    int n, count = 0;
if(fd!=0)
{
    while (count < lines && (n = read(fd, buf, sizeof(buf))) > 0) {
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
else
{
//	int n=0;
//	int line_count =0;
//	char lines[1000][1000];
/*	   while (line_count < 14) 
	   {
         n= read(0, lines[line_count],sizeof(lines[line_count]));
        line_count++;
        if(n==0)
                exit();
}*/
	/*

    while (line_count < 14)
    {
        memset(lines[line_count], 0, sizeof(lines[line_count]));
         n = read(0, lines[line_count], sizeof(lines[line_count])); // Read from stdin (file descriptor 0)

        if (n == 0)
            break; // EOF (Ctrl+D)

        line_count++;
    }
    printf(1, "You entered:\n");
    for (int i = 0; i < 14; i++) {
        printf(1, "%s\n", lines[i]);
    }

}
*/

	 char line[1024];
    int fd;

    printf(1,"Please enter a line of text:\n");

    memset(line, 0, sizeof(line));
    int n = read(0, line, sizeof(line)); // Read from stdin (file descriptor 0)

    if (n <= 0)
    {
        printf(1,"Error reading input.\n");
        exit();
    }

    fd = open("simeusoly", 0200); // Create or truncate the file
    if (fd < 0)
    {
        printf(1,"Error creating or opening the file.\n");
        exit();
    }

    // Write the line to the file
    head(fd,sizeof(line));
}
}

int main(int argc, char *argv[]) {
    int lines = DEFAULT_LINES;

    if (argc >= 2 && strcmp(argv[1], "-n") == 0 && argc > 2) {
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
            int fd;
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

