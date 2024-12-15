#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void show_prompt(void) {
    printf("$ ");
}

void get_command(char* program, char **args) {

    // input e.j.: /usr/bin/ping ping -c 1 8.8.8.8

    char command[100];
    char* token;
    int c, i;

    i = 0;

    while ((c = getchar()) != '\n') {
        command[i] = c;
        ++i;
    }

    token = strtok(command, " ");

    strcpy(program, token);

    i = 0;

    while (1) {
        token = strtok(NULL, " ");

        if (token == NULL) {
            args[i] = token;
            break;
        } else {
            args[i] = (char*)malloc(100);
            strcpy(args[i], token);
            ++i;
        }
    }
}

int main(void) {

    char programName[100];
    char* programArgs[10];
    int status;

    show_prompt();
    get_command(programName, programArgs);
    
    if (fork() != 0) {
        waitpid(-1, &status, 0);
    } else {
        execve(programName, programArgs, NULL);
    }

    return 0;
}