#include<iostream>

class ForwardList;
class Element;
class Iterator;
ForwardList operator+(const ForwardList& left, const  ForwardList& right);

class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;

public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
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
	Element* Head;
	Element* Tail;
public:
	ForwardList()
	{
		Head = Tail = nullptr;
		std::cout << "FLConstructor:\t" << this << std::endl;
	}
	ForwardList(const std::initializer_list<int>& list)
	{
		for (int i : list) push_back(i);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		*this = other;
		std::cout << "FLCopyConstructor:\t" << this << std::endl;
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);
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
		Element* Temp = new Element(Data);
		Temp->pNext = Head;
		if (Head)
			Head->pPrev = Temp;
		if(!Tail)
			Tail = Temp;
		Head = Temp;
	}
	void push_back(int Data)
	{
		Element* Temp = new Element(Data);
		Temp->pPrev = Tail;
		if (Tail)
			Tail->pNext = Temp;
		if (!Head)
			Head = Temp;
		Tail = Temp;
	}
	void pop_front()
	{
		if (!Head) return;
		Element* Temp = Head->pNext;
		if (Temp)
			Temp->pPrev = nullptr;
		else
			Tail = Temp;
		delete Head;
		Head = Temp;
	}
	void pop_back()
	{
		if (!Tail) return;
		Element* Temp = Tail->pPrev;
		if (Temp)
			Temp->pNext = nullptr;
		else
			Head = nullptr;
		delete Tail;
		Tail = Temp;
	}
	void insert(int index, int Data)
	{
		if (!index) return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			if (Temp->pNext)
				Temp = Temp->pNext;
		if (!Temp->pNext) return push_back(Data);
		Element* New = new Element(Data);
		New->pPrev = Temp;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Tail->pPrev = New;
	}
	void erase(int index)
	{
		if (!index) return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			if (Temp->pNext)
				Temp = Temp->pNext;
		if (!Temp->pNext) return pop_back();
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		Erased->pPrev = Erased->pPrev->pPrev;
		delete Erased;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Tail->pPrev = Temp;
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
		return Tail->pNext; ///???
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
//#define OPERATOR_PLUS_CHECK
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
		list.push_back(rand() % 100);
	list.print();
	
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	list.insert(10, 123);
	list.print();
	list.erase(10);
	list.print();

#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2 = list1;
	list2.print();
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
	std::cout << std::endl << std::endl << std::endl;

	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
	std::cout << std::endl << std::endl << std::endl;

#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_LIST

	ForwardList list = { 3, 5, 8, 13, 21, 34, 55};
	for (int i : list)
		std::cout << i << "\t" << std::endl;

#endif // RANGE_BASED_FOR_LIST
}