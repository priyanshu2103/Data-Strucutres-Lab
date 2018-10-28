#include <bits/stdc++.h>
using namespace std;

list<int> *table;
int buckets;

int hashFunction(int x)
{
	return x%buckets;
	// or any other hash function
}

void insertElem(int x)
{
	int hash_val=hashFunction(x);
	table[hash_val].push_back(x);
}

void deleteItem(int x)
{
	int hash_val=hashFunction(x);
	for(auto i=table[hash_val].begin();i!=table[hash_val].end();i++)
		if(*i==x)
		{
			table[hash_val].erase(i);
			break;
		}
}

void displayHashTable()
{
	for(auto i=0;i<buckets;i++)
	{
		cout<<i<<": ";
		for(auto j=table[i].begin();j!=table[i].end();j++)
		{
			cout<<"--> "<<*j;
		}
		cout<<endl;
	}
}

int main()
{
	cout<<"Tell the number of elements: ";
	int num;
	cin>>num;
	cout<<"Enter the number of buckets you want: ";
	cin>>buckets;

	table =new list<int>[buckets];

	cout<<"Enter elements"<<endl;
	int arr[num];

	for(auto i=0;i<num;i++)
	{
		cin>>arr[i];
		insertElem(arr[i]);
	}

	displayHashTable();
	deleteItem(arr[0]);
	displayHashTable();
	insertElem(arr[0]);
	displayHashTable();

}