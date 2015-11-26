#pragma once
#include <iostream>

template <typename tKey, typename tMValue> class CMyMap
{
public:
	/*the the datatype being stored in the map*/
	struct SValueType
	{
		tKey smKey;
		tMValue smMappedValue;
	};
	typedef bool(*fpComparrisonFunction)(tKey, tKey);
private:
	SValueType* mpFirst;//pointer to the first element in the map
	int mSize;//the size of the map
	fpComparrisonFunction fpCompare;//function to compare two keytypes. returns true if first value is higher, false otherwise
public:
	
	CMyMap(fpComparrisonFunction compFunc);
	~CMyMap();

	// - Getters - //
	//SValueType* Begin();//returns a pointer to the beggining of the array
	bool IsEmpty();//returns true if the map is empty
	int GetSize();//returns the number of elements in the map

	// - Interface Functions - //
	//inserts a new element into the map, 
	//if it doesn't already exists. returns true if inserted, false otherwise
	bool Insert(SValueType* newElement);

	//creates and inserts a new element if the new key doesnt already exist in the map
	//returns true if a new element is created and inserted, false otherwise
	bool Emplace(tKey Key, tMValue mapedValue);

	//removes an element with the given key from the map
	//returns true if the element was found and removed, false otherwise
	bool Erase(tKey Key);

	//removes and deletes all the elements in the current map
	void Clear();

	//Print contents of the map
	void PrintMap();
};

// - Constructor - //
template<class tKey, class tMValue>
CMyMap<tKey, tMValue>::CMyMap(fpComparrisonFunction compFunc)
{
	mSize = 0;
	fpCompare = compFunc;
	//todo?
}

// - Destructor - //
template<class tKey, class tMValue>
CMyMap<tKey, tMValue>::~CMyMap()
{
	//todo
}

//// - Getters - //
//template<class tKey, class tMValue>
//SValueType* CMyMap<tKey, tMValue>::Begin()
//{
//	return mpFirst;
//}

template<class tKey, class tMValue>
bool CMyMap<tKey, tMValue>::IsEmpty()
{
	if (mSize == 0)
	{
		return true;
	}
	else return false;
}

template<class tKey, class tMValue>
int CMyMap<tKey, tMValue>::GetSize()
{
	return mSize;
}

// - Interface Functions - //
template<class tKey, class tMValue>
inline bool CMyMap<tKey, tMValue>::Insert(SValueType * newElement)
{
	int place = 0;
	for (int i = 0; i < mSize; i++)
	{
		if ((mpFirst + i)->smKey == newElement->smKey)
		{
			return false;
		}
		else if (!fpCompare((mpFirst + i)->smKey, newElement->smKey))
		{
			place++;
		}
	}
	SValueType* temp = new SValueType[mSize + 1];
	for (int i = 0; i < mSize+1; i++)
	{
		if (i != place)
		{
			*(temp+i) = *(mpFirst + i);
		}
		else
		{
			*(temp + i) = *newElement;
			if (i != mSize)
			{
				i++;
				*(temp + i) = *(mpFirst + i);
			}
			
		}
	}
	Clear();
	mSize++;	
	mpFirst = temp;
	return true;//todo
}

template<class tKey, class tMValue>
inline bool CMyMap<tKey, tMValue>::Emplace(tKey Key, tMValue mapedValue)
{
	SValueType* temp = new SValueType;
	temp->smKey = Key;
	temp->smMappedValue = mapedValue;
	if (Insert(temp))
	{
		delete temp;
		return true;
	}
	else
	{
		delete temp;
		return false;
	}
}

template<class tKey, class tMValue>
inline bool CMyMap<tKey, tMValue>::Erase(tKey Key)
{
	return false;//todo
}

template<class tKey, class tMValue>
inline void CMyMap<tKey, tMValue>::Clear()
{
	for (int i = 0; i < mSize; i++)
	{
		if (mpFirst)
		{
			delete (mpFirst+i);
		}
	}
	mpFirst = nullptr;
	//todo
}

template<typename tKey, typename tMValue>
inline void CMyMap<tKey, tMValue>::PrintMap()
{
	for (int i = 0; i < mSize; i++)
	{
		std::cout << (mpFirst+i)->smKey<<std::endl;
	}
}