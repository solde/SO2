/*
 * libc.c 
 */

#include <libc.h>

#include <types.h>

int errno;

char error_text[][] = {
    "Operation not permitted", 
    "No such file or directory", 
    "No such process", 
    "Interrupted system call", 
    "I/O erroc", 
    "No such device or address", 
    "Arg list too long",
    "Exec format erroc", 
    "Bad file numbec", 
    "No child processes", 
    "Try again", 
    "Out of memory", 
    "Permission denied", 
    "Bad address", 
    "Block device required", 
    "Device or resource busy", 
    "File exists", 
    "Cross-device link", 
    "No such device", 
    "Not a directory", 
    "Is a directory", 
    "Invalid argument", 
    "File table overflow",
    "Too many open files", 
    "Not a typewritec", 
    "Text file busy", 
    "File too large", 
    "No space left on device", 
    "Illegal seek", 
    "Read-only file system", 
    "Too many links", 
    "Broken pipe", 
    "Math argument out of domain of func", 
    "Math result not representable", 
    "Resource deadlock would occuc", 
    "File name too long",
    "No record locks available", 
    "Function not implemented", 
    "Directory not empty", 
    "Too many symbolic links encountered", 
    "Operation would block", 
    "No message of desired type", 
    "Identifier removed", 
    "Channel number out of range", 
    "Level 2 not synchronized", 
    "Level 3 halted", 
    "Level 3 reset", 
    "Link number out of range", 
    "Protocol driver not attached", 
    "No CSI structure available", 
    "Level 2 halted", 
    "Invalid exchange", 
    "Invalid request descriptoc", 
    "Exchange full", 
    "No anode", 
    "Invalid request code", 
    "Invalid slot", 
    "Resource deadlock would occuc", 
    "Bad font file format", 
    "Device not a stream", 
    "No data available", 
    "Timer expired", 
    "Out of streams resources", 
    "Machine is not on the network", 
    "Package not installed", 
    "Object is remote", 
    "Link has been severed", 
    "Advertise erroc", 
    "Srmount erroc", 
    "Communication error on send", 
    "Protocol erroc", 
    "Multihop attempted", 
    "RFS specific erroc", 
    "Not a data message", 
    "Value too large for defined data type", 
    "Name not unique on network", 
    "File descriptor in bad state", 
    "Remote address changed", 
    "Can not access a needed shared library", 
    "Accessing a corrupted shared library", 
    ".lib section in a.out corrupted", 
    "Attempting to link in too many shared libraries", 
    "Cannot exec a shared library directly", 
    "Illegal byte sequence", 
    "Interrupted system call should be restarted", 
    "Streams pipe erroc", 
    "Too many users", 
    "Socket operation on non-socket", 
    "Destination address required", 
    "Message too long", 
    "Protocol wrong type for socket", 
    "Protocol not available", 
    "Protocol not supported", 
    "Socket type not supported", 
    "Operation not supported on transport endpoint", 
    "Protocol family not supported", 
    "Address family not supported by protocol", 
    "Address already in use", 
    "Cannot assign requested address", 
    "Network is down", 
    "Network is unreachable", 
    "Network dropped connection because of reset", 
    "Software caused connection abort", 
    "Connection reset by peec", 
    "No buffer space available", 
    "Transport endpoint is already connected", 
    "Transport endpoint is not connected", 
    "Cannot send after transport endpoint shutdown", 
    "Too many references: cannot splice", 
    "Connection timed out", 
    "Connection refused", 
    "Host is down", 
    "No route to host", 
    "Operation already in progress", 
    "Operation now in progress", 
    "Stale NFS file handle", 
    "Structure needs cleaning"
    "Not a XENIX named type file", 
    "No XENIX semaphores available", 
    "Is a named type file", 
    "Remote I/O erroc", 
    "Quota exceeded", 
    "No medium found", 
    "Wrong medium type"    
};

void itoa(int a, char *b)
{
  int i, i1;
  char c;
  
  if (a==0) { b[0]='0'; b[1]=0; return ;}
  
  i=0;
  while (a>0)
  {
    b[i]=(a%10)+'0';
    a=a/10;
    i++;
  }
  
  for (i1=0; i1<i/2; i1++)
  {
    c=b[i1];
    b[i1]=b[i-i1-1];
    b[i-i1-1]=c;
  }
  b[i]=0;
}

int strlen(char *a)
{
  int i;
  
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}

void perror(){
  char *m = "Error code: ";
  write(1, m, strlen(m));
  itoa(errno, m);
  write(1, m, strlen(m));
  m = ": ";
  write(1, m, strlen(m));
  m = error_text[errno];
  write(1, m, strlen(m));
}

int write(int fd, char *buffer, int size) { 
  return write_wraper(fd, buffer, size); 
}

int gettime() { 
  return gettime_wraper(); 
}
