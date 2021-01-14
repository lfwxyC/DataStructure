#include<iostream>
using namespace std;

int value=0;//价值的或 
int permutation(int k,int m,int a[])//k:初始值为0，用于计数 m:数组元素个数 a:输入的数组 
{
	int sum=0;//价值 
	
	if(k==m){//得到一组全排列 
		for(int i=0;i<m;i++)
			sum+=(i+1)^a[i];
	}
	else{//计算全排列 
		for(int i=k;i<m;i++){
			swap(a[i],a[k]);
			permutation(k+1,m,a);
			swap(a[i],a[k]);//交换后还原 
		}
	}
	value|=sum;
	return value;
} 

int main()
{
	int n;
	cin>>n;
	
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<permutation(0,n,a)<<endl;
	return 0;
}
