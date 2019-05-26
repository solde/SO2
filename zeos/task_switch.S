
ENTRY(task_switch)
  push %ebp
  movl %esp,%ebp
  push %esi
  push %edi
  push %ebx
  push 8(%ebp)
  call inner_task_switch
  pop %ebx
  pop %edi
  pop %esi
  pop 8(%ebp) //? si no funciona es por esto
  movl %ebp, %esp
  popl %ebp
  ret

ENTRY(getEBP)
movl %ebp,%eax
ret


ENTRY (setESP)
movl 8(%ebp),%esp
ret

