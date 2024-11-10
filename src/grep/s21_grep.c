#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_list.c"

const unsigned char ignore_case = 1;      // i
const unsigned char invert_match = 2;     // v
const unsigned char count_matching = 4;   // c
const unsigned char matching_files = 8;   // l
const unsigned char number_line = 16;     // n
const unsigned char no_filename = 32;     // h
const unsigned char suppress_error = 64;  // s
const unsigned char matching_only = 128;  // o

int regex_check(regex_t regex_c, char* str, char invert) {
  if (invert)
    return regexec(&regex_c, str, 0, NULL, 0);
  else
    return !regexec(&regex_c, str, 0, NULL, 0);
}

char parse_i_arg(int argc, char* argv[]) {  // флаг i
  char result = 0;
  char next_pattern = 0;
  char next_file = 0;
  for (int arg_i = 1; arg_i < argc; arg_i++) {
    if (next_pattern) {
      next_pattern = 0;
      continue;
    }
    if (next_file) {
      next_file = 0;
      continue;
    }
    if (argv[arg_i][0] == '-') {
      for (size_t i = 1; i < strlen(argv[arg_i]); i++) {
        if (argv[arg_i][i] == 'i') result |= ignore_case;
        if (argv[arg_i][i] == 'e') next_pattern = 1;
        if (argv[arg_i][i] == 'f') next_file = 1;
      }
    } else
      break;
  }
  return result;
}

char parse_args(int argc, char* argv[], int* arg_i,
                struct array_list* patterns) {
  char result = parse_i_arg(argc, argv);
  char next_pattern = 0;
  char next_file = 0;
  for (; *arg_i < argc; (*arg_i)++) {  // фоаг е
    if (next_pattern) {
      array_list_add(patterns, argv[*arg_i],
                     (result & ignore_case) ? REG_ICASE : 0);
      next_pattern = 0;
      continue;
    }
    if (next_file) {
      FILE* fp = fopen(argv[*arg_i], "r");
      if (!fp) {
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[*arg_i]);
        next_file = 0;
        continue;  // flag f
      }
      char buff[4096];
      while (fgets(buff, 4096, fp)) {
        if (buff[strlen(buff) - 1] == '\n') buff[strlen(buff) - 1] = '\0';
        array_list_add(patterns, buff,
                       (result & ignore_case)
                           ? REG_ICASE
                           : 0);  // построчно считываем файл и добавляем каждую
                                  // строку как регулярку
      }
      fclose(fp);
      next_file = 0;
      continue;
    }
    if (argv[*arg_i][0] == '-') {
      for (size_t i = 1; i < strlen(argv[*arg_i]); i++) {
        if (argv[*arg_i][i] == 'v') result |= invert_match;
        if (argv[*arg_i][i] == 'c') result |= count_matching;
        if (argv[*arg_i][i] == 'l') result |= matching_files;
        if (argv[*arg_i][i] == 'n') result |= number_line;
        if (argv[*arg_i][i] == 'h') result |= no_filename;
        if (argv[*arg_i][i] == 's') result |= suppress_error;
        if (argv[*arg_i][i] == 'o') result |= matching_only;
        if (argv[*arg_i][i] == 'e')
          next_pattern = 1;  // для будущей иттерации цикла
        if (argv[*arg_i][i] == 'f') next_file = 1;
      }
    } else
      break;
  }
  return result;
}

int process_file(char* filename, int file_count, char flags,
                 struct array_list patterns) {
  FILE* fp = fopen(filename, "r");
  int match_lines = 0;
  int number_string = 1;
  if (!fp) return !(flags & suppress_error);
  char buff[4096];
  char exit_file_flag = 0;  // for exit flag -l
  while (fgets(buff, 4096, fp)) {
    if (buff[strlen(buff) - 1] == '\n') buff[strlen(buff) - 1] = '\0';
    for (int patterns_count = 0; patterns_count < patterns.length;
         patterns_count++) {
      if (regex_check(patterns.array[patterns_count], buff,
                      flags & invert_match)) {
        if (flags & matching_files) {
          if (flags & count_matching) match_lines++;
          exit_file_flag = 1;  // exit while loop
          break;
        }
        if (flags & count_matching) {
          match_lines++;
          break;
        }
        if ((file_count > 1) && !(flags & no_filename)) printf("%s:", filename);
        if (flags & number_line) printf("%d:", number_string);
        if (flags & matching_only) {
          regmatch_t match;
          regexec(&(patterns.array[patterns_count]), buff, 1, &match, 0);
          printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                 &buff[match.rm_so]);
        } else
          puts(buff);
        break;
      }
    }
    if (flags & matching_files)
      if (exit_file_flag) break;  // exit flag -l
    number_string++;
  }
  if (flags & count_matching) {
    if ((file_count > 1) && !(flags & no_filename)) printf("%s:", filename);
    printf("%d\n", match_lines);
  }
  if (exit_file_flag) printf("%s\n", filename);
  fclose(fp);
  return 0;
}

int main(int argc, char* argv[]) {
  struct array_list patterns = create_array_list();
  int arg_num = 1;
  char flags = parse_args(argc, argv, &arg_num, &patterns);
  if (patterns.length == 0) {
    char* pattern = argv[arg_num];
    array_list_add(&patterns, pattern, (flags & ignore_case) ? REG_ICASE : 0);
    arg_num++;
  }
  int file_count = argc - arg_num;
  for (; arg_num < argc; arg_num++) {
    if (process_file(argv[arg_num], file_count, flags, patterns))
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[arg_num]);
  }
  trash_array(&patterns);
  return 0;
}
