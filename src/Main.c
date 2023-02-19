#include "../include/Lexer.h"
#include "../include/Parser.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {
        lexer_T *lexer = init_lexer(
		"var name = \"Banana\";\n"
                "print(name);"
	);

        parser_T* parser = init_parser(lexer);
        AST_T* root = parser_parse(parser);
        
        return 0;
}
