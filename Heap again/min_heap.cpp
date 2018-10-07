#include <iostream>
#include <stdlib.h>
#define MAX_SIZE 1000
using namespace std;

int heap_size;
int dup_heap_size;


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

int minimum(int arr[],int i,int l,int r)
{
	int smallest=i;

	if(l<=heap_size && arr[l]<arr[i])
		smallest=l;
	if(r<=heap_size && arr[r]<arr[smallest])
		smallest=r;

	return smallest;
}

void heapify_min(int arr[],int i)
{
	int l=left(i);
	int r=right(i);
	int index=minimum(arr,i,l,r);

	if(index!=i)
	{
		swap(&arr[i],&arr[index]);
		heapify_min(arr,index);
	}
}


void build_min_heap(int arr[])
{
	for(int i=heap_size/2;i>0;i--)
		heapify_min(arr,i);
}

void move_up(int arr[],int i)
{
	while(i>1 && arr[i]<arr[parent(i)])
	{
		swap(&arr[i],&arr[parent(i)]);
		i=parent(i);
	}
}

void heap_insert_min(int arr[],int i)
{
	static int loc=0;
	loc++;
	arr[loc]=i;
	move_up(arr,loc);
}

void heap_delete_min(int arr[],int i)
{
	if(i!=1)
	{
		arr[i]=arr[heap_size--];
		if(arr[i]<arr[parent(i)])
			move_up(arr,i);
		else
			heapify_min(arr,i);
	}
	if(i==1)
	{
		arr[1]=arr[heap_size--];
		heapify_min(arr,1);
	}
}

void heap_increase_key(int arr[],int index,int x)
{
	arr[index]=x;
	heapify_min(arr,index);
}

void print(int arr[])
{
	for(int i=1;i<=heap_size;i++)
		cout<<arr[i]<<" ";
}

int main()
{
	int arr[MAX_SIZE]={0};

	cout << "Enter number of elements" <<endl;
	cin >> heap_size;
	dup_heap_size=heap_size;

	cout << "Enter elements" << endl;

	/*
	for(int i = 1 ; i <= heap_size ;i++)
	{
		cin>>arr[i];
		//if(i>=2) move_up(arr,i);   (top bottom approach to build heap)
	}
	*/

	//build_max_heap(arr);     /* bottoms up approach to build heap*/
	
	for(int i=1;i<=heap_size;i++)
	{
		int x;
		cin>>x;
		heap_insert_min(arr,x);
	}
	
	
	 int ind;
	 cin>>ind;
	 int x;
	 cin>>x;

	 heap_increase_key(arr,ind,x);
	

	//heap_delete_min(arr,2);
	print(arr);
}