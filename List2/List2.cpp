#include<iostream>
#include"List_Header.h"
#include"List_Class.cpp"

//#define BASE_CHECK
#define LOOP_CHECK

void main()
{
	setlocale(LC_ALL, "");
	int n;

#ifdef BASE_CHECK
	std::cout << "Введите размер списка: "; std::cin >> n;
	List<int> list;
	for (int i = 0; i < n; i++)
		list.push_front(rand() % 100);
	list.print();
	std::cout << delim;
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
#ifdef LOOP_CHECK
	//List<int> list = { 3,5,8,13,21 };
	List<char> list = { 'H','e','l','l','o' };
	List<char> list2 = { 'W','o','r','l','d' };
	for (List<char>::constIterator i = list.cbegin(); i != list.cend(); ++i) std::cout << *i << "\t";
	std::cout << delim;
	for (List<char>::constIterator i = list2.cbegin(); i != list2.cend(); ++i) std::cout << *i << "\t";
	std::cout << delim;
	List<char> list3 = list + list2;
	for (List<
	char>::Iterator i = list3.begin(); i != list.end(); ++i) std::cout << *i;
#endif // LOOP_CHECK
}