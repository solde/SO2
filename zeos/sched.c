/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>
#include <libc.h>
#include <entry.h>
#include <utils.h>

#define USELESS 0

union task_union task[NR_TASKS]
  __attribute__((__section__(".data.task")));

#if 1
struct task_struct *list_head_to_task_struct(struct list_head *l)
{
  return list_entry( l, struct task_struct, list);
}
#endif


 struct list_head freequeue;
 struct list_head readyqueue;
 struct list_head keyboardqueue;
 int time;

/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t)
{
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t)
{
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}


int allocate_DIR(struct task_struct *t)
{
	int pos = 0;
	while (free_dirs[pos] != 0) pos++;

	t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[pos];
	t->dir_pos = pos;

	free_dirs[pos] = 1;
	return 0;
}

void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");

	while(1)
	{
	//printk("Hey...");
	;
	}
}

void init_idle (void)  //e=element; Sidle=idle pcb; uni= idle union(pcb+stack)
{
	struct list_head * e = list_first( &freequeue );
	list_del(e);
	struct task_struct * sidle = list_entry( e, struct task_struct, list ); //aixi conseguim el pcb de idle
	sidle->PID=0;
	allocate_DIR(sidle);

	union task_union *uni = (union task_union *) sidle;
	uni->stack[KERNEL_STACK_SIZE-1] = (long) &cpu_idle;  //lower point on the stack
	uni->stack[KERNEL_STACK_SIZE-2] = USELESS;
	sidle->kernel_ebp = (int) &uni->stack[KERNEL_STACK_SIZE-2];
	idle_task=sidle;
	sidle->clone_pid=1234;


}

void init_task1(void)
{
	struct list_head * e = list_first( &freequeue );
	list_del(e);
	struct task_struct * stask1 = list_entry( e, struct task_struct, list ); //aixi conseguim el pcb de task
	stask1->PID=1;
	allocate_DIR(stask1);
	set_user_pages(stask1);
	union task_union *un1 = (union task_union *) stask1;
	tss.esp0=(int) &un1->stack[KERNEL_STACK_SIZE];
	writeMSR(0x175, (int) &un1->stack[KERNEL_STACK_SIZE]);
	set_cr3(stask1->dir_pages_baseAddr);
	init_task=stask1;
	time=200;
	stask1->clone_pid=1234;

}


void init_sched(){

	for (int i = 0; i < NR_TASKS; i++) free_dirs[i] = 0;
	for (int i = 0; i < NR_SEMAPHORES; i++) semaphores[i].id = -1;
  	INIT_LIST_HEAD(&freequeue);
  	INIT_LIST_HEAD(&readyqueue);
    INIT_LIST_HEAD(&keyboardqueue);
 	int i=0;
 	while (i<NR_TASKS){
		struct task_struct *e = (struct task_struct *) &task[i];
		e->PID = 50+i; //2-50 per forks i clones
		e->quantum = 18;
		list_add(&e->list, &freequeue );
		i++;
	 }

}

struct task_struct* current()
{
  int ret_value;

  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );
  return (struct task_struct*)(ret_value&0xfffff000);
}

void init_stat(struct task_struct *t) {
	t->pstats.user_ticks = 0;
	t->pstats.system_ticks = 0;
	t->pstats.blocked_ticks = 0;
	t->pstats.ready_ticks = 0;
	t->pstats.elapsed_total_ticks = 0;
	t->pstats.total_trans = 0;
	t->pstats.remaining_ticks =t->quantum;
	t->clone_pid=1234;


}

void inner_task_switch(union task_union *new){
	//--UPDATE STATS--
	current()->pstats.system_ticks+=get_ticks()-current()->pstats.elapsed_total_ticks;
	current()->pstats.elapsed_total_ticks=get_ticks();
	struct task_struct *new_task= (struct task_struct *) new;
	new_task->pstats.ready_ticks+=get_ticks()-new_task->pstats.elapsed_total_ticks;
	new_task->pstats.elapsed_total_ticks=get_ticks();
	new_task->pstats.total_trans++;

	tss.esp0=(int) &new->stack[KERNEL_STACK_SIZE];
	writeMSR(0x175, (int) &new->stack[KERNEL_STACK_SIZE]);


	set_cr3(new_task->dir_pages_baseAddr);
	setESP(&(new_task->kernel_ebp),&(current()->kernel_ebp));


}


int get_quantum(struct task_struct *t) {
	return t->quantum;
}

void set_quantum(struct task_struct *t, int new_quantum) {
	t->quantum=new_quantum;
}

int needs_sched_rr() {
	int ret=0;
	if ( time<=0) ret=1;
	return ret;
}

void update_sched_data_rr() {
	time--;

}

void update_process_state_rr(struct task_struct *t, struct list_head *dest){

	if(current()->PID!=t->PID) list_del(&t->list);
	if(dest!=NULL) list_add_tail(&t->list, dest); //evitamos errores.
	if(dest==NULL) t->pstats.total_trans++;

}

void block_read_process(struct task_struct *t, struct list_head *dest){
	if(dest != NULL && t != idle_task){
		list_add(&t->list, dest);
	}
}

void sched_next_rr() {

	if(list_empty(&readyqueue)){
		task_switch( (union task_union*) idle_task);
		return;
	}
	struct list_head * e = list_first( &readyqueue );
	list_del(e);
	struct task_struct * next = list_entry( e, struct task_struct, list ); //aixi conseguim el pcb de next
	time=next->quantum; //reiniciar
	task_switch((union task_union*) next);
}
void controler(){

	update_sched_data_rr(); //cada tick s'actualitza time
	int ret=needs_sched_rr();
	if(ret==1){
		if(current()->PID!=0){
			update_process_state_rr(current(),&readyqueue);
			sched_next_rr();
		}
	}
}

void update_us(){
current()->pstats.user_ticks+=get_ticks()-current()->pstats.elapsed_total_ticks;
current()->pstats.elapsed_total_ticks=get_ticks();

}

void update_su(){
current()->pstats.system_ticks+=get_ticks()-current()->pstats.elapsed_total_ticks;
current()->pstats.elapsed_total_ticks=get_ticks();

}

void init_sems(){
	for(int i = 0;  i < NR_SEMAPHORES; ++i){
		semaphores[i].owner = -1;
		//semaphores[i].id = i;
	}
}
