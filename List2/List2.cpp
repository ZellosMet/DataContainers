#include<iostream>

#define delim "\n----------------------------------------------------------------\n"

class Iterator;
class ReversIterator;
class Element;

class List
{
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
		friend class List;

	}*Head, *Tail;  //сразу же объявляем элементы класса типа Element*
	unsigned int size;

	class constBaseIterator
	{
	protected:
		Element* Temp;
	public:
		constBaseIterator(Element* Temp) :Temp(Temp)
		{
			std::cout << "BItConstructor:\t" << this << std::endl;			
		}
		~constBaseIterator()
		{
			std::cout << "BItDestructor:\t" << this << std::endl;
		}
		bool operator==(const constBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const constBaseIterator& other)const
		{
			return this->Temp != other.Temp;	
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};
public:

//Iterators
class constIterator :public constBaseIterator
	{
	public:
		constIterator(Element* Temp = nullptr) : constBaseIterator(Temp)
		{
			std::cout << "IConstructor:\t" << this << std::endl;
		}
		~constIterator()
		{
			std::cout << "IDestructor:\t" << this << std::endl;
		}
		constIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		constIterator operator++(int)
		{
			constIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		constIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		constIterator operator--(int)
		{
			constIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};

class constReversIterator:public constBaseIterator
{
public:
	constReversIterator(Element* Temp = nullptr) : constBaseIterator(Temp)
	{
		std::cout << "RIConstructor:\t" << this << std::endl;
	}
	~constReversIterator()
	{
		std::cout << "RIDestructor:\t" << this << std::endl;
	}
	constReversIterator& operator++()
	{
		Temp = Temp->pPrev;
		return *this;
	}
	constReversIterator operator++(int)
	{
		constReversIterator old = *this;
		Temp = Temp->pPrev;
		return old;
	}
	constReversIterator& operator--()
	{
		Temp = Temp->pNext;
		return *this;
	}
	constReversIterator operator--(int)
	{
		constReversIterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
};
class Iterator :public constIterator
{
public:
	Iterator(Element* Temp = nullptr) : constIterator(Temp) {}
	int& operator*()
	{
		return Temp->Data;
	}
};
class ReversIterator :public constReversIterator
{
public:
	ReversIterator(Element* Temp = nullptr) : constReversIterator(Temp) {}
	int& operator*()
	{
		return Temp->Data;
	}
};
	const constIterator cbegin()const
	{
		return Head;
	}
	const constIterator cend()const
	{
		return nullptr;
	}

	constReversIterator rcbegin()const
	{
		return Tail;
	}
	constReversIterator rcend()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	constIterator end()
	{
		return nullptr;
	}
	ReversIterator rbegin()
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	List(const std::initializer_list<int>& il):List()
	{
		for (int i : il) push_back(i);
	}
	List(const List& other):List()
	{
		*this = other;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		std::cout << "LDestructor:\t" << this << std::endl;
	}

						//Operators
	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
			std::cout << "LCopyAssignment:\t" << std::endl;
		return *this;
	}
					//Ading elements
	void push_front(int Data)
	{
		if(!Head && !Tail) Head = Tail = new Element(Data);
		else Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (!Head && !Tail) Head = Tail = new Element(Data);
		else Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Data, int index)
	{
		if (!index) return push_front(Data);
		if (index > size) return;
		Element* Temp;
		if (index < size/2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size-index-1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

					//Removing elements
	void pop_front()
	{
		if (!Head && !Tail) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;		
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (!index) return pop_front();
		if (index >= size) return;
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
		size--;
	}
				//Methods
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp->pPrev << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	}
	void revprint()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			std::cout << Temp->pPrev << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	}
};
	List operator+(const List& left, const List& right)
	{
		List cat = left;
		for (List::constIterator it = right.cbegin(); it != right.cend(); ++it)
			//(*it) *= 10;
			cat.push_back(*it);
		return cat;
	}

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
	int n;

#ifdef BASE_CHECK
	std::cout << "Введите размер списка: "; std::cin >> n;
	List list;
	for (int i = 0; i < n; i++)
		list.push_front(rand() % 100);
	list.print();
	std::cout << std::endl;
	list.pop_back();
	list.print();
	std::cout << delim;
	list.insert(123, 4);
	list.print();
	std::cout << delim;
	list.erase(2);
	list.print();
	std::cout << delim;
#endif 

	List list = { 3,5,8,13,21 };
	for (List::constIterator i = list.cbegin(); i != list.cend(); ++i) std::cout << *i << "\t";
	std::cout << delim;
	for (List::constReversIterator i = list.rcbegin(); i != list.rcend(); ++i) std::cout << *i << "\t";
	List list3 = list + list;
	for (int i : list3) std::cout << i << "\t";
	for (List::Iterator it = list3.begin(); it != list.end(); ++it) (*it) *= 10;
	for (int i : list3) std::cout << i << "\t";
}