#pragma once
#include "string"
#include "iostream"
#include "ostream"
#include "stdafx.h"

using namespace std;

class CHwTest
{
public:
	static bool getMinChar(string &str,int &iPos,char &chResult)
	{
		int isize = (int)str.size();
		
		char ch;
		if (isize == 1)
		{
			ch = str[0];
			iPos = 0;
		}else if (isize > 1)
		{
			ch = str[0];
			iPos = 0;
			for (int i=1;i<isize;i++)
			{
				if (ch > str[i])
				{
					ch = str[i];
					iPos = i;
				}
			}
		}

		chResult = ch;

		return true;
		
	}

	static bool getMinCharBigger(string &str,int &iPos,char chSrc,char &chResult)
	{
		int isize = (int)str.size();

		char ch;
		bool flag = false;
		if (isize >= 1)
		{			
			for (int i=0;i<isize;i++)
			{
				if (str[i] <= chSrc)
				{
					continue;
				}

				if (!flag)
				{
					ch = str[i];
					iPos = i;
					flag = true;
				}else{
					if (ch > str[i])
					{
						ch = str[i];
						iPos = i;						
					}
				}
				
			}
		}

		if (flag)
		{
			if (chSrc == ch)
			{				
				return false;
			}else{
				chResult = ch;
				return true;
			}
		}else{
			return false;
		}
		

	}
	static void SortStringNum()
	{
		string strSrc;
		//cin>>strSrc;
		strSrc = "eeefgghhh";

		string strResult;
		int isize = (int)strSrc.size();
		int iPos;
		char chSrc,chResult;
		int sizeResult = 0;
		char ch;
		bool flag;
		char chLast;
		while(isize > 0)
		{
			if (sizeResult == 0)
			{
				getMinChar(strSrc,iPos,ch);
				strSrc.erase(iPos,1);
				strResult.push_back(ch);
				chLast = ch;
				sizeResult++;
				isize--;
			}else{
				if (strResult == "efg")
				{
					int yjm = 1;
				}
				flag = getMinCharBigger(strSrc,iPos,chLast,chResult);
				if (flag)
				{
					strSrc.erase(iPos,1);
					strResult.push_back(chResult);
					chLast = chResult;
					sizeResult++;
					isize--;
				}else{
					getMinChar(strSrc,iPos,ch);
					strSrc.erase(iPos,1);
					strResult.push_back(ch);
					chLast = ch;
					sizeResult++;
					isize--;
				}
			}			

		}

		cout<<strResult<<endl;
	}

	

};

#include "vector"

using namespace std;

class Solution {
public:
	int ii;
	int findEx(int &target, vector<vector<int> > &array,int &M,int&N,int m,int n)
	{
		ii++;
		printf("%d,%d\n",m,n);
		if (m<0 || n< 0 || m == M || n == N)
		{
			return 0;
		}

		if (target > array[m][n])
		{
			return findEx(target,array,M,N,m+1,n) + findEx(target,array,M,N,m,n+1);
		}else if (target < array[m][n])
		{
			return findEx(target,array,M,N,m-1,n) + findEx(target,array,M,N,m,n-1);
		}else{
			return 1;
		}
	}

	bool Find(int target, vector<vector<int> > array) {
		ii = 0;
		int irow = array.size();
		int icolumn = array[0].size();
		bool fFind = false;
		int iFirst,iLast;
		int i=0,j=icolumn-1;
		int iFind = findEx(target,array,irow,icolumn,i,j);

		if (iFind)
		{
			return true;
		}else{
			return false;
		}


	}

	static void test()
	{
		Solution sl;

		vector<vector<int> > array;
		vector<int> row;
		for (int i=0;i<10;i++)
		{
			row.clear();
			for (int j=0;j<10;j++)
			{
				row.push_back(i+j);
			}
			array.push_back(row);
		}
		int target = 5;
		bool flag = sl.Find(target,array);
		if (flag)
		{
			printf("true,%d",sl.ii);
		}else{
			printf("false,%d",sl.ii);
		}
	}
};