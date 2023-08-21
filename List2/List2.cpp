#include<iostream>

#define delin "\n_____________________________________________________\n"

class Iterator;
class ReversIterator;

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
		friend class Iterator;
		friend class ReversIterator;

	}*Head, *Tail;  //сразу же объявляем элементы класса типа Element*

	unsigned int size;
public:
	List()
	{
		Head = Tail = nullptr;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	List(const std::initializer_list<int>& il):List()
	{
		for (int i : il) push_back(i);
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		std::cout << "LDestructor:\t" << this << std::endl;
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
//Iterators

	class ReversIterator
	{
		Element* Temp;
	public:
		ReversIterator(Element* Temp = nullptr) : Temp(Temp)
		{
			std::cout << "IConstructor:\t" << this << std::endl;
		}
		~ReversIterator()
		{
			std::cout << "IDestructor:\t" << this << std::endl;
		}

		ReversIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		bool operator==(const ReversIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReversIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int operator*()
		{
			return Temp->Data;
		}	
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

	//Range-based for loop

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ReversIterator begin(int)
	{
		return Tail;
	}
	ReversIterator end(int)
	{
		return nullptr;
	}

};

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
	std::cout << delin;
	list.insert(123, 4);
	list.print();
	std::cout << delin;
	list.erase(2);
	list.print();
	std::cout << delin;
#endif 

	List list = { 3,5,8,13,21 };
	for (int i : list) std::cout << i << std::endl;
	for (int i = list.begin(); i != list.end(); i++) std::cout << i << std::endl;	
}