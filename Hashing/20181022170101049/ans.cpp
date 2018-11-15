#include <bits/stdc++.h>
using namespace std;

int buckets;
double load_factor;
list<int> *table;
int number_keys=0;

int hashFunction(int x)
{
	return x%buckets;
}

void insertElem(int x)
{
	int hash_val=hashFunction(x);
	table[hash_val].push_back(x);
}

void deleteItem(int x)
{
	int hash_val=hashFunction(x);
	list <int> :: iterator i;
	for(i=table[hash_val].begin();i!=table[hash_val].end();i++)
		if(*i==x)
		{
			table[hash_val].erase(i);
			break;
		}
}

void displayHashTable()
{
	cout<<"Number of keys is "<<number_keys<<endl;
	cout<<"Number of buckets is: "<<buckets<<endl;
	for(int i=0;i<buckets;i++)
	{
		
		cout<<"Bucket "<<i<<": ";
		list <int> :: iterator j;
		for(j=table[i].begin();j!=table[i].end();j++)
		{
			cout<<*j<<", ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int searchElem(int x)
{
	int index = hashFunction(x); 
  
  // find the key in (inex)th list 
  list <int> :: iterator i; 
  for (i = table[index].begin(); 
           i != table[index].end(); i++) { 
    if (*i == x) 
      break; 
  } 
  
  // if key is found in hash table, remove it 
  if (i != table[index].end()) 
    return *i;
  else
  	return INT_MIN;
  	// a garbage return value specifying that the key is not found
}

int main()
{
	cin>>load_factor;
	cin>>buckets;

	table =new list<int>[buckets];
	double count_factor=0;
	
	int arr[INT_MAX];
	int index=0;
	int a;

	while(cin>>a)
	{
		if(searchElem(a)==INT_MIN)
		{
			number_keys++;
			count_factor=number_keys/buckets;
			if(count_factor>load_factor)
			{
				buckets=buckets*3;
				table =new list<int>[buckets];
				for(int k=0;k<index;k++)
					insertElem(arr[k]);
				insertElem(a);
				arr[index++]=a;
			}
			else
			{
				insertElem(a);
				arr[index++]=a;
			}
		}	
		else
		{
			int returnedVal=searchElem(a);
			cout<<"Key "<<returnedVal<<" already exists in hash table. Status of hash table"<<endl;
			displayHashTable();
		}
		
	}

}