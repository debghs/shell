#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024
#define TOKEN_SIZE 64
#define TOKEN_DELIM " \t\r\n\a"

void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_execute(char **args);

#endif 
