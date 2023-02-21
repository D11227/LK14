#include "../include/Lexer.h"
#include "../include/Parser.h"
#include "../include/Visitor.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {
        lexer_T *lexer = init_lexer(
                "LK name3 = \"huh?\";\n"
                "LK name2 = \"Banana\";\n"
                "LK14(name3, name2);"
	);

        parser_T* parser = init_parser(lexer);
        AST_T* root = parser_parse(parser);
        visitor_T* visitor = init_visitor();
        visitor_visit(visitor, root);

        return 0;
}
