#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(2, "Usage: %s [-c] <input_file>\n", argv[0]);
        exit();
    }

    int count_mode = 0;
    char *input_file = NULL;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            count_mode = 1;
        } else {
            input_file = argv[i];
        }
    }

    if (input_file == NULL) {
        printf(2, "Error: Input file not provided.\n");
        exit();
    }

    int fd = open(input_file, 0);

    if (fd < 0) {
        printf(2, "Error: Cannot open file %s\n", input_file);
        exit();
    }

    char prev_line[MAX_LINE_LENGTH] = "";
    char current_line[MAX_LINE_LENGTH] = "";
    int bytesRead;
    int line_count = 1; // Initialize line count to 1

    printf(1, "Uniq command is getting executed in kernel mode.\n");

    int prevLinePrinted = 0;
    char current_char;

    while (read(fd, &current_char, 1) == 1) {
        // Check for newline character
        if (current_char == '\n') {
            current_line[strlen(current_line)] = '\0';

            // Check if the current line is different from the previous line
            if (strcmp(current_line, prev_line) != 0) {
                if (count_mode) {
                    printf(1, "%d %s\n", line_count, current_line);
                } else {
                    printf(1, "%s\n", current_line);
                }
                strcpy(prev_line, current_line);
            } else if (count_mode) {
                line_count++;
            }

            memset(current_line, 0, sizeof(current_line));
        } else {
            current_line[strlen(current_line)] = current_char;
        }
    }

    // Print the last line if it wasn't printed yet
    if (!prevLinePrinted) {
        if (count_mode) {
            printf(1, "%d %s\n", line_count, current_line);
        } else {
            printf(1, "%s\n", current_line);
        }
    }

    close(fd);
    exit();
}

