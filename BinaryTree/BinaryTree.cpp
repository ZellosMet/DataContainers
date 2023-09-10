#include"Header_Tree.h"
#include"Class_Tree.cpp"

//#define BASE_CHECK
//#define DEPTH_CHECK
//#define MEASURE
//#define BALANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
	int n;

#ifdef BASE_CHECK
	//std::cout << "Введите число элементов: "; std::cin >> n;	

	/*
	Tree tree = { 50, 25, 75, 16, 32, 64, 90, 28, 29};
	tree.tree_print();
	std::cout << delim;
	tree.insert(86);
	tree.insert(89);
	tree.insert(100);
	tree.insert(74);
	tree.insert(78);
	tree.insert(99);
	tree.insert(101);
	tree.tree_print();
	std::cout << delim;
	tree.balance();
	tree.tree_print();
	std::cout << delim;
	*/

	Tree tree = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
	tree.tree_print();
	std::cout << delim;
	tree.balance();
	tree.tree_print();

	/*
		UniqueTree u_tree;
		for (int i = 0; i < n; i++)
		{
			u_tree.insert(rand() % 100);
		}
		//u_tree.print();
		std::cout << std::endl;
		std::cout << "Минимальный элемент дерева: " << u_tree.minValue() << std::endl;
		std::cout << "Максимальный элемент дерева: " << u_tree.maxValue() << std::endl;
		std::cout << "Сумма элементов дерева: " << u_tree.sum() << std::endl;
		std::cout << "Количество элементов дерева: " << u_tree.count() << std::endl;
		std::cout << "Среднее-арифметическое элементов: " << u_tree.Avg() << std::endl;
		std::cout << "Глубина дерева: " << u_tree.depth() << std::endl;
	*/

#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 90, 28, 29};
	tree.print();
	std::cout << "\nГлубина дерева: " << tree.depth() << std::endl;

	//int depth;
	//std::cout << "Введите глубину дерева: "; std::cin >> depth;
	tree.tree_print();
#endif // DEPTH_CHECK

#ifdef MEASURE
	std::cout << "Введите число элементов: "; std::cin >> n;
	Tree tree;

	for (int i = 0; i < n; i++) tree.insert(rand() % 100);
	std::cout << delim;
	measure("Метод count ", tree, &Tree::count);
	std::cout << delim;
	measure("Метод erase ", tree, &Tree::erase, 1);
	std::cout << delim;
	measure("Метод AVG", tree, &Tree::Avg);
	std::cout << delim;
#endif // MEASURE

	Tree<int> tree = { 89,55,34,21,13,8,5,3 };
	tree.tree_print();
	std::cout << delim;
	tree.balance();
	tree.tree_print();
}