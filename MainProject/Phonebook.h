#pragma once
#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
struct pBook
{
	/*User information variables*/
	std::string key;
	std::string email;
	std::string phNum;
	std::string phType;

	/*Tree information variables*/
	pBook *left;
	pBook *right;

	/*Default constructor*/
	pBook()
	{
		left = NULL;
		right = NULL;
		email = "";
		phNum = "";
		phType = "";
	}

	/*Destructor*/
	~pBook()
	{
		left = NULL;
		right = NULL;
	}
};
class Phonebook
{
public:

	/*This node is created to create a new node with given parameters*/
	pBook* newNode(std::string key, std::string email, std::string phNum, std::string phType)
	{
		pBook *object = new pBook();
		object->key = key;
		object->phNum = phNum;
		object->phType = phType;
		object->email = email;
		return object;
	}

	/*This function is created to do comparison (first > last) lexicographically*/
	bool compare(string first, string last)
	{
		bool check = false;
		int count = 0;
		while (count < first.length() && count < last.length())
		{
			if ((int)first[count] > (int)last[count])
			{
				return true;
			}
			else if ((int)last[count] > (int)first[count])
			{
				return false;
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
		/*if (first > last)
		{
			return true;
		}
		return false;*/
	}
	/*This function is used to turn a given std::string into lowercaps*/
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
	/*This functions checks the given phone number, returns false if it contains anything
	  other than numbers (0-9) or dash (-)
	*/
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

	/*
		*This is a delete function*
		*It will take node as a parameter and a key*
		*It searches all the nodes, if the key is found, it checks different possible conditions*
		*Deletes the object using suitable condition so that other nodes don't get lost*
	*/
	pBook* deleteC(pBook *node, std::string key)
	{
		if (node == NULL)
		{
			return node;
		}
		
		if (compare(node->key, key))
		{
			node->left = deleteC(node->left, key);
		}
		else if (compare(key, node->key))
		{
			node->right = deleteC(node->right, key);
		}
		else
		{
			if (node->left == NULL)
			{
				pBook *temp = node->right;
				delete node;
				node = NULL;
				return temp;
			}
			else if (node->right == NULL)
			{
				pBook *temp = node->left;
				delete node;
				node = NULL;
				return temp;
			}

			pBook *leftmost = leftMost(node->right);
			pBook *temp = node;
			node = node->right;
			leftmost->left = temp->left;
			delete temp;
			temp = NULL;
			return node;
		}
		return node;
	}

	pBook* leftMost(pBook *node)
	{
		pBook *temp = node;
		while (temp != NULL && temp->left != NULL)
		{
			temp = temp->left;
		}
		//std::cout << temp->key << " " << temp->left << " " << temp->right << std::endl;
		return temp;
	}

	/*
		*This is a search function*
		*It will take root as parameter,*
		*It searches all the nodes recursively for key*
		*Returns the node where key is found, otherwise returns NULL*
	*/

	pBook* search(pBook* node, std::string key)
	{
		pBook *temp = node;
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				return temp;
			}
			else if (compare(key, temp->key))
			{
				temp = temp->right;
			}
			else if (compare(temp->key, key))
			{
				temp = temp->left;
			}
		}
		return NULL;
	}

	/*
		*This is an update function*
		*It takes just one object, the object which is to be updated*
		*It updates the object*
		*It doesn't need to return anything*
	*/
	void update( pBook* node, std::string email, std::string phNum, std::string phType)
	{
		
			node->email = email;
			node->phNum = phNum;
			node->phType = phType;
			return;
	}

	/*
		*This is an insert function*
		*It will take all the required info as parameter and keep passing it using recursion*
		*When the place is found (lexicographicall)y*
		*It calls newNode() which makes an object and place it in its place*
	*/
	pBook* insert(pBook *node, std::string key, std::string email, std::string phNum, std::string *phType)
	{
		if (node == NULL)
		{
			node = (newNode(key, email, phNum, *phType));
			return node;
			//std::cout << "Added node " << key << "\n";
			//save(root);
		}
		if (compare(node->key, key))
		{
			node->left = insert(node->left, key, email, phNum, phType);
		}
		else if (compare(key, node->key))
		{
			node->right = insert(node->right, key, email, phNum, phType);
		}
		else
		{
			*phType = "FOUND";
			return node;
		}
		return node;
	}

	//Filestream starts here
	pBook* load(pBook* node)
	{
		ifstream input;
		input.open("test.txt", std::ifstream::in);
		string temp;
		std::string key = "";
		std::string email;
		std::string phNum;
		std::string phType;
		int count = 0;
		if (!input.is_open())
		{
			cout << "There is no file available\n";
			return NULL;
		}
		while (!input.eof())
		{
			getline(input, temp);
			if (temp == "{")
			{
				continue;
			}
			else if (temp == "}" || count == 4)
			{
				count = 0;
			}
			else
			{
				if (temp == "")
				{
					input.close();
					cout << "Successfully loaded\n";
					return node;
				}

				switch (count)
				{
				case 0:
				{
					key = temp;
					break;
				}
				case 1:
				{
					email = temp;
					break;
				}
				case 2:
				{
					phNum = temp;
					break;
				}
				case 3:
				{
					phType = temp;
					break;
				}
				}
				//END of switch

				if (count == 3 && key != "")
				{
					node = insert(node, key, email, phNum, &phType);
				}
				count++;
			}
		}
		return node;
	}
};
