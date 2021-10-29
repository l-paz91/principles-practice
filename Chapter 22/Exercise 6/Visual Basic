'// -----------------------------------------------------------------------------
'// https://lptcp.blogspot.com/
'// 
'/*
'	Chapter 22 - Exercise 6

' For each language mentioned in this chapter, look at a popular textbook and 
'	see what is used as the first complete program. Write that program in all of 
'	the other languages. Warning: This could easily be a 100-program project.

'	The exercise I chose Is Chapter 3 - Exercise 2:
'	"Write a program in C++ that converts from miles to kilometres"

'	Visual Basic
' Built And written using Visual Studio Community 2019 on Windows 10.

'*/
'// https://github.com/l-paz91/principles-practice/
'// -----------------------------------------------------------------------------

Imports System

Module Module1

    Function checkQuit() As Boolean
        Console.WriteLine("Quit? y / n")
        Console.Write(">> ")
        Dim ans As Char     ' Dim declares space for a new variable
        ans = Console.ReadKey.KeyChar
        If ans = "y" Then
            Return True
        Else
            Return False
        End If
    End Function

    Sub Main()
        Const m2k As Double = 1.60934

        Console.Write("This program converts miles to kilometers.")

        Dim quit As Boolean = False
        Dim miles As Double = 0.0

        While Not quit
            Console.WriteLine(Environment.NewLine)
            Console.Write("Miles To Convert: ")
            miles = CDbl(Console.ReadLine())
            Console.WriteLine(">> " + CStr(miles * m2k) + "km")
            quit = checkQuit()
        End While
    End Sub
End Module
