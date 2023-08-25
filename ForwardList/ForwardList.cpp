#include<iostream>

template<typename T>class ForwardList;
template<typename T>class Element;
template<typename T>class Iterator;
template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);

template<typename T> class Element
{
	T Data; //значение элемента
	Element<T>* pNext; //адрес следующего элемента

public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		std::cout << "EConstructor:\t" << this << std::endl;
	}
	~Element()
	{
		std::cout << "EDestructor:\t" << this << std::endl;
	}

	friend class ForwardList<T>;
	friend class Iterator<T>;
	template<typename T> friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);

};

template<typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) : Temp(Temp)
	{
		std::cout << "IConstructor:\t" << this << std::endl;
	}
	~Iterator()
	{
		std::cout << "IDestructor:\t" << this << std::endl;
	}

	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	T operator*()
	{
		return Temp->Data;
	}
};

template<typename T> class ForwardList
{
	Element<T>* Head; //Голова списка, содержит адрес начального элемента списка
public:
	ForwardList()
	{
		Head = nullptr; //если список пуст, то его голова указывает на 0
		std::cout << "FLConstructor:\t" << this << std::endl;
	}
	ForwardList(const std::initializer_list<T>& list)
	{
		for (T i : list) push_back(i);
	}
	ForwardList(const ForwardList<T>& other):ForwardList()
	{
		*this = other;
		std::cout << "FLCopyConstructor:\t" << this << std::endl;
	}
	ForwardList(ForwardList<T>&& other): ForwardList()
	{
		*this = std::move(other); //функция move() принудительно вызывает MoveAssigment для объекта
		std::cout << "FLMoveConstructor:\t" << this << std::endl;
	}
	~ForwardList()
	{
		while (Head)
			pop_front();
		std::cout << "FLDestructor:\t" << this << std::endl;
	}
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		std::cout << "FLCopyAssignment:\t" << this << std::endl;
		return *this;
	}
	ForwardList<T>& operator=(ForwardList<T>&& other)
	{
		while (Head) pop_front();
		Head = other.Head;
		other.Head = nullptr;
		std::cout << "FLMoveAssignment:\t" << this << std::endl;
		return *this;
	}

	//Adding Elements

	void push_front(T Data)
	{
		Head = new Element<T>(Data, Head);
	}
	void push_back(T Data)
	{
		if (!Head) return push_front(Data);
		Element<T>* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data);
	}
	void pop_front() 
	{
		Element<T>* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
	}
	void pop_back()
	{
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;	
		Temp->pNext = nullptr;
	}
	void insert(int index, T Data)
	{
		if (index==0) return push_front(Data);
		Element<T>* Temp = Head;
		for (int i = 0; i < index-1; i++) 
			if(Temp->pNext)
				Temp = Temp->pNext;
		Element<T>* New = new Element<T>(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		if (index==0) return pop_front();
		Element<T>* Temp = Head;
		for (int i = 0; i < index-1; i++) 
			if (Temp->pNext)
				Temp = Temp->pNext;
		Element<T>* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
	}

	//Methods

	void print()const
	{	
		std::cout << "Head: " << Head << std::endl;
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	}

	//Range-based for loop

	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	friend class Iterator<T>;
	template<typename T> friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	for (Element<T>* Temp = right.Head; Temp; Temp = Temp->pNext) 
		cat.push_back(Temp->Data);
	return cat;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	//list.push_back(123);
	list = list;
	list.print();

	int value;
	int index;
	std::cout << "Введите индекс элемента: "; std::cin >> index;
	std::cout << "Введите значение элемента: "; std::cin >> value;
	list.insert(index, value);
	list.print();

	std::cout << "Введите индекс элемента: "; std::cin >> index;
	list.erase(index);
	list.print();

	//ForwardList list2 = list;	//Copy constructor
	//ForwardList list2;
	//list2 = list;		//Copy assignment
	//list2.print();
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

	ForwardList<char> list = { 'H','e','l','l','o' };
	ForwardList<char> list2 = { 'W', 'o', 'r','l','d'};
	ForwardList<char> list3 = list + list2;
	for ( char i : list3) 
		std::cout << i << "\t" << std::endl;
#endif // RANGE_BASED_FOR_LIST
}