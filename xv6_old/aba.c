#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_LINE_LENGTH 1024

// Function to filter and print unique lines from a file
void filterUniqueLines(int fd) {
    char prev_line[MAX_LINE_LENGTH] = "";
    char current_line[MAX_LINE_LENGTH];
    char current_char;
    int prevLinePrinted = 0;

    while (read(fd, &current_char, 1) == 1) {
        // Check for newline character
        if (current_char == '\n') {
            current_line[strlen(current_line)] = '\0';

            // Check if the current line is different from the previous line
            if (strcmp(current_line, prev_line) != 0) {
                printf(1, "%s\n", current_line);
                strcpy(prev_line, current_line);
            }

            memset(current_line, 0, sizeof(current_line));
        } else {
            current_line[strlen(current_line)] = current_char;
        }
    }

    // Print the last line if it wasn't printed yet
    if (!prevLinePrinted) {
        printf(1, "%s", current_line);
    }
    prevLinePrinted = 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(2, "Usage: %s <input_file>\n", argv[0]);
        exit();
    }

    char *input_file = argv[1];
    int fd = open(input_file, 0);

    if (fd < 0) {
        printf(2, "Error: Cannot open file %s\n", input_file);
        exit();
    }

    printf(1, "Uniq command is getting executed in kernel mode.\n");

    // Call the function to filter and print unique lines
    filterUniqueLines(fd);

    close(fd);
    exit();
}

