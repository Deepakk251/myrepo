#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || 
            c == '<' || c == '>' || c == '!' || c == '&' || c == '|' || c == '^');
}

int main() {
    FILE *file = fopen("input.c", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int tokenCount = 0;
    char c;
    int inComment = 0;

    while ((c = fgetc(file)) != EOF) {
        // Handle single-line comments
        if (c == '/' && !inComment) {
            char next = fgetc(file);
            if (next == '/') {
                while ((c = fgetc(file)) != '\n' && c != EOF);
                continue;
            } else if (next == '*') {
                inComment = 1;
                continue;
            } else if (next != EOF) {
                ungetc(next, file);
            }
        }

        // Handle multi-line comments
        if (inComment) {
            if (c == '*') {
                char next = fgetc(file);
                if (next == '/') {
                    inComment = 0;
                }
                continue;
            }
            continue;
        }

        // Count tokens
        if (isalnum(c) || c == '_') {
            tokenCount++;
            while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_'));
            ungetc(c, file);
        } else if (isOperator(c) || c == '(' || c == ')' || c == '{' || c == '}' || 
                   c == '[' || c == ']' || c == ';' || c == ',' || c == '.') {
            tokenCount++;
        }
    }

    fclose(file);
    printf("Total tokens: %d\n", tokenCount);
    return 0;
}