#include<iostream>

class Element
{
	int Data; //значение элемента
	Element* pNext; //адрес следующего элемента

public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		std::cout << "EConstructor:\t" << this << std::endl;
	}
	~Element()
	{
		std::cout << "EDestructor:\t" << this << std::endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head; //Голова списка, содержит адрес начального элемента списка
public:
	ForwardList()
	{
		Head = nullptr; //если список пуст, то его голова указывает на 0
		std::cout << "FLConstructor:\t" << this << std::endl;
	}
	ForwardList(const ForwardList& other)
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		std::cout << "FLCopyConstructor:\t" << this << std::endl;
	}
	ForwardList (ForwardList&& other)noexcept
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			Temp->pNext = other.Head->pNext;
			Temp = Temp->pNext;
			other.Head->pNext = nullptr;
		}
		std::cout << "FLMoveConstructor:\t" << this << std::endl;
	}
	~ForwardList()
	{
		while (Head)
			pop_front();
		std::cout << "FLDestructor:\t" << this << std::endl;
	}
	ForwardList& operator=(const ForwardList& other)
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		return *this;
	}
	ForwardList& operator=(const ForwardList&& other)noexcept
	{
		this->Head->pNext = other.Head->pNext;
		delete other.Head->pNext;
		return *this;
	}

	//Adding Elements

	void push_front(int Data)
	{
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		if (!Head) push_front(Data);
		else
		{
			Element* Temp = Head;
			while (Temp->pNext)
				Temp = Temp->pNext;
			Temp->pNext = new Element(Data);
		}
	}
	void pop_front() 
	{
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
	}
	void pop_back()
	{
		Element* Temp = Head;
		Element* Next = Temp->pNext;
		while (Next->pNext)
		{
			Temp = Temp->pNext;
			Next = Next->pNext;
		}
		Temp->pNext = nullptr;
		delete Next;	
	}
	void insert(int index, int Data)
	{
		int cnt = 0;
		Element* Temp = Head;
		while (cnt != index-1)
		{
			Temp = Temp->pNext;
			cnt++;
		}
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		int cnt = 0;
		Element* Temp = Head;
		Element* Next = Temp->pNext;
		while (cnt != index - 1)
		{
			Temp = Temp->pNext;
			Next = Next->pNext;
			cnt++;
		}
		Temp->pNext = Next->pNext;
		delete Next;
	}

	//Methods

	void print()const
	{	
		Element* Temp = Head; //Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных
		while (Temp) 
		{
			std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
			Temp = Temp->pNext; //Переход на следующий элемент
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
		list.push_front(rand() % 100);
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	list.insert(1, 5);
	list.print();
	list.erase(2);
	list.print();
	ForwardList list2 = list;
	list2.print();
	list2.push_back(10);
	ForwardList list3;
	list3 = list2;
	list3.print();
}