/*
 * sched.h - Estructures i macros pel tractament de processos
 */

#ifndef __SCHED_H__
#define __SCHED_H__

#include <list.h>
#include <libc.h>
#include <types.h>
#include <mm_address.h>

#define NR_TASKS      10
#define KERNEL_STACK_SIZE	1024

#define NR_SEMAPHORES 20

struct task_struct *idle_task;
struct task_struct *init_task;
enum state_t { ST_RUN, ST_READY, ST_BLOCKED };

struct semaphore {
	int id;
	int value;
	int owner; // pid
  int version;
	struct list_head blockqueue;
};
int free_dirs[NR_TASKS];
struct semaphore semaphores[NR_SEMAPHORES];

struct task_struct {
  int PID;			/* Process ID. This MUST be the first field of the struct. */
  page_table_entry * dir_pages_baseAddr;
  struct list_head list;
  int kernel_ebp;
  int quantum;
  struct stats pstats;
  int dir_pos;
  int clone_pid;
  int brk;
  int sem_ver;
  int read_count;
};

union task_union {
  struct task_struct task;
  unsigned long stack[KERNEL_STACK_SIZE];    /* pila de sistema, per procés */
};

extern union task_union task[NR_TASKS]; /* Vector de tasques */
extern struct list_head freequeue;
extern struct list_head readyqueue;
extern struct list_head keyboardqueue;

#define KERNEL_ESP(t)       	(DWord) &(t)->stack[KERNEL_STACK_SIZE]

#define INITIAL_ESP       	KERNEL_ESP(&task[1])

/* Inicialitza les dades del proces inicial */
void init_task1(void);

void init_idle(void);

void init_sched(void);

struct task_struct * current();

void task_switch(union task_union*t);

struct task_struct *list_head_to_task_struct(struct list_head *l);

int allocate_DIR(struct task_struct *t);

page_table_entry * get_PT (struct task_struct *t) ;

page_table_entry * get_DIR (struct task_struct *t) ;

void inner_task_switch(union task_union *new) ;

void init_stat(struct task_struct *t);
void update_us();
void update_su();

/* Headers for the scheduling policy */
void sched_next_rr();
void update_process_state_rr(struct task_struct *t, struct list_head *dest);
int needs_sched_rr();
void update_sched_data_rr();
void controler();


void init_sems();


#endif  /* __SCHED_H__ */
