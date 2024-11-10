#include <regex.h>
#include <stdlib.h>

struct array_list {
  regex_t* array;
  int length;
  int _length;
};

struct array_list create_array_list() {
  struct array_list result;
  result.length = 0;
  result._length = 10;
  result.array = malloc(10 * sizeof(regex_t));
  return result;
}

void array_list_add(struct array_list* result, char* pattern, int settings) {
  if (result->length + 1 == result->_length)
    result->array =
        realloc(result->array,
                sizeof(regex_t) * (result->_length = result->_length * 3 / 2));
  regcomp(&result->array[result->length++], pattern, settings);
}

void trash_array(struct array_list* result) {
  for (int i = 0; i < result->length; i++) regfree(&result->array[i]);
  free(result->array);
}