#include <iostream>
#include "MyMap.h"
bool afunction(int i, int j)
{
	if (i > j) return true;
	else return false;
}
int main()
{

	CMyMap<int, char> aMap(&afunction);
	aMap.Emplace(4, 'a');
	aMap.Emplace(2, 'c');
	aMap.Emplace(3, 'b');
	std::cout << "test emplace" << std::endl;
	aMap.PrintMap();

	aMap.EraseByKey(2);
	std::cout << "test erase" << std::endl;
	aMap.PrintMap();
	std::cout << "test getByKeyValue" << std::endl;
	std::cout << *aMap.GetByKeyValue(3)<<std::endl;
	std::cout << "test Using getByKeyValue to change mapped value" << std::endl;
	*aMap.GetByKeyValue(3) = 'l';
	std::cout << *aMap.GetByKeyValue(3) << std::endl;

	aMap.EmplaceOrAssign(3, 'J');
	aMap.EmplaceOrAssign(9, 't');
	std::cout << "test EmplaceOrAssign" << std::endl;
	aMap.PrintMap();

	std::cout << "test overloaded[] operator" << std::endl;

	std::cout << *aMap.GetByIndexValue(0)<<std::endl;
	std::cout << *aMap[0] << std::endl;

	//std::cout << "test overloaded = operator" << std::endl;

	//CMyMap<int, char> newMap(&afunction);
	//newMap = aMap;
	//aMap.Clear();
	//newMap.PrintMap();
	std::system("pause");
}