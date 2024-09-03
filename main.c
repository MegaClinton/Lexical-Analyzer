#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
char operators[] = {'+', '-', '*', '/', '%', '='};
char punctuation[] = {',', ';', '(', ')', '{', '}', '[', ']'};



int is_keyword(char *str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
void identify_token(FILE *file, char ch) {
    char buffer[256];
    int i = 0;

    // Check if the character is a letter
    if (isalpha(ch))
    {
        buffer[i++] = ch;
        while (isalnum(ch = fgetc(file)))
        {  // Continue while alphanumeric
            buffer[i++] = ch;
        }
        buffer[i] = '\0';  // Null-terminate the string

        // Unget the last character read that is not part of the identifier/keyword
        ungetc(ch, file);

        if (is_keyword(buffer))
        {
            printf("(%s, Keyword)\n", buffer);
        } else {
            printf("(%s, Identifier)\n", buffer);
        }
    }
        // Check if the character is a digit
    else if (isdigit(ch)) {
        buffer[i++] = ch;
        while (isdigit(ch = fgetc(file))) {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';

        // Unget the last character read that is not part of the integer
        ungetc(ch, file);

        printf("(%s, Integer)\n", buffer);
    }
        // Check if the character is an operator
    else if (strchr(operators, ch) != NULL) {
        printf("(%c, Operator)\n", ch);
    }
        // Check if the character is a punctuation mark
    else if (strchr(punctuation, ch) != NULL) {
        printf("(%c, Punctuation)\n", ch);
    }
    else if (isspace(ch)) {
        // Skip whitespace
    } else {
        printf("(%c, Unknown)\n", ch);  // For any unrecognized characters
    }
}

int main() {
    FILE *file = fopen("test1.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) //read each char from file
    {
        identify_token(file, ch);
    }

    fclose(file);
    return 0;
}

