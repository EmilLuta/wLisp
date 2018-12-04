#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

int main(int argc, char** argv) {
    puts("wLisp v0.0.0.1");

    while (1) {
        char* input = readline("> ");
        add_history(input);

        printf("Nope, %s\n", input);

        free(input);
    }

    return 0;
}
