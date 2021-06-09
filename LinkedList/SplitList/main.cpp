#include <iostream>

using namespace std;

/*
Работа №3

Для списка из "Работы №2" необходимо выполнить следующие преобразования:
1) Удалить из списка все узлы, содержащие заданный исходящий номер;
2) Заменить узлы, соответствующие звонкам с продолжительностью больше 5-ти 
на соответствующее количество узлов, имеющих длительность разговора <=5 по максимуму так, 
чтобы суммарная длительность в замещающих узлах была равна исходной. 
Например, если в узле было 14, то будет 5, 5 и 4. 
*/



/*
Основная проблема в том, что мы работаем с односвязным списком:
когда удаляется элемент, у предыдущего остаётся неправильный указатель 
на удалённый следующий элемент

Решение: отдельно работаю с head и далее передаю в ф-ию всегда следующий элемент.
*/


struct call 
{
	string in;
	string out;
	int length;
	call * next;
};

struct que {
	struct call * first;
	struct call * last;
};


call * create_list(call ** node);
void clean_list(call ** first);

void print(call * node);
int count(call * first);
void find_last(call ** first);
void divide_list(call ** node);
void delete_equals_in_list(call ** first, call ** last); 
void delete_equals_next(call ** next, string number);

int main()
{
	que q;
	q.last = create_list(&(q.first));

	cout << "Всего элементов: " << to_string(count(q.first)) << endl;
	
	divide_list(&q.first);
	cout << "После разбиения на числа <= 5" << endl;
	print(q.first);

	delete_equals_in_list(&(q.first), &(q.last));
	cout << "После удаления осталось элементов: " << endl;
	print(q.first);

	clean_list(&(q.first));
	return 0;
}


/*
	Создаёт список и возвращает последний элемент списка
*/
call * create_list(call ** node) 
{
	string in_x;
	string out_x;
	int length;
	static int max_length = 0;

	cout << "Исходящий номер: ";
	cin >> in_x;
	if (in_x == "0") 
	{
		cout << endl << "-------------------------------------------------------------" << endl;
		cout << "Максимальная длина разговора: " << to_string(max_length) << endl;
		*node = NULL;
		return *node;
	}

	cout << "Входящий номер: ";
	cin >> out_x;
	//проверка размера
	if (in_x.length() > 11 || out_x.length() > 11) 
	{
		cerr << "Ошибка, слишком большой номер";
		return NULL;
	}


	cout << "Введите длину разговора: ";
	cin >> length;
	if (length > max_length) max_length = length;

	cout << "\n";

	(*node) = new call;
	(*node)->in = in_x;
	(*node)->out = out_x;
	(*node)->length = length;

	create_list(&((*node)->next));
}	


/*
	Расщипляет список на числа <= 5

	Пример: list->number = 14. Значит, расщипляем на три листа: 5 + 5 + 4
*/
void divide_list(call ** first) 
{
	call * node = *first;
	if (node == NULL || node->length < 0) return;

	call * next_node = (*first)->next;
	int length = (*first)->length;

	//TODO: убери двойное условие
	while(length > 0)
	{
		int temp = (length - 5 > 0) ? (5) : (length);
		length -= 5;

		node->in = (**first).in;
		node->out = (**first).out;
		node->length = temp;

		if (length > 0) 
		{
			node->next = new call();
			node = node->next;	
		}
	}
	node->next = next_node;
	
	divide_list(&next_node);
}


/*
	Удаляет все элементы списка, которые содержат в in или out введённый с консоли номер
*/
void delete_equals_in_list(call ** first, call ** last) 
{
	cout << "Введите номер, который нужно удалить: ";
	string number;
	cin >> 	number;
	if (number == "0" || number.length() > 11 || first == NULL) return;

	int countBefore = count(*first);

	call * next = (*first)->next;

	//check all except head
	delete_equals_next(&next, number);

	//check head
	if ((*first)->out == number || (*first)->in == number) 
	{
		delete *first;
		*first = next;
	}

	//check end
	if (*last == NULL) find_last(last);

	cout << "delete_number: Нашёл и удалил элементов: " 
		 << to_string(countBefore - count(*first)) 
		 << endl;
}


/*
	Вспомогательная ф-ия для delete_equals_in_list(...):
		yдаляет все элементы if in == number || out == number.
	
	Предпочтительно обработать первый элемент, как частный случай 
	и передать в эту ф-цию остальную часть списка
*/
void delete_equals_next(call ** next, string number)
{
	
	if (next == NULL ||*next == NULL) return;

	if ((*next)->in == number || (*next)->out == number) 
	{
		call * temp = (*next)->next;
		delete *next;
		*next = temp;
		delete_equals_next(next, number);
	} 
	else 
	{
		delete_equals_next(&((*next)->next), number);
	}
}


/*
	Считает кол-во эл-в в списке
*/
int count(call * first)
{
	
	int i = 0;
	
	while (first != NULL) 
	{
		i++;
		first = first->next;	
	}
	
	return i;
}


/*
	Возвращает последний элемент
*/
void find_last(call ** first)
{
	call * node = *first;

	while (node != NULL)
	{
		if (node->next == NULL) 
		{
			*first = node;	
		}

		node = node->next;
	}
}

/*
	Печатает у всех элементов in, out и length
*/
void print(call * first) 
{
	for (int i = 1; first != NULL; i++) 
	{
		cout << "#"
		       	<< to_string(i) << endl
			<< "in: " << first->in << endl
			<< "out: " << first->out << endl
			<< "length: " << first->length << endl
			<< endl;
		first = first->next;
	}
}


/*
	Чистит за нами память
*/
void clean_list(call ** first) 
{
	int i = 0;

	while ((*first) != NULL) 
	{
		call * temp = (*first)->next;
		delete (*first);
		*first = temp;
		i++;
	}

	cout << endl
		<< "clean_list: Очистил оставшихся элементов: " 
	        << to_string(i) 
		<< endl;
}
