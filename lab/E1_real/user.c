#include <libc.h>

char buff[24];

int pid;

long inner(long n){
	int i;
	long suma;
	suma = 0;
	for(i=0; i<n; i++) suma = suma + i;
	return suma;
}
long outer(long n){
	int i;
	long acum;
	acum = 0;
	for(i=0; i<n; i++) acum = acum + inner(i);
	return acum;
	}

int write(int fd, char* buffer, int size);

int __attribute__ ((__section__(".text.main")))
  main(void)
{
  long count, acum;
  count = 75;
  acum = 0;
  acum = outer(count);
	runjp();
	//perror();

  while(1){
		//write(1, "user", 4);
		
	}
  return 0;
}
