#include<iostream>
using namespace std;

struct Student
{
	string name;//姓名 
	string phone;//电话号码
	int class_id;//班级
	int dormitory;//宿舍
};

template<class T>
void changeLength(T*& element,int oldLength,int newLength)//倍增数组长度 
{
	T *temp=new T[newLength];//创建新长度的数组 
	
	for(int i=0;i<oldLength;i++)//把旧数组的元素复制到新数组
		temp[i]=element[i]; 
	delete []element;//释放旧数组的空间 
	element=temp;
}

template<class T>
class arrayList
{
public:
	arrayList(int initialCapacity=5);
	~arrayList(){delete []element;}
	 
	int indexOf(string name1)const;//根据姓名获取索引 
	void insert(T stu1);//插入 
	void erase(string name1);//根据姓名删除 
	void edit_phone(string name1,string phone1);//编辑电话 
	void edit_cid(string name1,int cid);//编辑班级
	void edit_dorm(string name1,int dorm);//编辑宿舍 
	void search(string name1);//根据姓名查找 
	void output(int cid);//输出该班级的所有成员的宿舍号的异或值 
private:
	T *element; 
	int listSize;//线性表长度
	int arrayLength;//数组容量 
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	arrayLength=initialCapacity;
	element=new T[arrayLength];
	listSize=0;//初始时没有元素 
}

template<class T>
int arrayList<T>::indexOf(string name1)const
{
	for(int i=0;i<listSize;i++)
		if(element[i].name==name1)
			return i;
	return -1;//没有找到元素 
} 

template<class T>
void arrayList<T>::insert(T stu1)
{
	if(listSize==arrayLength)//数组已满时倍增数组 
	{
		changeLength<struct Student>(element,arrayLength,arrayLength*2);
		arrayLength*=2;
	}
	element[listSize]=stu1;
	listSize++;//线性表长度+1 
}

template<class T>
void arrayList<T>::erase(string name1)
{
	int theIndex=indexOf(name1);
	for(int i=theIndex;i<listSize-1;i++)
		element[i]=element[i+1];
	element[--listSize].~T();//线性表长度-1	
}

template<class T>
void arrayList<T>::edit_phone(string name1,string phone1)
{
	int theIndex=indexOf(name1);//根据姓名查找索引 
	element[theIndex].phone=phone1;
}

template<class T>
void arrayList<T>::edit_cid(string name1,int cid)
{
	int theIndex=indexOf(name1);
	element[theIndex].class_id=cid;
}
template<class T>
void arrayList<T>::edit_dorm(string name1,int dorm)
{
	int theIndex=indexOf(name1);
	element[theIndex].dormitory=dorm;
}

template<class T>
void arrayList<T>::search(string name1)
{
	int theIndex=indexOf(name1);
	if(theIndex==-1)//未找到元素 
		cout<<"0"<<endl;
	else//找到元素 
		cout<<"1"<<endl;
}

template<class T>
void arrayList<T>::output(int cid)
{
	int sum=0;
	
	for(int i=0;i<listSize;i++)
		if(element[i].class_id==cid)//找到指定班级 
			sum^=element[i].dormitory;//计算异或和 
	cout<<sum<<endl;
}

template<class T>
void addressBook(arrayList<T> &a)//对通讯录进行管理 
{
	int m;//操作数 
		
	cin>>m;
	switch(m)
	{
		case 0://插入 
			{
			struct Student stu1;
			
			cin>>stu1.name>>stu1.phone>>stu1.class_id>>stu1.dormitory;
			a.insert(stu1);
			break;
			}
		case 1://删除 
			{
				string name1;
			
			cin>>name1;
			a.erase(name1);
			break;
			}
		case 2://编辑 
			{
			string name1;
			int k;//编辑项目 
			
			cin>>name1>>k;
			switch(k)
			{
				case 1://编辑电话 
					{
					string phone1;
					
					cin>>phone1;
					a.edit_phone(name1,phone1);
					break;
					}					
				case 2://编辑班级 
					{
					int cid;
					
					cin>>cid;
					a.edit_cid(name1,cid);
					break;
					}					
				case 3://编辑宿舍 
					{
					int dorm;
					
					cin>>dorm;
					a.edit_dorm(name1,dorm); 
					break;
					}					
			}
			break;
			}			
		case 3://查找 
			{
			string name1;
			
			cin>>name1;
			a.search(name1);
			break;
			}			
		case 4://输出异或和 
			{
			int cid;
			
			cin>>cid;
			a.output(cid);
			break;
			}
	}
}

int main()
{
	int n;//操作数目 
	arrayList<struct Student> a;
	
	cin>>n;
	for(int i=0;i<n;i++)
		addressBook(a);
	return 0;
}
