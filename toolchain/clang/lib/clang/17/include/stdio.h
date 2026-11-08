#ifndef MYLINUX_STDIO_H
#define MYLINUX_STDIO_H

#ifndef __MYLINUX_SIZE_T_DEFINED
#define __MYLINUX_SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif

typedef __builtin_va_list va_list;

#define va_start(v, last) __builtin_va_start(v, last)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, type) __builtin_va_arg(v, type)
#define va_copy(dst, src) __builtin_va_copy(dst, src)

#define EOF (-1)
#define BUFSIZ 8192
#define FILENAME_MAX 4096
#define FOPEN_MAX 256
#define L_tmpnam 256

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

typedef struct __mylinux_FILE FILE;
typedef long long fpos_t;

#ifdef __cplusplus
extern "C" {
#endif

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

FILE *fopen(const char *path, const char *mode);
FILE *freopen(const char *path, const char *mode, FILE *stream);
int fclose(FILE *stream);
int fflush(FILE *stream);

int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);
int ungetc(int character, FILE *stream);

int fputc(int character, FILE *stream);
int putc(int character, FILE *stream);
int putchar(int character);

char *fgets(char *buffer, int size, FILE *stream);
int fputs(const char *string, FILE *stream);
int puts(const char *string);

size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *buffer, const char *format, ...);
int snprintf(char *buffer, size_t size, const char *format, ...);

int vprintf(const char *format, va_list args);
int vfprintf(FILE *stream, const char *format, va_list args);
int vsprintf(char *buffer, const char *format, va_list args);
int vsnprintf(char *buffer, size_t size, const char *format, va_list args);

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *buffer, const char *format, ...);

int fseek(FILE *stream, long offset, int origin);
long ftell(FILE *stream);
void rewind(FILE *stream);
int fgetpos(FILE *stream, fpos_t *position);
int fsetpos(FILE *stream, const fpos_t *position);

int feof(FILE *stream);
int ferror(FILE *stream);
void clearerr(FILE *stream);

void perror(const char *message);
int remove(const char *path);
int rename(const char *old_path, const char *new_path);
FILE *tmpfile(void);
char *tmpnam(char *buffer);

#ifdef __cplusplus
}
#endif

#endif
