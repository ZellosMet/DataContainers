#include<iostream>

#define delim "\n----------------------------------------------------------------\n"
template<typename T> class List;
template<typename T> class Element;
template<typename T> List<T> operator+(const List<T>& left, const List<T>& right);

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			std::cout << "EConstructor:\t" << this << std::endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			std::cout << "EDestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		friend class List<T>;
		template<typename T>friend List<T> operator+(const List<T>& left, const List<T>& right);
	} *Head, *Tail;  //сразу же объявляем элементы класса типа Element*
	unsigned int size;

	class constBaseIterator
	{
	protected:
		Element* Temp;
	public:
		constBaseIterator(Element* Temp) : Temp(Temp)
		{
#ifdef DEBUG
			std::cout << "BItConstructor:\t" << this << std::endl;
#endif // DEBUG

		}
		~constBaseIterator()
		{
#ifdef DEBUG
			std::cout << "BItDestructor:\t" << this << std::endl;
#endif // DEBUG

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
		constIterator(Element* Temp = nullptr) : constBaseIterator(Temp)
		{
#ifdef DEBUG
			std::cout << "IConstructor:\t" << this << std::endl;
#endif // DEBUG

		}
		~constIterator()
		{
#ifdef DEBUG
			std::cout << "IDestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		constIterator& operator++()
		{
			constBaseIterator::Temp = constBaseIterator::Temp->pNext;
			return *this;
		}
		constIterator operator++(int)
		{
			constIterator old = *this;
			constBaseIterator::Temp = constBaseIterator::Temp->pNext;
			return old;
		}
		constIterator& operator--()
		{
			constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
			return *this;
		}
		constIterator operator--(int)
		{
			constIterator old = *this;
			constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
			return old;
		}
	};

class constReversIterator: public constBaseIterator
{
public:
	constReversIterator(Element* Temp = nullptr) : constBaseIterator(Temp)
	{
#ifdef DEBUG
		std::cout << "RIConstructor:\t" << this << std::endl;
#endif // DEBUG

	}
	~constReversIterator()
	{
#ifdef DEBUG
		std::cout << "RIDestructor:\t" << this << std::endl;
#endif // DEBUG

	}
	constReversIterator& operator++()
	{
		constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
		return *this;
	}
	constReversIterator operator++(int)
	{
		constReversIterator old = *this;
		constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
		return old;
	}
	constReversIterator& operator--()
	{
		constBaseIterator::Temp = constBaseIterator::Temp->pNext;
		return *this;
	}
	constReversIterator operator--(int)
	{
		constReversIterator old = *this;
		constBaseIterator::Temp = constBaseIterator::Temp->pNext;
		return old;
	}
};

class Iterator :public constIterator
{
public:
	Iterator(Element* Temp = nullptr) : constIterator(Temp) {}
	T& operator*()
	{
		return constBaseIterator::Temp->Data;
	}
};

class ReversIterator :public constReversIterator
{
public:
	ReversIterator(Element* Temp = nullptr) : constReversIterator(Temp) {}
	T& operator*()
	{
		return constBaseIterator::Temp->Data;
	}
};

constIterator cbegin()const;	
constIterator cend()const;
constReversIterator rcbegin()const;
constReversIterator rcend()const;
Iterator begin();
Iterator end();
ReversIterator rbegin();
ReversIterator rend();

List();
List(const std::initializer_list<T>& il);
List(const List<T>& other);
~List();

						//Operators
List<T>& operator=(const List<T>& other);

					//Adding elements
void push_front(T Data);
void push_back(T Data);
void insert(T Data, int index);

					//Removing elements
void pop_front();
void pop_back();
void erase(int index);

						//Methods
void print()const;
void revprint()const;

						//Friends
template<typename T>friend List<T> operator+(const List<T>& left, const List<T>& right);
};

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::constIterator it = right.cbegin(); it != right.cend(); ++it)
		cat.push_back(*it);
	return cat;
}

template<typename T>typename List<T>::constIterator List<T>::cbegin()const
{
	return Head;
}
template<typename T>typename List<T>::constIterator List<T>::cend()const
{
	return nullptr;
}
template<typename T>typename List<T>::constReversIterator List<T>::rcbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::constReversIterator List<T>::rcend()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReversIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReversIterator List<T>::rend()
{
	return nullptr;
}

//Adding elements
template<typename T> void List<T>::push_front(T Data)
{
	if (!Head && !Tail) Head = Tail = new Element(Data);
	else Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T> void List<T>::push_back(T Data)
{
	if (!Head && !Tail) Head = Tail = new Element(Data);
	else Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T> void List<T>::insert(T Data, int index)
{
	if (!index) return push_front(Data);
	if (index > size) return;
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
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

//Removing elements
template<typename T> void List<T>::pop_front()
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
template<typename T> void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T> void List<T>::erase(int index)
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
template<typename T> void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		std::cout << Temp->pPrev << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
}
template<typename T> void List<T>::revprint()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		std::cout << Temp->pPrev << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
}
template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
#ifdef DEBUG
	std::cout << "LConstructor:\t" << this << std::endl;
#endif // DEBUG

}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T i : il) push_back(i);
}
template<typename T> List<T>::List(const List<T>& other) :List()
{
	*this = other;
}
template<typename T> List<T>::~List()
{
	while (!Tail)pop_back();
#ifdef DEBUG
	std::cout << "LDestructor:\t" << this << std::endl;
#endif // DEBUG

}

//Operators
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other) return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
#ifdef DEBUG
	std::cout << "LCopyAssignment:\t" << std::endl;
#endif // DEBUG

	return *this;
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
	List<char> list2 = { 'W','o','r','l','d'};
	for (List<char>::constIterator i = list.cbegin(); i != list.cend(); ++i) std::cout << *i << "\t";
	std::cout << delim;
	for (List<char>::constIterator i = list2.cbegin(); i != list2.cend(); ++i) std::cout << *i << "\t";
	std::cout << delim;
	List<char> list3 = list + list2;
	for (List<char>::Iterator i = list3.begin(); i != list.end(); ++i) std::cout << *i;
}