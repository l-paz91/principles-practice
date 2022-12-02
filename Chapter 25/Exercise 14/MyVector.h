// -----------------------------------------------------------------------------
#ifndef MYVECTOR_H_
#define MYVECTOR_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"
#include <type_traits>

// -----------------------------------------------------------------------------

template<typename T>
class MyAllocator
{
public:
	// allocate memory of a size suitable to hold an object of type T without initialising
	// allocate space for n objects of type T
	T* allocate(int n)
	{
		T* elements;
		elements = (T*)malloc(sizeof(T) * n);	// on pg1044, Bjarne says doing it without the cast should be avoided
		if (!elements)
			error("Could not allocate memory");
		return elements;
	}

	// deallocate uninitialised space of a size suitable for an object of type T
	// deallocate n objects of type T starting at p
	void deallocate(T* p, int n)
	{
		// return all the space that was previously allocated
		// don't know what the n is used for as free() releases a block of memory allocated at p
		free(p);
	}

	// construct an object of type T in uninitialised space
	// construct a T with the value v in p
	void construct(T* p, const T& v)
	{
		// space should already have been allocated, use placement new here
		new(p) T(v);	// copy v to p
	}

	// destroy an object of type T, thus returning its space to the uninitialised state
	// destroy the T in p
	void destroy(T* p)
	{
		// destroys data on a memory location which makes the object not usable 
		// but the memory is still there for use (object can be constructed again)
		p->~T();
	}
};

// -----------------------------------------------------------------------------

// give vector an allocator parameter
template<typename T, typename A = MyAllocator<T>>
class MyVector
{
public:
	// ---- constructors
	MyVector(int pAllocationSize = 0) 
		: mSize{ 0 }
		, mSpace{ 0 }
		, mElements{ nullptr } 
	{
		if (pAllocationSize > 0)
		{
			reserve(pAllocationSize);
		}
	}

	explicit MyVector(int pAllocationSize = 0, int pNumElements = 0) 
		: mSize{ pNumElements }
		, mSpace{ pNumElements }
		, mElements{ mAlloc.allocate(pNumElements) }
	{
		if (pAllocationSize > pNumElements)
		{
			reserve(pAllocationSize);
		}

		for (int i = 0; i < mSize; ++i)
			mAlloc.construct(&mElements[i], T());
	}

	~MyVector() { cout << "Destructor called" << endl; mAlloc.deallocate(mElements, mSize); }

	// copy constructor
	MyVector(const MyVector& pVec)
		: mSize(pVec.size()), mSpace(pVec.maxCapacity()), mElements(mAlloc.allocate(pVec.maxCapacity()))
	{
		for (int i = 0; i < pVec.size(); ++i)
			mAlloc.construct(&mElements[i], pVec[i]);
	}

	// move constructor
	MyVector(MyVector&& pVec)
		: mSize(pVec.size()), mSpace(pVec.maxCapacity()), mElements(pVec.getData())
	{
		pVec.clearVector();
	}

	// ---- operators

	// copy assignment
	MyVector& operator=(const MyVector& pVec)
	{
		// self assignment, no work needed
		if (this == &pVec)
			return *this;

		if (pVec.size() <= mSpace)
		{
			// enough space, no need for new allocation
			for (uint32_t i = 0; i < pVec.size(); ++i)
				mElements[i] = pVec[i];
			mSize = pVec.size();
			return *this;
		}

		// let reserve deal with memory allocation
		reserve(pVec.size());

		// now copy elements over. mElements and pVec should be same size
		for (int i = mSize; i < pVec.size(); ++i)
			mElements[i] = pVec[i];

		// return self-reference
		return *this;
	}

	// move assignment
	MyVector& operator=(MyVector&& pVec)
	{
		// deallocate old space
		mAlloc.deallocate(mElements, mSize);

		// copy pVec's elements and size
		mElements = pVec.getData();
		mSize = pVec.size();
		mSpace = pVec.maxCapacity();

		// empty pVec
		pVec.clearVector();

		return *this;
	}

	T& operator[](int pIndex)									// range checked access: return reference
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

	// ---- methods
	void resize(int pNewSize, T pItem = T());									// for growth
	void pushBack(const T& pItem);
	void reserve(int pNewAllocation);
	void clearVector() { mSize = 0; mSpace = 0; mElements = nullptr; }
	int size() const { return mSize; }
	int maxCapacity() const { return mSpace; }
	T* getData() const { return mElements; }
	T& first() const { return &mElements[0]; }
	T& last() const { return &mElements[mSize - 1]; }

private:
	int mSize;			// the size
	int mSpace;			// size + free space
	T* mElements;		// a pointer to the elements
	A   mAlloc;			// use allocate to handle memory for elements
};

// -----------------------------------------------------------------------------

template<typename T, typename A>
inline void MyVector<T, A>::resize(int pNewSize, T pItem)
{
	if (pNewSize < 0)
		error("New size of vector cannot be below 0.");

	reserve(pNewSize);
	for (int i = mSize; i < pNewSize; ++i)
		mAlloc.construct(&mElements[i], pItem);		// construct with defaults of T after old size

	for (int i = pNewSize; i < mSize; ++i)
		mAlloc.destroy(&mElements[i]);				// destroy - if new size is smaller, null out the values found there

	mSize = pNewSize;
}

// -----------------------------------------------------------------------------

template<typename T, typename A>
void MyVector<T, A>::pushBack(const T& pItem)
{
	if (mSpace == 0)
		reserve(8);				// start with space for 8 elements
	else if (mSize == mSpace)
		reserve(2 * mSpace);	// get more space

	mAlloc.construct(&mElements[mSize], pItem);		// add item at the end
	++mSize;					// increase the size
}

// -----------------------------------------------------------------------------

template<typename T, typename A>
void MyVector<T, A>::reserve(int pNewAllocation)
{
	if (pNewAllocation <= mSpace)
		return;												// never decrease allocation

	T* newElements = mAlloc.allocate(pNewAllocation);		// allocate new space

	for (int i = 0; i < mSize; ++i)
		mAlloc.construct(&newElements[i], mElements[i]);	// copy

	for (int i = 0; i < mSize; ++i)
		mAlloc.destroy(&mElements[i]);						// destroy aka call destructor of item

	mAlloc.deallocate(mElements, mSpace);					// deallocate old space
	mElements = newElements;
	mSpace = pNewAllocation;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MYVECTOR_H_
