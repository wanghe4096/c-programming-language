#include <stdio.h>

#include "charmatch.h"
#include "common.h"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  int i = 0;
  char word[MAXLEN] = {0};
  while ((i = getword(word, MAXLEN)) > 0) {
    if (should_evaluate(word)) {
      if (istypename(word)) {
        store_varname();
      } else if (strcmp(word, "#define") == 0) {
        handle_define();
      } else if (strcmp(word, "typedef") == 0) {
        handle_typedef();
      }
    }
  }

  display_varnames();
  cleanup();
  return 0;
}