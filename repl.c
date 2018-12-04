#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

void add_history(char* unused);

#elif __APPLE__

#include <editline/readline.h>

#else

#include <editline/readline.h>
#include <editline/history.h>

#endif

int main(int argc, char** argv) {
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expression = mpc_new("expression");
    mpc_parser_t* wLisp = mpc_new("wLisp");

    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                               \
            number : /-?[0-9]+/ ;                                       \
            operator : '+' | '-' | '*' | '/' ;                          \
            expression : <number> | '(' <operator> <expression>+ ')';   \
            wLisp : /^/ <operator> <expression>+ /$/ ;                  \
        ",
        Number, Operator, Expression, wLisp);
    puts("wLisp v0.0.0.1");

    while (1) {
        char* input = readline("> ");
        add_history(input);
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, wLisp, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        /* printf("Nope, %s\n", input); */

        free(input);
    }

    mpc_cleanup(4, Number, Operator, Expression, wLisp);
    return 0;
}
