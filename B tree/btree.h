#ifndef BTREE_H
#define BTREE_H
#include"node.h"
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class btree{
  public:
    btree();
    tuple<node*, int> search(node* subtree, int key);
    void insert(btree*, int key);
    void insertNonFull(node* x, int key);
    void insertSoft(btree *,int key);
    void insertNonLeaf(node *x,node *p,int key);
    void insertSoftNbh(btree *,int key);
    void insertNonLeafNbh(node *x,node *p,int key);
    void splitChild(node* x, int i);
    void postOrderTraversal(node* x, int depth);
    void inOrderTraversal(node* x, int depth);
    node* root;
    int count;
};

#endif
