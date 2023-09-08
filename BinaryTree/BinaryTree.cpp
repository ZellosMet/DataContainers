#include<iostream>
#include<ctime>
#include<iomanip>

#define delim "\n-------------------------------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int  Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRaght = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
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

		friend class Tree;
		friend class UniqueTree;
	}*Root;

	void insert_param(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert_param(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert_param(Data, Root->pRight);
		}
	}
	void erase_param(int Data, Element*& Root)
	{
			if (Root == nullptr)return;
			erase_param(Data, Root->pLeft);
			erase_param(Data, Root->pRight);
			if (Data == Root->Data)
			{
				if (Root->pLeft == Root->pRight)
				{
					delete Root;
					Root = nullptr;
				}
				else
				{
					if (count_param(Root->pLeft) > count_param(Root->pRight))
					{
						Root->Data = maxValue_param(Root->pLeft);
						erase_param(maxValue_param(Root->pLeft), Root->pLeft);
					}
					else
					{
						Root->Data = minValue_param(Root->pRight);
						erase_param(minValue_param(Root->pRight), Root->pRight);
					}
				}
			}
	}
	//void balance_param(Element*& Root)
	//{
	//	if (Root == nullptr)return;
	//	while (count_param(Root->pLeft) != count_param(Root->pRight) + 1 && count_param(Root->pLeft) !=count_param(Root->pRight))
	//	{
	//		int Temp = Root->Data;
	//		erase_param(Temp, Root);
	//		insert_param(Temp, Root);
	//	} 
	//	balance_param(Root->pLeft);
	//	balance_param(Root->pRight);
	//}

	void print_param(Element* Root)
	{
		if (Root == nullptr)return;
		print_param(Root->pLeft);
		std::cout << Root->Data << "\t";
		print_param(Root->pRight);
	}
	void depth_print_param(Element* Root, int Depth, int Width)const
	{
		if (Root == nullptr)
		{
			if (Depth == 0) 
			{
				std::cout.width(Width*pow(2,(this->depth() - Depth)/3));
				std::cout << "";
			}
			return;
		}
		if (Depth == 0)
		{	
			std::cout.width(Width);
			std::cout << Root->Data;
			std::cout.width(Width);
			std::cout << "";
		}
		depth_print_param(Root->pLeft, Depth - 1, Width);		
		depth_print_param(Root->pRight, Depth - 1, Width);
	}

	void tree_print_param(Element*  Root, int Width, int Depth = 0)
	{
		if (Root == nullptr) return;
		if (Depth >= this->depth())return;
		depth_print_param(Root, Depth, Width/2);
		std::cout << std::endl << std::endl;
		tree_print_param(Root, Width/2, Depth + 1);
	}
	void balance_param(Element* Root)
	{
		if (Root == nullptr) return;
		if (abs(count_param(Root->pLeft) - count_param(Root->pRight)) < 2) return;
		if (count_param(Root->pLeft) < count_param(Root->pRight))
		{
			if (Root->pLeft) insert_param(Root->Data, Root->pLeft);
			else Root->pLeft = new Element(Root->Data);
			Root->Data = minValue_param(Root->pRight);
			erase_param(minValue_param(Root->pRight), Root->pRight);
		}
		else 
		{
			if (Root->pRight)insert_param(Root->Data, Root->pRight);
			else Root->pRight = new Element(Root->Data);
			Root->Data = maxValue_param(Root->pLeft);
			erase_param(maxValue_param(Root->pLeft), Root->pLeft);
		}
		balance_param(Root->pLeft);
		balance_param(Root->pRight);
		balance_param(Root);
	}

	int minValue_param(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue_param(Root->pLeft);
	}
	int maxValue_param(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pRight == nullptr ? Root->Data : maxValue_param(Root->pRight);
	}
	int sum_param(Element* Root)const
	{
		return Root == nullptr ? 0 : sum_param(Root->pLeft) + sum_param(Root->pRight) + Root->Data;
	}
	int count_param(Element* Root)const
	{
		return Root == nullptr ? 0 : 1 + count_param(Root->pLeft) + count_param(Root->pRight);
	}
	int depth_param(Element* Root)const
	{
		if (Root == nullptr)return 0;
		int l_depth = depth_param(Root->pLeft) + 1;
		int r_depth = depth_param(Root->pRight) + 1;
		return	l_depth > r_depth ? l_depth : r_depth;
	}
	void clear_tree_param(Element* Root)
	{
		if (Root == nullptr) return;
		clear_tree_param(Root->pLeft);
		clear_tree_param(Root->pRight);
		delete Root;
	}
public:
	Element* getRoot()
	{
		return Root;
	}

	//						Constructors

	Tree() :Root(nullptr)
	{
#ifdef DEBUG
		std::cout << "EConstructor:\t" << this << std::endl;
#endif // DEBUG

	}
	Tree(const std::initializer_list<int>& list) :Tree()
	{
		for (int i : list)
			insert(i);
	}
	~Tree()
	{
		clear_tree();
#ifdef DEBUG
		std::cout << "TDestructor:\t" << this << std::endl;
#endif // DEBUG

	}

	//							Metods 


	void insert(int Data = 0)
	{
		insert_param(Data, Root);
	}
	void erase(int Data)
	{
		erase_param(Data, Root);
	}
	void balance()
	{
		balance_param(Root);
	}
	void clear_tree()
	{
		clear_tree_param(Root);
		Root = nullptr;
	}
	void print()
	{
		print_param(Root);
	}
	void depth_print(int depth)
	{
		depth_print_param(Root, depth, 64);
	}
	void tree_print()
	{
		tree_print_param(Root, 64);
	}
	int minValue()const
	{
		return minValue_param(Root);
	}
	int maxValue()const
	{
		return maxValue_param(Root);
	}
	int sum()const
	{
		return sum_param(Root);
	}
	int count()const
	{
		return count_param(Root);
	}
	double Avg()const
	{
		return (double)sum() / count();
	}
	int depth()const
	{
		return depth_param(Root);
	}

};

template<class T> void measure(const char* msg, Tree& t, T(Tree::* f)()const)
{
	std::cout << msg;
	clock_t start = clock();
	T res = (t.*f)();
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд, результат: " << res;
}
void measure(const char* msg, Tree& t, void (Tree::* f)(int), int Data)
{
	std::cout << msg;
	clock_t start = clock();
	(t.*f)(Data);
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд";
}

class UniqueTree : public Tree
{
	void insert_param(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert_param(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert_param(Data, Root->pRight);
		}
	}

public:
	void insert(int Data)
	{
		return insert_param(Data, Root);
	}
};

//#define BASE_CHECK
//#define DEPTH_CHECK
//#define MEASURE
#define BALANCE_CHECK

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

	Tree tree = { 89,55,34,21,13,8,5,3 };
	tree.tree_print();
	std::cout << delim;
	tree.balance();
	tree.tree_print();

}