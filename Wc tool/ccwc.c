#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Function to count bytes in the file
long count_bytes(FILE *file) {
    fseek(file, 0, SEEK_END);
    long bytes = ftell(file);
    rewind(file);
    return bytes;
}

// Function to count lines in the file
long count_lines(FILE *file) {
    long lines = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(file);
    return lines;
}

// Function to count words in the file
long count_words(FILE *file) {
    long words = 0;
    int in_word = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    rewind(file);
    return words;
}

// Function to count characters in the file
long count_chars(FILE *file) {
    setlocale(LC_ALL, "");
    long chars = 0;
    while (fgetc(file) != EOF) {
        chars++;
    }
    rewind(file);
    return chars;
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    int count_c = 0, count_l = 0, count_w = 0, count_m = 0;
    int no_option = 1;

    // Parse command-line arguments
    if (argc > 1 && argv[1][0] == '-') {
        no_option = 0;
        for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
            if (strchr(argv[i], 'c')) count_c = 1;
            if (strchr(argv[i], 'l')) count_l = 1;
            if (strchr(argv[i], 'w')) count_w = 1;
            if (strchr(argv[i], 'm')) count_m = 1;
        }
    }

    // Handle standard input or file
    if (argc == 1 || (argc == 2 && argv[1][0] == '-')) {
        file = stdin;
    } else {
        file = fopen(argv[argc - 1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
    }

    // Perform counts based on options
    if (count_c || no_option) printf("  %ld", count_bytes(file));
    if (count_l || no_option) printf("  %ld", count_lines(file));
    if (count_w || no_option) printf("  %ld", count_words(file));
    if (count_m) printf("  %ld", count_chars(file));

    if (file != stdin) printf(" %s\n", argv[argc - 1]);
    else printf("\n");

    if (file != stdin) fclose(file);

    return 0;
}
