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

	Java
	Built and written using Online Java Compiler IDE 
	https://www.jdoodle.com/online-java-compiler/

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------
import java.util.Scanner;  

public class MyClass 
{
    static boolean checkQuit()
    {
        System.out.print("\nQuit? y / n\n>> ");
        Scanner sc = new Scanner(System.in);   
        char ans = sc.next().charAt(0);  
        if(ans == 'y')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    
    public static void main(String args[]) 
    {
        final double m2k = 1.60934;
        System.out.println("This program converts miles to kilometers.");
        boolean quit = false;
	    double miles = 0.0;
	    
	    Scanner sc = new Scanner(System.in);
	    while(!quit)
	    {
	        System.out.print("\nMiles To Convert: ");
	        miles = sc.nextDouble();
	        System.out.print(">> " + miles*m2k + "km");
	        quit = checkQuit();
	    }
    }
}
