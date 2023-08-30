#include"List_Header.h"

template class List<int>;
template class List<double>;
template class List<char>;

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
	if (!index)return push_front(Data);
	if (index >= size)return push_back(Data);
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
		std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
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
template<typename T> List<T>::List(const List<T>& other) : List()
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

//Element
template<typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	std::cout << "EConstructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> List<T>::Element::Element::~Element()
{
#ifdef DEBUG
	std::cout << "EDestructor:\t" << this << std::endl;
#endif // DEBUG
}

//Iteratoes
template<typename T> List<T>::constBaseIterator::constBaseIterator(Element* Temp) : Temp(Temp)
{
#ifdef DEBUG
	std::cout << "BItConstructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> List<T>::constBaseIterator::~constBaseIterator()
{
#ifdef DEBUG
	std::cout << "BItDestructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> bool List<T>::constBaseIterator::operator==(const constBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::constBaseIterator::operator!=(const constBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> const T& List<T>::constBaseIterator::operator*()const
{
	return Temp->Data;
}

template<typename T> List<T>::constIterator::constIterator(Element* Temp) : constBaseIterator(Temp)
{
#ifdef DEBUG
	std::cout << "IConstructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> List<T>::constIterator::~constIterator()
{
#ifdef DEBUG
	std::cout << "IDestructor:\t" << this << std::endl;
#endif // DEBUG

}
template<typename T> typename List<T>::constIterator& List<T>::constIterator::operator++()
{
	constBaseIterator::Temp = constBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::constIterator List<T>::constIterator::operator++(int)
{
	constIterator old = *this;
	constBaseIterator::Temp = constBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::constIterator& List<T>::constIterator::operator--()
{
	constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::constIterator List<T>::constIterator::operator--(int)
{
	constIterator old = *this;
	constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
	return old;
}

template<typename T> List<T>::constReversIterator::constReversIterator(Element* Temp) : constBaseIterator(Temp)
{
#ifdef DEBUG
	std::cout << "RIConstructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> List<T>::constReversIterator::~constReversIterator()
{
#ifdef DEBUG
	std::cout << "RIDestructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> typename List<T>::constReversIterator& List<T>::constReversIterator::operator++()
{
	constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::constReversIterator List<T>::constReversIterator::operator++(int)
{
	constReversIterator old = *this;
	constBaseIterator::Temp = constBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename List<T>::constReversIterator& List<T>::constReversIterator::operator--()
{
	constBaseIterator::Temp = constBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::constReversIterator List<T>::constReversIterator::operator--(int)
{
	constReversIterator old = *this;
	constBaseIterator::Temp = constBaseIterator::Temp->pNext;
	return old;
}

template<typename T> List<T>::Iterator::Iterator(Element* Temp) : constIterator(Temp) {}
template<typename T> T& List<T>::Iterator::operator*()
{
	return constBaseIterator::Temp->Data;
}

template<typename T> List<T>::ReversIterator::ReversIterator(Element* Temp) : constReversIterator(Temp) {}
template<typename T> T& List<T>::ReversIterator::operator*()
{
	return constBaseIterator::Temp->Data;
}

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::constIterator it = right.cbegin(); it != right.cend(); ++it)
		cat.push_back(*it);
	return cat;
}