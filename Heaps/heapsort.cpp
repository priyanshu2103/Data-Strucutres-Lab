#include <iostream>
#include <stdlib.h>
#define MAX_SIZE 1000
using namespace std;

//int heap_size;
//int dup_heap_size;


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



int maximum(int arr[],int i,int l,int r,int n)
{
	int largest=i;

	if(l<=n && arr[l]>arr[i])
		largest=l;
	if(r<=n && arr[r]>arr[largest])
		largest=r;

	return largest;
}

void heapify(int arr[],int i,int n)
{
	int l=left(i);
	int r=right(i);
	int index=maximum(arr,i,l,r,n);

	if(index!=i)
	{
		swap(&arr[i],&arr[index]);
		heapify(arr,index,n);
	}
}

void build_max_heap(int arr[],int n)
{
	for(int i=n/2;i>0;i--)
		heapify(arr,i,n);
}

void heap_sort(int arr[],int n)
{
	build_max_heap(arr,n);
	while(n>1)
	{
		swap(&arr[n],&arr[1]);
		n--;
		heapify(arr,1,n);
	}
}

int main()
{
	int heap_size;
	cin>>heap_size;
	int arr[heap_size+1];
	for(int i=1;i<=heap_size;i++)
		cin>>arr[i];

	heap_sort(arr,heap_size);

	for(int i=1;i<=heap_size;i++)
		cout<<arr[i]<<" ";


}