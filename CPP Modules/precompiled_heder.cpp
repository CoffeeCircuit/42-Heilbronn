#include "stdc++.h"


/* 
USED TO INCREASE SPEED OF COMPILATIONS

Automatic:
Run: g++ stdc++.h and you'll get stdc++.h.ghc. the latter is the precompiled header

When you later compile a source file that includes #include "stdc++.h", g++ 
will automatically use stdc++.h.gch if it is present in the same directory as the header.

Manual: 
You can explicitly tell g++ to treat a file as a precompiled header using `-x c++-header`:
g++ -x c++-header pch.h [-o pch.gch]
	where -x c++-header tells the compiler the type of document of language 
	g++ -x c myfile.txt				// treats myfile.txt as C source
	g++ -x c++-header myheader.h 	// creates a C++ precompiled header
	g++ -x assembler file.s			// treats file.s as assembler

When compiling source files, you can force g++ to use the precompiled header 
with the -include flag:
g++ -include pch main.cpp -o main

This is useful if the precompiled header is not in the same directory, or you 
want to control which PCH is used.


Strict Conditions: 
 - The same compiler version and flags are used.
 - No code appears before the #include "pch.h" in the source file.
 - Macros and compiler options (e.g., -D, -O, -fexceptions) match the original build.

*/
int main()
{
	return 0;
}
