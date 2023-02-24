#include "../include/Builtins.h"

#include <stdio.h>

static const char* LK14_STUDENTS_LIST[34] = {
        "DANG NGOC LAN ANH", "NGUYEN TRAN NGOC ANH", "NGUYEN HONG ANH", "TRAN NGOC BAO CHAU",
        "CHAU NGUYEN THANH DUY", "PHAN MINH DAT", "TRAN QUOC DAT", "QUACH KHA DANG",
        "VO MINH HAO", "TRAN THI MY HANH", "TRAN VAN TRUNG HIEU", "HO HOANG HUY",
        "TRAN LE ANH HUY", "NGUYEN MAI HUYNH", "DANG THAI THIEN KHAI", "TRAN ANH KIET",
        "TRAN NGUYEN THAO LY", "LE HOANG NHUT NAM", "LUONG TRAN THANH NGAN", "DO XUAN NGOC",
        "NGUYEN MINH NGOC", "TRAN TUE NGOC", "NGUYEN THANH NHAN", "VO NGOC YEN NHI",
        "PHAN DUC PHU", "NGUYEN HOANG QUAN", "TRAN HOANG QUAN", "NGUYEN TAN TAI",
        "VO QUOC THINH", "PHAN TRAN ANH THU", "PHAN THI YEN TRANG", "TRAN TRONG TRI",
        "TONG DUC SANG TRONG", "PHAM NGUYEN HAI TRUC"
};

#define ERROR_COMPILE(condition, msg) \
        if (condition != 1) { \
                printf("\033[1;31m[Compilation Error]\033[0m: \033[1;32m%s\033[0m \n", msg); \
                exit(1); \
        }

AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size, int newline) {
        for (int i = 0; i < args_size; ++i) {
                AST_T* visited_ast = visitor_visit(visitor, args[i]);

                switch (visited_ast->type) {
                        case AST_STRING: printf("%s", visited_ast->string_value); break;
                        case AST_INT: printf("%ld", visited_ast->int_value); break;
                        default: printf("%p", visited_ast); break;
                }

                if (newline) printf("\n");
        }

        return init_ast(AST_NOOP);
}

AST_T* builtin_function_max_min(visitor_T* visitor, AST_T** args, int args_size, int min) {
        AST_T* visited_ast = visitor_visit(visitor, args[0]);
        ERROR_COMPILE(visited_ast->type == AST_INT, "Expected an argument in function is not a number");

        size_t result = visited_ast->int_value;
        for (int i = 1; i < args_size; ++i) {
                AST_T* visited_ast = visitor_visit(visitor, args[i]);
                ERROR_COMPILE(visited_ast->type == AST_INT, "Function is not supported STRING");
                if ((min && result > visited_ast->int_value) || (!min && result < visited_ast->int_value))
                        result = visited_ast->int_value;
        }

        AST_T* return_ast = init_ast(AST_INT);
        return_ast->int_value = result;

        return return_ast;
}

AST_T* builtin_function_STUDENTS(visitor_T* visitor) {
        for (int i = 0; i < 34; ++i) {
                printf("\033[1;3%dm%s\033[0m ", (i % 7), LK14_STUDENTS_LIST[i]);
                if ((i + 1) % 4 == 0) printf("\n");
        }
        printf("\n");
        return init_ast(AST_NOOP);
}
