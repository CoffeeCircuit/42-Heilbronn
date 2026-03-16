#include <iostream>
#include <iomanip>



using namespace std;

int main()
{

// Booleans
cout << "Booleans\n";
cout << false << "\n";
cout << boolalpha << false << "\n";

// Hexadecimal and octal numbers
cout << "\nHexadecimal and octal numbers\n";
int myInt = 14;
cout << dec << myInt << "\n";
cout << hex << myInt << "\n";
cout << oct << myInt << "\n";
cout << showbase << uppercase;
cout << hex << myInt << "\n";
cout << oct << myInt << "\n";
cout << dec;

// Floating point numbers
cout << "\nFloating point numbers\n";
float myFloat = 19.99;
cout << myFloat << "\n";
cout << showpos << showpoint << 12345.0 << "\n"; //showpos always displays '+'
cout << noshowpos << noshowpoint;
cout << fixed << myFloat << "\n";
cout << setprecision(4) << 12.34561546 << endl;
cout << scientific << myFloat << "\n";

// Alignment
cout << "\nAlignment\n";
cout << setw(10) << left << "Left" << "\n";
cout << setw(10) << right << "Right" << "\n";
cout << setw(10) << internal << -12345 << " (Internal)\n";


// Fill
cout << "\nFill" << endl;
cout << fixed << setfill('.') << setw(10) << 12 << "\n";

cout.width(4);
cout << "long string" << endl;

}
