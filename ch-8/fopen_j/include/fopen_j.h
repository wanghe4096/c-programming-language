#include <stdbool.h>
#include <stddef.h>

#define BUFF_SIZE 10

typedef struct _flags {
  bool _READ;
  bool _WRITE;
  bool _UNBUF;
  bool _EOF;
  bool _ERR;
  char _align[3];  // do not use, aligns struct to 8B
} _flags;

typedef struct _iobuf {
  int _align;    // (4B) do not use
  int fd;        // (4B) file descriptor
  char *buff;    // (8B) pointer to I/O buffer
  char *ptr;     // (8B) next character position within I/O buffer
  _flags flags;  // (8B)
} FILE_J;

/*
#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)
*/

// fopen.c
FILE_J *fopen_j(const char *const name, const char *const mode);

// fclose.c
int fclose_j(FILE_J *file);

// fseek.c
int fseek_j(FILE_J *const fp, const long offset, const int whence);

// buffering.c
void print_buffer(const FILE_J *const fp);
int fflush_j(FILE_J *const fp);
int _fillbuff(FILE_J *const fp);
int _flushbuff(FILE_J *const fp);

// io.c
int getc_j(FILE_J *const fp);
int putc_j(FILE_J *const fp, const int character);
