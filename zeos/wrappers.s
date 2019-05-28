#include <asm.h>

/*
ENTRY(write)   //write int

 push %ebp
 movl %esp,%ebp
 movl 8(%ebp),%ebx
 movl 12(%ebp),%ecx
 movl 16(%ebp),%edx
 movl $0x4, %eax
 int $0x80
 cmp $0, %eax
 jge safe
 lea errno, %ebx
 mov %eax, (%ebx)
 mov $-1, %eax
 jmp skip
safe:
 movl $0x00,%eax
skip:
 mov %ebp,%esp
 popl %ebp
 ret
 */

ENTRY(write)  //write sysenter
  push %ebp
  movl %esp, %ebp
  push %ebx
  movl 8(%ebp), %ebx
  movl 12(%ebp), %ecx
  movl 16(%ebp), %edx

  push %ecx // save ecx
  push %edx // save edx
  lea ret, %esi // return user
  push %esi
  push %ebp // fake dynamic link
  movl %esp, %ebp
  movl $4, %eax
  sysenter
 ret:
  popl %ebp
  popl %esi
  popl %edx
  popl %ecx
  popl %ebx

  cmp $0, %eax
  jge skip2
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
  jmp end
 skip2:
  movl 16(%ebp), %eax
 end:
  movl %ebp, %esp
  popl %ebp
  ret


ENTRY(gettime)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  lea retC, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $10, %eax
  sysenter
 retC:
  popl %ebp
  popl %esi
  popl %edx
  popl %ecx

  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(getpid)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  lea retP, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $20, %eax
  sysenter
 retP:
  popl %ebp
  popl %esi
  popl %edx
  popl %ecx

  mov %ebp, %esp
  pop %ebp
  ret

ENTRY(fork)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  lea retF, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $2, %eax
  sysenter
retF:
  popl %ebp
  popl %esi
  popl %edx
  popl %ecx

  cmp $0, %eax
  jge endF
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 endF:
  movl %ebp, %esp
  popl %ebp
  ret


ENTRY(exit)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  lea retE, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $1, %eax
  sysenter
 retE:
  popl %ebp
  popl %esi
  popl %edx
  popl %ecx

  mov %ebp, %esp
  pop %ebp
  ret

ENTRY(get_stats)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 12(%ebp), %ecx
  mov 8(%ebp), %ebx
  lea retS, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $35, %eax
  sysenter
 retS:
  popl %ebp
  popl %esi
  popl %ebx
  popl %edx
  popl %ecx

  cmp $0, %eax
  jge skip4
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 skip4:
  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(clone)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 12(%ebp), %ecx
  mov 8(%ebp), %ebx
  lea ret10, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $19, %eax
  sysenter
 ret10:
  popl %ebp
  popl %esi
  popl %ebx
  popl %edx
  popl %ecx

  cmp $0, %eax
  jge skip10
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 skip10:
  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(sem_init)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 12(%ebp), %ecx // value
  mov 8(%ebp), %ebx // n_sem
  lea reti, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $21, %eax
  sysenter
 reti:
  popl %ebp

  cmp $0, %eax
  jge skipi
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 skipi:
  popl %esi
  popl %ebx
  popl %edx
  popl %ecx
  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(sem_wait)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx // n_sem
  lea retw, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $22, %eax
  sysenter
 retw:
  popl %ebp
  cmp $0, %eax
  jge skipw
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 skipw:
  popl %esi
  popl %ebx
  popl %edx
  popl %ecx
  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(sem_signal)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx // n_sem
  lea rets, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $23, %eax
  sysenter
 rets:
  popl %ebp


  cmp $0, %eax
  jge skips
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 skips:
  popl %esi
  popl %ebx
  popl %edx
  popl %ecx
  movl %ebp, %esp
  popl %ebp
  ret

  ENTRY(sem_destroy)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx // n_sem
  lea retd, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $24, %eax
  sysenter
 retd:
  popl %ebp
  popl %esi
  popl %ebx
  popl %edx
  popl %ecx

  cmp $0, %eax
  jge skipd
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 skipd:
  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(sbrk)
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx // n_sem
  lea retsb, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $45, %eax
  sysenter
 retsb:
  popl %ebp
  popl %esi
  popl %ebx
  popl %edx
  popl %ecx

  cmp $0, %eax
  jge skipsb
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
 skipsb:
  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(read)  //read sysenter
  push %ebp
  movl %esp, %ebp
  push %ebx
  push %ecx // save ecx
  push %edx // save edx
  
  movl 8(%ebp), %ebx
  movl 12(%ebp), %ecx
  movl 16(%ebp), %edx


  lea retRead, %esi // return user
  push %esi
  push %ebp // fake dynamic link
  movl %esp, %ebp
  movl $0, %eax
  sysenter
retRead:
  popl %ebp
  popl %esi
  popl %edx
  popl %ecx
  popl %ebx

  cmp $0, %eax
  jge skipRead
  leal errno, %ebx
  negl %eax //negar errror
  movl %eax, (%ebx)
  movl $-1, %eax
  jmp endRead
skipRead:
  movl 16(%ebp), %eax
endRead:
  movl %ebp, %esp
  popl %ebp
  ret
