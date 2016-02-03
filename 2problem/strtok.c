#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	char buf[128]="c1 s1";
	char *str1,*str2;
	str1=strtok(buf," ");
	str2=strtok(NULL," ");
	printf("%s\n",str1 );
	printf("%s\n",str2 );

}