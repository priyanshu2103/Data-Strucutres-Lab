#include <bits/stdc++.h>
using namespace std;

// Program which uses STL functionality
int main()
{
/*----------------------------------------------VECTOR-----------------------------------------*/
	// vector<int> v;
	// for(auto i=0;i<5;i++)
	// 	v.push_back(i);

	// for(auto i=0;i<v.size();i++)
	// 	cout<<v[i]<<" ";
	// cout<<endl;
	// for(auto i=v.begin();i!=v.end();i++)
	// 	cout<<*i<<" ";

	// for(auto i=v.rbegin();i!=v.rend();i++)   // reverse print
	// 	cout<<*i<<" ";

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// some functionality
	//empty():- returns if empty or not
	// v.at(4):- returns 4th element
	// front() : returns first element of vector
	// back() : returns last element of vector
	// vector is passed as vector<int> &v1 in functions
	// sort(v.begin(),v.end())

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 // // Assign vector 
  //   vector<int> v; 
  
  //   // fill the array with 10 five times 
  //   v.assign(5, 10); 
  
  //   cout << "The vector elements are: "; 
  //   for (int i = 0; i < v.size(); i++) 
  //       cout << v[i] << " "; 
  
  //   // inserts 15 to the last position 
  //   v.push_back(15); 
  //   int n = v.size(); 
  //   cout << "\nThe last element is: " << v[n - 1]; 
  
  //   // removes last element 
  //   v.pop_back(); 
  
  //   // prints the vector 
  //   cout << "\nThe vector elements are: "; 
  //   for (int i = 0; i < v.size(); i++) 
  //       cout << v[i] << " "; 
  
  //   // inserts 5 at the beginning 
  //   v.insert(v.begin(), 5); 
  
  //   cout << "\nThe first element is: " << v[0]; 
  
  //   // removes the first element 
  //   v.erase(v.begin()); 
  
  //   cout << "\nThe first element is: " << v[0]; 
  
  //   // inserts at the beginning 
  //   v.emplace(v.begin(), 5); 
  //   cout << "\nThe first element is: " << v[0]; 
  
  //   // Inserts 20 at the end 
  //   v.emplace_back(20); 
  //   n = v.size(); 
  //   cout << "\nThe last element is: " << v[n - 1]; 
  
  //   // erases the vector 
  //   v.clear(); 
  //   cout << "\nVector size after erase(): " << v.size(); 
  
  //   // two vector to perform swap 
  //   vector<int> v1, v2; 
  //   v1.push_back(1); 
  //   v1.push_back(2); 
  //   v2.push_back(3); 
  //   v2.push_back(4); 
  
  //   cout << "\n\nVector 1: "; 
  //   for (int i = 0; i < v1.size(); i++) 
  //       cout << v1[i] << " "; 
  
  //   cout << "\nVector 2: "; 
  //   for (int i = 0; i < v2.size(); i++) 
  //       cout << v2[i] << " "; 
  
  //   // Swaps v1 and v2 
  //   v1.swap(v2); 
  
  //   cout << "\nAfter Swap \nVector 1: "; 
  //   for (int i = 0; i < v1.size(); i++) 
  //       cout << v1[i] << " "; 
  
  //   cout << "\nVector 2: "; 
  //   for (int i = 0; i < v2.size(); i++) 
  //       cout << v2[i] << " "; 

/*---------------------------------------------- PRIORITY QUEUE -----------------------------------*/
	// priority_queue<int> pq;
	// pq.push(10);
	// pq.push(20);
	// pq.push(30);
	// cout<<"Size of priority queue is "<<pq.size()<<endl;
	// while(!pq.empty())
	// {
	// 	cout<<pq.top()<<" ";
	// 	pq.pop();
	// }

		// min heap
		// priority_queue < int, vector<int>, greater<int> > pq;
		// pq.push(10);
		// pq.push(20);
		// pq.push(30);
		// while(!pq.empty())
		// {
		// 	cout<<pq.top()<<" ";
		// 	pq.pop();
		// }

/*-----------------------------------------------LIST --------------------------------------------*/
	// list<int> l1;
	// l1.push_back(10);
	// l1.push_back(20);
	// l1.push_back(30);
	// l1.push_back(15);

	// l1.sort();

	// for(auto i=l1.begin();i!=l1.end();i++)
	// 	cout<<*i<<" ";

	// l1.reverse();

	// front() – Returns the value of the first element in the list
	// back() – Returns the value of the last element in the list
	// push_front(g) – Adds a new element ‘g’ at the beginning of the list
	// push_back(g) – Adds a new element ‘g’ at the end of the list
	// pop_front() – Removes the first element of the list, and reduces size of the list by 1
	// pop_back() – Removes the last element of the list, and reduces size of the list by 1
	// begin() – Returns an iterator pointing to the first element of the list
	// end() – Returns an iterator pointing to the theoretical last element which follows the last element
	// empty() – Returns whether the list is empty(1) or not(0)
	// insert() – Inserts new elements in the list before the element at a specified position
	// erase() – Removes a single element or a range of elements from the list
	// assign() – Assigns new elements to list by replacing current elements and resizes the list
	// remove() – Removes all the elements from the list, which are equal to given element
	// reverse() – Reverses the list
	// size() – Returns the number of elements in the list
	// sort() – Sorts the list in increasing order

/* --------------------------------------------- PAIR ----------------------------------------------------*/
	// pair <int,char> PAIR1 (1,'A');
	// pair <int,char> PAIR2;
	// PAIR2.first=1;
	// PAIR2.second='A';

	// pair <int,char> PAIR3;
	// PAIR3=make_pair(1,'A');

	// // you can use >,<,>=,<= operators in comparing pairs, but it gives a bool return value with comparing only first elements of pair
	// PAIR2.swap(PAIR3);

	// vector< pair <int,int> > vect; // declaring vector of pairs
	// sort(vect.begin(),vect.end()); // sort in ascending order on the basis of first element
	// sort(vect.begin(),vect.end(),sortBySec); // sortBySec function used to sort on the basis of 2nd element in descending order

	// bool sortbysec(const pair<int,int> &a, const pair<int,int> &b)   
	// { 
 //    	return (a.second < b.second); 
 //    }

/* ----------------------------------------- STACKS AND QUEUES -------------------------------------------*/
	// STACK :
	// 	empty() – Returns whether the stack is empty – Time Complexity : O(1)
	// 	size() – Returns the size of the stack – Time Complexity : O(1)
	// 	top() – Returns a reference to the top most element of the stack – Time Complexity : O(1)
	// 	push(g) – Adds the element ‘g’ at the top of the stack – Time Complexity : O(1)
	// 	pop() – Deletes the top most element of the stack – Time Complexity : O(1)

	// stack<int> s;

	// QUEUE:
	// 	empty() – Returns whether the queue is empty
	// 	size() – Returns the size of the queue
	// 	front() – Returns a reference to the first element of the queue
	// 	back() – Returns a reference to the last element of the queue
	// 	push(g) – Adds the element ‘g’ at the end of the queue
	// 	pop() – Deletes the first element of the queue

	// queue<int> q;



}

 