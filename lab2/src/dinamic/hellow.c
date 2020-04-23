//helow.c 

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int min()
{}

int max()
{}


int main()
{
	
	int a = fork();
	if(a==0)
	{
		int b = min();
		
	}	
	else printf("%d",a);
	return 0;
}
