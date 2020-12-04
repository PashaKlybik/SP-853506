#include <stdio.h>
#include <iostream>

using namespace std;

struct Data
{
	char *str;
};

struct Node
{
	Node *next;
	Node *prev;
	Data *data;
};

Node *Tail(Node *head)
{
	Node *temp = head;
	while (temp != NULL)
	{
		if (temp->next != NULL)
			temp = temp->next;
		else
			break;
	}
	return temp;
}

Node *AddToStart(Node *head)
{
	cout << "Введите строку: \n";
	char *text = new char[80];
	cin >> text;
	if (head == NULL)
	{
		Node *temp = new Node;
		temp->next = NULL;
		temp->prev = NULL;
		Data *data = new Data;
		data->str = text;
		temp->data = data;
		head = temp;
	}
	else
	{
		Node *swap = head;
		Node *temp = new Node;
		head->prev = temp;
		temp->next = swap;
		temp->prev = NULL;
		Data *data = new Data;
		data->str = text;
		temp->data = data;
		head = temp;
	}
	return head;
}

Node *AddToEnd(Node *head)
{
	cout << "Введите строку: \n";
	char *text = new char[80];
	cin >> text;
	if (head == NULL)
	{
		Node *temp = new Node;
		temp->next = NULL;
		temp->prev = NULL;
		Data *data = new Data;
		data->str = text;
		temp->data = data;
		head = temp;
	}
	else
	{
		Node *swap = Tail(head);
		Node *temp = new Node;
		swap->next = temp;
		temp->prev = swap;
		temp->next = NULL;
		Data *data = new Data;
		data->str = text;
		temp->data = data;
	}
	return head;
}

Node *DeleteWithNumber(Node *head, bool print)
{
	int number;
	if (print)
		cin >> number;
	else
		number = 0;
	int i = 0;
	if (head != NULL)
	{
		Node *temp = head;
		bool find = false;
		while (temp != NULL)
		{
			if (number == i)
			{
				find = true;
				break;
			}
			if (temp->next != NULL)
				temp = temp->next;
			else
				break;
			i++;
		}
		if (find)
		{
			Node *prev = temp->prev;
			Node *next = temp->next;
			if (prev != NULL) prev->next = next;
			if (next != NULL) next->prev = prev;
			if (temp == head) head = head->next;
			delete temp;
		}
		else
		{
			if (print)
				cout << "Нет элемента с указанным номером\n";
		}
	}
	else
	{
		if(print)
			cout << "Нет элемента с указанным номером\n";
	}
	return head;
}

Node *ClearList(Node *head)
{
	while (head != NULL)
		head = DeleteWithNumber(head, false);
	return head;
}

void ShowList(Node *head)
{
	Node *temp = head;
	while (temp != NULL)
	{
		cout << temp->data->str << "\n";
		if (temp->next != NULL)
			temp = temp->next;
		else
			break;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int choice = 0;
	Node *head = NULL;
	bool flag = true;
	while (flag)
	{
		system("cls");
		cout << "1 - добавить строку в начало списка;\n2 - добавить строку в конец списка;\n3 - удалить элемент списка с номером;\n4 - очистить список;\n5 - показать список;\n6 - выход;\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			head = AddToStart(head);
			break;
		case 2:
			head = AddToEnd(head);
			break;
		case 3:
			cout << "Введите число (нумерация с 0): \n";
			head = DeleteWithNumber(head, true);
			break;
		case 4:
			head = ClearList(head);
			break;
		case 5:
			ShowList(head);
			break;
		case 6:
			flag = false;
			break;
		}
		if(choice != 6)
			system("pause");
	}
	system("pause");
	return 0;
}