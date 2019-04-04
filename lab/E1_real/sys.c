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

int NEXT_PID = 2;

#define FIRST_FREE_PAGES (PAG_LOG_INIT_DATA + NUM_PAG_DATA)

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
  update_stats_a();
  int ret = current()->PID;
  update_stats_b();
	return ret;
}

int ret_from_frok(){
  return 0;
}

int sys_fork()
{
  update_stats_a();
  // creates the child process
  if(list_empty(&freequeue)) return -EAGAIN; // No free process
  struct list_head *el = list_first(&freequeue);
  list_del(el);

  struct task_struct *new_task_struct = list_entry(el, struct task_struct, list);
  union task_union *new_task_union = (union task_union *) new_task_struct;

  struct task_struct *current_task_struct = current();
  union task_union *current_task_union = (union task_union *) current_task_struct;

  copy_data(current_task_union, new_task_union, KERNEL_STACK_SIZE * sizeof(long)); // Copy data from current task to the new task
  int e = allocate_DIR(new_task_struct); // Allocate memory for the new task

  if(e < 0) return e;

  page_table_entry *new_pt = get_PT(new_task_struct);
  page_table_entry *current_pt = get_PT(current_task_struct);

  for (int i = 0; i < NUM_PAG_CODE; i++)
		set_ss_pag(new_pt, PAG_LOG_INIT_CODE + i, current_pt[PAG_LOG_INIT_CODE+i].bits.pbase_addr);
	for (int i = 0; i < NUM_PAG_KERNEL; i++)
		set_ss_pag(new_pt, i, current_pt[i].bits.pbase_addr);

  int dataFrames[NUM_PAG_DATA];
  for(int i = 0; i < NUM_PAG_DATA; i++){
    dataFrames[i] = alloc_frame();
    if(dataFrames[i] < 0){
      for(int j =0; j < i; j++) free_frame(dataFrames[j]);
      return -ENOMEM; // Out of memory :(((
    }
  }
  for(int i = 0; i<NUM_PAG_DATA; i++){
    set_ss_pag(new_pt, PAG_LOG_INIT_DATA +i, dataFrames[i]);
    set_ss_pag(current_pt, FIRST_FREE_PAGES +i, dataFrames[i]);
    copy_data((void*)((PAG_LOG_INIT_DATA + i)*PAGE_SIZE), (void*)((FIRST_FREE_PAGES+i)*PAGE_SIZE), PAGE_SIZE);
    del_ss_pag(current_pt, FIRST_FREE_PAGES +i);
    set_cr3(current_task_struct->dir_pages_baseAddr);
  }

  new_task_struct->PID = NEXT_PID;
  ++NEXT_PID;

  set_quantum(new_task_struct, get_initial_quantum());
  new_task_struct->state = ST_READY;

  int offsetEBP = getEBP() & 0xfff;
  int newEBP = offsetEBP + (int)new_task_struct;

  new_task_union->task.kernel_esp = newEBP - sizeof(long);
  new_task_union->stack[offsetEBP/sizeof(long)] = (long)&ret_from_frok;
  new_task_union->stack[offsetEBP/sizeof(long) - 1] = 0;


  list_add_tail(&new_task_struct->list, &readyqueue);

  //init_stats(new_task_struct);

  update_stats_b();

  return new_task_struct->PID;
}

#define BLOCK_SIZE 4

int sys_write(int fd, char* buffer, int size){
  update_stats_a();
  char correct_fd = check_fd(fd, ESCRIPTURA);
  if(correct_fd) {
    update_stats_b();
    return -correct_fd;
  }
  if(buffer == NULL) {
    update_stats_b();
    return EFAULT;
  }
  if(size < 0) {
    update_stats_b();
    return EINVAL;
  }
  
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
  update_stats_b();
	return 0;
}


void sys_exit(){ 
  update_stats_a();
  current()->PID = -1;
  free_user_pages(current()); // Free memory
  update_process_state_rr(current(), &freequeue); //Free the structure
  sched_next_rr(); //Execute de cheducler
  update_stats_b();
}

int sys_gettime() {
  update_stats_a();
	return get_ticks();

}

struct task_struct *get_ts(int pid){
  for(int i = 0; i < NR_TASKS; i++){
    if((&task[i])->task.PID == pid) return (struct task_struct *)&task[i];
  }
  return NULL;
};


int sys_get_stats(int pid, struct stats* st) {
  update_stats_a();
  // Get task struct
	struct task_struct *t = get_ts(pid);
  if(t==NULL) {
    update_stats_b();
    return -1;
  }
  // Test the acces to st
  if(!access_ok(VERIFY_WRITE, st, sizeof(struct stats))) return -EACCES;
  // Send data to user
  t->s.remaining_ticks = t->quantum;
  copy_to_user(&t->s, st, sizeof(struct stats));
  update_stats_b();
  return 0;	
}