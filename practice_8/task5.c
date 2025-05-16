#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024    
#define MAX_ARGS 64      
#define MAX_PIPES 10    

typedef struct {
    char *args[MAX_ARGS];
    int argc;
} Command;


int parse_command_line(char *line, Command *commands, int *num_commands) {
    char *token;
    *num_commands = 0;
    int arg_count = 0;


    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }


    token = strtok(line, " ");
    while (token != NULL) {
        if (strcmp(token, "|") == 0) {
            commands[*num_commands].args[arg_count] = NULL;
            commands[*num_commands].argc = arg_count;
            (*num_commands)++;
            arg_count = 0;
        } else {
            commands[*num_commands].args[arg_count++] = token;
        }
        token = strtok(NULL, " ");
    }

    commands[*num_commands].args[arg_count] = NULL;
    commands[*num_commands].argc = arg_count;
    (*num_commands)++;

    return 0;
}

int execute_commands(Command *commands, int num_commands) {
    int pipes[MAX_PIPES][2];
    pid_t pids[MAX_PIPES + 1];
    int i;

    for (i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < num_commands; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {

            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }

            if (i < num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            if (execvp(commands[i].args[0], commands[i].args) < 0) {
                fprintf(stderr, "Error: command '%s' not found\n", commands[i].args[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    for (i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}

int main() {
    char line[MAX_LINE];
    Command commands[MAX_PIPES + 1];
    int num_commands;

    printf("Type 'exit' to exit comm mode.\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL) {
            break;
        }

        if (strcmp(line, "exit\n") == 0) {
            break;
        }

        parse_command_line(line, commands, &num_commands);

        if (num_commands == 1 && commands[0].argc == 0) {
            continue;
        }

        execute_commands(commands, num_commands);
    }

    printf("It is so over\n");
    return 0;
}
