#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
 * Ex. 6.1 - The listed version of getword() doesn't handle:
 * underscores - _int
 * comments - // int
 * preprocessor control lines - #if, #elif, #else,
 * string constants - char foo[] = {"int if"}
 *
 * Write a better version that handles these correctly.
 * ---
 * The original statement of this problem was for a program that would count all
 * keywords in a C program. As such, this program will answer that question and
 * ensure that underscores, comments, constants, and preprocessor directives are
 * handled correctly. A similar problem was answered in 1.24, so I reused some
 * code with slight modification. See the comment above main() at the bottom for
 * the solution strategy.
 */

#define MAXWORD 100
#define KW_COUNT (sizeof(keywords) / sizeof(keyword))
#define TIMER_MAX 15  // prevents runaway terminal output

// states for parser FSM
typedef struct ps {
  int in_single_comment;  // are we in a // comment?
  int in_multi_comment;   // are we in a /* comment?
  int in_single_quote;    // are we in a 'single quote'?
  int in_double_quote;    // are we in "double quotes"?
  int should_parse;       // should we start looking for keywords?
} parsing_state;

typedef struct keyword {
  char* word;
  long count;
} keyword;

// C keywords as (mostly) listed here: https://en.cppreference.com/w/c/keyword
static keyword keywords[] = {
    {"auto", 0},     {"break", 0},    {"case", 0},     {"char", 0},
    {"const", 0},    {"continue", 0}, {"default", 0},  {"do", 0},
    {"double", 0},   {"else", 0},     {"enum", 0},     {"extern", 0},
    {"float", 0},    {"for", 0},      {"goto", 0},     {"if", 0},
    {"inline", 0},   {"int", 0},      {"long", 0},     {"register", 0},
    {"return", 0},   {"short", 0},    {"signed", 0},   {"sizeof", 0},
    {"static", 0},   {"struct", 0},   {"switch", 0},   {"typedef", 0},
    {"union", 0},    {"void", 0},     {"volatile", 0}, {"while", 0},
    {"#if", 0},      {"#elif", 0},    {"#else", 0},    {"#defined", 0},
    {"#ifdef", 0},   {"#ifndef", 0},  {"#define", 0},  {"#undef", 0},
    {"#include", 0}, {"#line", 0},    {"#error", 0},   {"#pragma", 0}};

// check_keyword(): given a word, check if it's a keyword and increment if so.
static void check_keyword(const char* const word) {
  for (unsigned long i = 0; i < KW_COUNT; i++) {
    long result = strcmp(word, keywords[i].word);
    printf("%s == %s: %ld\n", keywords[i].word, word, result);
    if (result == 0) {
      printf("check_keyword() | adding %s\n", word);
      keywords[i].count++;
      return;
    }
  }
  printf("check_keyword() | no match for %s\n", word);
}

// display_keywords(): Print all keywords and their counts
static void display_keywords(void) {
  printf("display_keywords() | displaying: \n");
  for (unsigned long i = 0; i < KW_COUNT; i++) {
    if (keywords[i].count) {
      printf("%s: %ld\n", keywords[i].word, keywords[i].count);
    }
  }
}

// get_word(): assuming the stream is in a valid region of code, get the next
// word. Will break if the word is longer than MAXWORD.
static void getword(int c, char* word) {
  int i;
  for (i = 0; i < MAXWORD - 1; c = (char)getchar(), i++) {
    printf("getword() | got %c\n", c);
    if (isalnum(c) || c == '#') {
      printf("getword() | adding %c\n", c);
      word[i] = (char)c;
    } else {
      word[i] = '\0';
      return;
    }
  }
}

// parsing_test(): A nasty function with a lot of nested
// logic to determine if we are in a valid region of code for keyword parsing;
// note that we ignore C preprocessor directives - we explicitly parse for
// preprocessor control statements as we would any other keyword, and
// consider any keywords in #define statements as valid.
static void parsing_test(const int c1, parsing_state* ps) {
  int c2 = 0;

  // Test for beginning of single or multi comment
  if (c1 == '/' && !(ps->in_single_quote || ps->in_double_quote)) {
    c2 = getchar();
    if (c2 == '*' && ps->in_multi_comment == 0) {
      ps->in_multi_comment = 1;
    } else if (c2 == '/' && ps->in_multi_comment == 0) {
      ps->in_single_comment = 1;
    } else {
      ungetc(c2, stdin);
    }
  }  // test for ending of a multi comment
  else if (c1 == '*' && ps->in_multi_comment == 1) {
    c2 = getchar();
    if (c2 == '/') {
      ps->in_multi_comment = 0;
    } else {
      ungetc(c2, stdin);
    }
  }  // exit a single line comment
  else if (c1 == '\n') {
    ps->in_single_comment = 0;
  }  // enter or exit a single-tick quote
  else if (c1 == '\'' && !(ps->in_single_comment || ps->in_multi_comment ||
                           ps->in_double_quote)) {
    ps->in_single_quote = ~(ps->in_single_quote);
  }  // enter or exit a double-tick quote
  else if (c1 == '\"' && !(ps->in_single_comment || ps->in_multi_comment ||
                           ps->in_single_quote)) {
    ps->in_double_quote = ~(ps->in_double_quote);
  }

  // combine all flags to determine if parsing should occur
  ps->should_parse = !(ps->in_single_comment || ps->in_multi_comment ||
                       ps->in_single_quote || ps->in_multi_comment);
}

/* main(): read characters from stdin, using a global FSM to keep track of
 * state based on whether we are in a string constant, comment, or
 * preprocessor directive; in each valid line of code, check each word to see
 * if it is a keyword, and increment the keyword count if so.
 */
int main() {
  int c;
  char word[MAXWORD];
  int timer = 0;  // prevents runaway terminal outoput
  parsing_state ps = {0, 0, 0, 0, 0};

  printf("main() | beginning parsing.\n");

  while ((c = getchar()) != EOF && timer < TIMER_MAX) {
    printf("main() | got %c\n", c);

    parsing_test(c, &ps);
    if (ps.should_parse) {
      printf("main() | parsing at %c\n", c);
      getword(c, word);
      check_keyword(word);
    } else {
      printf("main() | not parsing %c\n", c);
    }
    // timer++;
  }

  display_keywords();
  return 0;
}
