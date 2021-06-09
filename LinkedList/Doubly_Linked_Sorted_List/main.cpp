#include <iostream>

using namespace std;

/*
Для списков из работ №2-3 доработать программу таким образом, чтобы после ввода информации 
она предоставляла циклическое меню, содержащая следующие пункты:
1. Вывести информацию в порядке исходного ввода данных;
2. Вывести информацию в порядке роста исходящих номеров;
3. Добавить новый узел в список;
4. Выйти из меню.

P.S. Желательно решить оформление обоих видов связи на этапе оформления
*/


struct call 
{
	string in;
	string out;
	int length;

	call * sort;
	call * next;
	call * prev;
};

struct que 
{
	call * first = nullptr;
	call * last = nullptr;
} q; 


void print(call * element);
void print_all(call * first);
void print_sort(call * first);
void print_head_and_end();
void find_last(call *& first);
void clean_list(call *& first);
void sort(call * first, call * last);
void add_element_menu();
void add_element(call *& last, string in_x, string out_x, int length);
void swap(call *& el, call *& next);
int count(call * first);
void menu();

int main()
{
	menu();
	return 0;
}



void menu()
{
	while (true)
	{
		cout << endl; 
		cout << "--------------------------------------------" << endl;
		cout << "Main Menu" << endl	
				<< "1) Вывод инф-ы в порядке ввода" << endl 
				<< "2) Вывод инф-ы в порядке роста исходящих номеров" << endl 
				<< "3) Добавить узел" << endl
				<< "4) Напечатать head & end" << endl
				<< "5) Кол-во элементов" << endl
				<< "0) Выход" << endl
				<< endl;
		char choice;
		cout << "Ваш выбор - ";
		cin >> choice;
		cout << "--------------------------------------------" << endl;

		switch (choice)
		{
			case '0':
				clean_list(q.first);
				return;
			case '1':
				print_all(q.first);
				break;
			case '2':
				print_sort(q.first);
				break;
			case '3':
				add_element_menu();
				break;
			case '4':
				print_head_and_end();
				break;
			case '5':
				cout << "Кол-во элементов: "
					 << to_string(count(q.first))
					 << endl;
				break;
			default:
				cerr << "Неккоректный ввод пункта меню, введите ещё раз" << endl;
				break;
		}
	}

}


/*
 * Выводит меню для ввода
 */
void add_element_menu()
{
	string in_x;
	string out_x; 
	int length;

	cout << "Исходящий номер: ";
	cin >> in_x;
	cout << "Входящий номер: ";
	cin >> out_x;

	cout << "Введите длину разговора: ";
	cin >> length;
	cout << "\n";

	add_element(q.last, in_x, out_x, length);
	if (q.first == nullptr) q.first = q.last;
	sort(q.first, q.last);
}


/*
	Добавляет элемент в конец списка
*/
void add_element(call *& last, string in_x, string out_x, int length)
{
	//проверка размера
	if (in_x.length() > 11 || out_x.length() > 11) 
	{
		cerr << "Ошибка, слишком большой номер";
		return;
	}

	call * element = new call;
	element->in = in_x;
	element->out = out_x;
	element->length = length;
	element->next = nullptr;
	element->prev = last;

	if (last != nullptr) last->next = element;
	last = element;
}


/*
 * Bubble sort
 */
void sort(call * head, call * end)
{
	if (head == end) head->sort = head;

	for (call * c = head; c != nullptr; c = c->next)
	{
		for (call * c_next = head; c_next != nullptr; c_next = c_next->next)
		{
			if (c->in > c_next->in)
			{
				call * temp = c->sort;
				c_next->sort = temp; 
				c->sort = c_next->sort;
			}
		}
	}
}



/*
	Считает кол-во эл-в в списке
*/
int count(call * first)
{
	int i = 0;
	while (first != nullptr) 
	{
		i++;
		first = first->next;	
	}
	return i;
}

/*
 * Print for all address, in, out, length
*/
void print_all(call * first) 
{
	for (int i = 1; first != nullptr; i++) 
	{
		cout << "#" << to_string(i) << endl;	
		print(first);
		first = first->next;
	}
}

void print_sort(call * first)
{
	for (int i = 1; first != nullptr; i++) 
	{
		cout << "#" << to_string(i) << endl;
		print(first->sort);
		first = first->next;
	}
}

/*
 * Print head and end of list
 */
void print_head_and_end()
{
	call * first = q.first;
	call * last = q.last;

	cout << "Do you need sorted list (1 - YES, 0 - NO)";
	char c;
	cin >> c;
	if (c == '1')
	{
		first = q.first->sort; 
		last = q.last->sort;
	}

	cout << "Head" << endl;
	print(first);
	cout << "End" << endl;
	print(last);
}

/*
 * Печатает один элемент
 */
void print(call * element)
{
	if (element == nullptr) return;

	cout << "address: " << element << endl
		 << "in: " << element->in << endl
		 << "out: " << element->out << endl
		 << "length: " << element->length << endl
		 << "next: " << element->next << endl
		 << "prev: " << element->prev << endl
		 << endl;
}


/*
	Чистит за нами память
*/
void clean_list(call *& first) 
{
	int i = 0;

	while (first != nullptr) 
	{
		call * temp = first->next;
		delete first;
		first = temp;
		i++;
	}

	cout << endl
		<< "clean_list: Очистил элементов: " 
		<< to_string(i) 
		<< endl;
}
