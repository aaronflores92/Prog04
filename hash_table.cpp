/*****
	Create a hash table class/struct.
	Define an array that holds 27 elements.
	Define a function called Hash(int)
	-This function returns the modulo of that int by the size of the table (array).
	Define an add function that takes an integer.
	-This function takes the integer, determines the hash of that number by calling the above hash function, then adds it to the table using linear probing for collision resolution.
	Define a function that looks up a value, it takes an integer, return -1 if the value is not in the table.
	Create a main that allows the user to add and lookup items in the table.
*****/

#include <iostream>
#include <string>

using namespace std;

class HashTable
{
	public:
		HashTable();
		void add_val(int & v);
		int search(int & v);
		bool is_full() { return size == 27; }
	
	//private:
		int hash(int v);
		int hash_table[27] = {};
		int size = 0;
};

HashTable::HashTable()
{
	for(int i = 0; i < 27; i++) hash_table[i] = -1;
}

int HashTable::hash(int v)
{
	int hash_index = v % 27;
	return hash_index;
}

void HashTable::add_val(int & v)
//Takes the integer, determines the hash of that number by calling the above hash function, then adds it to the table using linear probing for collision resolution.
{
	int loop = 0;
	int hash_val = v;

	while(hash_table[hash(hash_val)] != -1 && !is_full() && loop != 2)
	{
		hash_val += 1;
		if(hash(hash_val) == 0) loop++;
	}
	
	if(!is_full())
	{
		hash_table[hash(hash_val)] = v;
		size++;
	}
	else std::cout << "the hash table is full." << endl;
}

int HashTable::search( int & v)
// Looks up a value, it takes an integer, return -1 if the value is not in the table.
{
	for(int i = 0; i < 27; i++) if(hash_table[i] == v) return i;
	return -1;
}


int main()
{
	std::cout << "...Hash Table Program..." << endl;
	HashTable test;
	std::cout << "Enter 'A' to add a value, 'S' to search for a value, or 'Q' to quit:" << endl;
	std::string reply = "";
	int i_val = 0;
	int s_val = 0;
	
	while(getline(std::cin, reply) && reply != "Q")
	{
		if(reply == "A")
		{
			std::cout << "Enter a value to add to the hash table: " << endl;
			std::cin >> i_val;
			std::cout << "Adding value " << i_val << "..." << endl;
			test.add_val(i_val);
			std::cout << "Enter 'A' to add a value, 'S' to search for a value, or 'Q' to quit:" << endl;
			std::cin.ignore();
		}
		else if(reply == "S")
		{
			std::cout << "Enter a value to search for in the hash table: " << endl;
			std::cin >> s_val;
			std::cout << "Searching for value " << s_val << "... An index of '-1' indicates the value does not exist in the hash table..." << endl;
			std::cout << "The value " << s_val << " is in index " << test.search(s_val) << " of the hash table." << endl;
			std::cout << "Enter 'A' to add a value, 'S' to search for a value, or 'Q' to quit:" << endl;
			std::cin.ignore();
		}
		else std::cout << "That value was not valid, please enter a valid value ('A' to add a value, 'S' to search for a value, or 'Q' to quit):" << endl;
	}
	return 0;
}
