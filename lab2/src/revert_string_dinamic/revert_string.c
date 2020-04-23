#include "revert_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RevertString(char *str)
{
        int n =strlen(str);
        char *arr = malloc(sizeof(char) * n);
        int j=0;
        for(int i=n-1;i>=0;i--)
        {
                arr[j] = str[i];
                j=j+1;
        }
	for(int i=0;i<n;i++)
		str[i]=arr[i];
	free(arr);

}

