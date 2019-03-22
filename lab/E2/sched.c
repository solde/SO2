/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>

union task_union task[NR_TASKS]
  __attribute__((__section__(".data.task")));

#if 0
struct task_struct *list_head_to_task_struct(struct list_head *l)
{
  return list_entry( l, struct task_struct, list);
}
#endif

struct element {

};

struct task_struct * idle_task;

struct task_struct * ini_task;

struct list_head freequeue;

struct list_head readyqueue;

extern struct list_head blocked;

struct task_struct * idle_task;


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
	int pos;

	pos = ((int)t-(int)task)/sizeof(union task_union);

	t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[pos]; 

	return 1;
}

void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");

	while(1)
	{
	;
	}
}


void init_idle (void)
{
	struct list_head * e = list_first( &freequeue );
	idle_task = list_entry(e, struct task_struct, list); // Get the task_struct
	idle_task->PID = 1; // Assign a PID
	allocate_DIR(idle_task); // Assign memory pages
	list_del(e); // Delete form freequeue
	union task_union *task_union_idle_task = ( union task_union *) idle_task; // Get the task_union of the task

	task_union_idle_task->stack[KERNEL_STACK_SIZE] = (unsigned long)&cpu_idle; // Set the return addr
	task_union_idle_task->stack[KERNEL_STACK_SIZE -1] = 666; // Set de esp (it is not be used)

	idle_task->top_stack = (int*)&task_union_idle_task->stack[KERNEL_STACK_SIZE -1];
}

void init_task1(void)
{
	struct list_head * e = list_first( &freequeue );
	struct task_struct * ini_task = list_entry(e, struct task_struct, list);
	ini_task->PID = 0;
	int r = allocate_DIR(ini_task);
	list_del(e);
}


void init_sched(){
	INIT_LIST_HEAD( &freequeue );
	int i = 0;
	while(i < NR_TASKS){
		list_add( &(task[i].task.list), &freequeue );
		++i;
	}
	INIT_LIST_HEAD( &readyqueue );
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

void inner_task_switch(union task_union*t){
	struct task_struct *act = current();
	tss.esp0 = &t->stack[KERNEL_STACK_SIZE];
	writeMSR(0x175, (int)&t->stack[KERNEL_STACK_SIZE]);
	set_cr3(t->task.dir_pages_baseAddr);
	act->task.top_stack = getESP();
	setESP(&t->task.stack[KERNEL_STACK_SIZE]);
}