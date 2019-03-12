/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#include <zeos_error.h>

#include <system.h>

#define LECTURA 0
#define ESCRIPTURA 1

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -9; /*EBADF*/
  if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
  return 0;
}

int sys_ni_syscall()
{
	return -38; /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

int sys_fork()
{
  int PID=-1;

  // creates the child process
  
  return PID;
}

#define BLOCK_SIZE 4

int sys_write(int fd, char* buffer, int size){
  char correct_fd = check_fd(fd, ESCRIPTURA);
  if(correct_fd) return -correct_fd;
  if(buffer == NULL) return EFAULT;
  if(size < 0) return EINVAL;
  
  char buff[BLOCK_SIZE];
  int offset = 0;
  	while (offset + BLOCK_SIZE <= size) {
		copy_from_user(buffer+offset, buff, BLOCK_SIZE);
		sys_write_console(buff, BLOCK_SIZE);
		offset += BLOCK_SIZE;
	}
	if (offset < size) {
		int res = size - offset;
		copy_from_user(buffer+offset, buff, res);
		sys_write_console(buff, res);
	}
	return 0;
}


void sys_exit()
{  
}

int sys_gettime() {
	return get_ticks();
}
