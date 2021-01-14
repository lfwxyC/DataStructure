#include<iomanip>
#include<iostream>
using namespace std;

template<class T>
class arrayStack
{
public:
	arrayStack(int initialCapacity = 10);//构造函数 
	~arrayStack() { delete[] stack; }//析构函数 
	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T& top() {
		if (stackTop == -1)
			exit(1);
		return stack[stackTop];
	}
	void pop()
	{
		if (stackTop == -1)
			exit(1);
		stack[stackTop--].~T();//T的析构函数 
	}
	void push(const T& theElement);
private:
	int stackTop;
	int stackLength;
	T* stack;
};
//构造函数 
template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
		exit(1);
	stackLength = initialCapacity;
	stack = new T[stackLength];
	stackTop = -1;
}
template<class T>
void arrayStack<T>::push(const T& theElement)
{//将元素theElement压入栈 
	if (stackTop == stackLength - 1) {//judge if the capacity is full
		stackLength *= 2;      //将栈的容量扩充二倍 
		T *newStack=new T[stackLength];
		for (int i = 0;i < stackLength;i++)
		{
			newStack[i] = stack[i];
		}
		delete []stack;
		stack = newStack;
	}
	stack[++stackTop] = theElement;
}

void compute(arrayStack<double>& number, arrayStack<char>& opr)
{
	double right_num = number.top();
	number.pop();
	double left_num = number.top();
	number.pop();
	
	switch (opr.top())
	{
	case '+':
		number.push(left_num + right_num);
		break;
	case '-':
		number.push(left_num - right_num);
		break;
	case '*':
		number.push(left_num * right_num);
		break;
	case '/':
		number.push(left_num / right_num);
		break;
	default:
		break;
	}
	opr.pop();
}

void operate(string& str)
{
	arrayStack<double> number;
	arrayStack<char> opr;//运算符号

	for (int j = 0;j < (int)str.length();j++)
	{
		switch (str[j])
		{
		case '+':
		case '-':
			while (!opr.empty() && opr.top() != '(' && opr.top() != ')')
				compute(number, opr);

			opr.push(str[j]);
			break;
		case '*':
		case '/':
			if (!opr.empty() && (opr.top() == '*' || opr.top() == '/'))
				compute(number, opr);

			opr.push(str[j]);
			break;
		case '(':
			opr.push(str[j]);
			break;
		case ')':
			while (opr.top() != '(')
				compute(number, opr);
			opr.pop();
			if (!opr.empty() && (opr.top() == '*' || opr.top() == '/'))
				compute(number, opr);
			break;
		default:
		{
			double num = str[j] - '0';
			number.push(num);
			break;
		}
		}
	}
	while (!opr.empty())
		compute(number, opr);
	cout << setiosflags(ios::fixed) << setprecision(2) << number.top() << endl;
}

int main()
{
	int n;

	cin >> n;
	for (int i = 0;i < n;i++)
	{
		string str;
		cin >> str;
		operate(str);
	}
	return 0;
}
