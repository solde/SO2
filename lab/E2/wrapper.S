#include <asm.h>
#include <segment.h>

ENTRY(write_wraper)
	push %ebp;
	mov %esp, %ebp;
	mov 16(%ebp), %edx; //size
	mov 12(%ebp), %ecx; //buffer
	mov 8(%ebp), %ebx; 	//#fd
	push %ecx; // save ecx
	push %edx; // save edx
	lea ret, %eax; // sysenter return
	push %eax;
	push %ebp; // fake dynamic link
	movl %esp, %ebp;
	mov $4, %eax;
	sysenter;
ret:    
	pop %ebp;
	add $4, %esp; // remove lea
	pop %edx;
	pop %ecx;
	cmp $0, %eax; // check return value
	neg %eax;
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

ENTRY(gettime_wraper)
	push %ebp;
	mov %esp, %ebp;
	push %ecx; // save ecx
	push %edx; // save edx
	lea ret, %eax; // sysenter return
	push %eax;
	push %ebp; // fake dynamic link
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