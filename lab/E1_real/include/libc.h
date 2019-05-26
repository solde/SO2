/*
 * libc.h - macros per fer els traps amb diferents arguments
 *          definició de les crides a sistema
 */
 
#ifndef __LIBC_H__
#define __LIBC_H__

#include <stats.h>

int write(int fd, char *buffer, int size);

void itoa(int a, char *b);

int strlen(char *a);

int getpid();

int fork();

void exit();

void perror();

char* error_msg(int i_errno);

int write_wraper(int fd, char* buffer, int size);
int gettime_wraper();

extern int errno;

int gettime();
#endif  /* __LIBC_H__ */
