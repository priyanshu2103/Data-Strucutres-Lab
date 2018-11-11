#include<string>
#include "node.h"
#include "btree.h"
using namespace std;

// Tree initialization
btree::btree(){
  root = new node();
  root->setLeaf(true);
  root->setNumKeys(0);
}

tuple<node*, int> btree::search(node* subtree, int key)
{
  // Implementation based on CLRS
  int i = 0;
  // Find the right key position.
  while ( i < subtree->getNumKeys() & key > subtree->getKeyAtIndex(i)){
	i++;
  }
  // If key matches, return the result as a tuple.
  if (i < subtree->getNumKeys() & key == subtree->getKeyAtIndex(i)){
	return make_tuple(subtree, i);
  }
  else{
	// Key does not matches and is a leaf node, return NULL.
	if (subtree->getLeaf()){
	  return make_tuple(static_cast<node*>(NULL), 0);
	}
	// Search recursively the correct subtree.
	else return search(subtree->getChildAtIndex(i), key);
  }
}

void btree::insert(btree* tree, int key){
  // Implementation based on CLRS
  node* root = tree->root;
  // btree::insertSoft(root,key,NULL,0);
  // If root is full, split it.
  if (root->getNumKeys() == (2 * MIN_DEGREE) - 1){
    node* s = new node();
    tree->root = s;
    s->setLeaf(false);
    s->setNumKeys(0);
    s->setChildAtIndex(root, 0);
    btree::splitChild(s, 0);
    btree::insertNonFull(s, key);
  }
  else{
    btree::insertNonFull(root, key);
  }
}

// void btree::insertSoft(node* p,int key,node* parent,int index)
// {
// 	if(p->getLeaf())
// 	{
// 		if(p->getNumKeys()+1<=2*MIN_DEGREE-1)
// 		{
// 			p->setKeyAtIndex(key,p->getNumKeys());
// 			p->setNumKeys(p->getNumKeys()+1);
// 			sort(this->children,this->children+p->getNumKeys());
// 		}
// 		else
// 		{
// 			if(key<=p->getKeyAtIndex(p->getNumKeys()-1))
// 				int temp=p->getChildAtIndex(p->getNumKeys()-1);
// 			else
// 				int temp=key;
// 			int i=0;
// 			while(i<p->getNumKeys()&&key>p->getChildAtIndex(i))
// 				i++;
// 			for(int j=p->getNumKeys()-1;j>i;j--)
// 				p->setKeyAtIndex(p->getKeyAtIndex(j-1),j);
// 			p->setKeyAtIndex(key,i);
// 			int sent=p->getKeyAtIndex(MIN_DEGREE);
// 			if(parent->getNumKeys()<2*MIN_DEGREE-1)
// 			{
// 				for(int j=index+1;j<parent->getNumKeys()+1;j++)
// 					parent->setKeyAtIndex(parent->getKeyAtIndex(j-1),j);
// 				parent->setKeyAtIndex(sent,index);
// 				parent->setNumKeys(parent->getNumKeys()+1);
// 				for(int j=i;j<p->getNumKeys()-1;j++)
// 					p->setKeyAtIndex(p->getKeyAtIndex(j+1),j);
// 				p->setKeyAtIndex(temp,p->getNumKeys()-1);
// 				node* z =new node();
// 				for(int j=0;j<MIN_DEGREE;j++)
// 					z->setKeyAtIndex(p->getKeyAtIndex(MIN_DEGREE+j),j);
// 				y->setNumKeys(MIN_DEGREE);
// 				for(int j=index+2;j<parent->getNumKeys()+1;j++)
// 					parent->setChildAtIndex(parent->getChildAtIndex(j-1,j));
// 				parent->setChildAtIndex(y,index);
// 				parent->setChildAtIndex(z,index+1);
// 			}
// 			else
// 			{

// 			}
// 		}
// 	}
// 	else
// 	{
// 		int i=0;
// 		while(i<p->getNumKeys()&&key>p->getChildAtIndex(i))
// 			i++;
// 		btree::insertSoft(p->getChildAtIndex(i),key,p,i);
// 	}
// }

void btree::insertNonFull(node* x, int key){
  // Implementation based on CLRS
  cout << "Insert node full called on " << key << endl;
  int i = x->getNumKeys();
  // If the node is a leaf node, insert at the correct position.
  if (x->getLeaf()){
    while (i > 0 and key < x->getKeyAtIndex(i - 1)){
      x->setKeyAtIndex(x->getKeyAtIndex(i - 1), i);
      i--;
    }
    x->setKeyAtIndex(key, i);
    x->setNumKeys(x->getNumKeys() + 1);
  }
  else{
    // Is the node is not a leaf node, find the candidate child.
    while(i > 0 & key < x->getKeyAtIndex(i - 1)){
      i--;
    }
    i++;
    // If the child is full, split it.
    if (x->getChildAtIndex(i - 1)->getNumKeys() == (2 * MIN_DEGREE) - 1){
      btree::splitChild(x, i - 1);
      if (key > x->getKeyAtIndex(i - 1)){
        i++;
      }
    }
    btree::insertNonFull(x->getChildAtIndex(i - 1), key);
  }
}

void btree::splitChild(node* x, int i){
  // Implementation based on CLRS
  cout << "Splitting child at index " << i << endl;
  node* z = new node();
  node* y = x->getChildAtIndex(i);
  z->setLeaf(y->getLeaf());
  z->setNumKeys(MIN_DEGREE - 1);

  for (int j = 0; j < MIN_DEGREE - 1; j++){
	z->setKeyAtIndex(y->getKeyAtIndex(j + MIN_DEGREE), j);
  }

  if (!y->getLeaf()){
	for (int j = 0; j <= MIN_DEGREE; j++){
	  z->setChildAtIndex(y->getChildAtIndex(j+MIN_DEGREE), j);
	}
  }
  y->setNumKeys(MIN_DEGREE - 1);
  for (int j = x->getNumKeys(); j >= i + 1; j--){
	x->setChildAtIndex(x->getChildAtIndex(j), j + 1);
  }
  x->setChildAtIndex(z, i + 1);
  for (int j = x->getNumKeys(); j > i; j--){
	x->setKeyAtIndex(x->getKeyAtIndex(j - 1), j);
  }
  x->setKeyAtIndex(y->getKeyAtIndex(MIN_DEGREE - 1), i);
  x->setNumKeys(x->getNumKeys() + 1);
}

void btree::postOrderTraversal(node* subtree, int depth){
  // Print the vertical tree for debugging.
  // The number of times '-' illustrate the depth of the node within the tree.
  // Please check the provided test case.
  int nodesPresent = subtree->getNumKeys();
  if (subtree->getLeaf()){
	for (int j = nodesPresent - 1; j >= 0; j--){
	  cout <<  std::string(depth + 1, '-') << subtree->getKeyAtIndex(j) << endl;
	}
  }
  else{
	for (int j = nodesPresent; j > 0; j--){
	  btree::postOrderTraversal(subtree->getChildAtIndex(j), depth + 1);
	  cout <<  std::string(depth + 1, '-') << subtree->getKeyAtIndex(j - 1) << endl;
	}
	btree::postOrderTraversal(subtree->getChildAtIndex(0), depth + 1);
  }
}
