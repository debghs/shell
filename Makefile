CC = gcc
CFLAGS = -Wall -g
DEPS = include/shell.h include/builtins.h
OBJ = src/main.o src/shell.o src/builtins.o src/execute.o src/parser.o src/utils.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o shell
