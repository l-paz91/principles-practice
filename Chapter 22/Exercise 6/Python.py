#// -----------------------------------------------------------------------------
#// https://lptcp.blogspot.com/
#// 
#/*
#	Chapter 22 - Exercise 6
#
#	For each language mentioned in this chapter, look at a popular textbook and 
#	see what is used as the first complete program. Write that program in all of 
#	the other languages. Warning: This could easily be a 100-program project.
#
#	The exercise I chose is Chapter 3 - Exercise 2:
#	"Write a program in C++ that converts from miles to kilometres"
#
#	Python
#	Built and written using Visual Studio Community 2019 on Windows 10.
#
#*/
#// https://github.com/l-paz91/principles-practice/
#// -----------------------------------------------------------------------------

def checkQuit():
    ans = input("Quit? y / n\n>> ")
    if(ans == "y"):
        return True
    else:
        return False

#// -----------------------------------------------------------------------------

m2k = 1.60934
print("This program converts miles to kilometers.")
quit = False
miles = 0.0

while not quit:
    miles = input("\nMiles To Convert: ")
    print(float(miles)*m2k, "km\n")
    quit = checkQuit()
#// -----------------------------------------------------------------------------
