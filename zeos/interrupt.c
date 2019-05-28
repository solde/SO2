/*
 * interrupt.c -
 */
#include <types.h>
#include <interrupt.h>
#include <segment.h>
#include <hardware.h>
#include <io.h>
#include <entry.h>
#include <system.h>
#include <zeos_interrupt.h>
#include <sched.h>

#include <circular_buffer.h>

Gate idt[IDT_ENTRIES];
Register    idtR;

struct circular_buffer keyboard_buffer;


char char_map[] =
{
  '\0','\0','1','2','3','4','5','6',
  '7','8','9','0','\'','�','\0','\0',
  'q','w','e','r','t','y','u','i',
  'o','p','`','+','\0','\0','a','s',
  'd','f','g','h','j','k','l','�',
  '\0','�','\0','�','z','x','c','v',
  'b','n','m',',','.','-','\0','*',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0','\0','\0','\0','\0','\0','7',
  '8','9','-','4','5','6','+','1',
  '2','3','0','\0','\0','\0','<','\0',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0'
};

void setInterruptHandler(int vector, void (*handler)(), int maxAccessibleFromPL)
{
  /***********************************************************************/
  /* THE INTERRUPTION GATE FLAGS:                          R1: pg. 5-11  */
  /* ***************************                                         */
  /* flags = x xx 0x110 000 ?????                                        */
  /*         |  |  |                                                     */
  /*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
  /*         |   \ DPL = Num. higher PL from which it is accessible      */
  /*          \ P = Segment Present bit                                  */
  /***********************************************************************/
  Word flags = (Word)(maxAccessibleFromPL << 13);
  flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

  idt[vector].lowOffset       = lowWord((DWord)handler);
  idt[vector].segmentSelector = __KERNEL_CS;
  idt[vector].flags           = flags;
  idt[vector].highOffset      = highWord((DWord)handler);
}

void setTrapHandler(int vector, void (*handler)(), int maxAccessibleFromPL)
{
  /***********************************************************************/
  /* THE TRAP GATE FLAGS:                                  R1: pg. 5-11  */
  /* ********************                                                */
  /* flags = x xx 0x111 000 ?????                                        */
  /*         |  |  |                                                     */
  /*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
  /*         |   \ DPL = Num. higher PL from which it is accessible      */
  /*          \ P = Segment Present bit                                  */
  /***********************************************************************/
  Word flags = (Word)(maxAccessibleFromPL << 13);

  //flags |= 0x8F00;    /* P = 1, D = 1, Type = 1111 (Trap Gate) */
  /* Changed to 0x8e00 to convert it to an 'interrupt gate' and so
     the system calls will be thread-safe. */
  flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

  idt[vector].lowOffset       = lowWord((DWord)handler);
  idt[vector].segmentSelector = __KERNEL_CS;
  idt[vector].flags           = flags;
  idt[vector].highOffset      = highWord((DWord)handler);
}


void setIdt()
{
  /* Program interrups/exception service routines */
  idtR.base  = (DWord)idt;
  idtR.limit = IDT_ENTRIES * sizeof(Gate) - 1;

  set_handlers();
  setInterruptHandler(33, keyboard_handler, 0);
  setInterruptHandler(32, clock_handler, 0);
  setTrapHandler(0x80, write_call_handler, 3);
  /* ADD INITIALIZATION CODE FOR INTERRUPT VECTOR */
  writeMSR(0x174, __KERNEL_CS);
  writeMSR(0x175, INITIAL_ESP);
  writeMSR(0x176, syscall_handler_sysenter);

  set_idt_reg(&idtR);
}


void printtest(){ //TEST
	printk("hola");
}

void test_change_context(){

struct task_struct *e = idle_task;
union task_union *u = (union task_union *) e;
task_switch(u);

}


void printchar(){ //DONE
 char out='C';
 unsigned char c=inb(0x60);
 int tmp = c & 0x80;
 int tmpm= c & 0x7f;
 
 if(tmp==0){
 	char fin=char_map[tmpm];
	cb_write(&keyboard_buffer, fin);
	
	if(!list_empty(&keyboardqueue)){
	 struct list_head *e = list_first( &keyboardqueue );
	 struct task_struct *ts = list_entry( e, struct task_struct, list );
	 if(ts->read_count == cb_size(&keyboard_buffer) || cb_is_full(&keyboard_buffer)){
		update_process_state_front(ts, &readyqueue);
		update_process_state_rr(current(), &readyqueue);
		sched_next_rr();
	 }
	}
 }
}

void clock_int(){
 zeos_show_clock();
 zeos_ticks++;
 controler();
}

void init_keyboard_buffer(){
  init_circular_buffer(&keyboard_buffer);
}
