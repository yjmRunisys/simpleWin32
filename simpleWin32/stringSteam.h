#pragma once
#include "string"
#include "sstream"
using namespace std;

void testStringStream()
{
 	stringstream mStream;
 	mStream<<1;
 	string str = mStream.str();
 
 	cout<<str;
 	//getchar();
	system("pause");
}