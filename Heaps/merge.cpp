#include <iostream>
#include <stdlib.h>
#define MAX_SIZE 1000
using namespace std;

int heap_size_1;
int heap_size_2;

int parent(int i)
{
	return i/2;
}

int left(int i)
{
	return 2*i;
}

int right(int i)
{
	return (2*i+1);
}

void swap(int* a,int* b)
{
	int t=*a;
	*a=*b;
	*b=t;
	return ;
}

int maximum(int arr[],int i,int l,int r)
{
	int largest=i;

	if(l<=heap_size_1+heap_size_2 && arr[l]>arr[i])
		largest=l;
	if(r<=heap_size_1+heap_size_2 && arr[r]>arr[i] && arr[r]>arr[largest])
		largest=r;

	return largest;
}

void heapify(int arr[],int i)
{
	int l=left(i);
	int r=right(i);
	int index=maximum(arr,i,l,r);

	if(index!=i)
	{
		swap(&arr[i],&arr[index]);
		heapify(arr,index);
	}
}

void build_max_heap_merge(int A1[])
{
	int size=heap_size_1+heap_size_2;
	for(int i=size/2;i>0;i--)
		heapify(A1,i);
}

void heap_merge(int A1[],int A2[],int A3[])
{
	for(int i=1;i<=heap_size_1;i++)
		A1[i]=A2[i];
	for(int i=heap_size_1+1;i<=heap_size_1+heap_size_2;i++)
		A1[i]=A3[i-heap_size_1];

	build_max_heap_merge(A1);
}

int main()
{
	cin>>heap_size_1>>heap_size_2;

	int arr1[MAX_SIZE]={0};
	int arr2[MAX_SIZE]={0};
	int arr3[MAX_SIZE]={0};

	for(int i=1;i<=heap_size_1;i++)
		cin>>arr1[i];

	for(int i=1;i<=heap_size_2;i++)
		cin>>arr2[i];


	for(int i=heap_size_1/2;i>0;i--)
		heapify(arr1,i);
	for(int i=heap_size_2/2;i>0;i--)
		heapify(arr2,i);

	heap_merge(arr3,arr1,arr2);

	for(int i=1;i<=heap_size_2+heap_size_1;i++)
		cout<<arr3[i]<<" ";

}