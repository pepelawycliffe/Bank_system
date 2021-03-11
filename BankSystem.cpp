//
// BankSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
// http://www.cppforschool.com/project/banking-system-project.html
// http://www.cplusplus.com/doc/tutorial/files/
//

#include "pch.h"
#include <iostream>
#include "Header.h"
#include <fstream>
#include<cctype>
#include<iomanip>
using namespace std;

// *******************************************
// Class for Account definition
// *******************************************
char file[13] = "account.dat";


class account 
{
	int acno;	// account number
	char name[50];	// account name
	int deposit;
	char type;

public:
	// by adding const to the end of function, it is cached for later

	//withdraw money (int n), subtract from blance
	void withdraw(int);
	//deposit money (int n)
	void dep(int);
	//create account
	void create_account();
	//show account details CONST
	void show_account() const;
	//modify account
	void modify();
	//report - show data in tabular format CONST
	void report() const;
	//getAccountNumber CONST
	int getAcNo() const;
	//get balanceAmount CONST
	int getBal() const;
	//getAccountType CONST
	char getAcType() const;
};

// *******************************************
// Class methods definitions
// *******************************************
void account::create_account()
{
	// show / direct user to enter details
	cout << "\nEnter the account No. :";
	cin >> acno;
	cout << "\nEnter account Holder Name :";
	cin.ignore();
	cin.getline(name, 50);	// sets size of input to 50 characters
	
	while (true)
	{
		cout << "\nEnter Type of Account (Checking/Saving) as C or S :";
		cin >> type;
		type = toupper(type);
		if (type == 'C' || type == 'S')
			break;
	}
	cout << "\nEnter Inital amount:";
	cin>>deposit;
	cout << "\n\nAccount Created...";
}
void account::show_account() const
{
	cout << "\nAccount No. : " << acno;
	cout << "\nAccount Holder Name : " << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance amount : " << deposit;
}
void account::modify()
{
	cout << "\nAccount No. :" << acno;
	cout << "\nEnter account Holder Name :";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account (C/S) :";
	cin >> type;
	type = toupper(type);
	cout << "\nModify Balance amount :";
	cin >> deposit;
}
void account::withdraw(int n)
{
	deposit -= n;
}
void account::dep(int n)
{
	deposit += n;
}
void account::report() const
{
	//setw(int) is set width
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}
int account::getAcNo() const
{
	return acno;
}
int account::getBal() const
{
	return deposit;
}
char account::getAcType() const
{
	return type;
}

// *******************************************
// function declaration
// *******************************************
void write_account();
void display_sp(int);	// specific record
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

// *******************************************
// File Operation Functions
// *******************************************

//***************************************************************
//    	function to write in file
//****************************************************************
void write_account()
{
	// need account
	account ac;
	//output to file, binary, append
	ofstream outFile;
	outFile.open(file, ios::binary | ios::app);
	// call account's create_account();
	ac.create_account();
	// put into file
	// We need to cast because write expects char
	outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
	//close file
	outFile.close();
}
//***************************************************************
//    	function to read specific record from file
//****************************************************************
void display_sp(int n)
{
	// display specific record, n as acno, using show_account()
	account ac;
	bool exist_flag = false;	// account exists flag, defualt 0 or false
	ifstream inFile;
	inFile.open(file, ios::binary);
	
	// make sure file exists
	if (!inFile)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETIALS\n";

	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.getAcNo() == n)
		{
			ac.show_account();
			exist_flag = true;
		}
	}
	inFile.close();
	if (!exist_flag)	//exist_flag is false
		cout << "\n\nAccount Number does not exist";
}
void modify_account(int n)
{
	account ac;
	bool found_flag = false;
	fstream kFile;
	kFile.open(file, ios::binary | ios::in | ios::out);
	if (!kFile)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}
	while (!kFile.eof() && !found_flag)
	{
		// read file contents
		kFile.read(reinterpret_cast<char *>(&ac), sizeof(account));
		if (ac.getAcNo() == n)
		{
			ac.show_account();
			cout << "\n\nEnter the New Details of account" << endl;
			ac.modify();
			// have a pointer at the start of the account
			int pos = (-1) * static_cast<int>(sizeof(account));
			// goes to the line before data entry
			kFile.seekp(pos, ios::cur);
			// writes over old data
			kFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
			
			cout << "\n\n\t Record Updated";
			found_flag = true;
		}
	}
	kFile.close();
	if (!found_flag)
		cout << "\n\nRecord Not Found";
}
void delete_account(int n)
{
	bool found;
	//account declare
	account ac;
	//open 2 files, one as input, one as output
	ifstream inFile;
	inFile.open(file, ios::binary);
	ofstream outFile;
	outFile.open("temp.dat", ios::binary | ios::out);

	if (!inFile)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}

	//read file line by line starting at begining
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
	{
		// everything but the account number
		if (ac.getAcNo() != n)
		{
			outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
			found = true;
		}
	}

	//close both files
	inFile.close();
	outFile.close();
	//delete one file
	remove(file);
	//rename temp as original
	rename("temp.dat", file);
	cout << "\n\n\tRecord Deleted ...";
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open(file, ios::binary);

	if (!inFile)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}

	cout << "\n\n\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open(file, ios::binary | ios::out | ios::in);

	if (!File)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}

	while (!File.eof() && !found)
	{
		File.read(reinterpret_cast<char *>(&ac), sizeof(account));
		if (ac.getAcNo() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSIT AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.getBal() - amt;
				if ((bal < 500 && ac.getAcType() == 'S') || (bal < 1000 && ac.getAcType() == 'C'))
					cout << "Insufficience balance";
				else
					ac.withdraw(amt);
			}
			// modify account in file
			int pos = (-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (!found)
		cout << "\n\n Record Not Found ";
}

// *******************************************
// Intro, copied for appearance
// *******************************************
void intro()
{
	cout << "\n\n\n\t  BANK";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\t  SYSTEM";
	cout << "\n\n\n\nPress enter to continue...";

	cin.get();
}


// *******************************************
// main
// *******************************************
/**
int main()
{
    std::cout << "Hello World!\n"; 
	int p = writeFile();
	int q = addToFile();
	int r = readFile();
}
*/

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\n\t02. DEPOSIT AMOUNT";
		cout << "\n\n\t03. WITHDRAW AMOUNT";
		cout << "\n\n\t04. BALANCE ENQUIRY";
		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t06. CLOSE AN ACCOUNT";
		cout << "\n\n\t07. MODIFY AN ACCOUNT";
		cout << "\n\n\t08. EXIT";
		cout << "\n\n\tSelect Your Option (1-8) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "\n\n\tThanks for using bank managemnt system";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}
