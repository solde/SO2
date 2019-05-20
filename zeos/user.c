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
  /*struct circular_buffer cb;

  init_circular_buffer(cb);

  if(is_empty(cb)) write(1, "test", 4);*/

  runjp();
  //sem_init(1, 2);


  while(1);
	
  return 0;
}
/*
12
13
14
16
*/
