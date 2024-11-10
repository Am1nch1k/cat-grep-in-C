#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char number_non_blank = 1;
const char end_of_line = 2;
const char line_numbering = 4;
const char squeeze_blank = 8;
const char show_tabs = 16;
const char show_non_print = 32;

char parse_args(int argc, char *argv[], int *arg_i) {
  char result = 0;
  for (*arg_i = 1; *arg_i < argc; (*arg_i)++) {
    if (argv[*arg_i][0] == '-') {
      if (strcmp(argv[*arg_i], "-b") == 0) result |= number_non_blank;
      if (strcmp(argv[*arg_i], "-n") == 0) result |= line_numbering;
      if (strcmp(argv[*arg_i], "-s") == 0) result |= squeeze_blank;
      if (strcmp(argv[*arg_i], "-T") == 0) result |= show_tabs;
      if (strcmp(argv[*arg_i], "-E") == 0) result |= end_of_line;
      if (strcmp(argv[*arg_i], "-v") == 0) result |= show_non_print;
      if (strcmp(argv[*arg_i], "-e") == 0)
        result |= show_non_print | end_of_line;
      if (strcmp(argv[*arg_i], "-t") == 0) result |= show_non_print | show_tabs;
      if (strcmp(argv[*arg_i], "--number-nonblank") == 0)
        result |= number_non_blank;
      if (strcmp(argv[*arg_i], "--number") == 0) result |= line_numbering;
      if (strcmp(argv[*arg_i], "--squeeze-blank") == 0) result |= squeeze_blank;
    } else
      break;
  }
  return result;
}

void nonprinting(unsigned char current) {
  if (current >= 32) {
    if (current < 127)
      putchar(current);
    else if (current == 127)
      printf("^?");
    else {
      printf("M-");
      if (current >= 128 + 32) {
        if (current < 128 + 127)
          putchar(current - 128);
        else
          printf("^?");
      } else
        printf("^%c", current - 128 + 64);
    }
  } else
    printf("^%c", current + 64);
}

void char_process(char proc, char flags) {
  if (proc == '\n') {
    if (flags & end_of_line) putchar('$');
    putchar('\n');
    return;
  }
  if (proc == '\t') {
    if (flags & show_tabs)
      printf("^I");
    else
      putchar('\t');
    return;
  }
  if (flags & show_non_print)
    nonprinting((unsigned char)proc);
  else
    putchar(proc);
}

int main(int argc, char *argv[]) {
  int arg_num = 1;

  int line_a = 1;  // number string
  unsigned char blank_lines = 0;
  char flags = parse_args(argc, argv, &arg_num);
  for (; arg_num < argc; arg_num++) {
    char buffer[4096];
    FILE *fp = fopen(argv[arg_num], "r");
    while (fgets(buffer, 4096, fp)) {
      int is_blank_line = 0;
      if (strlen(buffer) <= 1) is_blank_line = 1;
      if (is_blank_line)
        blank_lines++;
      else
        blank_lines = 0;
      if (flags & squeeze_blank)
        if (blank_lines > 1 && is_blank_line) continue;
      if ((flags & line_numbering) || (flags & number_non_blank)) {
        if (is_blank_line && (flags & number_non_blank))
          line_a--;
        else
          printf("%6d\t", line_a);
      }
      for (size_t i = 0; i < strlen(buffer); i++) {
        char_process(buffer[i], flags);
      }
      line_a++;
    }
    fclose(fp);
  }
  return 0;
}
