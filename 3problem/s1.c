#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define ssfifo "si.dat"
#define eerror(msg) { printf("%s\n", msg); exit(1); }

int main() {
	char buf[30];


	printf("this is s1.c\n");
	    int fd = open(ssfifo,O_WRONLY);
        if(fd == -1) eerror("ssfifo error");
        printf("ssfifo opened in write mode\n");    

    dup2(fd,1);    
	execlp("ls", "ls", NULL);



	return 0;
}