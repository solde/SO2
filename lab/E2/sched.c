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
	struct task_struct * t1 = list_entry(e, struct task_struct, list); // Get the task_struct
	t1->PID = 1; // Assign a PID
	int r = allocate_DIR(t1); // Assign memory pages
	list_del(e); // Delete form freequeue
	union task_union task_union_t1 = ( union task_union *) t1; // Get the task_union of the task

	task_union_t1->stack[KERNEL_STACK_SIZE] = &cpu_idle; // Set the return addr
	task_union_t1->stack[KERNEL_STACK_SIZE -1] = 666; // Set de esp (it is not be used)

	t1->top_stack = &task_union_t1->stack[KERNEL_STACK_SIZE -1];
}

void init_task1(void)
{
	struct list_head * e = list_first( &freequeue );
	struct task_struct * t0 = list_entry(e, struct task_struct, list);
	t0->PID = 0;
	int r = allocate_DIR(t0);
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

