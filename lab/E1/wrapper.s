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
# 33 "wrapper.S"
.globl write_wraper; .type write_wraper, @function; .align 0; write_wraper:
 push %ebp;
 mov %esp, %ebp;
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
 je end_err;
 lea errno, %ebx;
 mov %eax, (%ebx);
 mov $-1, %eax;
 jmp end;
end_err:
 mov 16(%ebp), %eax;
end:
 mov %ebp, %esp;
 pop %ebp;
 ret;

.globl gettime_wraper; .type gettime_wraper, @function; .align 0; gettime_wraper:
 push %ebp;
 mov %esp, %ebp;
 push %ecx;
 push %edx;
 lea ret, %eax;
 push %eax;
 push %ebp;
 movl %esp, %ebp;
 mov $4, %eax;
 sysenter;
ret2:
 pop %ebp;
 add $4, %esp;
 pop %edx;
 pop %ecx;
    mov %ebp, %esp;
 pop %ebp;
 ret;
