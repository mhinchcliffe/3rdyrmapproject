#pragma once
#include <iostream>

template <typename tKey, typename tMValue> class CMyMap
{
public:
	//the datatype being stored in the map
	struct SValueType
	{
		tKey smKey;
		tMValue smMappedValue;
	};

	//Comparison function
	typedef bool(*fpComparrisonFunction)(tKey, tKey);
	fpComparrisonFunction fpCompare;//function to compare two keytypes. returns true if first value is higher, false otherwise
private:
	// - Iterrators - //
	SValueType* mpFirst;//pointer to the first element in the map
	SValueType* mpLast;//pointer to the last element in the map
	SValueType* mpItter;//pointer to the valuetypes held in the map. used to loop through the mapped values

	// - other values - //
	int mSize;//the size of the map
	
public:
	CMyMap(fpComparrisonFunction compFunc);
	~CMyMap();

	// - Getters - //
	bool IsEmpty();//returns true if the map is empty
	int  GetSize();//returns the number of elements in the map

	//returns a pointer to the first element of the map
	SValueType* Begin()
	{
		return mpFirst;
	}

	//returns a pointer to the last element of the map
	SValueType* End()
	{
		return mpLast;
	}

	//returns a pointer to the mapped value associated with the given key,
	//returns nullptr if no such key exists
	tMValue* GetByKeyValue(tKey key); 

	//returns a pointer to the mapped value at the given index in the map,
	//returns nullptr if index is out of range of the map
	tMValue* GetByIndexValue(int i);

	// - Overloaded Operators - //
	tMValue* operator[](int index)
	{
		return GetByIndexValue(index);
	}

	void operator=(const CMyMap &aMap)
	{
		Clear();
		mSize = aMap.mSize;
		mpFirst = new SValueType[mSize];
		mpLast = mpFirst + mSize - 1;
		for (int i = 0; i < mSize; i++)
		{
			*(mpFirst + i) = *(aMap.mpFirst + i);
		}
	}

	// - Interface Functions - //
	//inserts a new element into the map, 
	//if it doesn't already exists. returns true if inserted, false otherwise
	bool Insert(SValueType* newElement);

	//if it doesn't already exists, it inserts it into the map.
	//if it already exists, it changes the mapped value to the new mapeed value
	void InsertOrAssign(SValueType* newElement);

	//creates and inserts a new element if the new key doesnt already exist in the map
	//returns true if a new element is created and inserted, false otherwise
	bool Emplace(tKey Key, tMValue mapedValue);

	//creates and inserts a new element if the new key doesnt already exist in the map
	//If the new key already exists, updates the mapped value to the newly offered mapped value
	void EmplaceOrAssign(tKey Key, tMValue mapedValue);

	//removes an element with the given key from the map
	//returns true if the element was found and removed, false otherwise
	bool EraseByKey(tKey Key);

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
	mpItter = nullptr;
	mpFirst = nullptr;
	mpLast = nullptr;
}

// - Destructor - //
template<class tKey, class tMValue>
CMyMap<tKey, tMValue>::~CMyMap()
{
	Clear();
}

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

template<typename tKey, typename tMValue>
inline tMValue * CMyMap<tKey, tMValue>::GetByKeyValue(tKey key)
{
	for (int i = 0; i < mSize;i++)
	{
		if ((mpFirst+i)->smKey == key)
		{
			return &(mpFirst + i)->smMappedValue;
		}
	}
	throw "Key not found";
}

template<typename tKey, typename tMValue>
inline tMValue * CMyMap<tKey, tMValue>::GetByIndexValue(int i)
{
	if (i >= mSize||i<0)
	{
		throw "provided index is outside of the maps range";
	}
	return &(mpFirst + i)->smMappedValue;
}

// - Interface Functions - //
template<class tKey, class tMValue>
inline bool CMyMap<tKey, tMValue>::Insert(SValueType * newElement)
{
	int placeOfInsert = 0;
	for (int i = 0; i < mSize; i++)
	{
		if ((mpFirst + i)->smKey == newElement->smKey)
		{
			throw "Key already exists in map";
		}
		else if (!fpCompare((mpFirst + i)->smKey, newElement->smKey))
		{
			placeOfInsert++;
		}
	}
	SValueType* temp = new SValueType[mSize + 1];
	for (int i = 0; i < mSize+1; i++)
	{
		if (i != placeOfInsert)
		{
			if (i != mSize)
			{
				*(temp + i) = *(mpFirst + i);
			}
			else
			{
				*(temp + i) = *mpLast;
			}
		}
		else
		{
			*(temp + i) = *newElement;
			if (i < mSize)
			{
				*(temp + i+1) = *(mpFirst + i);
				i++;
			}		
		}
	}
	int newsize = mSize + 1;
	Clear();
	mSize=newsize;	
	mpFirst = temp;
	mpLast = temp + (mSize-1);
	return true;
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
inline bool CMyMap<tKey, tMValue>::EraseByKey(tKey Key)
{
	bool isInMap = false;
	int Position=0;
	for (mpItter = mpFirst; mpItter != mpLast&&!isInMap; mpItter++)
	{
		Position++;
		if (mpItter->smKey == Key)
		{
			isInMap = true;
			Position--;
		}
	}
	if (isInMap)
	{
		SValueType* temp = new SValueType[mSize - 1];
		mpItter = mpFirst;
		for (int i = 0; i < mSize-1; i++)
		{
			if (i!=Position)
			{
				*(temp + i) = *(mpItter);
				mpItter++;
			}
			else
			{
				mpItter++;
				*(temp + i) = *(mpItter);
				mpItter++;
			}
		}
		int newSize = mSize - 1;
		Clear();
		mSize=newSize;
		mpFirst = temp;
		mpLast = (temp + mSize - 1);
	}
	return isInMap;
}

template<class tKey, class tMValue>
inline void CMyMap<tKey, tMValue>::Clear()
{
	if (mpFirst != nullptr)
	{
		delete[] mpFirst;
	}
	mSize = 0;
	mpFirst = nullptr;
	mpLast = nullptr;
	mpItter = nullptr;
}

template<typename tKey, typename tMValue>
inline void CMyMap<tKey, tMValue>::PrintMap()
{
	for (mpItter = mpFirst; mpItter <= mpLast; mpItter++)
	{
		std::cout <<"key:  "<<mpItter->smKey<<", value: "<<mpItter->smMappedValue <<std::endl;
	}
}

template<typename tKey, typename tMValue>
inline void CMyMap<tKey, tMValue>::InsertOrAssign(SValueType * newElement)
{
	int placeOfInsert = 0;
	for (int i = 0; i < mSize; i++)
	{
		if ((mpFirst + i)->smKey == newElement->smKey)
		{
			(mpFirst + i)->smMappedValue = newElement->smMappedValue;
			return;
		}
		else if (!fpCompare((mpFirst + i)->smKey, newElement->smKey))
		{
			placeOfInsert++;
		}
	}
	SValueType* temp = new SValueType[mSize + 1];
	for (int i = 0; i < mSize + 1; i++)
	{
		if (i != placeOfInsert)
		{
			if (i != mSize)
			{
				*(temp + i) = *(mpFirst + i);
			}
			else
			{
				*(temp + i) = *mpLast;
			}
		}
		else
		{
			*(temp + i) = *newElement;
			if (i < mSize)
			{
				*(temp + i + 1) = *(mpFirst + i);
				i++;
			}
		}
	}
	int newsize = mSize + 1;
	Clear();
	mSize= newsize;
	mpFirst = temp;
	mpLast = temp + (mSize - 1);
}

template<typename tKey, typename tMValue>
inline void CMyMap<tKey, tMValue>::EmplaceOrAssign(tKey Key, tMValue mapedValue)
{
	SValueType* temp = new SValueType;
	temp->smKey = Key;
	temp->smMappedValue = mapedValue;
	InsertOrAssign(temp);
	delete temp;
}