#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define ssfifo "file1.dat"
#define error(msg) { printf("this is an error in creating sfifo"); exit(1); }
#define eerror(msg) { printf("%s\n", msg); exit(1); }   

int main()
{

	char buf[128]; 
 	int fd = open("ssfifo", O_WRONLY);
     if(fd == -1) eerror("open() error");
     while(1) 
     {
     	memset(buf, 128, '\0');
     	scanf("%s", buf);
     	write(fd, buf, 128);
     }
}