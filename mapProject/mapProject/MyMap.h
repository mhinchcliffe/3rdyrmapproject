#pragma once
template <class tKeyClass, class tMappedClass> class CMyMap
{
public:
	//the the datatype being stored in the map
	struct SValueType
	{
		tKeyClass smKey;
		tMappedClass smMappedValue;
	};

private:
	SValueType* mpFirst;//pointer to the first element in the map
	int mSize;//the size of the map
	typedef void (*fpComparrisonFunction)(tKeyClass, tKeyClass);
	fpComparrisonFunction fpCompare;//function to compare two keytypes. returns true if first value is higher, false otherwise
public:
	
	CMyMap(tKeyClass KeyType, tMappedClass MappedType, &void NewComparrisonFunction(tKeyClass,tKeyClass));
	~CMyMap();

	// - Getters - //
	SValueType* Begin();//returns a pointer to the beggining of the array
	bool IsEmpty();//returns true if the map is empty
	int GetSize();//returns the number of elements in the map

	// - Interface Functions - //
	//inserts a new element into the map, 
	//if it doesn't already exists. returns true if inserted, false otherwise
	bool Insert(SValueType* newElement);

	//creates and inserts a new element if the new key doesnt already exist in the map
	//returns true if a new element is created and inserted, false otherwise
	bool Emplace(tKeyClass Key, tMappedClass mapedValue);

	//removes an element with the given key from the map
	//returns true if the element was found and removed, false otherwise
	bool Erase(tKeyClass Key);

	//removes and deletes all the elements in the current map
	void Clear();
};

// - Constructor - //
template<class tKeyClass, class tMappedClass>
CMyMap<tKeyClass, tMappedClass>::CMyMap(tKeyClass KeyType, tMappedClass MappedType, &void NewComparrisonFunction(tKeyClass, tKeyClass))
{
	mSize = 0;
	fpCompare = NewComparrisonFunction;
	//todo?
}

// - Destructor - //
template<class tKeyClass, class tMappedClass>
CMyMap<tKeyClass, tMappedClass>::~CMyMap()
{
	//todo
}

// - Getters - //
template<class tKeyClass, class tMappedClass>
SValueType * CMyMap<tKeyClass, tMappedClass>::Begin()
{
	return mpFirst;
}

template<class tKeyClass, class tMappedClass>
bool CMyMap<tKeyClass, tMappedClass>::IsEmpty()
{
	if (mSize == 0)
	{
		return true;
	}
	else return false;
}

template<class tKeyClass, class tMappedClass>
int CMyMap<tKeyClass, tMappedClass>::GetSize()
{
	return mSize;
}

// - Interface Functions - //
template<class tKeyClass, class tMappedClass>
inline bool CMyMap<tKeyClass, tMappedClass>::Insert(SValueType * newElement)
{
	
	return false;//todo
}

template<class tKeyClass, class tMappedClass>
inline bool CMyMap<tKeyClass, tMappedClass>::Emplace(tKeyClass Key, tMappedClass mapedValue)
{
	return false;//todo
}

template<class tKeyClass, class tMappedClass>
inline bool CMyMap<tKeyClass, tMappedClass>::Erase(tKeyClass Key)
{
	return false;//todo
}

template<class tKeyClass, class tMappedClass>
inline void CMyMap<tKeyClass, tMappedClass>::Clear()
{
	//todo
}