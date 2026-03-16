#include <iostream>

void square(int &lvalref) // only lvalue
{
	lvalref *= lvalref;
};

void square(const int &lvalref) // lvalue and rvalue
{
	/* Passing an rvalue to a const lvalue reference binds directly, 
	with no copy or move. The temporary's lifetime is extended to 
	match the reference.

	You normally use const T& parameters when:
		You want to avoid copying large or complex objects (like std::string, std::vector, custom classes).
		The function does not need to modify the argument.
		You want to accept both lvalues and rvalues efficiently. 
	*/
	lvalref;
}; 

void square2(int &&lvalref) // only rvalue
{
/* 	Key points:

	Only rvalues (temporaries or std::move/casts) can bind to int&&.
	You can modify lvalref inside the function, but changes won’t affect 
	the original variable unless you forcibly cast an lvalue (like (int&&)x), 
	which is rarely needed and can be dangerous.
	
	For built-in types like int, rvalue references are rarely useful except for
	perfect forwarding or move semantics in templates and classes.
	
	Summary:
	square2(int&&) only accepts rvalues. Inside, lvalref is a reference to the 
	temporary or casted value, but unless you modify it, nothing happens. 
	For int, this is mostly a demonstration of reference binding rules
 */
	lvalref;
}; 


/* 

A copy happens when:
	You pass an object by value (T obj) and the argument is an lvalue (named variable).
	You assign or initialize an object from another lvalue (e.g., T b = a;).
	The copy constructor 
		MyClass(const MyClass& other); 
		MyClass b(a);
	or copy assignment operator 
		MyClass& operator=(const MyClass& other); 
		MyClass b = a;
	is called.

A move happens when:
	You pass an object by value (T obj) and the argument is an rvalue 
	(temporary or std::move).
	You assign or initialize an object from an rvalue (e.g., T b = std::move(a);).
	The move constructor 
		MyClass(MyClass&& other); 
		MyClass b = std::move(a);
	or move assignment operator is called (for an existing object).
		MyClass& operator=(MyClass&& other);
		b = std::move(a);). 
		It releases the current object's resources and takes ownership of 
		other's resources.

Summary:
	Copy: lvalue → new object (makes a duplicate).
	Move: rvalue → new object (transfers resources, leaves source in valid but unspecified state).

C++ chooses move if possible (move constructor/assignment exists and argument 
is rvalue), otherwise falls back to copy. For built-in types, copy and move are 
the same. For classes with dynamic resources, move is more efficient.

*/

int main()
{
	int x = 5;
	square(x);
	square(5);
	square2(5);
	// square2(x);  //this will error
	square2((int &&)x);

	std::string a = "hello";
	std::string b = std::move(a); 
	// b now owns the "hello" data, a is empty
	// a is still alive, but its contents are unspecified (usually empty)

/* 
NOTE
	“It releases the current object's resources and takes ownership of 
	other's resources” means:

	The destination object (the one being assigned to) first frees or cleans 
	up any resources it already owns (like deleting a pointer or closing a file).
	Then, it takes over the resources (like pointers, file handles, etc.) from 
	the source (the rvalue being moved from), instead of making a copy.
	The source object is not destroyed, but its resources are set to a safe, 
	empty, or default state (e.g., its pointer is set to nullptr).
	
	Lifetimes:
	The destination object continues to exist and now owns the resources.
	The source object also continues to exist until its scope ends, but it is 
	in a valid but unspecified (often “empty”) state. You should not use it 
	except to assign a new value or destroy it.


*/



	std::cout << x << std::endl;
}
