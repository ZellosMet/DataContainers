#include<iostream>
#include<ctime>

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


	void insert(int Data)
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

//#define BASE_BINARYTREE
#define BINARYTREE_HOME_WORK

void main()
{
	setlocale(LC_ALL, "");
	int n;
	std::cout << "Введите размер дерева: "; std::cin >> n;

#ifdef BASE_BINARYTREE

	std::cout << "Введите размер дерева: "; std::cin >> n;
	clock_t start = clock();
	Tree tree;
	for (int i = 0; i < n; i++)
		tree.insert(rand() % 100);
	tree.print();
	std::cout << std::endl;
	std::cout << "Минимальное значение в дереве: " << tree.minValue() << std::endl;
	std::cout << "Минимальное значение в дереве: " << tree.maxValue() << std::endl;
	std::cout << "Сумма элементов дерева: " << tree.sum() << std::endl;
	std::cout << "Количество элементов в дереве: " << tree.count() << std::endl;
	std::cout << "Среднее-арифметическое элементов дерева: " << tree.Avg() << std::endl;
	std::cout << std::endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
		u_tree.insert(rand() % 100, u_tree.getRoot());
	u_tree.print();
	std::cout << std::endl;
	std::cout << "Минимальное значение в дереве: " << u_tree.minValue() << std::endl;
	std::cout << "Минимальное значение в дереве: " << u_tree.maxValue() << std::endl;
	std::cout << "Сумма элементов дерева: " << u_tree.sum() << std::endl;
	std::cout << "Количество элементов в дереве: " << u_tree.count() << std::endl;
	std::cout << "Среднее-арифметическое элементов дерева: " << u_tree.Avg() << std::endl;
	std::cout << std::endl;

	clock_t end = clock();
	std::cout << "Время работы кода: " << (double)(end - start) / CLOCKS_PER_SEC << " секунды" << std::endl;

#endif // BASE_BINARYTREE
	
#ifdef BINARYTREE_HOME_WORK

	clock_t start = clock();	

	Tree tree;// = { 50, 25, 75, 16, 32, 64, 90 };
	for (int i = 0; i < n; i++)
		tree.insert(rand() % 100);
	tree.print();
	//tree.insert(28);
	std::cout << std::endl;
	std::cout << "Глубина дерева: " << tree.depth();
	std::cout << std::endl;
	//tree.erase(13);
	//tree.tree_print();
	std::cout << std::endl;

	clock_t end = clock();
	std::cout << "Время работы кода: " << (double)(end - start) / CLOCKS_PER_SEC << " секунды" << std::endl;

#endif // BINARYTREE_HOME_WORK
};	