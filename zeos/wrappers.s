# 1 "wrappers.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "wrappers.S"
# 1 "include/asm.h" 1
# 2 "wrappers.S" 2
# 27 "wrappers.S"
.globl write; .type write, @function; .align 0; write:
  push %ebp
  movl %esp, %ebp
  push %ebx
  movl 8(%ebp), %ebx
  movl 12(%ebp), %ecx
  movl 16(%ebp), %edx

  push %ecx
  push %edx
  lea ret, %esi
  push %esi
  push %ebp
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
  negl %eax
  movl %eax, (%ebx)
  movl $-1, %eax
  jmp end
 skip2:
  movl 16(%ebp), %eax
 end:
  movl %ebp, %esp
  popl %ebp
  ret


.globl gettime; .type gettime, @function; .align 0; gettime:
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

.globl getpid; .type getpid, @function; .align 0; getpid:
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

.globl fork; .type fork, @function; .align 0; fork:
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
  negl %eax
  movl %eax, (%ebx)
  movl $-1, %eax
 endF:
  movl %ebp, %esp
  popl %ebp
  ret


.globl exit; .type exit, @function; .align 0; exit:
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

.globl get_stats; .type get_stats, @function; .align 0; get_stats:
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
  negl %eax
  movl %eax, (%ebx)
  movl $-1, %eax
 skip4:
  movl %ebp, %esp
  popl %ebp
  ret

.globl clone; .type clone, @function; .align 0; clone:
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
  negl %eax
  movl %eax, (%ebx)
  movl $-1, %eax
 skip10:
  movl %ebp, %esp
  popl %ebp
  ret

.globl sem_init; .type sem_init, @function; .align 0; sem_init:
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 12(%ebp), %ecx
  mov 8(%ebp), %ebx
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
  negl %eax
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

.globl sem_wait; .type sem_wait, @function; .align 0; sem_wait:
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx
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
  negl %eax
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

.globl sem_signal; .type sem_signal, @function; .align 0; sem_signal:
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx
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
  negl %eax
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

  .globl sem_destroy; .type sem_destroy, @function; .align 0; sem_destroy:
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx
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
  negl %eax
  movl %eax, (%ebx)
  movl $-1, %eax
 skipd:
  movl %ebp, %esp
  popl %ebp
  ret

.globl sbrk; .type sbrk, @function; .align 0; sbrk:
  push %ebp
  movl %esp, %ebp
  push %ecx
  push %edx
  push %ebx

  mov 8(%ebp), %ebx
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
  negl %eax
  movl %eax, (%ebx)
  movl $-1, %eax
 skipsb:
  movl %ebp, %esp
  popl %ebp
  ret

.globl read; .type read, @function; .align 0; read:
  push %ebp
  movl %esp, %ebp
  push %ebx
  movl 8(%ebp), %ebx
  movl 12(%ebp), %ecx
  movl 16(%ebp), %edx

  push %ecx
  push %edx
  lea retRead, %esi
  push %esi
  push %ebp
  movl %esp, %ebp
  movl $4, %eax
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
  negl %eax
  movl %eax, (%ebx)
  movl $-1, %eax
  jmp endRead
skipRead:
  movl 16(%ebp), %eax
endRead:
  movl %ebp, %esp
  popl %ebp
  ret
