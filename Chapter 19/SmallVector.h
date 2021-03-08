// -----------------------------------------------------------------------------
#ifndef SMALLVECTOR_H_
#define SMALLVECTOR_H_
// -----------------------------------------------------------------------------

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//----INCLUDES----//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

template<typename T>
class VectorRep
{
public:
	// ------ constructors

	//defaults
	VectorRep() : mCapacity(0), mSize(0), mElements(nullptr) {}
	explicit VectorRep(int pSize) : mCapacity(pSize), mSize(pSize)
	{
		T* elements = DBG_NEW T[mSize];
		mElements = elements;
		for (int i = 0; i < mSize; ++i)
			mElements[i] = T();
	}

	~VectorRep() 
	{ 
		delete[] mElements; 
		cout << "VectorRep destructor" << endl;
	}

	//copy
	VectorRep(const VectorRep& pVec)
		: mCapacity(pVec.mCapacity), mSize(pVec.mSize)
	{
		T* elements = DBG_NEW T[mSize];
		mElements = elements;
		for (int i = 0; i < pVec.mSize; ++i)
			mElements[i] = pVec[i];
	}

	//move
	VectorRep(VectorRep&& pVec)
		: mCapacity(pVec.mCapacity), mSize(pVec.mSize), mElements(pVec.mElements) 
	{
		pVec.mCapacity = 0;
		pVec.mSize = 0;
		pVec.mElements = nullptr;
	}

	// ------ operators

	//copy
	VectorRep& operator=(const VectorRep& pVec)
	{
		// self assignment, no work needed
		if (this == &pVec)
			return *this;

		// enough space, no need for new allocation
		if (pVec.mSize <= mCapacity)
		{
			for (uint32_t i = 0; i < pVec.mSize; ++i)
				mElements[i] = pVec[i];
			mSize = pVec.mSize;
			return *this;
		}

		// not enough space. Get more space
		// let reserve deal with memory allocation
		reserve(pVec.mSize);

		// now copy elements over. mElements and pVec should be same size
		for (int i = mSize; i < pVec.mSize; ++i)
			mElements[i] = pVec[i];

		// return self-reference
		return *this;
	}

	//move
	VectorRep& operator=(VectorRep&& pVec)
	{
		// deallocate old space
		delete[] mElements;

		// copy pVec's elements and size
		mElements = pVec.mElements;
		mSize = pVec.mSize;
		mCapacity = pVec.mCapacity;

		// empty pVec
		pVec.mCapacity = 0;
		pVec.mSize = 0;
		pVec.mElements = nullptr;

		return *this;
	}

	T& operator[](int pIndex)
	{
		if (pIndex < 0 || mSize <= pIndex)
			throw Range_error(pIndex);
		return mElements[pIndex];
	}

	const T& operator[](int pIndex) const
	{
		if (pIndex < 0 || mSize <= pIndex)
			throw Range_error(pIndex);
		return mElements[pIndex];
	}

	// ------ methods
	void resize(int pNewSize, T pItem = T());
	void pushBack(const T& pItem);
	void reserve(int pNewAllocation);
	int size() { return mSize; }

	// ------ members
	int mCapacity;
	int mSize;
	T* mElements;
};

// -----------------------------------------------------------------------------

template<typename T>
void VectorRep<T>::resize(int pNewSize, T pItem)
{
	if (pNewSize < 0)
		error("New size of vector cannot be below 0.");

	reserve(pNewSize);
	for (int i = mSize; i < pNewSize; ++i)
		mElements[i] = 0;	// construct with defaults after old size

	for (int i = pNewSize; i < mSize; ++i)
	{
		T* p = &mElements[i];	// destroy - if new size is smaller, null out the values found there
		p->~T();
	}
	
	mSize = pNewSize;
}

// -----------------------------------------------------------------------------

template<typename T>
void VectorRep<T>::pushBack(const T& pItem)
{
	if (mCapacity == 0)
		reserve(8);				// start with space for 8 elements
	else if (mSize == mCapacity)
		reserve(2 * mCapacity);	// get more space

	mElements[mSize] = pItem;		// add item at the end
	++mSize;					// increase the size
}

// -----------------------------------------------------------------------------

template<typename T>
void VectorRep<T>::reserve(int pNewAllocation)
{
	if (pNewAllocation <= mCapacity)
		return;												// never decrease allocation

	T* newElements = DBG_NEW T[pNewAllocation];				// allocate new space

	for (int i = 0; i < mSize; ++i)
		newElements[i] = mElements[i];						// copy

	for (int i = 0; i < mSize; ++i)
	{
		T* p = &mElements[i];						// destroy 
		p->~T();
	}								

	delete[] mElements;										// deallocate old space
	mElements = newElements;
	mCapacity = pNewAllocation;
}

// -----------------------------------------------------------------------------

template<typename T>
class SmallVector
{
public:
	// ---- constructors -------------------------------------------------------
	SmallVector() : mVector(DBG_NEW VectorRep<T>()) {}
	explicit SmallVector(int pSize) 
		: mVector(DBG_NEW VectorRep<T>(pSize)) {}

	~SmallVector() 
	{
		if (mVector)
		{
			delete mVector;
		}

		cout << "SmallVector destructor" << endl; 
	}

	// copy
	SmallVector(const SmallVector& pVec)
	{
		mVector = DBG_NEW VectorRep<T>(pVec.mVector->mSize);
		for (int i = 0; i < pVec.mVector->mSize; ++i)
			mVector->mElements[i] = pVec.mVector->mElements[i];
	}

	//move
	SmallVector(SmallVector&& pVec)
	{ 
		mVector = pVec.mVector;

		pVec.mVector = nullptr; 
	}

	// ---- operators ----------------------------------------------------------

	// copy
	SmallVector& operator=(const SmallVector& pVec)
	{
		// self assignment, no work needed
		if (this == &pVec)
			return *this;

		mVector = pVec.mVector;

		return *this;
	}

	// move
	SmallVector& operator=(SmallVector&& pVec)
	{
		delete mVector;

		mVector = pVec.mVector;

		pVec.mVector = nullptr;

		return *this;
	}

	T& operator[](int pIndex)
	{
		return mVector->mElements[pIndex];
	}

	const T& operator[](int pIndex) const
	{
		return mVector->mElements[pIndex];
	}

	// ---- methods ------------------------------------------------------------
	void resize(int pNewSize, T pItem = T()) { mVector->resize(pNewSize, pItem); }
	void pushBack(const T& pItem) { mVector->pushBack(pItem); }
	void reserve(int pNewAllocation) { mVector->reserve(pNewAllocation); }
	int size() { return mVector->mSize; }

	// ---- members ------------------------------------------------------------
	VectorRep<T>* mVector;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SMALLVECTOR_H_
