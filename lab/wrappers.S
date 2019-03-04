#include <asm.h>
#include <segment.h>

#define SAVE_ALL \
      pushl %gs; \
      pushl %fs; \
      pushl %es; \
      pushl %ds; \
      pushl %eax; \
      pushl %ebp; \
      pushl %edi; \
      pushl %esi; \
      pushl %edx; \
      pushl %ecx; \
      pushl %ebx; \
      movl $__KERNEL_DS, %edx;    \
      movl %edx, %ds;           \
      movl %edx, %es

#define RESTORE_ALL \
	pop %ebx; \
	pop %ecx; \
	pop %edx; \
	pop %esi; \
	pop %edi; \
	pop %ebp; \
	pop %eax; \
	pop %ds; \
	pop %es; \
	pop %fs; \
	pop %gs; \

ENTRY(write)
	push %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ebx;
	movl 12(%ebp), %ecx;
	movl 16(%ebp), %edx;
	movl $4, %eax;
	int $0x80;
	pop %ebp
	cmp %eax, $0
	jge end
	movl errno, %eax	
end: 
	ret	
