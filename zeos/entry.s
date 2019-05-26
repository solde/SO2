# 1 "entry.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "entry.S"




# 1 "include/asm.h" 1
# 6 "entry.S" 2
# 1 "include/segment.h" 1
# 7 "entry.S" 2
# 1 "include/myerror.h" 1
# 8 "entry.S" 2
# 74 "entry.S"
.globl keyboard_handler; .type keyboard_handler, @function; .align 0; keyboard_handler:
  pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
  movb $0x20, %al; outb %al, $0x20 ;
  call printchar
  popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
  iret


.globl clock_handler; .type clock_handler, @function; .align 0; clock_handler:
  pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
  movb $0x20, %al; outb %al, $0x20 ;
  call clock_int
  popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
  iret

.globl write_call_handler; .type write_call_handler, @function; .align 0; write_call_handler:

  pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
  cmpl $0, %EAX
  jl err
  cmpl $MAX_SYSCALL, %EAX
  jg err
  call *sys_call_table(, %EAX, 0x04)
  jmp fin
err:
  movl $-38, %EAX
fin:
  movl %EAX, 0x18(%esp)
  popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
  iret

.globl writeMSR; .type writeMSR, @function; .align 0; writeMSR:
 push %ebp
 movl %esp,%ebp
 movl 8(%ebp), %ecx
 movl 12(%ebp), %eax
 wrmsr
 pop %ebp
 ret

.globl syscall_handler_sysenter; .type syscall_handler_sysenter, @function; .align 0; syscall_handler_sysenter:

  push $0x2B
  push %ebp
  pushfl
  push $0x23
  push 4(%ebp)
  pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
  cmpl $0, %EAX
  jl errsys
  cmpl $MAX_SYSCALL, %EAX
  jg errsys
  push %eax
  call update_us
  pop %eax

  call *sys_call_table(, %EAX, 0x04)
  push %eax
  call update_su
  pop %eax
  jmp finsys
 errsys:
  movl $-38, %EAX
 finsys:
  movl %EAX, 0x18(%esp)

  popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
  movl (%esp), %edx
  movl 12(%esp), %ecx
  sti
  sysexit


.globl task_switch; .type task_switch, @function; .align 0; task_switch:
  push %ebp
  movl %esp,%ebp
  push %esi
  push %edi
  push %ebx
  push 8(%ebp)
  call inner_task_switch
  add $4, %esp
  pop %ebx
  pop %edi
  pop %esi
  movl %ebp, %esp
  pop %ebp
  ret

.globl getEBP; .type getEBP, @function; .align 0; getEBP:
 movl %ebp,%eax
 ret


.globl setESP; .type setESP, @function; .align 0; setESP:
 push %ebp
 mov %esp, %ebp

 mov 12(%ebp), %eax
 mov %esp, (%eax)

 mov 8(%ebp), %eax
 mov (%eax), %esp

 pop %ebp
ret
