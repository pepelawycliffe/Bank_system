//
// basic opertion on text file in c++
// 1. include header file fstream in program
// 2. declare file stream object
// 3. open file with file stream object
// 4. use file stream object >>, << or other i/o functions
// 5. close the files.
// http://www.cppforschool.com/tutorial/files2.html
//


#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

int openfile()
{
	ofstream fout;
	// tries to find or writes the file called out.txt
	fout.open("out.txt");
	char str[30] = "Hello World!";

	fout << str;	 //Write string to file;
	fout.close();	// close file

	return 0;
}

int readfile()
{
	ifstream fin;
	fin.open("out.txt");
	char ch;

	while (!fin.eof())	// eof() stands for end of file, boolean
	{
		fin.get(ch);
		cout << ch;
	}

	fin.close();
	return 0;
}

int numOfLines()
{
	ifstream fin;
	fin.open("out.txt");

	int count = 0;
	char str[80];

	while (!fin.eof())
	{
		// getline( is, str, delim)
		// is: object of istream class where to pull read input from
		// str: string object input stored in object
		// delim: delimation char, tells func to stop reading further
		fin.getline(str, 80);
		count++;
	}
	return 0;
}

/*
writing in binary is faster bc no time lost
considered binary files
Example of Student class
*/
class Student
{
	int admno;
	char name[50];
public:
	void setData();
	void showData();
	int getAdmno();
};
void Student::setData()
{
	cout << "\nEnter admission number. ";
	cin >> admno;
	cout << "\nEnter name of student ";
	cin.getline(name, 50);
}
void Student::showData()
{
	cout << "\nAdmission no. : " << admno;
	cout << "\nStudent Name : " << name;
}
int Student::getAdmno()
{
	return admno;
}

/*
* Function to write in a binary file.
*/
void write_record()
{
	ofstream outFile;	// output file stream, declared
	// open with binary mode and append to file.
	outFile.open("student.dat", ios::binary | ios::app);

	Student obj;
	obj.setData();	// get input data
	// write(const char* s, streamsize n)
	// s: pointer to an array of atleast n characters
	// n: number of char's to insert
	// therefore pointer of the address of obj
	outFile.write((char*)&obj, sizeof(obj));

	outFile.close();
}
/*
* Function to display records of file
*/
void display()
{
	ifstream inFile;	// input file stream
	inFile.open("student.dat", ios::binary);

	Student obj;

	//read(pointer to characters, size of file)
	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		obj.showData();
	}
	inFile.close();
}

/*
* function to search and display from binary file
*/

void search(int n)
{
	ifstream inFile;
	inFile.open("student.dat", ios::binary);

	Student obj;

	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		if (obj.getAdmno() == n)
		{
			obj.showData();
		}
	}

	inFile.close();
}

/*
* function to delete a record
* rewrites the data file
* but without the specific line w/ your data
*/
void delete_record(int n)
{
	Student obj;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);

	ofstream outFile;
	outFile.open("temp.dat", ios::out | ios::binary);

	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		// everything but my specific primary key
		if (obj.getAdmno() != n)
		{
			outFile.write((char*)&obj, sizeof(obj));
		}
	}

	inFile.close();
	outFile.close();

	remove("student.dat");
	rename("temp.dat", "student.dat");
}

/*
* function to modify a record
*/

void modify_record(int n)
{
	fstream file;
	file.open("student.dat", ios::in | ios::out);

	Student obj;

	while (file.read((char*)&obj, sizeof(obj)))
	{
		if (obj.getAdmno() == n)
		{
			cout << "\nEnter the new details of student";
			obj.setData();

			// changes pointer to start of obj?
			// seekp -> seek pointer
			// ios::beg (beginning of stream)
			// ios:cur (current pos in stream)
			// ios:end (end of stream)
			int pos = -1 * static_cast<int>(sizeof(obj));
			file.seekp(pos, ios::cur);

			file.write((char*)&obj, sizeof(obj));
		}
	}

	file.close();
}

/*
int main()
{
	//Store 4 records in file
	for(int i = 1; i <= 4; i++)
	   write_record();

	//Display all records
	cout << "\nList of records";
	display();

	//Search record
	cout << "\nSearch result";
	search(100);

	//Delete record
	delete_record(100);
	cout << "\nRecord Deleted";

	//Modify record
	cout << "\nModify Record 101 ";
	modify_record(101);

	return 0;
}
*/