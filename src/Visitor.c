#include "../include/Visitor.h"
#include "../include/Builtins.h"

#include <stdio.h>
#include <string.h>

visitor_T* init_visitor() {
        visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
        visitor->variable_definitions = (void*)0;
        visitor->variable_definitions_size = 0;
        return visitor;
}

AST_T* visitor_visit(visitor_T* visitor, AST_T* node) {
        switch (node->type) {
                case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node);
                case AST_VARIABLE: return visitor_visit_variable(visitor, node);
                case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node);
                case AST_STRING: return visitor_visit_string(visitor, node);
                case AST_INT: return visitor_visit_int(visitor, node);
                case AST_COMPOUND: return visitor_visit_compound(visitor, node);
                case AST_NOOP: return node;
        }

        printf("[Compilation Error]: \033[1;32mUncaught statement of type '%d'\033[0m \n", node->type);
        exit(1);

        return init_ast(AST_NOOP);
}

AST_T* visitor_visit_variable_definition(visitor_T* visitor, AST_T* node) {
        ++visitor->variable_definitions_size;
        if (visitor->variable_definitions == (void*)0) {
                visitor->variable_definitions = calloc(1, sizeof(struct AST_STRUCT*));
                visitor->variable_definitions[0] = node;
        } else {
                visitor->variable_definitions = realloc(
                        visitor->variable_definitions,
                        visitor->variable_definitions_size * sizeof(struct AST_STRUCT*)
                );
                visitor->variable_definitions[visitor->variable_definitions_size - 1] = node;
        }

        return node;
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node) {
        for (int i = 0; i < visitor->variable_definitions_size; ++i) {
                AST_T* vardef = visitor->variable_definitions[i];

                if(strcmp(vardef->variable_definition_variable_name, node->variable_name) == 0)
                        return visitor_visit(visitor, vardef->variable_definition_value);
        }

        printf("[Compilation Error]: \033[1;32mUndefined variable '%s'\033[0m\n", node->variable_name);
        exit(1);
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node) {
        if (strcmp(node->function_call_name, "LK14") == 0)
                return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size, 0);
        if (strcmp(node->function_call_name, "LK14ln") == 0)
                return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size, 1);
        if (strcmp(node->function_call_name, "LK14_min") == 0)
                return builtin_function_max_min(visitor, node->function_call_arguments, node->function_call_arguments_size, 1);
        if (strcmp(node->function_call_name, "LK14_max") == 0)
                return builtin_function_max_min(visitor, node->function_call_arguments, node->function_call_arguments_size, 0);
        if (strcmp(node->function_call_name, "LK14_STUDENTS") == 0)
                return builtin_function_STUDENTS(visitor);

        printf("[Compilation Error]: \033[1;32mUndefined method '%s'\033[0m\n", node->function_call_name);
        exit(1);
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node) {
        return node;
}

AST_T* visitor_visit_int(visitor_T* visitor, AST_T* node) {
        return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node) {
        for (int i = 0; i < node->compound_size; ++i)
                visitor_visit(visitor, node->compound_value[i]);

        return init_ast(AST_NOOP);
}
