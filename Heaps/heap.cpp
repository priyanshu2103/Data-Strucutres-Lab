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

int maximum(int arr[],int i,int l,int r)
{
	int largest=i;

	if(l<=heap_size && arr[l]>arr[i])
		largest=l;
	if(r<=heap_size && arr[r]>arr[largest])
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


void build_max_heap(int arr[])
{
	for(int i=heap_size/2;i>0;i--)
		heapify(arr,i);
}

void move_up(int arr[],int i)
{
	while(i>1 && arr[i]>arr[parent(i)])
	{
		swap(arr[i],arr[parent(i)]);
		i=parent(i);
	}
}

void print_duplicate(int arr[])
{
	for(int i=1;i<=dup_heap_size;i++)
		cout<<arr[i]<<" ";
}

void print(int arr[])
{
	for(int i=1;i<=heap_size;i++)
		cout<<arr[i]<<" ";
}

void heap_sort(int arr[])
{
	build_max_heap(arr);
	while(heap_size>1)
	{
		swap(&arr[heap_size],&arr[1]);
		heap_size--;
		heapify(arr,1);
	}
}

void heap_insert(int arr[],int x)
{
	static int loc=0;
	loc++;
	arr[loc]=x;
	move_up(arr,loc);
}

void heap_delete(int arr[],int i)
{
	if(i!=1)
	{
		arr[i]=arr[heap_size--];
		if(arr[i]>arr[parent(i)])
		{
			move_up(arr,i);
		}
		else
			heapify(arr,i);
	}
	else
	{
		arr[1]=arr[heap_size--];
		heapify(arr,1);
	}
}

int heap_extract_max(int arr[])
{
	int max=arr[1];
	arr[1]=arr[heap_size--];
	heapify(arr,1);
	return max;
}

void heap_increase_key(int arr[],int index, int x)
{
	arr[index]=x;
	move_up(arr,index);
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
		heap_insert(arr,x);
	}
	
	/*
	int ind;
	cin>>ind;
	int x;
	cin>>x;

	heap_increase_key(arr,ind,x);
	*/

	heap_delete(arr,1);
	print(arr);
}