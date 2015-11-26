#include <iostream>
#include "MyMap.h"
void afunction(int i, int j)
{
	i + i;
}
int main()
{

	CMyMap<int, int> aMap(&afunction);
	std::system("pause");
}