CC = gcc
CFLAGS =-g -fsanitize=address -static-libasan
all: corruption
%.o : %.c
	$(CC) $(CFLAGS) -o $^
clean:
	rm -rf *.o corruption
