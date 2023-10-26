// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 16

	Use macros to obscure (simplify the notation for) the implementation in the 
	previous exercise.

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

// macros to define and declare methods
#define DECLARE_METHOD(TYPE, METHOD) void TYPE ## _ ## METHOD(TYPE* pThis)
#define INVOKE_METHOD(OBJECT, METHOD) ((*(OBJECT)).vtable->METHOD(OBJECT))

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
typedef struct Shape Shape;

struct Shape 
{
	struct ShapeVTable 
	{
		void (*draw)(Shape*);
	} *vtable;
};

// -----------------------------------------------------------------------------

// the circle "derived class"
typedef struct Circle Circle;

struct Circle 
{
	Shape base;
};

// -----------------------------------------------------------------------------

// function prototypes for Shape and Circle draw methods
DECLARE_METHOD(Shape, draw);
DECLARE_METHOD(Circle, draw);

// -----------------------------------------------------------------------------

// vtables
struct ShapeVTable Shape_vtable = { Shape_draw };
struct ShapeVTable Circle_vtable = { (void (*)(Shape*)) Circle_draw };

// -----------------------------------------------------------------------------

// function implementations for Shape and Circle draw methods
void Shape_draw(Shape* pThis) 
{
	printf("Shape::draw()\n");
}

// -----------------------------------------------------------------------------

void Circle_draw(Circle* pThis) 
{
	printf("Circle::draw()\n");
}

// -----------------------------------------------------------------------------

// Constructors
void Shape_constructor(Shape* pShape) 
{
	pShape->vtable = &Shape_vtable;
}

// -----------------------------------------------------------------------------

void Circle_constructor(Circle* pCircle) 
{
	Shape_constructor((Shape*)pCircle);
	pCircle->base.vtable = &Circle_vtable;
}

// -----------------------------------------------------------------------------

int main()
{
	Shape s;
	Circle c;

	Shape_constructor(&s);
	Circle_constructor(&c);

	INVOKE_METHOD(&s, draw);  // Outputs: Drawing Shape
	INVOKE_METHOD(&(c.base), draw);  // Outputs: Drawing Circle

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
