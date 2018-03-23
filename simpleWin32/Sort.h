#pragma once
#include "stdafx.h"
#include "RecordTime.hpp"
//À„∑®≤‚ ‘

static int sortNum = 10;
static int oriNum[] = {12,15,26,5,24,14,88,50,10};
static int desNum[10];

void PrintSortedResult(int desNum[],int sortNum)
{
	printf("Sorted Array Result is£∫\n");
	for (int i=0;i<sortNum;i++)
	{
		printf("%d",desNum[i]);
		if (i <sortNum -1)
		{
			printf(" ");
		}else{
			printf("\n");
		}
	}
}