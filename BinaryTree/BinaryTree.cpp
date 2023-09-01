#include<iostream>

class Tree
{
	class Element
	{
		int  Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRaght = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
			std::cout << "EConstructor:\t" << this << std::endl;
		}
		~Element()
		{
			std::cout << "EDestructor:\t" << this <<std::endl;
		}
	}*Root;

public:
	Tree() :Root(nullptr)
	{
		std::cout << "EConstructor:\t" << this << std::endl;
	}
	Tree(Element* Root = nullptr) : Root(Root)
	{
		std::cout << "EConstructor:\t" << this << std::endl;
	}
	~Tree()
	{
		std::cout << "TDestructor:\t" << this << std::endl;
	}
	void insert(int Data)
	{
		
	}

};

void main()
{
	setlocale(LC_ALL, "");
}