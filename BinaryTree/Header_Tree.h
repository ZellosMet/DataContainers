#pragma once

#include<iostream>
#include<ctime>
#include<iomanip>

#define delim "\n-------------------------------------------------------------------------\n"

template<class T>class Tree
{
protected:
	class Element
	{
		T  Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(T Data, Element* pLeft = nullptr, Element* pRaght = nullptr);
		~Element();

		friend class Tree;
		friend class UniqueTree<T>;

	}*Root;

	void insert(T Data, Element* Root);
	void erase(T Data, Element*& Root);
	void clear_tree(Element* Root);
	T depth(Element* Root)const;
	T sum(Element* Root)const;
	T count(Element* Root)const;
	T minValue(Element* Root)const;
	T maxValue(Element* Root)const;
	void print(Element* Root);
	void depth_print(Element* Root, int Depth, int Width)const;
	void tree_print(Element* Root, int Width, int Depth = 0)const;
	void balance(Element* Root);

public:

	//						Constructors
	Tree();
	Tree(const std::initializer_list<T>& list);
	~Tree();

	//							Metods 
	void insert(T Data);
	void erase(T Data);
	void clear_tree();
	T count()const;
	T sum()const;
	T depth()const;
	double Avg()const;
	T minValue()const;
	T maxValue()const;
	void print()const;
	void depth_print(int depth)const;
	void tree_print()const;
	void balance();
};
template<typename T>class UniqueTree : public Tree<T>
{
	void insert(T Data, typename Tree<T>::Element* Root);
public:
	void insert(int Data);
};

template<typename T> void measure(const char* msg, Tree<T>& t, T(Tree<T>::* f)()const);
template<typename T> void measure(const char* msg, Tree<T>& t, void (Tree<T>::* f)(int), int Data);
template<typename T> void measure(const char* msg, Tree<T>& t, void (Tree<T>::* f)());
