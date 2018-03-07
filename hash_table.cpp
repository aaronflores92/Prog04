/******
Build a hash table using chaining as the collision resolution technique. Insertions into the hash table will correspond to declarations of variables and values in a program, searches will be requests for the value of a variable. Some variables will be local and have a narrow scope while some variables will be global.

The program will take input from a file, another program written in the omnipotent programming language BORG (Bionicly Omnipotent Resistance Grinders) and generate output from this program.
******/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <math.h>

class Node
{
	public:
		Node() : next_node(0), prev_node(0), variable(""),  value(0), exe_lvl(0) { }
		Node(std::string var, int & val, int & e_lvl) : next_node(0), prev_node(0), variable(var), value(val), exe_lvl(e_lvl) { } 
	
	//private:
		Node * next_node;
		Node * prev_node;
		std::string variable = "";
		int value = 0;
		int exe_lvl = 0;
};

class hashChain
{
	public:
		hashChain() : head(0), tail(0), size(0) { }
		void insert(std::string & var, int & val, int & e_lvl);
		int pop(int & e_lvl);
		int iterate();
		bool empty() { return (size == 0); }
		int search(std::string & var, int & e_lvl);
		void update(std::string & updt_var, int & updt_val, int & e_lvl);
		
	private:
	Node * head;
	Node * tail;
	int size = 0;
}; 

void hashChain::insert(std::string & var, int & val, int & e_lvl)
{
	std::cout << "inserting var " << var << " with val " << val << " and exe_lvl " << e_lvl << "...\n";
	Node * N = new Node(var, val, e_lvl);
	if(empty()) head = tail = N;
	else
	{
		N->prev_node = tail;
		tail->next_node = N;
		tail = N;
	}
	size++;
}

int hashChain::pop(int & e_lvl)
{
	//start from tail >> Node * current = new Node(); current = tail
	//if empty() return 0
	//if current->exe_lvl == e_lvl {if current == tail{ tail = curent->prev_node} else {connect current->next_node->prev_node to current->prev_node and current->prev_node to curren->next_node}}
	std::cout << "poppin' bottles...\n";
	Node * current = new Node();
	current = tail;
	if(empty()) return 0;
	else
	{
		for(int i = size; i > 0; i--)
		{
			if(current->exe_lvl == e_lvl)
			{
				if(current == tail)
				{
					tail = current->prev_node;
					current = tail;
					size--;
				}
				else
				{
					current->next_node->prev_node = current->prev_node;
					current->prev_node->next_node = current->next_node;
					current = current->prev_node;
					size--;
				}
			}
			else current = current->prev_node;
		}
	}
	std::cout << "... finished poppin' bottles\n";
	return 1;
	
	/*****
	int pop_val = 0;
	if(empty()) return 0;
	else
	{
		pop_val = tail->value;
		tail = tail->prev_node;
		size--;
		return pop_val;
	}
	
	Node * current = new Node(); //necessary?
	delete current; //necessary?
	
	****/
}

int hashChain::search(std::string & var, int & e_lvl)
{
	Node * current = new Node();
	current = head;
	int i = 0;
	std::cout << "checking for curr!=tail\n";
	while(i < size)  //(current != tail) //fails to check. might be failing since when first node is first added, head == tail == node
	{
		std::cout << "checking...\n";
		if((current->variable == var) && (current->exe_lvl == e_lvl)) 
		{
			std::cout << "match made! var name is " << current->variable << ", var value is " << current->value << ", and exe lvl is " << current->exe_lvl << '\n';
			return current->value;
		}
		current = current->next_node;
		i++;
		if(i == size) break;
	}
	return -1;
}

void hashChain::update(std::string & updt_var, int & updt_val, int & e_lvl)
{
	Node * current = new Node();
	current = head;
	int i = 0;
	while(i < size)
	{
		if((current->variable == updt_var) && (current->exe_lvl == e_lvl))
		{
			current->value = updt_val;
			break;
		}
		else
		{
			current = current->next_node;
			i++;
			if(i == size) break;
		}
	}
}

class hashTable
{
	public:
		hashTable();
		int hash(std::string & var);
		void insert(std::string & var, int & val, int & e_lvl);
		int search(std::string & var, int & e_lvl);
		void pop_local_scope(int & ind, int & e_lvl);
		void update(std::string & updt_var, int & updt_val, int & e_lvl);
	
	private:
		//List* am = new List[nodes]; creates array of Lists
		hashChain* hash_table; //= new hashChain[30]; //creates array named hash_table of type hashChain
		//int hash_table[30] = { };
		int table_size = 0;
};

hashTable::hashTable()
{
	std::cout << "creating new hash table... \n";
	hash_table = new hashChain[30];
	table_size = 0;
}

int hashTable::hash(std::string & var)
{
	//hash value is (sum((ordinal vals of a char in the string) * (char position))) % TABLESIZE
	int i = 0;
	int hash_val = 0;
	for(int i = 0; i < var.size(); i++) hash_val += var[i] * (i + 1);
	hash_val = hash_val % 30;
	std::cout << "hash val is " << hash_val << '\n';
	return hash_val;
}

void hashTable::insert(std::string & var, int & val, int & e_lvl)
{
	int hash_val = hash(var);
	hash_table[hash_val].insert(var, val, e_lvl); //calls on hashChain.insert() to insert var, var val, and exe_level
}

int hashTable::search(std::string & var, int & e_lvl)
{
	int srch_ind = hash(var);
	int srch_val = 0;
	srch_val = hash_table[srch_ind].search(var, e_lvl); //calls hashChain.search() to search for var to print;
	return srch_val;
}

void hashTable::pop_local_scope(int & ind, int & e_lvl)
{
	hash_table[ind].pop(e_lvl);
}

void hashTable::update(std::string & updt_var, int & updt_val, int & e_lvl)
{
	int updt_ind = hash(updt_var);
	hash_table[updt_ind].update(updt_var, updt_val, e_lvl);
}

int main()
{
	//create stack that will control what level of the program you are in
	std::stack<std::string> execution;
	
	//ifstream infile;
	//inflie.open("c:\\location\\of\\file.ext") //must escape the backslash
	
	std::string in_line ="";
	int pos = 0, space = 0;
	int exe_lvl = 0;
	hashTable test;
	
	//while statement to read file input until the thend input (while !eof())
	while(getline(std::cin, in_line))
	{
		std::cout << in_line << '\n';
		std::cout << "start if blocks: \n";
		
		if((in_line.find("Q") != std::string::npos)  && in_line.find_first_of("Q") == 0) break; //if(('Q' is found) and Q is in the first position) break;
		
		else if((in_line.find("COM")!= std::string::npos) && in_line.find_first_of("COM") == 0)
		{
			std::cout << "COM in line, position " << in_line.find_first_of("COM") << "\n";
		}
		
		else if((in_line.find("VAR")!= std::string::npos) && (in_line.find_first_of("VAR") == 0))
		{
			//extract variable name
			pos = in_line.find_first_of("VAR") + 4; //start index of var name start
			space = in_line.find_first_of(' ', pos) - 4; //end index of var name
			std::string var_name = in_line.substr(pos, space); //extract substring of length space beginning @ pos
			std::cout << "var name = " << var_name << '\n';
			
			//extracts variable value
			int val_pos = in_line.find_last_of(' ') + 1; //var val begins after last space
			int val_len = in_line.length()-val_pos; //length of var val
			int var_val = std::stoi(in_line.substr(val_pos, val_len));
			std::cout << "VAR " << var_name << "'s val begins at pos " << val_pos << ", is " << val_len << " bytes long, and contains the value " << var_val << "\n";
			if(test.search(var_name, exe_lvl) == -1) test.insert(var_name, var_val, exe_lvl);
			else std::cout << "Cannot use that variable name in this scope as that variable already exists!\n";
		}
		
		else if((in_line.find("PRINT")!= std::string::npos)  && in_line.find_first_of("PRINT") == 0)
		{
			pos = in_line.find_first_of("PRINT") + 6; //start index of var to print
			int op_pos = 0;
			std::string print_var = "";
			
			if(in_line.find("%") != std::string::npos)
			{
				//find position of operator
				op_pos = in_line.find("%");
				int var_name_len = op_pos - (pos + 1);
				//extract variable name on left side
				print_var = in_line.substr(pos, var_name_len);
				//extract new var value on right
				int op_val = std::stoi(in_line.substr((op_pos + 2)));
				//find var in hashTable and perform operation
				for(int i = exe_lvl; i >= 0; i--)
				{
					if(test.search(print_var, i) != -1) 
					{
						std::cout << "var modulo by " << op_val << " is " << test.search(print_var, i) % op_val << '\n';
						break;
					}
					else std::cout << print_var << " does not exist\n";
				}
			}
			
			else if(in_line.find("^") != std::string::npos)
			{
				//find position of operator
				op_pos = in_line.find("^");
				int var_name_len = op_pos - (pos + 1);
				//extract variable name on left side
				print_var = in_line.substr(pos, var_name_len);
				//extract new var value on right
				int op_val = std::stoi(in_line.substr((op_pos + 2)));
				//find var in hashTable and perform operation
				for(int i = exe_lvl; i >= 0; i--)
				{
					if(test.search(print_var, i) != -1) 
					{
						std::cout << "var to the power " << op_val << " is " << pow(test.search(print_var, i), op_val) << '\n';
						break;
					}
					else std::cout << print_var << " does not exist\n";
				}
			}
			
			else if(in_line.find("*") != std::string::npos)
			{
				//find position of operator
				op_pos = in_line.find("*");
				int var_name_len = op_pos - (pos + 1);
				//extract variable name on left side
				print_var = in_line.substr(pos, var_name_len);
				//extract new var value on right
				int op_val = std::stoi(in_line.substr((op_pos + 2)));
				//find var in hashTable and perform operation
				for(int i = exe_lvl; i >= 0; i--)
				{
					if(test.search(print_var, i) != -1) 
					{
						std::cout << "var multiplied by " << op_val << " is " << test.search(print_var, i) * op_val << '\n';
						break;
					}
					else std::cout << print_var << " does not exist\n";
				}
			}
			
			else if(in_line.find("/") != std::string::npos)
			{
				//find position of operator
				op_pos = in_line.find("/");
				int var_name_len = op_pos - (pos + 1);
				//extract variable name on left side
				print_var = in_line.substr(pos, var_name_len);
				//extract new var value on right
				int op_val = std::stoi(in_line.substr((op_pos + 2)));
				//find var in hashTable and perform operation
				for(int i = exe_lvl; i >= 0; i--)
				{
					if(test.search(print_var, i) != -1) 
					{
						std::cout << "var divided by " << op_val << " is " << test.search(print_var, i) / op_val << '\n';
						break;
					}
					else std::cout << print_var << " does not exist\n";
				}
			}
			else if(in_line.find("+") != std::string::npos)
			{
				//find position of operator
				op_pos = in_line.find("+");
				int var_name_len = op_pos - (pos + 1);
				//extract variable name on left side
				print_var = in_line.substr(pos, var_name_len);
				//extract new var value on right
				int op_val = std::stoi(in_line.substr((op_pos + 2)));
				//find var in hashTable and perform operation
				for(int i = exe_lvl; i >= 0; i--)
				{
					if(test.search(print_var, i) != -1) 
					{
						std::cout << "var plus " << op_val << " is " << test.search(print_var, i) + op_val << '\n';
						break;
					}
					else std::cout << print_var << " does not exist\n";
				}
			}
			else if(in_line.find("-") != std::string::npos)
			{
				//find position of operator
				op_pos = in_line.find("-");
				int var_name_len = op_pos - (pos + 1);
				//extract variable name on left side
				print_var = in_line.substr(pos, var_name_len);
				//extract new var value on right
				int op_val = std::stoi(in_line.substr((op_pos + 2)));
				//find var in hashTable and perform operation
				for(int i = exe_lvl; i >= 0; i--)
				{
					if(test.search(print_var, i) != -1) 
					{
						std::cout << "var minus " << op_val << " is " << test.search(print_var, i) - op_val << '\n';
						break;
					}
					else std::cout << print_var << " does not exist\n";
				}
			}
			
			//insert other operators
			else
			{
				int print_len = in_line.length() - pos; //length of var to print
				print_var = in_line.substr(pos, print_len); //var to print
				std::cout << "PRINT in line, position " << pos << "\n";
				std::cout << print_var << "\n";
				std::cout << "VAR " << print_var << "'s value is ";
				for(int i = exe_lvl; i >= 0; i--)
				{
					if(test.search(print_var, i) != -1) break;
					else std::cout << test.search(print_var, i) << '\n';
				}
			}
		}
		
		else if((in_line.find("VAR") == std::string::npos) && (in_line.find("=") != std::string::npos)) //IF VAR not in line and assign op in line
		{
			//extract variable name on left side
			//extract new var value on right
			//create pointer to var in node (search local scope first, then global)
			//update var w/ new val
			
			pos = in_line.find_first_of("="); //assignment operator pos
			std::string updt_var = in_line.substr(0, (pos - 1)); //var name to update
			std::cout << "var name to update: " << updt_var << "yeah!\n";
			int updt_val = std::stoi(in_line.substr((pos + 2)));
			std::cout << "value to update: " << updt_val << "yeah!!\n";
			for(int i = exe_lvl; i >= 0; i--)
			{
				if(test.search(updt_var, i) != -1)
				{
					test.update(updt_var, updt_val, i);
					break;
				}
				else std::cout << "nothing to update\n";
			}
		}
		
		else if(in_line.find("--") != std::string::npos)
		{	
			pos = in_line.find_first_of("--"); //assignment operator pos
			std::string updt_var = in_line.substr(0, pos); //var name to update
			std::cout << "var name to update: " << updt_var << "yeah!\n";
			int updt_val = 0;
			for(int i = exe_lvl; i >= 0; i--)
			{
				if(test.search(updt_var, i) != -1)
				{
					updt_val = test.search(updt_var, i) - 1;
					std::cout << "value to update: " << updt_val << "yeah!!\n";
					test.update(updt_var, updt_val, i);
					break;
				}
				else if(i != 0) continue;
				else std::cout << "nothing to update\n";
			}
		}
		
		else if(in_line.find("++") != std::string::npos)
		{
			//same code used in "--"
			pos = in_line.find_first_of("++"); //assignment operator pos
			std::string updt_var = in_line.substr(0, pos); //var name to update
			std::cout << "var name to update: " << updt_var << "yeah!\n";
			int updt_val = 0;
			for(int i = exe_lvl; i >= 0; i--)
			{
				if(test.search(updt_var, i) != -1)
				{
					updt_val = test.search(updt_var, i) + 1;
					std::cout << "value to update: " << updt_val << "yeah!!\n";
					test.update(updt_var, updt_val, i);
					break;
				}
				else if(i != 0) continue;
				else std::cout << "nothing to update\n";
			}
		}
		
		else if((in_line.find("START")!= std::string::npos)  && in_line.find_first_of("START") == 0)
		{
			std::cout << "current execution level: " << exe_lvl << "\n";
			exe_lvl++;
			std::cout << "updated execution level: " << exe_lvl << "\n";
		}
		
		else if((in_line.find("FINISH")!= std::string::npos)  && in_line.find_first_of("FINISH") == 0)
		{
			std::cout << "current execution level: " << exe_lvl << "\n";
			if(exe_lvl > 0) 
			{
				for(int i = 0; i < 30; i++) test.pop_local_scope(i, exe_lvl);
			}
			if(exe_lvl > 0) exe_lvl--;
			else std::cout << "cannot drop execution level below 0 \n";
			std::cout << "updated execution level: " << exe_lvl << "\n";
		}	
		//std::cin.ignore();
	}
	
	return 0;
}
