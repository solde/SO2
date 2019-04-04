/*
 * interrupt.h - Definició de les diferents rutines de tractament d'exepcions
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <types.h>

#define IDT_ENTRIES 256

extern Gate idt[IDT_ENTRIES];
extern Register idtR;

void setInterruptHandler(int vector, void (*handler)(), int maxAccessibleFromPL);
void setTrapHandler(int vector, void (*handler)(), int maxAccessibleFromPL);

void writeMSR(int addr, int val);

void setIdt();

void keyboard_RSI();
void clock_RSI();

void clock_handler();
void keyboard_handler();
void system_call_handler();

void syscall_handler_sysenter();
void writeMSR(int addr, int val);

void update_schedule();

extern struct task_struct * idle_task;

extern struct task_struct * ini_task;

#endif  /* __INTERRUPT_H__ */
