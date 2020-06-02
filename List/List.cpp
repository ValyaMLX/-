#include <iostream>

template<typename type>
class List {
private:
	template<typename type>
	class Node {
	public:
		type data;
		Node* next;
		Node* prev;

		Node(type data, Node* next = nullptr, Node* prev = nullptr)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};

	size_t size;
	Node<type>* head;
	Node<type>* tail;

public:
	List();
	~List();

	void Add(type data);
	void AddHead(type data);
	type& operator[](const int index);
	size_t GetSize();
	void Insert(type data, int index);
	type Peek();
	void Delete(int index);
	void Clear();
};

template<typename type>
List<type>::List()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename type>
List<type>::~List()
{
}

template<typename type>
void List<type>::Add(type data)
{
	if (head == nullptr)
	{
		head = tail = new Node<type>(data);
	}
	else
	{
		Node<type>* current = new Node<type>(data, nullptr, tail);
		tail->next = current;
		tail = current;
	}

	size++;
}

template<typename type>
void List<type>::AddHead(type data)
{
	if (head == nullptr)
	{
		head = tail = new Node<type>(data);;
	}
	else
	{
		Node<type>* current = new Node<type>(data, head);
		head = current;
	}

	size++;
}

template<typename type>
type& List<type>::operator[](const int index)
{
	Node<type>* current;
	int iterator;

	if (index <= size / 2)
	{
		current = head;
		iterator = 0;
		while (true)
		{
			if (iterator == index)
			{
				return current->data;
			}
			else
			{
				current = current->next;
				iterator++;
			}
		}
	}
	else
	{
		current = tail;
		iterator = size - 1;
		while (true)
		{
			if (iterator == index)
			{
				return current->data;
			}
			else
			{
				current = current->prev;
				iterator--;
			}
		}
	}
}

template<typename type>
size_t List<type>::GetSize()
{
	return size;
}

template<typename type>
void List<type>::Insert(type data, int index)
{
	if (index == 0)
	{
		AddHead(data);
	}
	else if (index == size)
	{
		Add(data);
	}
	else
	{
		Node<type>* previous;
		Node<type>* current;

		if (index <= size / 2)
		{
			previous = head;

			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}

			current = new Node<type>(data, previous->next, previous);
			previous->next->prev = current;
			previous->next = current;
		}
		else
		{
			previous = tail;

			for (int i = size - 1; i > index; i--)
			{
				previous = previous->prev;
			}

			current = new Node<type>(data, previous, previous->prev);
			previous->prev->next = current;
			previous->prev = current;
		}
	}

	size++;
}

template<typename type>
type List<type>::Peek()
{
	return tail->data;
}

template<typename type>
void List<type>::Delete(int index)
{
	if (index == 0)
	{
		Node<type>* temp = head;
		head = head->next;
		delete temp;
	}
	else if (index == size - 1)
	{
		Node<type>* temp = tail;
		tail = tail->prev;
		delete temp;
	}
	else
	{
		Node<type>* previous;
		Node<type>* toDelete;

		if (index <= size / 2)
		{
			previous = head;

			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}

			toDelete = previous->next;
			previous->next = toDelete->next;
			toDelete->next->prev = previous;
		}
		else
		{
			previous = tail;

			for (int i = size - 1; i > index + 1; i--)
			{
				previous = previous->prev;
			}

			toDelete = previous->prev;
			previous->prev = toDelete->prev;
			toDelete->prev->next = previous;
		}

		delete toDelete;
	}
	size--;
}

template<typename type>
void List<type>::Clear()
{
	while (size > 0)
	{
		Node<type>* temp = head;
		head = head->next;
		delete temp;
		size--;
	}
}

int main()
{
	List<int> list;

	for (int i = 0; i < 10; i++)
		list.Add(i * 10);

	list.Insert(65, 7);
	//list.AddHead(-10);
	list.Delete(10);

	for (int i = 0; i < list.GetSize(); i++)
		std::cout << list[i] << std::endl;

	list.Clear();

	for (int i = 0; i < 5; i++)
		list.Add(i * 2);

	for (int i = 0; i < list.GetSize(); i++)
		std::cout << list[i] << std::endl;

	return 0;
}