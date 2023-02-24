#ifndef BUILTINS_H
#define BUILTINS_H

#include "Visitor.h"

AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size, int newline);
AST_T* builtin_function_max_min(visitor_T* visitor, AST_T** args, int args_size, int min);
AST_T* builtin_function_STUDENTS(visitor_T* visitor);

#endif
