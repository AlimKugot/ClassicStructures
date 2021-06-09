#include <iostream>

using namespace std;

/*
Работа №5

С клавиатуры вводится последовательность целых чисел. Необходимо:
1) Построить дерево бинарного поиска;
2) Предоставить пользователю меню, содержащее 4 пункта:
1. Найти введённое с клавиатуры число;
2. Вывести дерево в префиксном порядке;
3. Вывести дерево в инфиксном порядке;
4. Вывести дерево в постфиксном порядке.
*/


struct Node 
{
	int data;
	struct Node* left;
	struct Node* right;

	Node(int x)
	{
		data = x;
		left = nullptr;
		right = nullptr;
	}
};


void start(Node*& root);
void menu(Node*& root);
void printPrefix(Node* root);
void printInfix(Node* root);
void printPostfix(Node* root);
void find_menu(Node * root); 
Node* find(Node* root, int n);
void insertNode(Node*& n, int num);
void cleanUp(Node*& n);


int main()
{
	struct Node* root;
	start(root);
	menu(root);
	return 0;
}


void start(Node*& root)
{
	string temp;
	int num;
	cout << "Работа с бинарным деревом:" << endl
		<< endl
		<< "Предлагается вводить элементы(признак окончания \"exit\")" << endl
		<< "После чего выведется меню" << endl
		<< endl
		<< "Let's start!"
		<< endl
		<< endl
		<< "-------------------------------------" << endl;

	cout << "Вставьте корень(root): ";
	cin >> temp;
	if (temp == "exit") 
	{
		cout << endl << "Вы ничего не ввели :(" << endl;
		exit(0);
	}
	root = new Node(stoi(temp));

	while (true)
	{
		cout << "Вставьте элемент: ";
		cin >> temp;

		if (temp == "exit") break;
		num = stoi(temp);

		insertNode(root, num);
	}

	cout << endl
		<< "Вставка окончена" << endl
		<< endl
		<< "-------------------------------------" << endl;
}


void menu(Node*& root) 
{
	cout << "Меню:" << endl;
	
	cout << "1. Найти введённое с клавиатуры число" << endl;
	cout << "2. Вывести дерево в префиксном порядке" << endl;
	cout << "3. Вывести дерево в инфиксном порядке" << endl;
	cout << "4. Вывести дерево в постфиксном порядке." << endl;
	cout << "0. Выход" << endl;
	cout << endl;

	cout << "Вы выбрали: ";
	int choice;
	cin >> choice;
	cout << "--------------" << endl;

	switch (choice)
	{
		case 1:
			find_menu(root);
			break;
		case 2:
			printPrefix(root);
			break;
		case 3: 
			printInfix(root);
			break;
		case 4:
			printPostfix(root);
			break;
		case 0:
			cleanUp(root);
			cout << endl << "Выход из программы ..." << endl;
			exit(0);
		default:
			cout << "Incorrect input, please try again ... " << endl;
			break;
	}
	cout << endl << endl << endl;
	menu(root);
}


void insertNode(Node*& n, int num)
{
	Node * son = n;
	Node * father = nullptr;
	while (son != nullptr) 
	{
		father = son;
		son = (num < son->data) ? son->left : son->right;
	}

	if (father == nullptr) father = new Node(num);
	else if (num > father->data) father->right = new Node(num);
	else if (num < father->data) father->left = new Node(num);
}


void find_menu(Node * root) 
{
	int num;
	cout << "Введите число для поиска: ";
	cin >> num;

	Node* res = find(root, num);
	if (res == nullptr)
		cout << "Не найдено" << endl;
	else 
		cout << "Нашёлся, address: " << res << endl;
}


Node* find(Node * root, int n)
{
	if (root == nullptr || root->data == n) return root;
	(n < root->data) ? find(root->left, n) : find(root->right, n);
	return nullptr;
}


void printPrefix(Node * root) 
{
	if (root == nullptr) return;

	cout << root->data << " "; 
	printPrefix(root->left);
	printPrefix(root->right);
}


void printInfix(Node* root)
{
	if (root == nullptr) return;

	printPrefix(root->left);
	cout << root->data << " "; 
	printPrefix(root->right);
}


void printPostfix(Node * root) 
{
	if (root == nullptr) return;

	printPrefix(root->left);
	printPrefix(root->right);
	cout << root->data << " "; 
}


void cleanUp(Node *& root)
{
	if (root == nullptr) return;

	cleanUp(root->left);
	cleanUp(root->right);

	cout << "Удаляю ветку: " << root->data << endl;
	delete root;
}
