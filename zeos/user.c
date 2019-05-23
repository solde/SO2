#include <libc.h>
#include <myerror.h>

int pid;

void breakpnt(){ //dummy fn used for easier breakpoints
int n=0;
}

void test(){
	return;
}



int __attribute__ ((__section__(".text.main")))
  main(void)
{
  runjp();

  while(1);

  return 0;
}
