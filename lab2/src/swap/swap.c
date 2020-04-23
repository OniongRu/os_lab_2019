#include "swap.h"

void Swap(char *left, char *right)
{
	// ваш код здесь
	// ок
	char x = *left;
	*left = *right;
	*right = x;
}
