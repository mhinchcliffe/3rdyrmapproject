#include <iostream>
#include "MyMap.h"
bool afunction(int i, int j)
{
	if (i > j) return true;
	else return false;
}
int main()
{

	CMyMap<int, int> aMap(&afunction);
	aMap.Emplace(1, 2);
	std::system("pause");
}