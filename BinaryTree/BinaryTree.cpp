#include<iostream>
#include<ctime>
#include<iomanip>

template<class T> class Tree;
template<typename T> class UniqueTree;

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

template<typename T> void measure(const char* msg, Tree<T>& t, T(Tree<T>::* f)()const)
{
	std::cout << msg;
	clock_t start = clock();
	T res = (t.*f)();
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд, результат: " << res;
}
template<typename T> void measure(const char* msg, Tree<T>& t, void (Tree<T>::* f)(int), int Data)
{
	std::cout << msg;
	clock_t start = clock();
	(t.*f)(Data);
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд";
}
template<typename T> void measure(const char* msg, Tree<T>& t, void (Tree<T>::* f)())
{
	std::cout << msg;
	clock_t start = clock();
	(t.*f)();
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд";
}
template<typename T> void UniqueTree<T>::insert(T Data, typename Tree<T>::Element* Root)
{
	if (this->Root == nullptr) this->Root = new Tree::Element(Data);
	if (Root == nullptr) return;
	if (Data < Root->Data)
	{
		if (Root->pLeft == nullptr) Root->pLeft = new Tree::Element(Data);
		else insert(Data, Root->pLeft);
	}
	else if (Data > Root->Data)
	{
		if (Root->pRight == nullptr) Root->pRight = new Tree::Element(Data);
		else insert(Data, Root->pRight);
	}
}
template<typename T> void UniqueTree<T>::insert(int Data)
{
	return insert(Data, Tree<T>::Root);
}
template<typename T > Tree<T>::Element::Element(T Data, Element* pLeft, Element* pRaght) : Data(Data), pLeft(pLeft), pRight(pRight)
{
#ifdef DEBUG
	std::cout << "EConstructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T > Tree<T>::Element::~Element()
{
#ifdef DEBUG
	std::cout << "EDestructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> void Tree<T>::insert(T Data, Element* Root)
{
	if (this->Root == nullptr)this->Root = new Element(Data);
	if (Root == nullptr)return;
	if (Data < Root->Data)
	{
		if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
		else insert(Data, Root->pLeft);
	}
	else
	{
		if (Root->pRight == nullptr)Root->pRight = new Element(Data);
		else insert(Data, Root->pRight);
	}
}
template <typename T> void Tree<T>::erase(T Data, Element*& Root)
{
	if (Root == nullptr)return;
	erase(Data, Root->pLeft);
	erase(Data, Root->pRight);
	if (Data == Root->Data)
	{
		if (Root->pLeft == Root->pRight)
		{
			delete Root;
			Root = nullptr;
		}
		else
		{
			if (count(Root->pLeft) > count(Root->pRight))
			{
				Root->Data = maxValue(Root->pLeft);
				erase(maxValue(Root->pLeft), Root->pLeft);
			}
			else
			{
				Root->Data = minValue(Root->pRight);
				erase(minValue(Root->pRight), Root->pRight);
			}
		}
	}
}
template <typename T> void Tree<T>::print(Element* Root)
{
	if (Root == nullptr)return;
	print_param(Root->pLeft);
	std::cout << Root->Data << "\t";
	print_param(Root->pRight);
}
template <typename T> void Tree<T>::depth_print(Element* Root, int Depth, int Width)const
{
	if (Root == nullptr)
	{
		if (Depth == 0)
		{
			std::cout.width(Width * pow(2, (this->depth() - Depth) / 3));
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
	depth_print(Root->pLeft, Depth - 1, Width);
	depth_print(Root->pRight, Depth - 1, Width);
}
template <typename T> void Tree<T>::tree_print(Element* Root, int Width, int Depth)const
{
	if (Root == nullptr) return;
	if (Depth >= this->depth())return;
	depth_print(Root, Depth, Width / 2);
	std::cout << std::endl << std::endl;
	tree_print(Root, Width / 2, Depth + 1);
}
template <typename T> void Tree<T>::balance(Element* Root)
{
	if (Root == nullptr) return;
	if (abs(count(Root->pLeft) - count(Root->pRight)) < 2) return;
	if (count(Root->pLeft) < count(Root->pRight))
	{
		if (Root->pLeft) insert(Root->Data, Root->pLeft);
		else Root->pLeft = new Element(Root->Data);
		Root->Data = minValue(Root->pRight);
		erase(minValue(Root->pRight), Root->pRight);
	}
	else
	{
		if (Root->pRight)insert(Root->Data, Root->pRight);
		else Root->pRight = new Element(Root->Data);
		Root->Data = maxValue(Root->pLeft);
		erase(maxValue(Root->pLeft), Root->pLeft);
	}
	balance(Root->pLeft);
	balance(Root->pRight);
	balance(Root);
}
template <typename T> T Tree<T>::minValue(Element* Root)const
{
	return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
}
template <typename T> T Tree<T>::maxValue(Element* Root)const
{
	return Root == nullptr ? 0 : Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
}
template <typename T> T Tree<T>::sum(Element* Root)const
{
	return Root == nullptr ? 0 : sum_param(Root->pLeft) + sum_param(Root->pRight) + Root->Data;
}
template <typename T> T Tree<T>::count(Element* Root)const
{
	return Root == nullptr ? 0 : 1 + count(Root->pLeft) + count(Root->pRight);
}
template <typename T> T Tree<T>::depth(Element* Root)const
{
	if (Root == nullptr)return 0;
	int l_depth = depth(Root->pLeft) + 1;
	int r_depth = depth(Root->pRight) + 1;
	return	l_depth > r_depth ? l_depth : r_depth;
}
template <typename T> void Tree<T>::clear_tree(Element* Root)
{
	if (Root == nullptr) return;
	clear_tree(Root->pLeft);
	clear_tree(Root->pRight);
	delete Root;
}

//							Constructors

template <typename T> Tree<T>::Tree() : Root(nullptr)
{
	#ifdef DEBUG
	std::cout << "EConstructor:\t" << this << std::endl;
	#endif // DEBUG
}
template <typename T> Tree<T>::Tree(const std::initializer_list<T>& list) :Tree()
{
	for (T i : list)
		insert(i);
}
template <typename T> Tree<T>::~Tree()
{
	clear_tree();
	#ifdef DEBUG
		std::cout << "TDestructor:\t" << this << std::endl;
	#endif // DEBUG
}

//								Metods 

template <typename T> void Tree<T>::insert(T Data)
	{
		insert(Data, Root);
	}
template <typename T> void Tree<T>::erase(T Data)
	{
		erase(Data, Root);
	}
template <typename T> void Tree<T>::balance()
	{
		balance(Root);
	}
template <typename T> void Tree<T>::clear_tree()
	{
		clear_tree(Root);
		Root = nullptr;
	}
template <typename T> void Tree<T>::print()const
	{
		print(Root);
	}
template <typename T> void Tree<T>::depth_print(int depth)const
	{
		depth_print(Root, depth, 64);
	}
template <typename T> void Tree<T>::tree_print()const
	{
		tree_print(Root, 64);
	}
template <typename T> T Tree<T>::minValue()const
	{
		return minValue(Root);
	}
template <typename T> T Tree<T>::maxValue()const
	{
		return maxValue(Root);
	}
template <typename T> T Tree<T>::sum()const
	{
		return sum(Root);
	}
template <typename T> T Tree<T>::count()const
	{
		return count(Root);
	}
template <typename T> double Tree<T>::Avg()const
	{
		return (double)sum() / count();
	}
template <typename T> T Tree<T>::depth()const
	{
		return depth(Root);
	}

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

	Tree<int> tree = { 89,55,34,21,13,8,5,3 };
	tree.tree_print();
	std::cout << delim;
	tree.balance();
	tree.tree_print();
}