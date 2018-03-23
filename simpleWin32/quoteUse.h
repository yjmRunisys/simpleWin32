#pragma once
//引用类型

#include <iostream>  
using namespace std;  
int jQuote=3;//j是全局变量  
int val()   
{   

	int i = 1;   
	return i;   
}   
int & ref()   
{   
	//   int j=3;j不能是局部变量！  
	int &i = jQuote;   
	return i; //不能返回局部对象的引用  
}   

int testQuote()
{

	int   vv = val();   
	int   rv = val();//int   &rv = val()错误！val()返回的是一个int型的数，而给引用&rv 赋值的必须是一个同类型的变量。  
	int   vr = ref();   
	int & rr = ref(); 

	cout<<"jQuote--Address:"<<&jQuote<<"--Value:"<<jQuote<<endl;
	cout<<"vv--Address:"<<&vv<<"--Value:"<<vv<<endl;  
	cout<<"rv--Address:"<<&rv<<"--Value:"<<rv<<endl;  
	cout<<"vr--Address:"<<&vr<<"--Value:"<<vr<<endl;  
	cout<<"rr--Address:"<<&rr<<"--Value:"<<rr<<endl; 

	return 0;  
}   