#include<iostream>
#include<ctime>

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

	void erase_param(int Data, Element* Root)
	{
		Element* pPrev = nullptr;
		Element* root = Root;

		while (root != nullptr && root->Data != Data)
		{
			pPrev = root;
			if (Data < root->Data) root = root->pLeft;
			else root = root->pRight;
		}

		if (root == nullptr) return;

		if (root->pLeft == nullptr && root->pRight == nullptr)
		{
			if (root != Root)
			{
				if (pPrev->pLeft == root) pPrev->pLeft = nullptr;
				else pPrev->pRight = nullptr;
			}
			else Root = nullptr;
			delete root;
		}
		else if (root->pLeft && root->pRight)
		{
			Element* tmp = root;
			while (tmp->pLeft != nullptr) tmp = root->pLeft;
			int tmp_data = tmp->Data;
			erase_param(tmp_data, root);
			root->Data = tmp_data;
		}
		else
		{
			Element* pNext = (root->pLeft) ? root->pLeft : root->pRight;
			if (root != Root)
			{
				if (root == pPrev->pLeft) pPrev->pLeft = pNext;
				else pPrev->pRight = pNext;
			}
			else Root = pNext;
			delete root;
		}
	}
	void print_param(Element* Root)
	{
		if (Root == nullptr)return;
		print_param(Root->pLeft);
		std::cout << Root->Data << "\t";
		print_param(Root->pRight);
	}
	void tree_print_param(Element* Root, int depth)
	{
		if (Root == nullptr) return;
		tree_print_param(Root->pLeft, depth + 1);
		for (int i = 0; i < depth; i++)
			std::cout << "   ";
		std::cout << Root->Data << std::endl << std::endl;
		tree_print_param(Root->pRight, depth + 1);
	}
	void insert_param(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert_param(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert_param(Data, Root->pRight);
		}
	}
	int minValue_param(Element* Root)
	{
		return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue_param(Root->pLeft);
	}
	int maxValue_param(Element* Root)
	{
		return Root == nullptr ? 0 : Root->pRight == nullptr ? Root->Data : maxValue_param(Root->pRight);
	}
	int sum_param(Element* Root)
	{
		return Root == nullptr ? 0 : sum_param(Root->pLeft) + sum_param(Root->pRight) + Root->Data;
	}
	int count_param(Element* Root)
	{
		return Root == nullptr ? 0 : 1 + count_param(Root->pLeft) + count_param(Root->pRight);
	}
	int depth_param(Element* Root)
	{
		if (Root == nullptr) return 0;
		return Root->pLeft != nullptr ? 1 + depth_param(Root->pLeft) : 1 + depth_param(Root->pRight);
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
	Tree(const std::initializer_list<int>& list):Tree()
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


	void insert(int Data=0)
	{
		insert_param(Data, Root);
	}
	void erase(int Data)
	{
		erase_param(Data, Root);
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
	void tree_print()
	{
		tree_print_param(Root, depth());
	}
	int minValue()
	{
		return minValue_param(Root);
	}
	int maxValue()
	{
		return maxValue_param(Root);
	}
	int sum()
	{
		return sum_param(Root);
	}
	int count()
	{
		return count_param(Root);
	}
	double Avg()
	{
		return (double)sum() / count();
	}
	int depth()
	{
		return depth_param(Root);
	}

};

template<class T> T measure(Tree& t, T (Tree::*f)())
{
	clock_t start = clock();
	T res = (t.*f)();
	clock_t end = clock();
	std::cout << "Метод отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд, результат: ";
	return (t.*f)();
}
void measure(Tree& t, void (Tree::*f)())
{
	clock_t start = clock();
	(t.*f)();
	clock_t end = clock();
	std::cout << "\nМетод отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
}
void measure(Tree& t, void (Tree::*f)(int), int Data)
{
	clock_t start = clock();
	(t.*f)(Data);
	clock_t end = clock();
	std::cout << "Метод отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд";
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

void main()
{
	setlocale(LC_ALL, "");
	int n;

#ifdef BASE_CHECK
	std::cout << "Введите число элементов: "; std::cin >> n;
	Tree tree;
	clock_t start = clock();
	for (int i = 0; i < n; i++) tree.insert(rand() % 100);

	measure(tree, &Tree::print);
	std::cout << measure(tree, &Tree::count) << std::endl;
	std::cout << measure(tree, &Tree::Avg) << std::endl;

	clock_t end = clock();
	std::cout << "Дерево заполнилось за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	//tree.Clear();
	//tree.print();
	std::cout << std::endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Минимальный элемент дерева: ";
	start = clock();
	int min = tree.minValue();
	end = clock();
	std::cout << min << ", расчитано за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Максимальный элемент дерева: ";
	start = clock();
	int max = tree.maxValue();
	end = clock();
	std::cout << max << ", расчитано за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Сумма элементов дерева: ";
	start = clock();
	int sum = tree.sum();
	end = clock();
	std::cout << sum << ", расчитано за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Количество элементов дерева: ";
	start = clock();
	int count = tree.count();
	end = clock();
	std::cout << count << ", расчитано за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Среднее-арифметическое элементов: ";
	start = clock();
	double avg = tree.Avg();
	end = clock();
	std::cout << avg << ", расчитано за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Глубина дерева: ";
	start = clock();
	int depth = tree.depth();
	end = clock();
	std::cout << depth << ", расчитано за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////////////////////	

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
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 90, 28, 29 };
	tree.print();
	std::cout << "Глубина дерева: " << tree.depth() << std::endl;
#endif // DEPTH_CHECK

	std::cout << "Введите число элементов: "; std::cin >> n;
	Tree tree;
	
	for (int i = 0; i < n; i++) tree.insert(rand() % 100);
	std::cout << delim;
	measure(tree, &Tree::print);
	std::cout << delim;
	std::cout << measure(tree, &Tree::count) << std::endl;
	std::cout << delim;
	measure(tree, &Tree::erase, 1);
	std::cout << delim;
	std::cout << measure(tree, &Tree::Avg) << std::endl;
}