/*top down approach*/

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#define MAX 30
using namespace std;

/* Declaring array essentials*/
int heap_size;
int * arr = new int[MAX];

int heap_size2;
int * arr2 = new int[MAX];


void insert(int x);
int parent(int i);
int left(int i);
int right(int i);
void swap(int *x, int *y);
void print();
int max(int i, int l , int r);
void heapify(int i);
void build_max_heap();
void heap_sort();
void moveup(int index);
void heap_delete(int index);
int heap_extract_max();
void heap_increase_key(int index,int newkey);

int main()
{
	//top down approach
	/*int a;

	cout << "Enter sequence/ -1 to exit : \n";
	cin >> a;
	while(a != -1)
	{
		insert(a);
		cin>>a;
	}
	cout << endl;
	for(int i = 0 ; i <=heap_size ; i++)
		cout << arr[i] << " ";
	cout << endl;*/
	
	/*-----------------------*/
	//bottom up approach
	cout << "Enter number of elements" <<endl;
	cin >> heap_size;
	//int size=heap_size;
	cout << "Enter elements" << endl;
	for(int i = 1 ; i <= heap_size ;i++)
	{
		cin>>arr[i];
	}
	
	//sorting
	//heap_sort();
	build_max_heap();
	print();
	cout<<"Enter index you want to delete" << endl;
	int index;
	cin>>index;
	heap_delete(index);
	print();
	
	return 0;
}


void insert(int x)
{
	heap_size++;
	arr[heap_size]=x;
	int i = heap_size;
	while( i > 1 && arr[i] > arr[parent(i)])
	{
		swap(&arr[i],&arr[parent(i)]);
		i = parent(i);
	}
}

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
	return (2*i + 1);
}

void swap(int *x, int *y)
{
	int temp = (*x);
	(*x)=(*y);
	(*y)=temp;
	return;
}


void heapify(int i)
{
	int l = left(i);
	int r = right(i);

	int x = max(i,l,r);
	if(x!=i)
	{
		swap(arr[x],arr[i]);
		heapify(x);
	}
}


int max(int i, int l , int r)
{
	int largest = i;

	if(l<=heap_size && arr[l]>arr[i])
		largest=l;

	if(r<=heap_size && arr[r] > arr[largest])
		largest = r;

	return largest;
}


void build_max_heap()
{
	for(int i = (heap_size/2); i>=1; i--)
	{
		heapify(i);
	}
}

void heap_sort()
{
	build_max_heap();
	while(heap_size>1)
	{
		swap(arr[heap_size],arr[1]);
		heap_size--;
		heapify(1);
	}
}

void moveup(int index)
{
	int i = index;
	while( i >1 && arr[i] > arr[parent(i)])
	{
		swap(&arr[i],&arr[parent(i)]);
		i = parent(i);
	}
}
void heap_delete(int index)
{
	arr[index] = arr[heap_size--];
	if(arr[index] > arr[parent(index)])
		moveup(index);

	else
		heapify(index);
}

int heap_extract_max()
{
	int temp = arr[1];
	arr[1]=arr[heap_size--];
	heapify(1);

	return temp;
}

void heap_increase_key(int index,int newkey)
{
	if(newkey < arr[index])
		cout<< "Error" << endl;
	else
	{
		arr[index]=newkey;
		moveup(index);
	}
}
void print()
{
	for(int i = 1 ; i <= heap_size ;i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void heap_union(int * arr1,int* arr2)
{
	int *result = new int[2*MAX];
	copy(arr1,arr1+heap_size,result);
	copy(arr2,arr2+heap_size2,result+heap_size);
}