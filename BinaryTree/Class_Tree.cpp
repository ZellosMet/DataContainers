#include"Header_Tree.h"

////////////////////////////////////////  TreeConstructors  ////////////////////////////////////////					

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

////////////////////////////////////////  Element  ////////////////////////////////////////	

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

////////////////////////////////////////  TreeInternalMethods  ////////////////////////////////////////	

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
	print(Root->pLeft);
	std::cout << Root->Data << "\t";
	print(Root->pRight);
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
		if (Root->pRight) insert(Root->Data, Root->pRight);
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
	return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
}
template <typename T> int Tree<T>::count(Element* Root)const
{
	return Root == nullptr ? 0 : 1 + count(Root->pLeft) + count(Root->pRight);
}
template <typename T> int Tree<T>::depth(Element* Root)const
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

////////////////////////////////////////  TreeMetods  ////////////////////////////////////////

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
template <typename T> int Tree<T>::count()const
{
	return count(Root);
}
template <typename T> double Tree<T>::Avg()const
{
	return (double)sum() / count();
}
template <typename T> int Tree<T>::depth()const
{
	return depth(Root);
}

////////////////////////////////////////  UniqueTree  ////////////////////////////////////////

template<typename T> void UniqueTree<T>::insert(T Data, typename Tree<T>::Element* Root)
{
	if (this->Root == nullptr) this->Root = new typename Tree<T>::Element(Data);
	if (Root == nullptr) return;
	if (Data < Root->Data)
	{
		if (Root->pLeft == nullptr) Root->pLeft = new typename Tree<T>::Element(Data);
		else insert(Data, Root->pLeft);
	}
	else if (Data > Root->Data)
	{
		if (Root->pRight == nullptr) Root->pRight = new typename Tree<T>::Element(Data);
		else insert(Data, Root->pRight);
	}
}

template<typename T> void UniqueTree<T>::insert(T Data)
{
	return insert(Data, Tree<T>::Root);
}
////////////////////////////////////////  Function  ////////////////////////////////////////

template <typename T> void measure(const char* msg, Tree<T>& t, T(Tree<T>::* f)()const)
{
	std::cout << msg;
	clock_t start = clock();
	T res = (t.*f)();
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд, результат: " << res;
}
template <typename T> void measure(const char* msg, Tree<T>& t, void (Tree<T>::* f)(T), T Data)
{
	std::cout << msg;
	clock_t start = clock();
	(t.*f)(Data);
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд";
}
template <typename T> void measure(const char* msg, Tree<T>& t, void (Tree<T>::* f)())
{
	std::cout << msg;
	clock_t start = clock();
	(t.*f)();
	clock_t end = clock();
	std::cout << "отработал за " << double(end - start) / CLOCKS_PER_SEC << " секунд";
}

