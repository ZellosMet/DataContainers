#include<iostream>

#define delim "\n----------------------------------------------------------------\n"

template<typename T>
class List
{
	template<typename T>
	class Element
	{
		T Data;
		Element<T>* pNext;
		Element<T>* pPrev;

	public:
		Element(T Data, Element<T>* pNext = nullptr, Element<T>* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			std::cout << "EConstructor:\t" << this << std::endl;
		}
		~Element()
		{
			std::cout << "EDestructor:\t" << this << std::endl;
		}
		friend class List;
	};
	Element<T>* Head;
	Element<T>* Tail;  //сразу же объявляем элементы класса типа Element*
	unsigned int size;

class constBaseIterator
	{
	protected:
		Element<T>* Temp;
	public:
		constBaseIterator(Element<T>* Temp) : Temp(Temp)
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
		const T& operator*()const
		{
			return Temp->Data;
		}
	};
public:

//Iterators
class constIterator :public constBaseIterator
	{
	public:
		constIterator(Element<T>* Temp = nullptr) : constBaseIterator(Temp)
		{
			std::cout << "IConstructor:\t" << this << std::endl;
		}
		~constIterator()
		{
			std::cout << "IDestructor:\t" << this << std::endl;
		}
		constIterator& operator++()
		{
			this->Temp = this->Temp->pNext;
			return *this;
		}
		constIterator operator++(int)
		{
			constIterator old = *this;
			this->Temp = this->Temp->pNext;
			return old;
		}
		constIterator& operator--()
		{
			this->Temp = this->Temp->pPrev;
			return *this;
		}
		constIterator operator--(int)
		{
			constIterator old = *this;
			this->Temp = this->Temp->pPrev;
			return old;
		}
	};

class constReversIterator:public constBaseIterator
{
public:
	constReversIterator(Element<T>* Temp = nullptr) : constBaseIterator(Temp)
	{
		std::cout << "RIConstructor:\t" << this << std::endl;
	}
	~constReversIterator()
	{
		std::cout << "RIDestructor:\t" << this << std::endl;
	}
	constReversIterator& operator++()
	{
		this->Temp = this->Temp->pPrev;
		return *this;
	}
	constReversIterator operator++(int)
	{
		constReversIterator old = *this;
		this->Temp = this->Temp->pPrev;
		return old;
	}
	constReversIterator& operator--()
	{
		this->Temp = this->Temp->pNext;
		return *this;
	}
	constReversIterator operator--(int)
	{
		constReversIterator old = *this;
		this->Temp = this->Temp->pNext;
		return old;
	}
};

class Iterator :public constIterator
{
public:
	Iterator(Element<T>* Temp = nullptr) : constIterator(Temp) {}
	T& operator*()
	{
		return this->Temp->Data;
	}
};
class ReversIterator :public constReversIterator
{
public:
	ReversIterator(Element<T>* Temp = nullptr) : constReversIterator(Temp) {}
	T& operator*()
	{
		return this->Temp->Data;
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
	List(const std::initializer_list<T>& il):List()
	{
		for (T i : il) push_back(i);
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
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
			std::cout << "LCopyAssignment:\t" << std::endl;
		return *this;
	}
					//Ading elements
	void push_front(T Data)
	{
		if(!Head && !Tail) Head = Tail = new Element<T>(Data);
		else Head = Head->pPrev = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (!Head && !Tail) Head = Tail = new Element<T>(Data);
		else Tail = Tail->pNext = new Element<T>(Data, nullptr, Tail);
		size++;
	}
	void insert(T Data, int index)
	{
		if (!index) return push_front(Data);
		if (index > size) return;
		Element<T>* Temp;
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
		Temp->pPrev = Temp->pPrev->pNext = new Element<T>(Data, Temp, Temp->pPrev);
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
		Element<T>* Temp;
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
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp->pPrev << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	}
	void revprint()const
	{
		for (Element<T>* Temp = Tail; Temp; Temp = Temp->pPrev)
			std::cout << Temp->pPrev << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	}
	friend List<T> operator+(const List<T>& left, const List<T>& right);
};

template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (List<T>::template constIterator<T> it = right.cbegin(); it != right.cend(); ++it)
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

	//List<int> list = { 3,5,8,13,21 };
	List<char> list = { 'H','e','l','l','o'};
	for (List<char>::constIterator i = list.cbegin(); i != list.cend(); ++i) std::cout << *i << "\t";
	std::cout << delim;
	for (List<char>::constReversIterator i = list.rcbegin(); i != list.rcend(); ++i) std::cout << *i << "\t";
	List<char> list3 = list + list;
	for (int i : list3) std::cout << i << "\t";
	for (List<char>::Iterator it = list3.begin(); it != list.end(); ++it) (*it) *= 10;
	for (int i : list3) std::cout << i << "\t";
}