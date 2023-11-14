#include "Phonebook.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
bool compare(std::string first, std::string last);
void heading();
void equals();
void line();
void mainmenu(Phonebook *object, pBook *root);
std::string toSmall(std::string word);
void takeInput(std::string *name, std::string *email, std::string *phNum, std::string *phType);
bool number(std::string x);
void outputstream(pBook* node);
void outputD(pBook *node);
void save(pBook *node);
void updateInput( std::string *email, std::string *phNum, std::string *phType);
void trav(pBook *node);
ofstream output;
void main()
{
	Phonebook *object = new Phonebook();
	pBook *root = NULL;
	mainmenu(object, root);
	line();
	cout << "\t\t\t Have a nice day <3 \n";
	output.close();
	system("Pause");
}



void mainmenu(Phonebook *object, pBook *root)
{
	root = object->load(root);
	string choice = "";
	do
	{
		output.open("test.txt", std::ofstream::app);
		heading();
		cout << "What do you want to do?\n";
		cout << "1) Enter a phone number\n2) Search a phone number\n";
		cout << "3) Delete a phone number\n4) Update a phone number\n";
		cout << "5) Display All\n";
		cout << "6) Exit\n";
		line();
		cin >> choice;
		line();
		switch (choice[0])
		{
		case '1':
		{
			std::string name, email, phNum, phType;
			takeInput(&name, &email, &phNum, &phType);
			root = object->insert(root, toSmall(name), email, phNum, &phType);
			if (phType == "FOUND")
			{
				cout << "The given name is already available, try updating instead\n";
				cout << "Press return to continue....\n";
				_getch();
			}
			else
			{
				output.close();
				output.open("test.txt");
				save(root);
				output.close();
				cout << "Record successfully added\n";
				cout << "Press return to continue....\n";
				_getch();
			}
			break;
		}
		case '2':
		{
			std::string name;
			cout << "Enter a name to search\n";
			cin.ignore();
			getline(cin, name);
			name = toSmall(name);
			if (name == "")
			{
				cout << "Please enter a valid name\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			pBook *check = NULL;
			check = object->search(root, name);
			if (check == NULL)
			{
				cout << "No record found\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			outputD(check);
			cout << "Press return to continue....\n";
			_getch();
			break;
		}
		case '3':
		{
			std::string name;
			cout << "Enter a name to search\n";
			cin.ignore();
			getline(cin, name);
			name = toSmall(name);
			if (name == "")
			{
				cout << "Please enter a valid name\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			pBook *check = NULL;
			check = object->search(root, name);
			if (check == NULL)
			{
				cout << "No record found to be deleted\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			if (name == root->key)
			{
				root = object->deleteC(root, name);
				output.close();
				output.open("test.txt");
				save(root);
				output.close();
				cout << "Item successfully deleted\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			object->deleteC(root, name);
			output.close();
			output.open("test.txt");
			save(root);
			output.close();
			cout << "Item successfully deleted\n";
			cout << "Press return to continue....\n";
			_getch();
			cout << 3 << endl;
			break;
		}
		case '4':
		{
			std::string name;
			cout << "Enter a name to search\n";
			cin.ignore();
			getline(cin, name);
			name = toSmall(name);
			if (name == "")
			{
				cout << "Please enter a valid name\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			pBook *temp = object->search(root, name);
			if (temp == NULL)
			{
				cout << "No such record is available\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			string phNum, email, phType;
			updateInput(&email, &phNum, &phType);
			object->update(temp, email, phNum, phType);
			output.close();
			output.open("test.txt");
			save(root);
			output.close();
			cout << "Item successfully updated\n";
			cout << "Press return to continue....\n";
			_getch();
			break;
		}
		case '5':
		{
			if (root == NULL)
			{
				std::cout << "There are no records available\n";
				cout << "Press return to continue....\n";
				_getch();
				break;
			}
			trav(root);
			cout << "Press return to continue....\n";
			_getch();
			break;
		}
		case '6':
		{
			return;
			break;
		}
		default:
		{
			cout << "Enter a valid number\n";
			cout << "Press return to continue....\n";
			_getch();
			system("CLS");
			continue;
		}
		}
		system("CLS");
	} while (true);
}

void save(pBook *node)
{
	if (node != NULL)
	{
		save(node->left);
		outputstream(node);
		save(node->right);
	}
}

void trav(pBook *node)
{
	if (node != NULL)
	{
		trav(node->left);
		outputD(node);
		line();
		trav(node->right);
	}
}

void outputstream(pBook* node)
{
	output << "{\n";
	output << node->key << std::endl;
	if (node->email == "")
	{
		output << " " << std::endl;
	}
	else
	{
		output << node->email << std::endl;
	}
	output << node->phNum << std::endl;
	if (node->phType == "")
	{
		output << " " << std::endl;
	}
	{
		output << node->phType << std::endl;
	}
	output << "}\n";
}

void updateInput( std::string *email, std::string *phNum, std::string *phType)
{
	do
	{
		cout << "Enter your phone number: ";
		getline(cin, *phNum);
		if (*phNum != "")
		{
			break;
		}
		else
		{
			cout << "You entered wrong phone number, press return and try again.. ";
			_getch();
			line();
		}
	} while (true);
	
	cout << "Enter your email: ";
	getline(cin, *email);
	cout << "Enter your phone type (Office, Home or Mobile): ";
	getline(cin, *phType);
}

void outputD(pBook *node)
{
	cout << "Name: " << node->key << endl;
	cout << "Phone number: " << node->phNum << endl;
	if (node->email == " ")
	{

	}
	else
	{
		cout << "Email: " << node->email << endl;
	}
	if (node->phType == " ")
	{

	}
	else
	{
		cout << "Phone type: " << node->phType << endl;
	}
}

void heading()
{
	cout << "\t\t\tPHONE BOOK\n";
	equals();
}

void line()
{
	cout << "--------------------------------------------------------------------\n";
}

void equals()
{
	cout << "====================================================================\n";
}

void takeInput(std::string *name, std::string *email, std::string *phNum, std::string *phType)
{
	do
	{
		cout << "Enter your name: ";
		cin.ignore();
		getline(cin, *name);
		if (*name != "")
		{
			break;
		}
	} while (true);

	do
	{
		cout << "Enter your phone number: ";
		getline(cin, *phNum);
		if (number(*phNum) && *phNum != "")
		{
			break;
		}
	} while (true);

	cout << "Enter your email address: ";
	getline(cin, *email);

	cout << "Enter your phone type (Home, Office or Mobile): ";
	getline(cin, *phType);
}

bool compare(std::string first, std::string last)
{
	int count = 0;
	bool check = false;
	while (count < first.length() && count < last.length())
	{
		if (first[count] > last[count])
		{
			return true;
		}
		count++;
	}
	if (check == false)
	{
		if (first.length() > last.length())
		{
			return true;
		}
	}
	return false;
}

std::string toSmall(std::string word)
{
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] > 64 && word[i] < 91)
		{
			word[i] += 32;
		}
	}
	return word;
}

bool number(std::string x)
{
	for (int i = 0; i < x.length(); i++)
	{
		if ((x[i] > 47 && x[i] < 58) || x[i] == 45)
		{

		}
		else
		{
			return false;
		}
	}
	return true;
}