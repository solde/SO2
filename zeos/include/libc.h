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
int get_stats(int pid, struct stats* st);

char *error_switch();

#endif  /* __LIBC_H__ */
