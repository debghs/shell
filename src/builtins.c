#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "../include/builtins.h"

// ANSI color codes for output
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_DEFAULT "\x1b[39m"

// Built-in command functions
int shell_cd(char **args) {
    if (args[1] == NULL) {
        // No argument provided; change to home directory
        char *home_dir = getenv("HOME");
        if (home_dir == NULL) {
            fprintf(stderr, "shell: HOME environment variable not set\n");
        } else {
            if (chdir(home_dir) != 0) {
                perror("shell");
            }
        }
    } else {
        // Change to the specified directory
        if (chdir(args[1]) != 0) {
            perror("shell");
        }
    }
    return 1;
}

int shell_help(char **args) {
    printf("Simple Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built-in commands:\n");

    for (int i = 0; i < shell_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int shell_exit(char **args) {
    return 0;
}

int shell_ls(char **args) {
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        perror("shell");
        return 1;
    }

    while ((de = readdir(dr)) != NULL) {
        struct stat st;
        stat(de->d_name, &st);

        if (S_ISDIR(st.st_mode)) {
            printf(COLOR_BLUE "%s" COLOR_RESET "\n", de->d_name);
        } else {
            printf(COLOR_DEFAULT "%s" COLOR_RESET "\n", de->d_name);
        }
    }

    closedir(dr);
    return 1;
}

// Array of built-in command strings
char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "ls" // Add more built-in commands here
};

// Array of function pointers to built-in commands
int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &shell_ls  // Add more function pointers here
};

// Return the number of built-in commands
int shell_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

