#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *fp;

/* Check if keyword */
int isKeyword(char buffer[]) {
    char keywords[10][10] = {
        "int", "float", "if", "else", "while",
        "return", "for", "char", "double", "void"
    };

    for (int i = 0; i < 10; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[50];
    int i = 0;

    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {

        /* Skip whitespace */
        if (isspace(ch))
            continue;

        /* Identifier or keyword */
        if (isalpha(ch)) {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            fseek(fp, -1, SEEK_CUR);

            if (isKeyword(buffer))
                printf("KEYWORD : %s\n", buffer);
            else
                printf("IDENTIFIER : %s\n", buffer);
        }

        /* Number */
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            fseek(fp, -1, SEEK_CUR);

            printf("NUMBER : %s\n", buffer);
        }

        /* Operators */
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' || ch == '>') {

            printf("OPERATOR : %c\n", ch);
        }

        /* Separators */
        else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}') {

            printf("SEPARATOR : %c\n", ch);
        }

        /* Comments */
        else if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n');
                printf("SINGLE LINE COMMENT\n");
            } else {
                fseek(fp, -1, SEEK_CUR);
                printf("OPERATOR : /\n");
            }
        }

        /* Unknown symbol */
        else {
            printf("UNKNOWN SYMBOL : %c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
