#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define eerror(msg) { printf("%s\n", msg); exit(1); }

int main() {
	char buf[30];
		printf("this is s1.c\n");
	//scanf("%s",buf);
	 execlp("ls", "ls", NULL);



	return 0;
}