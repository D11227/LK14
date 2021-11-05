#include "../include/Lexer.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {
        lexer_T *lexer = init_lexer(
                "var hello =\"Hello World\";\n"
                "print(hello);\n"
        );

        token_T *token = (void*)0;

        while ((token = lexer_get_next_token(lexer)) != (void*)0) {
                printf("TOKEN(%d, %s)\n", token->type, token->value);
        }
        return 0;
}
