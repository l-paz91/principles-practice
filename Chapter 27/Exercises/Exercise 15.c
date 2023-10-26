// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 15

	Simulate single inheritance in C. let each "base class" contain a pointer to 
	an array of pointers to functions (to simulate virtual functions as freestanding 
	functions taking a pointer to a "base class" object as their first argument); 
	see section 27.2.3. Implement "derivation" by making the "base class" the type 
	of the first member of the derived class. For each class, initialise the array 
	of "virtual functions" appropriately. To test the ideas, implement a version 
	of "the old shape example" with the base and derived draw() just printing out 
	the name of their class. Use only language features and library facilities 
	available in standard C.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

// -----------------------------------------------------------------------------

#include <assert.h>
#include <conio.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------

void keepWindowOpen()
{
	printf("\nPress any key to continue...");
	_getch();
}

// -----------------------------------------------------------------------------

// define the type for our draw function pointer
typedef void(*drawFunc)(void*);

// -----------------------------------------------------------------------------

// the shape "base class"
typedef struct Shape
{
	// this is our virtual function table
	drawFunc* mVtable;
} Shape;

// -----------------------------------------------------------------------------

// draw function for the shape "base class"
void drawShape(void* pShape)
{
	printf("Drawing Shape\n");
}

// -----------------------------------------------------------------------------

// global vtable for the shape "base class"
drawFunc shapeVtable[] = { drawShape };

// -----------------------------------------------------------------------------

// constructor for the shape "base class"
void shapeConstructor(Shape* pShape)
{
	// set the vtable to Shape's vtable
	pShape->mVtable = shapeVtable;
}

// -----------------------------------------------------------------------------

// the circle "derived class"
typedef struct Circle
{
	// this is how we "inherit" from Shape
	Shape mShape;
} Circle;

// -----------------------------------------------------------------------------

// draw function for the circle "derived class"
void drawCircle(void* pCircle)
{
	printf("Drawing Circle\n");
}

// -----------------------------------------------------------------------------

//global vtable for the circle "derived class"
drawFunc circleVtable[] = { drawCircle };

// -----------------------------------------------------------------------------

// constructor for the circle "derived class"
void circleConstructor(Circle* pCircle)
{
	// first call the constructor for the base class
	shapeConstructor(&pCircle->mShape);

	// set the vtable to Circle's vtable
	pCircle->mShape.mVtable = circleVtable;
}

// -----------------------------------------------------------------------------

// function to draw a shape
void draw(void* pShape)
{
	// this calls the appropriate draw function for the object based on its vtable
	((Shape*)pShape)->mVtable[0](pShape);
}

// -----------------------------------------------------------------------------

int main()
{
	// create a shape
	Shape shape;
	Circle circle;

	shapeConstructor(&shape);
	circleConstructor(&circle);

	// draw the shape
	draw(&shape);
	draw(&circle);

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
