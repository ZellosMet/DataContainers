#include<iostream>

class ForwardList;
class Element;
class Iterator;
ForwardList operator+(const ForwardList& left, const  ForwardList& right);

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
	friend class Iterator;
	friend ForwardList operator+(const ForwardList& left, const  ForwardList& right);
};

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		std::cout << "IConstructor:\t" << this << std::endl;
	}
	~Iterator()
	{
		std::cout << "IDestructor:\t" << this << std::endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}
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
	ForwardList(const std::initializer_list<int>& list)
	{
		for (int i : list) push_back(i);
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		*this = other;
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		//	push_back(Temp->Data);
		std::cout << "FLCopyConstructor:\t" << this << std::endl;
	}
	ForwardList(ForwardList&& other): ForwardList()
	{
		//this->Head = other.Head;
		//other.Head = nullptr;

		*this = std::move(other); //функция move() принудительно вызывает MoveAssigment для объекта
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
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		std::cout << "FLCopyAssignment:\t" << this << std::endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		while (Head) pop_front();
		Head = other.Head;
		other.Head = nullptr;
		std::cout << "FLMoveAssignment:\t" << this << std::endl;
		return *this;
	}

	//Adding Elements

	void push_front(int Data)
	{
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		if (!Head) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
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
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;	
		Temp->pNext = nullptr;
	}
	void insert(int index, int Data)
	{
		if (index==0) return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++) 
			if(Temp->pNext)
				Temp = Temp->pNext;
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		if (index==0) return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++) 
			if (Temp->pNext)
				Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
	}

	//Methods

	void print()const
	{	
		std::cout << "Head: " << Head << std::endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	}

	//Range-based for loop

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	friend class Iterator;
	friend ForwardList operator+(const ForwardList& left, const  ForwardList& right);

};
ForwardList operator+(const ForwardList& left, const  ForwardList& right)
{
	ForwardList cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext) 
		cat.push_back(Temp->Data);
	return cat;
}

//#define BASE_CHECK
#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	//list.push_back(123);
	list = list;
	list.print();

	/*int value;
	int index;
	cout << "Введите индекс элемента: "; cin >> index;
	cout << "Введите значение элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс элемента: "; cin >> index;
	list.erase(index);
	list.print();*/

	//ForwardList list2 = list;	//Copy constructor
	ForwardList list2;
	list2 = list;		//Copy assignment
	list2.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	std::cout << std::endl;

	ForwardList list2 = list1+list1;
	/*list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);*/
	list2.print();
	std::cout << std::endl;

	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
	std::cout << std::endl;

#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST

	ForwardList list = {3, 5, 8, 13, 21};
	for ( int i : list) 
		std::cout << i << "\t" << std::endl;
#endif // RANGE_BASED_FOR_LIST
}