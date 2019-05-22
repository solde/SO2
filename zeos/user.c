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
  //FAIL

//SEMAFORO 0..11 ok [3 medium] [10 Page fault(si rank(0,10)) pero ok(si rank(10,10)) why? bad destroy/exit?] 12 bad 13..14 page fault 15 ok 16 bad 
//Clone    0..2 ok 3 (bulce inf?) 4..6 Page fault 7..8 (bulce inf?) 9..10 Page Fault  

  //runjp_rank(0, 13);
  //runjp_rank(4,4);

  //runjp_rank(1, 1);

  //runjp_rank(7, 7); 
 
  //runjp_rank(12, 12);


  //runjp_rank(15,15);

  //runjp_rank(16,16);

  //runjp();
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
