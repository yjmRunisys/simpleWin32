#pragma once
//��������

#include <iostream>  
using namespace std;  
int jQuote=3;//j��ȫ�ֱ���  
int val()   
{   

	int i = 1;   
	return i;   
}   
int & ref()   
{   
	//   int j=3;j�����Ǿֲ�������  
	int &i = jQuote;   
	return i; //���ܷ��ؾֲ����������  
}   

int testQuote()
{

	int   vv = val();   
	int   rv = val();//int   &rv = val()����val()���ص���һ��int�͵�������������&rv ��ֵ�ı�����һ��ͬ���͵ı�����  
	int   vr = ref();   
	int & rr = ref(); 

	cout<<"jQuote--Address:"<<&jQuote<<"--Value:"<<jQuote<<endl;
	cout<<"vv--Address:"<<&vv<<"--Value:"<<vv<<endl;  
	cout<<"rv--Address:"<<&rv<<"--Value:"<<rv<<endl;  
	cout<<"vr--Address:"<<&vr<<"--Value:"<<vr<<endl;  
	cout<<"rr--Address:"<<&rr<<"--Value:"<<rr<<endl; 

	return 0;  
}   