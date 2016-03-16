#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define eerror(msg) { printf("%s\n", msg); exit(1); }

int main() {
	char buf[1024];
		//printf("this is s1.c\n");
		//printf("enter the option : \n 1. '.' \n 2. -l \n 3. /home \n");
		//scanf("%s",buf);
	write(1,"hii brodas",128);
		 read(0,buf,1024);
		 printf("%s\n",buf );
		 sleep(2);
		execlp("ls", "ls",buf, NULL);
			eerror("execlp error");
	return 0;
}