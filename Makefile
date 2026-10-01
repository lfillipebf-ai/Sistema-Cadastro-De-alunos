CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c
OUT = sistema-cadastro

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT) data/alunos.dat

run: all
	./$(OUT)
