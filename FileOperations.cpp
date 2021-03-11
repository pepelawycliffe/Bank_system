//
// basic file operations
// https://www.w3schools.com/python/python_ref_file.asp
// http://www.cppforschool.com/tutorial/files2.html
//

#include "pch.h"
#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;	// needed for iostream inclusion

/**
Rewrites the file completely.
open the file, mess around, then close it.
cin.ignore() clears the input space. should be put before any input space.
system("cls") goes to the system and clears the page. 
*/
int writeFile()
{
	ofstream myfile;
	myfile.open("example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();
	return 0;
}


/**
Should add to the end of the file.
myfile.is_open() returns a boolean
*/
int addToFile()
{
	ofstream myfile;
	myfile.open("example.txt", ios::ate | ios::app);
	myfile << "Adding to the file.\n";
	myfile.close();
	return 0;
}

/**
Reading text files
file.read()		//returns number of bytes from file default of whole file

https://www.geeksforgeeks.org/set-position-with-seekg-in-cpp-language-file-handling/
file.seekg()	// seek arbitrary position in file. ios_base::beg (cur, end)


file.seekp()	// set position of pointer in ouput
remove("example.txt")	// removes / deletes file
rename("original_name", "new_name")		// rename file

file.eof()		// return bool, if it is the end of the file

getline(file, line)
cin.get()		// get(string_name, size)
*/
int readFile()
{
	string line;
	ifstream myfile("example.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << "\n";
		}
		myfile.close();
	}
	else cout << "unable to open file";

	return 0;
}

/**
reinterpret_cast	//convert one pointer to another pointer
// data_type *var_name = reinterpret_cast <data_type *>(pointer_var);
int* p = new int(65);
char* ch = reinterpret_cast<char*>(p); 
// *p -> 65; *ch -> A; p -> 0x1609c20; ch -> A
int q;
char* dh = reinterpret_cast<char*>(&q);
*/
