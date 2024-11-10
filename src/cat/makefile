CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

default: all

all: s21_cat

s21_cat: clean
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

clean:
	- rm s21_cat

format: 
	clang-format -i --style=Google s21_cat.c

style:
	clang-format -n --style=Google s21_cat.c	


test:
	./testing/start.sh