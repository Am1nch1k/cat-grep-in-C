CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

default: all

all: s21_grep 

s21_grep: clean
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

clean:
	- rm s21_grep

format: 
	clang-format -i --style=Google *.c

style:
	clang-format -n --style=Google *.c

test:
	./testing/start.sh