#include <iostream>

using namespace std;


struct Node 
{
	int* key[2];
	Node* child[3];
	Node* parrent;
	
	Node()
    {
		parrent = nullptr;
		key[0] = nullptr;
		key[1] = nullptr;
		child[0] = nullptr;
		child[1] = nullptr;
		child[2] = nullptr;
	}

	Node(int data)
	{
		parrent = nullptr;
		key[0] = new int(data);
		key[1] = nullptr;
		child[0] = nullptr;
		child[1] = nullptr;
		child[2] = nullptr;
	}
};


void insert(Node*& n);
void insert(Node*& n, int data);
void insert_key(Node *& n, int new_key);
void search(Node* root);
Node* search(int data);
void split(Node*& n, int third);
void delete_node(Node*& root);
void delete_node(int data);
void print(Node* n);
void print_leaf_line(Node* n, int width, bool isEndOfLine);
void menu(Node*& root);

int* find_min_mid_max(int a, int b, int c);




Node* root = new Node();

int main()
{
	menu(root);
	return 0;
}



void menu(Node*& root)
{
	cout << endl; 
	cout << "--------------------------------------------" << endl;
	cout << "Main Menu" << endl	
			<< "1) Insert node" << endl 
			<< "2) Print tree" << endl
			<< "3) Search" << endl
			<< "4) Delete node" << endl
			<< "0) Exit" << endl
			<< endl;
	char choice;
	cout << "Your choice - ";
	cin >> choice;

	switch(choice)
	{
		case '1':
			insert(root);
			break;
		case '2':
			print(root);
			break;
		case '3':
			search(root);
			break;
		case '4':
			delete_node(root);
			break;
		case '0':
			cout << "Exit" << endl;
			return;
		default:
			cout << "Incorrect input, please try again ..." << endl;
			break;
	}
	cout << "--------------------------------------------" << endl;
	menu(root);
}


// static variables to print
int hight;

void print(Node* n)
{
	hight = 1;
	print_leaf_line(n, 70, true);
	cout << endl;
}

/*
 * Function-helper for print(Node* n) to print all leafes from one parrent in one line
 */
void print_leaf_line(Node* n, int width, bool isEndOfLine)
{
	int spaces = width - 10*hight;

	string k1 = " ";
	string k2 = " ";
	
	if (n != nullptr) 
	{
		if (n->key[0] != nullptr) k1 = to_string(*n->key[0]);
		if (n->key[1] != nullptr) k2 = to_string(*n->key[1]);
	}

	cout << string(spaces, ' ') 
		<< "["
		<< k1
		<< " , "
		<< k2
		<< "]";

	if (isEndOfLine && n != nullptr 
					&& (n->child[0] != nullptr 
						|| n->child[1] != nullptr
						|| n->child[2] != nullptr))
	{
		cout << endl
			 << string(spaces - 3, ' ')
			 << '/'
			 << string(5, ' ')
			 << '|'
			 << string(5, ' ')
			 << '\\'
			 << endl;
		hight++;
		// collect_numbers_in_children()
		print_leaf_line(n->child[0], width, false);
		print_leaf_line(n->child[1], 11*hight, false);
		print_leaf_line(n->child[2], 11*hight, true);
	}
}



/*
 * Console menu to insert into 2-3 tree
 */
void insert(Node*& n)
{
	cout << "Enter num: ";
	string data;
	cin >> data;
	if (data == "exit") return;

	insert(n, stoi(data));
	print(n);
	insert(n);
}


void insert(Node*& n, int data)
{
	if (n == nullptr || n->key[0] == nullptr) 
	{
		n = new Node(data);
	}
	else if (n->child[0] == nullptr && n->child[1] == nullptr && n->child[2] == nullptr)
	{
		//if full
		if (n->key[1] != nullptr) 
		{
			split(n, data);
		}
		else 
		{
			insert_key(n, data);
		}
	}
	//we have children
	else 
	{
		if (data > *n->key[0])
		{
			if (n->key[1] == nullptr)
			{
				//insert right
				insert(n->child[2], data);
			}
			else 
			{
				//keys are full
				if (data > *n->key[1])
				{
					if (n->child[0] == nullptr && n->child[1] == nullptr && n->child[2] == nullptr)
					{
						split(n, data);
					}
					else
					{
						insert(n->child[2], data);
					}
				}
				else 
				{
					//insert mid
					insert(n->child[1], data);
				}
			}
		}
		else 
		{
			if (n->key[1] == nullptr)
			{
				n->key[1] = new int(*n->key[0]);
				*n->key[0] = data;
			}
			else 
			{
				//insert left
				insert(n->child[0], data);
			}
		}
	}
}

void insert_key(Node *& n, int new_key)
{
	if (n == nullptr) 
	{
		n = new Node(new_key);
	}

	if(n->key[0] == nullptr)
	{
		*n->key[0] = new_key;
	}
	// if full use another func:  split(Node* n, int data)
	else if (n->key[1] != nullptr)
	{
		return;
	}
	// ex:
	// -> 3
	// [1,  ]
	//
	// [1, 3]
	else if (new_key > *n->key[0]) 
	{
		n->key[1] = new int(new_key);
	}
	// ex:
	// -> 1
	// [5,  ]
	//
	// [1, 5]
	else if (new_key < *n->key[0])
	{
		n->key[1] = new int(*n->key[0]);
		*n->key[0] = new_key;
	}
}

/*
 * Rebalancing 2-3 tree. Call this func when leaf is full
 */
void split(Node*& n, int third) 
{
	if (n == nullptr || n->key[0] == nullptr || n->key[1] == nullptr) return;

	int* res = find_min_mid_max(*n->key[0], *n->key[1], third);
	int min = *res;
	int mid = *(res + 1);
	int max = *(res + 2);

	Node* parrent = n->parrent;

	if (parrent == nullptr) 
	{
		if (n->child[0] == nullptr && n->child[1] == nullptr) 
		{
			Node* parrent = n;
			*n->key[0] = mid;
			n->key[1] = nullptr;
			Node* left = new Node(min);
			Node* right = new Node(max);
		
			left->parrent = parrent;
			right->parrent = parrent;	

			parrent->child[0] = left;
			parrent->child[2] = right;
		}
		else 
		{
			// There is the hardest moment in my programm.
			// Illustrate this situation to understand it, for example: 1 2 3 4 5 6 7 
			parrent = new Node(mid);
			n->parrent = parrent;

			//right child
			parrent->child[2] = new Node(max);
			parrent->child[2]->parrent = parrent;
			
			parrent->child[2]->child[0] = n->child[2];
			parrent->child[2]->child[2] = new Node(*n->child[2]->key[1]);
			parrent->child[2]->child[2]->parrent = parrent->child[2]->child[2];
			n->child[2]->key[1] = nullptr;
		
			//left child
			parrent->child[0] = n;
			n->key[1] = nullptr;
			n->child[2] = n->child[1];
			n->child[1] = nullptr;
			
			root = parrent;
		}
	}
	else if (parrent->key[1] == nullptr)
	{
		insert_key(parrent, mid);
		insert_key(parrent->child[1], min);
		
		*n->key[0] = max;
		n->key[1] = nullptr;
	}
	//parrent and n are full
	else 
	{
		*n->key[0] = min;
		*n->key[1] = max;
		split(parrent, mid);
	}
}


/*
 * Menu with console to find node
 */
void search(Node* root)
{
	cout << "Enter number to search: ";
	int data;
	cin >> data;
	Node* res = search(data);

	cout << endl;
	if (res == nullptr) 
	{
		cout << "Oups, nothing :(" << endl;
	}
	else 
	{
		cout << "Address: " << res << endl;
	}
}


/*
 * Searching algorithm in 2-3 tree
 */
Node* search(int data)
{
	return nullptr;
}


void delete_node(Node*& root)
{

}

void delete_node(int data)
{

}


/*
 * Function to find minimal, middle and maximum in 3 numbers
 *
 * @return array where first is min, second - mid, third - max
 */
int* find_min_mid_max(int a, int b, int c)
{
	int min;
	int mid;
	int max;

	if (a > b) 
	{
		if (a > c)
		{
			max = a;
			if (b > c)
			{
				mid = b;
				min = c;
			}
			else 
			{
				mid = c;
				min = b;
			}
		}
		else 
		{
			max = c;
			mid = a;
			min = b;
		}
	} 
	else 
	{
		if (b > c)
		{
			max = b;
			if (a > c)
			{
				mid = a;
				min = c;
			}
			else 
			{
				mid = c;
				min = a;
			}
		}	
		else 
		{
			max = c;
			mid = b;
			min = a;
		}
	}
	int* res = new int(3); 
	res[0] = min;
	res[1] = mid;
	res[2] = max;
	return res;
}
