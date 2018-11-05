#ifndef NODE_H
#define NODE_H
#include<iostream>

using namespace std;

class node
{
    public:
        node(int keyValue);
        virtual ~node();
        node* getParent();
        bool setParent(node* parentNode);

        node* getLeft();
        bool setLeft(node* leftNode);

        node* getRight();
        bool setRight(node* rightNode);

        int getKey();
        bool setLHeight(int height);
        bool setRHeight(int height);
        int getLHeight();
        int getRHeight();
        void setValue(int a);

    protected:
    private:
        node* parent;
        node* left;
        node* right;
        int lheight;
        int rheight;

        int key;
};

#endif // NODE_H

