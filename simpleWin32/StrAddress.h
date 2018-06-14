#pragma once
#include "stdlib.h"
#include "stdio.h"
void testStrAddress()
{	
	char nums[][4] = {
		{"123"},{"23"},{"45"},{"56"}
	};	

	char **newNums;
	int row = 4,column = 10;
	newNums = new char *[row];
	for (int i=0;i<row;i++)
	{
		newNums[i] = new char[column];
		strcpy_s(newNums[i],strlen(nums[i])+1,nums[i]);
	}

	long long1 = atol((char*)newNums[1]);
	
	getchar();

	if (newNums != NULL)
	{
		for (int i=0;i<row;i++)
		{
			delete[] newNums[i];
		}
		delete[] newNums;
	}
	
}