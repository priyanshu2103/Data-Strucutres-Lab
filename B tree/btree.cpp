#include <string>
#include "node.h"
#include "btree.h"
using namespace std;
// B Tree of order m means maximum m children
// Tree initialization
btree::btree(){
  root = new node();
  root->setLeaf(true);
  root->setNumKeys(0);
  root->setParent(NULL);
  count=0;
}

tuple<node*, int> btree::search(node* subtree, int key){
  // Implementation based on CLRS
  int i = 0;
  // Find the right key position.
  while ( i < subtree->getNumKeys() && key > subtree->getKeyAtIndex(i)){
    i++;
  }
  // If key matches, return the result as a tuple.
  if (i < subtree->getNumKeys() && key == subtree->getKeyAtIndex(i)){
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

// call this function for soft splitting
void btree::insertSoft(btree *tree,int key)
{
  //Not allowing duplicates
  int searchResultIndex;
  node *searchResult;
  tie(searchResult, searchResultIndex) = tree->search(tree->root, key);
  if(searchResult!=NULL) return;
  node *r=tree->root;
  int l;
  while(!r->getLeaf())
  {
    l=r->getNumKeys()-1;
    while(l>=0 && key < r->getKeyAtIndex(l))
      l--;
    r=r->getChildAtIndex(l+1);
  }
  // now we are at the leaf node
    if(r->getNumKeys()<(2*MIN_DEGREE-1))
    {
        // if leaf node is not full, just insert
      int i=r->getNumKeys()-1;
      while(i>=0 && key < r->getKeyAtIndex(i))
      {
        r->setKeyAtIndex(r->getKeyAtIndex(i),i+1);
        i--;
      }
      r->setKeyAtIndex(key,i+1);
      r->setNumKeys(r->getNumKeys()+1);
    }
    else
    {
        // if leaf node is full, we are extending array and for that we are taking a temp var
      int temp;
      if(key>r->getKeyAtIndex(r->getNumKeys()-1))
      {
        temp=key;
      }
      else
      {
        int i=r->getNumKeys()-2;
        temp =r->getKeyAtIndex(i+1);
        while(i>=0 && key < r->getKeyAtIndex(i))
        {
          r->setKeyAtIndex(r->getKeyAtIndex(i),i+1);
          i--;
        }
        r->setKeyAtIndex(key,i+1);
      }
      // node y and node z are the split nodes of r
      node *y=r;
      node *z=new node();
      count++;
      for (int j = MIN_DEGREE+1; j <= 2*MIN_DEGREE - 2; j++){
        z->setKeyAtIndex(y->getKeyAtIndex(j), j- MIN_DEGREE -1);
      }
      z->setKeyAtIndex(temp,MIN_DEGREE-2);
      temp=y->getKeyAtIndex(MIN_DEGREE);
      y->setNumKeys(MIN_DEGREE);
      z->setNumKeys(MIN_DEGREE-1);
      z->setParent(y->getParent());
      z->setLeaf(true);
      if(y==tree->root)
      {
        node *s=new node();
        s->setLeaf(false);
        tree->root=s;
        s->setParent(NULL);
        s->setChildAtIndex(y,0);
        s->setChildAtIndex(z,1);
        s->setKeyAtIndex(temp,0);
        y->setParent(s);
        z->setParent(s);
        s->setNumKeys(1);
        return;
      }
      node *s=y->getParent();
      btree::insertNonLeaf(s,z,temp);
    }
}

void btree::insertNonLeaf(node *x,node *p,int key)
{
  if(x->getNumKeys()<2*MIN_DEGREE -1)
  {
    // if the parent has accomodation , it's all well and good then
    int i=x->getNumKeys()-1;
    while(i>=0 && key < x->getKeyAtIndex(i))
    {
      x->setKeyAtIndex(x->getKeyAtIndex(i),i+1);
      x->setChildAtIndex(x->getChildAtIndex(i+1),i+2);
      x->getChildAtIndex(i+2)->setParent(x);
      i--;
    }
    x->setKeyAtIndex(key,i+1);
    x->setChildAtIndex(p,i+2);
    x->setNumKeys(x->getNumKeys()+1);
    return;
  }
  int temp;
  node *t;
  node *r=x; 
      if(key>r->getKeyAtIndex(r->getNumKeys()-1))
      {
        temp=key;
        t=p;
      }
      else
      {
        int i=r->getNumKeys()-2;
        temp =r->getKeyAtIndex(i+1);
        t=r->getChildAtIndex(i+2);
        while(i>=0 && key < r->getKeyAtIndex(i))
        {
          r->setKeyAtIndex(r->getKeyAtIndex(i),i+1);
          r->setChildAtIndex(r->getChildAtIndex(i+1),i+2);
          r->getChildAtIndex(i+2)->setParent(r);
          i--;
        }
        r->setKeyAtIndex(key,i+1);
        r->setChildAtIndex(p,i+2);
      }
      node *y=r;
      node *z=new node();
      count++;
      for (int j = MIN_DEGREE+1; j <= 2*MIN_DEGREE - 2; j++){
        z->setKeyAtIndex(y->getKeyAtIndex(j), j- MIN_DEGREE -1);
        z->setChildAtIndex(y->getChildAtIndex(j),j- MIN_DEGREE-1);
        z->getChildAtIndex(j - MIN_DEGREE-1)->setParent(z);
      }
      z->setKeyAtIndex(temp,MIN_DEGREE-2);
      z->setChildAtIndex(y->getChildAtIndex(2*MIN_DEGREE-1),MIN_DEGREE-2);
      z->getChildAtIndex(MIN_DEGREE-2)->setParent(z);
      z->setChildAtIndex(t,MIN_DEGREE-1);
      z->getChildAtIndex(MIN_DEGREE-1)->setParent(z);
      temp=y->getKeyAtIndex(MIN_DEGREE);
      y->setNumKeys(MIN_DEGREE);
      z->setNumKeys(MIN_DEGREE-1);
      z->setParent(y->getParent());
      z->setLeaf(y->getLeaf());
      if(y->getParent()==NULL)
      {
        node *s=new node();
        s->setLeaf(false);
        this->root=s;
        s->setParent(NULL);
        s->setChildAtIndex(y,0);
        s->setChildAtIndex(z,1);
        s->setKeyAtIndex(temp,0);
        y->setParent(s);
        z->setParent(s);
        s->setNumKeys(1);
        return;
      }
      node *s=y->getParent();
      btree::insertNonLeaf(s,z,temp);
}


void btree::insertSoftNbh(btree *tree,int key)
{
  //Not allowing duplicates
  int searchResultIndex;
  node *searchResult;
  tie(searchResult, searchResultIndex) = tree->search(tree->root, key);
  if(searchResult!=NULL) return;
  node *r=tree->root;
  int l;
  while(!r->getLeaf())
  {
    l=r->getNumKeys()-1;
    while(l>=0 && key < r->getKeyAtIndex(l))
    {
      //root->setKeyAtIndex(root->getKeyAtIndex(l),l+1);
      l--;
    }
    r=r->getChildAtIndex(l+1);
  }
  //if(root->getLeaf())
  //{
    if(r->getNumKeys()<(2*MIN_DEGREE-1))
    {
      int i=r->getNumKeys()-1;
      while(i>=0 && key < r->getKeyAtIndex(i))
      {
        r->setKeyAtIndex(r->getKeyAtIndex(i),i+1);
        i--;
      }
      r->setKeyAtIndex(key,i+1);
      r->setNumKeys(r->getNumKeys()+1);
    }
    else
    {

      int temp;
      if(key>r->getKeyAtIndex(r->getNumKeys()-1))
      {
        temp=key;
      }
      else
      {
        int i=r->getNumKeys()-2;
        temp =r->getKeyAtIndex(i+1);
        while(i>=0 && key < r->getKeyAtIndex(i))
        {
          r->setKeyAtIndex(r->getKeyAtIndex(i),i+1);
          i--;
        }
        r->setKeyAtIndex(key,i+1);
      }

      node *m=r->getParent();
      if(m!=NULL)
      {
        int k=r->getKeyAtIndex(0);
        int q=m->getNumKeys()-1;
        while(q>=0 && k < m->getKeyAtIndex(q))
        {
          q--;
        }
        q++;
        int li=q-1;
        int ri=q+1;
        if(li>=0)
        {
          node *lc=m->getChildAtIndex(li);
          if(lc->getNumKeys()<2*MIN_DEGREE-1)
          {
            lc->setKeyAtIndex(m->getKeyAtIndex(q-1),lc->getNumKeys());
            m->setKeyAtIndex(r->getKeyAtIndex(0),q-1);
            lc->setNumKeys(lc->getNumKeys()+1);
           // lc->setChildAtIndex(r->getChildAtIndex(0),lc->getNumKeys());
            for(int j=0;j<r->getNumKeys()-1;j++)
            {
              r->setKeyAtIndex(r->getKeyAtIndex(j+1),j);
            }
            r->setKeyAtIndex(temp,r->getNumKeys()-1);
            return;
          }
        }
        if(ri<=m->getNumKeys())
        {
          node *rc=m->getChildAtIndex(ri);
          if(rc->getNumKeys()<2*MIN_DEGREE-1)
          {
            for(int j=rc->getNumKeys()-1;j>=0;j--)
            {
              rc->setKeyAtIndex(rc->getKeyAtIndex(j),j+1);
            }
            rc->setKeyAtIndex(m->getKeyAtIndex(q),0);
            m->setKeyAtIndex(temp,q);
            rc->setNumKeys(rc->getNumKeys()+1);
           // lc->setChildAtIndex(r->getChildAtIndex(0),lc->getNumKeys());
            return;
          }
        }
      }
      node *y=r;
      node *z=new node();
      for (int j = MIN_DEGREE+1; j <= 2*MIN_DEGREE - 2; j++){
        z->setKeyAtIndex(y->getKeyAtIndex(j), j- MIN_DEGREE -1);
      }
      z->setKeyAtIndex(temp,MIN_DEGREE-2);
      temp=y->getKeyAtIndex(MIN_DEGREE);
      y->setNumKeys(MIN_DEGREE);
      z->setNumKeys(MIN_DEGREE-1);
      z->setParent(y->getParent());
      z->setLeaf(true);
      if(y==tree->root)
      {
        node *s=new node();
        s->setLeaf(false);
        tree->root=s;
        s->setParent(NULL);
        s->setChildAtIndex(y,0);
        s->setChildAtIndex(z,1);
        s->setKeyAtIndex(temp,0);
        y->setParent(s);
        z->setParent(s);
        s->setNumKeys(1);
        return;
      }
      node *s=y->getParent();
      btree::insertNonLeafNbh(s,z,temp);
      //  btree::split(prev,l+1);
    }
}

void btree::insertNonLeafNbh(node *x,node *p,int key)
{
  if(x->getNumKeys()<2*MIN_DEGREE -1)
  {
    int i=x->getNumKeys()-1;
    while(i>=0 && key < x->getKeyAtIndex(i))
    {
      x->setKeyAtIndex(x->getKeyAtIndex(i),i+1);
      x->setChildAtIndex(x->getChildAtIndex(i+1),i+2);
      x->getChildAtIndex(i+2)->setParent(x);
      i--;
    }
    x->setKeyAtIndex(key,i+1);
    x->setChildAtIndex(p,i+2);
    x->setNumKeys(x->getNumKeys()+1);
    return;
  }
  int temp;
  node *t;
  node *r=x; 
      if(key>r->getKeyAtIndex(r->getNumKeys()-1))
      {
        temp=key;
        t=p;
      }
      else
      {
        int i=r->getNumKeys()-2;
        temp =r->getKeyAtIndex(i+1);
        t=r->getChildAtIndex(i+2);
        while(i>=0 && key < r->getKeyAtIndex(i))
        {
          r->setKeyAtIndex(r->getKeyAtIndex(i),i+1);
          r->setChildAtIndex(r->getChildAtIndex(i+1),i+2);
          r->getChildAtIndex(i+2)->setParent(r);
          i--;
        }
        r->setKeyAtIndex(key,i+1);
        r->setChildAtIndex(p,i+2);
      }

      node *m=r->getParent();
      if(m!=NULL)
      {
        int k=r->getKeyAtIndex(0);
        int q=m->getNumKeys()-1;
        while(q>=0 && k < m->getKeyAtIndex(q))
        {
          q--;
        }
        q++;
        int li=q-1;
        int ri=q+1;
        if(li>=0)
        {
          node *lc=m->getChildAtIndex(li);
          if(lc->getNumKeys()<2*MIN_DEGREE-1)
          {
            lc->setKeyAtIndex(m->getKeyAtIndex(q-1),lc->getNumKeys());
            m->setKeyAtIndex(r->getKeyAtIndex(0),q-1);
            lc->setNumKeys(lc->getNumKeys()+1);
            lc->setChildAtIndex(r->getChildAtIndex(0),lc->getNumKeys());
            lc->getChildAtIndex(lc->getNumKeys())->setParent(lc);
            for(int j=0;j<r->getNumKeys()-1;j++)
            {
              r->setKeyAtIndex(r->getKeyAtIndex(j+1),j);
              r->setChildAtIndex(r->getChildAtIndex(j+1),j);
              r->getChildAtIndex(j)->setParent(r);
            }
            r->setKeyAtIndex(temp,r->getNumKeys()-1);
            r->setChildAtIndex(r->getChildAtIndex(r->getNumKeys()),r->getNumKeys()-1);
            r->getChildAtIndex(r->getNumKeys()-1)->setParent(r);
            r->setChildAtIndex(t,r->getNumKeys());
            r->getChildAtIndex(r->getNumKeys())->setParent(r);
            return;
          }
        }
        if(ri<=m->getNumKeys())
        {
          node *rc=m->getChildAtIndex(ri);
          if(rc->getNumKeys()<2*MIN_DEGREE-1)
          {
            rc->setChildAtIndex(rc->getChildAtIndex(rc->getNumKeys()),rc->getNumKeys()+1);
            rc->getChildAtIndex(rc->getNumKeys()+1)->setParent(rc);
            for(int j=rc->getNumKeys()-1;j>=0;j--)
            {
              rc->setKeyAtIndex(rc->getKeyAtIndex(j),j+1);
              rc->setChildAtIndex(rc->getChildAtIndex(j),j+1);
              rc->getChildAtIndex(j+1)->setParent(rc);
            }
            rc->setKeyAtIndex(m->getKeyAtIndex(q),0);
            rc->setChildAtIndex(t,0);
            rc->getChildAtIndex(0)->setParent(rc);
            m->setKeyAtIndex(temp,q);
            rc->setNumKeys(rc->getNumKeys()+1);
            return;
          }
        }
      }
      node *y=r;
      node *z=new node();
      for (int j = MIN_DEGREE+1; j <= 2*MIN_DEGREE - 2; j++){
        z->setKeyAtIndex(y->getKeyAtIndex(j), j- MIN_DEGREE -1);
        z->setChildAtIndex(y->getChildAtIndex(j),j- MIN_DEGREE-1);
        z->getChildAtIndex(j - MIN_DEGREE-1)->setParent(z);
      }
      z->setKeyAtIndex(temp,MIN_DEGREE-2);
      z->setChildAtIndex(y->getChildAtIndex(2*MIN_DEGREE-1),MIN_DEGREE-2);
      z->getChildAtIndex(MIN_DEGREE-2)->setParent(z);
      z->setChildAtIndex(t,MIN_DEGREE-1);
      z->getChildAtIndex(MIN_DEGREE-1)->setParent(z);
      temp=y->getKeyAtIndex(MIN_DEGREE);
      y->setNumKeys(MIN_DEGREE);
      z->setNumKeys(MIN_DEGREE-1);
      z->setParent(y->getParent());
      z->setLeaf(y->getLeaf());
      if(y->getParent()==NULL)
      {
        node *s=new node();
        s->setLeaf(false);
        this->root=s;
        s->setParent(NULL);
        s->setChildAtIndex(y,0);
        s->setChildAtIndex(z,1);
        s->setKeyAtIndex(temp,0);
        y->setParent(s);
        z->setParent(s);
        s->setNumKeys(1);
        return;
      }
      node *s=y->getParent();
      btree::insertNonLeafNbh(s,z,temp);
}

// call this function for proactive splitting
void btree::insert(btree* tree, int key){
  // Implementation based on CLRS
  //Not allowing duplicates
  int searchResultIndex;
  node *searchResult;
  tie(searchResult, searchResultIndex) = tree->search(tree->root, key);
  if(searchResult!=NULL) return;
  node* root = tree->root;
  // If root is full, split it.
  if (root->getNumKeys() == (2 * MIN_DEGREE) - 1){
    node* s = new node();
    tree->root = s;
    s->setLeaf(false);
    s->setNumKeys(0);
    s->setChildAtIndex(root, 0);
    root->setParent(s);
    btree::splitChild(s, 0);
    btree::insertNonFull(s, key);
  }
  else{
    btree::insertNonFull(root, key);
  }
}

void btree::insertNonFull(node* x, int key){
  // Implementation based on CLRS
  cout << "Insert node full called on " << key << endl;
  int i = x->getNumKeys()-1;
  // If the node is a leaf node, insert at the correct position.
  if (x->getLeaf()){
    while (i >= 0 && key < x->getKeyAtIndex(i)){
      x->setKeyAtIndex(x->getKeyAtIndex(i),i+1);
      i--;
    }
    x->setKeyAtIndex(key,i+1);
    x->setNumKeys(x->getNumKeys()+1);
  }
  else{
    // Is the node is not a leaf node, find the candidate child.
    while(i >=0 && key < x->getKeyAtIndex(i)){
      i--;
    }
    i++;
    // If the child is full, split it.
    if (x->getChildAtIndex(i)->getNumKeys() == (2 * MIN_DEGREE) - 1){
      btree::splitChild(x,i);
      if (key > x->getKeyAtIndex(i)){
        i++;
      }
    }
    btree::insertNonFull(x->getChildAtIndex(i),key);
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
      z->getChildAtIndex(j)->setParent(z);
    }
  }
  y->setNumKeys(MIN_DEGREE - 1);
  for (int j = x->getNumKeys(); j >= i + 1; j--){
    x->setChildAtIndex(x->getChildAtIndex(j), j + 1);
    x->getChildAtIndex(j+1)->setParent(x);
  }
  x->setChildAtIndex(z, i + 1);
  x->getChildAtIndex(i + 1)->setParent(x);
  for (int j = x->getNumKeys(); j > i; j--){
    x->setKeyAtIndex(x->getKeyAtIndex(j - 1), j);
  }
  x->setKeyAtIndex(y->getKeyAtIndex(MIN_DEGREE - 1), i);
  x->setNumKeys(x->getNumKeys() + 1);
  z->setParent(x);
}

void btree::postOrderTraversal(node* subtree, int depth){
  // Print the vertical tree for debugging.
  // The number of times '-' illustrate the depth of the node within the tree.
  // Please check the provided test case.
  int nodesPresent = subtree->getNumKeys();
  if (subtree->getLeaf()){
    for (int j = nodesPresent - 1; j >= 0; j--){
      cout << string(depth + 1, '-') << subtree->getKeyAtIndex(j) << endl;
    }
  }
  else{
    for (int j = nodesPresent; j > 0; j--){
      btree::postOrderTraversal(subtree->getChildAtIndex(j), depth + 1);
      cout << string(depth + 1, '-') << subtree->getKeyAtIndex(j - 1) << endl;
    }
    btree::postOrderTraversal(subtree->getChildAtIndex(0), depth + 1);
  }
}

void btree::inOrderTraversal(node* subtree, int depth){
  // Print the vertical tree for debugging.
  // The number of times '-' illustrate the depth of the node within the tree.
  // Please check the provided test case.
  int nodesPresent = subtree->getNumKeys();
  if (subtree->getLeaf()){
    for (int j = 0; j <= nodesPresent-1; j++){
      cout << string(depth + 1, '-') << subtree->getKeyAtIndex(j) << endl;
    }
  }
  else{
    for (int j = 0; j <nodesPresent; j++){
      btree::inOrderTraversal(subtree->getChildAtIndex(j), depth + 1);
      cout << string(depth + 1, '-') << subtree->getKeyAtIndex(j) << endl;
    }
    btree::inOrderTraversal(subtree->getChildAtIndex(nodesPresent), depth + 1);
  }
}

