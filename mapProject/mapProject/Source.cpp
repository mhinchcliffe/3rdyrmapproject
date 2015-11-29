#include <iostream>
#include "MyMap.h"
#include <map>
bool IntCompFunction(int i, int j)
{
	if (i > j) return true;
	else return false;
}
//tests how the map handles user defined structures
struct TestStruct
{
	int a;
	int b;
	void operator=(const TestStruct&newstruct)
	{
		a = newstruct.a;
		b = newstruct.b;
	}
	bool operator==(const TestStruct&newstruct)
	{
		if (a == newstruct.a&&b == newstruct.b)
		{
			return true;
		}
		else return false;
	}
	friend std::ostream &operator<<(std::ostream &output,
		const TestStruct&newstruct)
	{
		output << newstruct.a << ", " << newstruct.b;
		return output;
	}
};
bool TestStructCompFunction(TestStruct i, TestStruct j)
{
	if (i.a  > j.b)
	{
		return true;
	}
	else return false;
}
int main()
{
	//-test functionality of the map-//
	//series of tests to check if the functions of the map behave as expected
	char* TableSort = "%-8s%-21s%-10s%-17s%-17s%-4s\n";// when put into printf, changes output to look like a table
	printf("Test Program for CMyMap\n");
	printf("testing a table of int, chars\n");
	printf("at test 3, 10 elements are emplaced into the map\n");
	CMyMap<int, char> aMap(&IntCompFunction);
	CMyMap<int, char> testEqualMap(&IntCompFunction);
	CMyMap<TestStruct, int> TestStructKeyMap(&TestStructCompFunction);

	printf(TableSort, "Test", "Method/operator", "Input", "Expected Output","Actual Ouput", "fail?");
	//test 1
	if (aMap.IsEmpty()==true)
	{
		printf(TableSort, "1", "IsEmpty", "N/A", "true", "true", "pass");
	}
	else
	{
		printf(TableSort, "1", "IsEmpty", "N/A", "true", "false", "fail");
	}
	//test 2
	if (aMap.GetSize() == 0)
	{
		printf(TableSort, "2", "GetSize", "N/A", "0", "0", "pass");
	}
	else
	{
		printf(TableSort, "2", "IsEmpty", "N/A", "0", aMap.GetSize(), "fail");
	}
	//test 3
	char insertChar = 'a';
	int Keyvalue = 1;
	for (int i = 0; i < 10; i++)
	{
		aMap.Emplace(Keyvalue+i, insertChar+i);
		testEqualMap.Emplace(Keyvalue + i, insertChar + i*2);
	}
	if (*aMap.GetByKeyValue(Keyvalue) == insertChar)
	{
		try 
		{
			printf(TableSort, "3", "GetByKeyValue", "1", "a", "a", "pass");
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
		}
	}
	else
	{
		try
		{
			printf(TableSort, "3", "GetByKeyValue", "1", "a", aMap.GetByKeyValue(3), "fail");
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
		}
	}
	//test 4
	if (*aMap.GetByIndexValue(0) == 'a')
	{
		try
		{
			printf(TableSort, "4", "GetByIndexValue", "0", "a", "a", "pass");
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
		}
	}
	else
	{
		try
		{
			printf(TableSort, "4", "GetByIndexValue", "0", "a", aMap.GetByIndexValue(0) , "fail");
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
		}
	}
	//test 5
	aMap.EmplaceOrAssign(1, 'z');
	if (*aMap.GetByKeyValue(1) == 'z')
	{
		printf(TableSort, "5", "EmplaceOrAssign", "1,z", "z", "z", "pass");
	}
	else
	{
		printf(TableSort, "5", "EmplaceOrAssign", "1,z", "z",aMap.GetByKeyValue(1), "pass");
	}
	//test 6
	if (aMap.IsEmpty() == false)
	{
		printf(TableSort, "6", "IsEmpty", "N/A", "false", "false", "pass");
	}
	else
	{
		printf(TableSort, "6", "IsEmpty", "N/A", "true", "false", "fail");
	}
	//test 7
	if (aMap.GetSize() == 10)
	{
		printf(TableSort, "7", "GetSize", "N/A", "10", "10", "pass");
	}
	else
	{
		printf(TableSort, "7", "IsEmpty", "N/A", "0", aMap.GetSize(), "fail");
	}
	//test 8
	if (aMap.Begin()->smKey == 1)
	{
		printf(TableSort, "8", "Begin", "N/A", "key value of 1", "key value of 1", "pass");
	}
	else
	{
		printf(TableSort, "8", "Begin", "N/A", "key value of 1","keyvalue isn't 1", "fail");
	}
	//test 9
	if (aMap.End()->smKey == 10)
	{
		printf(TableSort, "9", "End", "N/A", "key value of 10", "key value of 10", "pass");
	}
	else
	{
		printf(TableSort, "9", "End", "N/A", "key value of 10", "keyvalue isn't 10", "fail");
	}
	//test 10
	if (*aMap[0] == 'z')
	{
		printf(TableSort, "10", "[]", "0", "z", "z", "pass");
	}
	else
	{
		printf(TableSort, "10", "[]", "0", "z", aMap[0], "fail");
	}
	//test 11
	aMap.EraseByKey(1);
	if (*aMap.GetByIndexValue(0) == 'b')
	{
		try
		{
			printf(TableSort, "11", "EraseByKey", "1", "index 0 to be 'b'", "index 0 is 'b'", "pass");
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
		}
	}
	else
	{
		try
		{
			printf(TableSort, "11", "EraseByKey", "1", "index 0 to be 'b'", aMap.GetByIndexValue(0), "fail");
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
		}
	}
	//test 12
	aMap.Clear();
	if (aMap.IsEmpty() == true)
	{
		printf(TableSort, "12", "Clear", "N/A", "empty map", "empty map", "pass");
	}
	else
	{
		printf(TableSort, "12", "Clear", "N/A", "empty map", "map not empty", "fail");
	}
	//test 13
	aMap = testEqualMap;
	if (*aMap.GetByIndexValue(0) == *testEqualMap.GetByIndexValue(0))
	{
		printf(TableSort, "13", "= operator", "N/A", "map values equal", "map values equal", "pass");
	}
	else
	{
		printf(TableSort, "13", "= operator", "N/A", "map values equal", "map values not equal", "fail");
	}
	//test 14
	std::cout << "///////////\n";
	std::cout << "testing creation of a map with keytype being a user created struct" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		TestStruct temp;
		temp.a = (5 * i);
		temp.b = i+5;
		TestStructKeyMap.Emplace(temp,i);
		TestStructKeyMap.PrintMap();
		std::cout << "/////////" << std::endl;
	}
	TestStructKeyMap.PrintMap();


	std::system("pause");
}