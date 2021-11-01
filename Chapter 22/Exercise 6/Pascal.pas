(*
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
	
	Pascal
	Built and written using https://www.tutorialspoint.com/compile_pascal_online.php
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------
*)

(*// --------------------------------------------------------------------- //*)

Program HelloWorld(input, output);
var
  quit : boolean;
  miles : double;
  m2k : double;
  
(*// --------------------------------------------------------------------- //*)

(*what a hideous way to define/declare a function*)
function checkQuit(): boolean;

var (*local variables for function need to be defined first*)
  ans: char;
    
begin
  writeln('Quit? y / n >> ');
  readLn(input, ans);
  if ans = 'y' then
    checkQuit := true
  else
    checkQuit := false;
end;

(*// --------------------------------------------------------------------- //*)

begin
  quit := false;
  m2k := 1.60934;
  while not quit do
  begin
    writeLn('Miles To Convert: ');
    readLn(input, miles);
    writeLn(miles*M2K, 'km'); (* this has the floating point in the wrong place *shrug*)
    quit := checkQuit;
  end;
end.

(*// --------------------------------------------------------------------- //*)
