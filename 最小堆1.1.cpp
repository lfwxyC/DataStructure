#include<iostream>
using namespace std;

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
class minHeap//小根堆 
{
public:
	minHeap(int initialCapacity=10);
	~minHeap() {delete[]heap;}

	bool empty() { return heapSize == 0; }//判断堆是否为空 
	int size()const { return heapSize; }//获取堆的大小 
	T& top()const { return heap[1]; }//获取堆的根节点 
	void push(const T& theElement);//插入 
	void pop();//删除堆的根节点 
	void initialize(int theSize);//初始化 
	void deactiveArray() { heap = NULL; }
private:
	T* heap;//数组指针 
	int arrayLength;//数组容量 
	int heapSize;//堆大小 
};

template<class T>
minHeap<T>::minHeap(int initialCapacity)//构造函数 
{
	arrayLength =initialCapacity;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<class T>
void minHeap<T>::push(const T& theElement)//插入 
{
	if (heapSize == arrayLength - 1)//数组已满 
	{
		changeLength1D(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;//插入元素所在位置 

	while (currentNode != 1 && theElement < heap[currentNode / 2])//判断是否可以插入 
	{
		heap[currentNode] = heap[currentNode / 2];//父节点下移 
		currentNode /= 2;//currentNode移至父节点 
	}
	heap[currentNode] = theElement;//插入元素 
}

template<class T>
void minHeap<T>::pop()//删除 
{
	heap[1].~T();//删除根节点 

	T lastElement = heap[heapSize--];//最后一个元素 
	int currentNode = 1;//最后一个元素所在位置 
	int child = 2;

	while (child <= heapSize)//判断能否放入 
	{
		if (child<heapSize && heap[child]>heap[child + 1])//lastElement与较小的孩子比较 
		{
			child++;
		}
		if (lastElement <= heap[child])//可以放入，停止循环 
		{
			break;
		}
		heap[currentNode] = heap[child];//较小孩子上移 
		currentNode = child;//currentNode移到较小孩子所在位置 
		child *= 2;
	}
	heap[currentNode] = lastElement;//放入lastElement 
}

template<class T>
void minHeap<T>::initialize(int theSize)//初始化 
{
	delete[]heap;//删除堆中原有元素 
	heap = new T[theSize+1];//从1开始存放元素 
	heapSize = theSize;
	arrayLength=theSize+1;

	for (int i = 1; i <= theSize; i++)//输入堆的元素 
	{
		cin >> heap[i];
	}

	for (int root = heapSize / 2; root >= 1; root--)//从拥有叶子的节点开始初始化 
	{
		T rootElement = heap[root];//子树的根节点 
		int child = root * 2;

		while (child <= heapSize)//判断根节点是否需要移动 
		{
			if (child<heapSize && heap[child]>heap[child + 1])//寻找较小孩子的位置 
			{
				child++;
			}
			if (rootElement <= heap[child])//不用移动，停止循环 
			{
				break;
			}
			heap[child / 2] = heap[child];//较小孩子上移 
			child *= 2;//向下比较 
		}
		heap[child / 2] = rootElement;//放入rootElement 
	}
}

template<class T>
void heapSort(int n)//堆排序 
{
	minHeap<T> heap;
	heap.initialize(n);

	for (int i = 0; i < n; i++)
	{
		cout << heap.top() << " ";//根节点为最小元素 
		heap.pop();
	}
	cout << endl;
	heap.deactiveArray();
}

int main()
{
	int n, m; 

	cin >> n;//堆元素个数 
	minHeap<long long> heap;

	heap.initialize(n);
	cout << heap.top() << endl;
	cin >> m;//操作数个数 

	for (int i = 0; i < m; i++)
	{
		int opt;

		cin >> opt;
		switch (opt)
		{
		case 1://插入 
		{
			int num;

			cin >> num;
			heap.push(num);
			cout << heap.top() << endl;
			break;
		}
		case 2://删除 
		{
			heap.pop();
			cout << heap.top() << endl;
			break;
		}
		case 3://排序 
		{
			int n;

			cin >> n;
			heapSort<long long>(n);
			break;
		}
		default:
			break;
		}
	}
	return 0;
}
