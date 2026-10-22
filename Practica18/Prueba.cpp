#include "Debug.h"
#include <iostream>

int main()
{
	for(int i = 0; i < 5; ++i)
	{
		printf("I is %d\n", i);
		ASSERT(i < 4);
	}
}