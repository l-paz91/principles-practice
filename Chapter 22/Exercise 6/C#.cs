// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 22 - Exercise 6

	For each language mentioned in this chapter, look at a popular textbook and 
	see what is used as the first complete program. Write that program in all of 
	the other languages. Warning: This could easily be a 100-program project.

	The exercise I chose is Chapter 3 - Exercise 2:
	"Write a program in C++ that converts from miles to kilometres"

	C#
	Built and written using Visual Studio Community 2019 on Windows 10.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
using System;

namespace Exercise6
{
    class Program
    {
        // ---------------------------------------------------------------------

        static bool checkQuit()
        {
            Console.Write("Quit? y / n \n>>");
            char ans;
            ans = Console.ReadKey().KeyChar;
            if (ans == 'y')
                return true;
            else
                return false;
        }

        // ---------------------------------------------------------------------

        static void Main(string[] args)
        {
            const double m2k = 1.60934;

            Console.WriteLine("This program converts miles to kilometers.");

            bool quit = false;
            double miles = 0.0;

            while(!quit)
            {
                Console.Write("\nMiles To Convert: ");
                miles = Double.Parse(Console.ReadLine());
                Console.WriteLine("\n>>  " + miles * m2k + "km");
                quit = checkQuit();
            }
        }

        // ---------------------------------------------------------------------
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
