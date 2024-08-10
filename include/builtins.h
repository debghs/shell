//this header file will contain declarations for built-in command funcs.
#ifndef BUILTINS_H
#define BUILTINS_H

int shell_ls(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
int shell_num_builtins(void);

#endif
