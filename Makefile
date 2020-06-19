CC=gcc
CFLAGS=-I.
DEPS = SLL.h CommandHandler.h
OBJ = SLL.o CommandHandler.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

StudentQueue: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)