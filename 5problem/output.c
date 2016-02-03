#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
			char buf[1024];
	int ofd=open("out.dat",0666);
	while(1)
	{
		memset(buf,1024,'\0');
		read(ofd,buf,1024);
		printf("%s\n",buf);
	}
}