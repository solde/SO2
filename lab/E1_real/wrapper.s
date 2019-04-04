# 1 "wrapper.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "wrapper.S"
# 1 "include/asm.h" 1
# 2 "wrapper.S" 2
# 1 "include/segment.h" 1
# 3 "wrapper.S" 2

.globl write_wraper; .type write_wraper, @function; .align 0; write_wraper:
 push %ebp;
 mov %esp, %ebp;
 push %ebx;
 mov 16(%ebp), %edx;
 mov 12(%ebp), %ecx;
 mov 8(%ebp), %ebx;
 push %ecx;
 push %edx;
 lea ret, %eax;
 push %eax;
 push %ebp;
 movl %esp, %ebp;
 mov $4, %eax;
 sysenter;
ret:
 pop %ebp;
 add $4, %esp;
 pop %edx;
 pop %ecx;
 cmp $0, %eax;
 neg %eax;
 je end_err;
 lea errno, %ebx;
 mov %eax, (%ebx);
 mov $-1, %eax;
 jmp end;
end_err:
 mov 16(%ebp), %eax;
end:
 pop %ebx;
 mov %ebp, %esp;
 pop %ebp;
 ret;

.globl gettime_wraper; .type gettime_wraper, @function; .align 0; gettime_wraper:
 push %ebp;
 mov %esp, %ebp;
 push %ecx;
 push %edx;
 lea ret2, %eax;
 push %eax;
 push %ebp;
 movl %esp, %ebp;
 mov $10, %eax;
 sysenter;
ret2:
 pop %ebp;
 add $4, %esp;
 pop %edx;
 pop %ecx;
    mov %ebp, %esp;
 pop %ebp;
 ret;

.globl getpid; .type getpid, @function; .align 0; getpid:
 push %ebp
 mov %esp, %ebp
 push %ecx
 push %edx

 lea r1, %eax
 push %eax
 push %ebp
 movl %esp, %ebp
 mov $20, %eax
 sysenter

r1:
 pop %ebp
 add $4, %esp

 pop %edx
 pop %ecx
 mov %ebp, %esp
 pop %ebp
 ret

.globl fork; .type fork, @function; .align 0; fork:
 push %ebp
 mov %esp, %ebp
 push %ecx
 push %edx
 push %ebx

 lea r2, %eax
 push %eax
 push %ebp
 movl %esp, %ebp
 mov $2, %eax
 sysenter

r2: pop %ebp
 add $4, %esp

 pop %ebx
 pop %edx
 pop %ecx
    mov %ebp, %esp
 pop %ebp
 ret

.globl exit; .type exit, @function; .align 0; exit:
 push %ebp
 mov %esp, %ebp
 push %ecx
 push %edx
 push %ebx

 lea r3, %eax
 push %eax
 push %ebp
 movl %esp, %ebp
 mov $1, %eax
 sysenter

r3:
 pop %ebp
 add $4, %esp

 pop %ebx
 pop %edx
 pop %ecx
    mov %ebp, %esp
 pop %ebp
 ret

.globl get_stats; .type get_stats, @function; .align 0; get_stats:
 push %ebp
 mov %esp, %ebp

 push %ecx
 push %edx
 push %ebx

 mov 12(%ebp), %ecx
 mov 8(%ebp), %ebx


 lea r4, %eax
 push %eax
 push %ebp
 movl %esp, %ebp
 mov $35, %eax
 sysenter

r4: pop %ebp
 add $4, %esp

 pop %ebx
 pop %edx
 pop %ecx
    mov %ebp, %esp
 pop %ebp
 ret
