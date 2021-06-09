#include <iostream>

using namespace std;

/*
Работа №2

Необходимо построить линейный односвязный список вида "очередь". 
Каждый узел списка описывает телефонный звонок и имеет информационные поля:
а) номер телефона-источника (11 знаков);
б) номер телефона-приёмника (11 знаков);
в) продолжительность разговора в минутах (целое число).
Информация для построения списка вводится с клавиатуры. Признак окончания - "0". 
Для построенного списка необходимо:
1) вывести информацию о звонке с максимальной длительностью разговора;
2) очистить память после использования списка.
*/



struct call 
{
	string in;
	string out;
	int length;
	call * next;
};

struct que {
	struct call * first, last;
};


call * create_list(call ** node);
void clean_list(call * first);


int main()
{
	que q;
	q.last = * create_list(&(q.first));

	clean_list(q.first);
	return 0;
}

/*
	Создаёт список и возвращает последний элемент списка

	call ** node -- указатель на указатель, потому что изменяем указатель
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
		cout << "Максимальная длина разговора: " +  to_string(max_length) << endl;
		(*node)->next = NULL;
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

	//			TODO:
	//На последнем шаге мы даём пустой элемент, а не последний
	create_list(&((*node)->next));
}	


void clean_list(call * first) 
{
	call * branch = first;
	int i = 0;

	while (branch != NULL) 
	{
		call * temp = branch->next;
		delete branch;
		branch = temp;
		i++;
	}

	cout << "Удалил " + to_string(i) + " элементов(а)" << endl;
}