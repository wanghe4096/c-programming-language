#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

static char usage[] = "usage: sort -d -f -n -r -i ";

// parse_args(): validate argc/argv; allowed args are -r, -n, -d, and -f
int parse_args(const int argc, char** const argv, input_flags* const p_flags,
               input_flags* const s_flags) {
  for (int i = 1; i < argc; i++) {
    const char* const current_arg = argv[i];

    if (current_arg[0] != '-') {
      printf("sort: illegal arg '%s'\n", argv[i]);
      printf("%s\n", usage);
      return -1;
    } else {
      switch (current_arg[1]) {
        case 'd':
          if (!(s_flags->in_use)) {
            p_flags->directory = true;
          } else {
            s_flags->directory = true;
          }
          break;
        case 'f':
          if (!(s_flags->in_use)) {
            p_flags->fold = true;
          } else {
            s_flags->fold = true;
          }
          break;
        case 'n':
          if (!(s_flags->in_use)) {
            p_flags->numeric = true;
          } else {
            s_flags->numeric = true;
          }
          break;
        case 'r':
          if (!(s_flags->in_use)) {
            p_flags->reverse = true;
          } else {
            s_flags->reverse = true;
          }
          break;
        case 'i':
          s_flags->in_use = true;
          break;
        default:
          printf("sort: unknown option '%c'\n", current_arg[1]);
          printf("%s\n", usage);
          return -1;
      }
    }
  }
  return 0;
}
