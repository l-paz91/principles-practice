!// -----------------------------------------------------------------------------
!// https://lptcp.blogspot.com/
!// 
!/*
!	Chapter 22 - Exercise 6
!
!	For each language mentioned in this chapter, look at a popular textbook and 
!	see what is used as the first complete program. Write that program in all of 
!	the other languages. Warning: This could easily be a 100-program project.
!
!	The exercise I chose is Chapter 3 - Exercise 2:
!	"Write a program in C++ that converts from miles to kilometres"
!
!	Fortran95
!	Built and written using https://www.tutorialspoint.com/compile_fortran_online.php
! If you use that compiler, you'll get an error if the input in stdin isn't correct
!
!*/
!// https://github.com/l-paz91/principles-practice/
!// -----------------------------------------------------------------------------

logical function checkQuit()
    implicit none
    character (len = 1) :: ans
    print *, "Quit? y / n"    
    read *, ans
    if (ans == 'y') then
        checkQuit = .true.
    else
        checkQuit = .false.
    end if
end function

program Hello
    implicit none
    
    logical :: quit
    logical :: checkQuit
    real    :: m2k
    real    :: miles
    
    quit = .false.   
    m2k = 1.60934
    miles = 0.0
    
    print *, "This program converts miles to kilometers."
    
    do while (.not.(quit))
        print *, "Miles To Convert: "
        read *, miles
        print *, ">> ", miles*m2k
        quit = checkQuit()        
    end do
end program Hello
