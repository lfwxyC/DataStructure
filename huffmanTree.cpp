#include<iostream>
using namespace std;

template<class T>
struct binaryTreeNode//二叉树节点 
{
	T element;//数值 
	binaryTreeNode<T>* leftChild, * rightChild;//左右孩子 

	//构造函数 
	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeftChild, binaryTreeNode<T>* theRightChild)
	{
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

template<class E>
class linkedBinaryTree//二叉树 
{
public:
	linkedBinaryTree() { root = NULL; treeSize = 0; }
	~linkedBinaryTree() { erase(); }

	void erase() { postOrder(dispose); root = NULL; }//删除 
	void postOrder(void(*theVisit)(binaryTreeNode<E>*)) { visit = theVisit; postOrder(root); }//后序遍历
	void makeTree(const E&, linkedBinaryTree<E>&, linkedBinaryTree<E>&);//创建树
private:
	binaryTreeNode<E>* root;//根节点 
	int treeSize;//节点个数 

	static void (*visit)(binaryTreeNode<E>*);
	static void postOrder(binaryTreeNode<E>* t);//后序遍历 
	static void dispose(binaryTreeNode<E>* t) { delete t; }//删除 
	static int height(binaryTreeNode<E>* t);//计算子树高度 
};


template<class E>
void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t)//后序遍历 
{
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element, linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)//创建树
{
	root = new binaryTreeNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;

	left.root = right.root = NULL;
	left.treeSize = right.treeSize = 0;
}

template<class T>
void changeLength1D(T*& element, int oldLength, int newLength)//倍增数组长度 
{
	T* temp = new T[newLength];//创建新长度的数组 

	//copy(element + 1, element + oldLength, temp+1);
	for (int i = 1; i < oldLength; i++)//把旧数组的元素复制到新数组
		temp[i] = element[i];
	delete[]element;//释放旧数组的空间 
	element = temp;
}

template<class T>
class minHeap
{
public:
	minHeap(int initialCapacity = 10);
	~minHeap() { delete[]heap; }

	T& top()const { return heap[1]; }
	void push(const T& theElement);
	void pop();
	void initialize(T* theHeap, int theSize);
	void deactiveArray() { heap = NULL; }
private:
	T* heap;
	int arrayLength;
	int heapSize;
};

template<class T>
minHeap<T>::minHeap(int initialCapacity)
{
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<class T>
void minHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1)
	{
		changeLength1D(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;

	while (currentNode != 1 && theElement < heap[currentNode / 2])
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

template<class T>
void minHeap<T>::pop()
{
	heap[1].~T();

	T lastElement = heap[heapSize--];
	int currentNode = 1;
	int child = 2;

	while (child <= heapSize)
	{
		if (child<heapSize && heap[child]>heap[child + 1])
		{
			child++;
		}
		if (lastElement <= heap[child])
		{
			break;
		}
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<class T>
void minHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[]heap;
	heap = theHeap;
	heapSize = theSize;

	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];
		int child = root * 2;

		while (child <= heapSize)
		{
			if (child<heapSize && heap[child]>heap[child + 1])
			{
				child++;
			}
			if (rootElement <= heap[child])
			{
				break;
			}
			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootElement;
	}
}

template<class T>
class huffmanNode//霍夫曼节点
{
public:
	operator T()const { return weight; }//操作符重载
	friend void huffmanTree(int weight[], int n);//构造霍夫曼树
private:
	linkedBinaryTree<T>* tree;
	T weight;//权重
};

void huffmanTree(int weight[], int n)//构造霍夫曼树
{
	huffmanNode<int>* hNode = new huffmanNode<int>[n + 1];
	linkedBinaryTree<int> emptyTree;
	int length = 0;//记录编码后的长度

	//创建一组单节点树
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new linkedBinaryTree<int>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);
	}

	minHeap<huffmanNode<int> > heap(1);
	heap.initialize(hNode, n);//将单节点树初始化为小根堆

	//合并
	for (int i = 1; i < n; i++)
	{
		huffmanNode<int> w, x, y;
		linkedBinaryTree<int>* z = new linkedBinaryTree<int>;

		//将权重最小的两个树合并
		x = heap.top();
		heap.pop();

		y = heap.top();
		heap.pop();

		z->makeTree(0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		length += w.weight;//内部节点权重的加和即为编码长度
		w.tree = z;
		heap.push(w);

		delete x.tree;
		delete y.tree;
	}
	cout << length << endl;//输出编码长度
}

int main()
{
	string str;
	int a[26];//存放26个小写字母的个数
	int n = 0, count = 1;

	cin >> str;
	//初始化数组a
	for (int i = 0; i < 26; i++)
	{
		a[i] = 0;
	}

	for (int i = 0; i < (int)str.length(); i++)
	{
		int index = str[i] - 'a';//小写字母按顺序存入数组

		a[index]++;
		if (a[index] == 1)
		{
			n++;//计算字符串中包含的小写字母个数
		}
	}

	int* b = new int[n + 1];//存放字符出现的频率

	for (int i = 0; i < 26; i++)
	{
		if (a[i])
		{
			b[count] = a[i];
			count++;
		}
	}

	huffmanTree(b, n);//构造霍夫曼树并计算编码长度
	delete[]b;
	return 0;
}
