#include "../include/Lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

lexer_T *init_lexer(char *contents) {
        lexer_T *lexer = calloc(1, sizeof(struct LEXER_STRUCT));

        lexer->contents = contents;
        lexer->i = 0;
        lexer->c = contents[lexer->i];

        return lexer;
}

void lexer_advance(lexer_T *lexer) {
        if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
                ++lexer->i;
                lexer->c = lexer->contents[lexer->i];
        }
}

char lexer_peek(lexer_T *lexer, int offset) {
        return lexer->contents[lexer->i + offset];
}

void lexer_skip_whitespace(lexer_T *lexer) {
        while (lexer->c == ' ' || lexer->c == '\n') {
                lexer_advance(lexer);
        }
}

void lexer_skip_comment(lexer_T *lexer) {
        if (lexer->c == '#') {
                while (lexer->c != '\n')
                        lexer_advance(lexer);
        }
        else if (lexer->c == '/' && lexer_peek(lexer, 1) == '*') {
                while (1) {
                        if (lexer->c == '*' && lexer_peek(lexer, 1) == '/') {
                                lexer_advance(lexer);
                                lexer_advance(lexer);
                                break;
                        }
                        lexer_advance(lexer);
                }
        }
}

#define isValidCharacter(c) (isalnum(c) || c == '_')

token_T *lexer_get_next_token(lexer_T *lexer) {
        while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
                lexer_skip_whitespace(lexer);
                lexer_skip_comment(lexer);

                if (isdigit(lexer->c))
                        return lexer_collect_number(lexer);

                if (isValidCharacter(lexer->c))
                        return lexer_collect_id(lexer);

                if (lexer->c == '"')
                        return lexer_collect_string(lexer);

                switch (lexer->c) {
                        case '=': return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)));
                        case ';': return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
                        case '(': return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)));
                        case ')': return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer)));
                        case ',': return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer)));
                }
        }

        return init_token(TOKEN_EOF, "\0");
}

token_T *lexer_collect_string(lexer_T* lexer) {
        lexer_advance(lexer);

        char *value = calloc(1, sizeof(char));
        value[0] = '\0';

        while (lexer->c != '"') {
                char *s = lexer_get_current_char_as_string(lexer);
                value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
                strcat(value, s);

                lexer_advance(lexer);
        }

        lexer_advance(lexer);

        return init_token(TOKEN_STRING, value);
}

token_T* lexer_collect_number(lexer_T* lexer) {
        char *value = calloc(1, sizeof(char));
        value[0] = '\0';

        while (isdigit(lexer->c)) {
                char *s = lexer_get_current_char_as_string(lexer);
                value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
                strcat(value, s);

                lexer_advance(lexer);
        }

        return init_token(TOKEN_INT, value);
}

token_T *lexer_collect_id(lexer_T* lexer) {
        char *value = calloc(1, sizeof(char));
        value[0] = '\0';

        while (isValidCharacter(lexer->c)) {
                char *s = lexer_get_current_char_as_string(lexer);
                value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
                strcat(value, s);

                lexer_advance(lexer);
        }

        return init_token(TOKEN_ID, value);
}

token_T *lexer_advance_with_token(lexer_T *lexer, token_T *token) {
        lexer_advance(lexer);

        return token;
}

char *lexer_get_current_char_as_string(lexer_T *lexer) {
        char *str = calloc(2, sizeof(char));

        str[0] = lexer->c;
        str[1] = '\0';

        return str;
}
