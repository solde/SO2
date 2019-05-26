#include <asm.h>
#include <segment.h>

ENTRY(write_wraper)
	push %ebp;
	mov %esp, %ebp;
	push %ebx;
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
	pop %ebx;
	mov %ebp, %esp;
	pop %ebp;
	ret;

ENTRY(gettime_wraper)
	push %ebp;
	mov %esp, %ebp;
	push %ecx; // save ecx
	push %edx; // save edx
	lea ret2, %eax; // sysenter return
	push %eax;
	push %ebp; // fake dynamic link
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

ENTRY(getpid)
	push %ebp
	mov %esp, %ebp
	push %ecx
	push %edx
	// kernel trap to return PID
	lea r1, %eax 
	push %eax
	push %ebp
	movl %esp, %ebp
	mov $20, %eax
	sysenter
	//Return point
r1:	
	pop %ebp
	add $4, %esp
	//Restore
	pop %edx
	pop %ecx
	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(fork)
	push %ebp
	mov %esp, %ebp
	push %ecx // save ecx
	push %edx // save edx
	push %ebx // save ebx
	//Kernel trap to create process
	lea r2, %eax // sysenter return correctly
	push %eax
	push %ebp // fake dynamic link
	movl %esp, %ebp
	mov $2, %eax
	sysenter
	//Retrun point
r2: pop %ebp
	add $4, %esp
	//Restore
	pop %ebx
	pop %edx
	pop %ecx
   	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(exit)
	push %ebp
	mov %esp, %ebp
	push %ecx
	push %edx
	push %ebx

	lea r3, %eax // sysenter return correctly
	push %eax
	push %ebp // fake dynamic link
	movl %esp, %ebp
	mov $1, %eax
	sysenter
	//Return point
r3:	
	pop %ebp
	add $4, %esp
	//Restore 
	pop %ebx
	pop %edx
	pop %ecx
   	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(get_stats)
	push %ebp
	mov %esp, %ebp

	push %ecx // save ecx
	push %edx // save edx
	push %ebx // save ebx

	mov 12(%ebp), %ecx #stats*
	mov 8(%ebp), %ebx #pid

	lea r6, %eax // sysenter return correctly
	push %eax
	push %ebp // fake dynamic link
	movl %esp, %ebp
	mov $35, %eax
	sysenter
r6: 
	pop %ebp
	add $4, %esp

	pop %ebx
	pop %edx
	pop %ecx

	mov %ebp, %esp
	pop %ebp


	cmp $0, %eax // check return value of the implementation
	je end_stat // if 0, leave it as is, the syscall succeeded
	// if syscall fails, store the reason in errno
	lea errno, %ebx
	mov %eax, (%ebx)
	mov $-1, %eax // return -1

end_stat:
	pop %ebx
	pop %edx
	pop %ecx

	mov %ebp, %esp
	pop %ebp
	ret