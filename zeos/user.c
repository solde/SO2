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
  runjp_rank(7, 7);
  //runjp();
  //runjp_rank(8,10);
/*
  char c[4];
  read(0, c, 4);
  write(1, "test", 4);
  write(1, c, 4);
*/
  while(1);

  return 0;
}
