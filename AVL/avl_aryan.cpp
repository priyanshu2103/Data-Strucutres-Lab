#include "avl.h"
#include <algorithm>
using namespace std;

avl::avl()
{
    head=NULL;
}

avl::~avl()
{
    //dtor
}

void avl::inorderTraversal(node* tempNode){
  if(tempNode == NULL){
    return;
  }
  else{
    // Explore the left subtree.
    inorderTraversal(tempNode->getLeft());

    // Print the current node as well as its left and right nodes.
    cout << tempNode->getKey();
    if (tempNode->getLeft()){
      cout << "\t(" << tempNode->getLeft()->getKey() << ")";
    }
    else{
      cout << "\t(-)";
    }
    if (tempNode->getRight()){
      cout << "\t(" << tempNode->getRight()->getKey() << ")";
    }
    else{
      cout << "\t(-)";
    }
    cout << endl;

    // Explore the right subtree.
    inorderTraversal(tempNode->getRight());
  return;
  }
}

bool avl::treeInsertNode(node* newNode){
  // If tree is empty, return null.
  if(head == NULL){
    head = newNode;
    return true;
  }
  else{
    if(insertNode(newNode, head) >= 0){
      return true;
    }
    else{
      return false;
    }
  }
}

int avl::insertNode(node* newNode, node* headNode){
  node *parent;
  node *temp;
  // Search for node, it it already exists return false.
  temp = searchKey(newNode->getKey(), headNode);
  if (temp != NULL){
    cout << "Cannot insert duplicates for " << newNode->getKey() << endl;
    return false;
  }
  temp = headNode;
  // Search for the correct position where the node can be inserted.
  while(true){
    parent = temp;
    bool goLeft = temp->getKey() > newNode->getKey();
    temp = goLeft ? temp->getLeft() : temp->getRight();
    if (temp == NULL){
      if (goLeft){
        // Update both new node to parent and parent to new node pointers.
        parent->setLeft(newNode);
        newNode->setParent(parent);
      }
      else{
        // Update both new node to parent and parent to new node pointers.
        parent->setRight(newNode);
        newNode->setParent(parent);
      }
      // Check for height imbalance.
      rebalance(parent);
      break;
    }
  }
  return true;
}

void avl::rebalance(node* n){
  // Update the height of node n as well as all height of its descendants.
  updateHeights(n);

  // Compute the balance factor.
  int balance_factor = n->getRHeight() - n->getLHeight();

  // The four rotation cases.
  if (balance_factor == -2){
    if (n->getLeft()->getLHeight() >= n->getLeft()->getRHeight()){
      n = rotateRight(n);
      cout << "Rotate Right" << endl;
    }
    else{
      n = rotateLeftThenRight(n);
      cout << "Rotate Left Then Right" << endl;
    }
  }
  if (balance_factor == 2){
    if (n->getRight()->getRHeight() >= n->getRight()->getLHeight()){
      n = rotateLeft(n);
      cout << "Rotate Left" << endl;
    }
    else{
      cout << "Rotate Right Then Left" << endl;
      n = rotateRightThenLeft(n);
    }
  }

  // Recursively call rebalance till we reach the head node.
  if (n->getParent() != NULL){
    rebalance(n->getParent());
  }
  else{
    head = n;
  }
}


int avl::updateHeights(node *n){
  // Recursively update the height of node n as well as all height of its descendants.
  int height = 0;
  if (n != NULL){
    int l_height = updateHeights(n->getLeft());
    int r_height = updateHeights(n->getRight());
    int max_height = max(l_height, r_height);
    height = 1 + max_height;
    n->setLHeight(l_height);
    n->setRHeight(r_height);
  }
  return height;
}

node* findMinNode(node* tempHead){
  node* current = tempHead;
  // Loop down to find the left most node.
  while (current->getLeft() != NULL){
    current = current->getLeft();
  }
  return current;
}


node* avl::deleteNode(node* victimNode){

  // Temp. store the parent pointer of the victim node.
  node* parent = victimNode->getParent();

  // If node that two child.
  if (victimNode->getLeft() && victimNode->getRight()){
    // Find minimum from the right subtree.
    node* temp = findMinNode(victimNode->getRight());
    // Add a new node in place of victimNode with content of temp node
    // If a node was allowed to update its key, this case could be written in two lines of code.
    node* newNode = new node(temp->getKey());
    newNode->setParent(parent);
    newNode->setLeft(victimNode->getLeft());
    victimNode->getLeft()->setParent(newNode);
    newNode->setRight(victimNode->getRight());
    victimNode->getRight()->setParent(newNode);
    if (parent){
      if (parent->getLeft() == victimNode){
        parent->setLeft(newNode);
      }
      if (parent->getRight() == victimNode){
        parent->setRight(newNode);
      }
    }
    else{
      head = newNode;
    }
    delete victimNode;
    // Delete temp node: Case reduced to deletion of a node with one or no child.
    deleteNode(temp);

  }
  else{
    // If node that one child.
    if (victimNode->getLeft() || victimNode->getRight()){
      // If node has left child.
      if (victimNode->getRight() == NULL){
        victimNode->getLeft()->setParent(parent);
        if (parent == NULL){
          head = victimNode->getLeft();
        }
        else{
          parent->setLeft(victimNode->getLeft());
        }
        rebalance(victimNode->getLeft());
      }
      else{
        // If node has right child.
        victimNode->getRight()->setParent(parent);
        if (parent == NULL){
          head = victimNode->getRight();
        }
        else{
          parent->setRight(victimNode->getRight());
        }
        rebalance(victimNode->getRight());
      }
    }
    else{
      // The node has no children.
      if (parent == NULL){
        head = NULL;
      }
      else{
        if (parent->getLeft() == victimNode){
          parent->setLeft(NULL);
        }
        else{
          parent->setRight(NULL);
        }
        delete victimNode;
        rebalance(parent);
      }
    }
  }
  return NULL;
}


node* avl::rotateRightThenLeft(node* n){
  n->setRight(rotateRight(n->getRight()));
  return rotateLeft(n);

}

node* avl::rotateLeftThenRight(node* n){
  n->setLeft(rotateLeft(n->getLeft()));
  return rotateRight(n);
}

node* avl::rotateRight(node* j){
  /*
   *          j
   *         / \
   *        /   \
   *       k     Z(h)
   *      / \
   *     /   \
   *    /     \
   *   /       \
   *  X(h+1)    Y(h)
   *    Imbalance at j, perform a right rotation.
   *
   *         k
   *        / \
   *       /   \
   *      /     \
   *    X(h+1)  j
   *           / \
   *          /   \
   *         /     \
   *        /       \
   *       /         \
   *      Y(h)       Z(h)
   *
   *
   */
    if(j==NULL)
      return j;
    node* temp1 = j;
    node* temp2= j->getLeft();
    node* parent = j->getParent();
    if(temp2==NULL)
      return j;
    temp2->setParent(parent);
    if(parent!=NULL)
    {
      if(parent->getLeft()==temp1)
          parent->setLeft(temp2);
      else
          parent->setRight(temp2);
    }
    else
      head=temp2;
    temp1->setLeft(temp2->getRight());
    if (temp2->getRight())
    {
      temp2->getRight()->setParent(temp1);
    }
    temp1->setParent(temp2);
    temp2->setRight(temp1);
    updateHeights(head); 

    return temp2;  

}

node* avl::rotateLeft(node* j){
    if(j==NULL)
      return j;
    node* temp1 = j;
    node* temp2= j->getRight();
    node* parent = j->getParent();
    if(temp2==NULL)
      return j;
    temp2->setParent(parent);
    if(parent!=NULL)
    {
      if(parent->getLeft()==temp1)
        parent->setLeft(temp2);
      else
        parent->setRight(temp2);
    }
    else
      head=temp2;
    
    temp1->setRight(temp2->getLeft());
    if (temp2->getLeft())
    {
      temp2->getLeft()->setParent(temp1);
    }
    temp1->setParent(temp2);
    temp2->setLeft(temp1);
    updateHeights(head);
    return temp2;

}

node* avl::searchKey(int keyValue, node* headNode){
  // If subtree is empty.
  if(headNode == NULL){
    return NULL;
  }

  if(headNode->getKey() == keyValue){
    return headNode;
  }

  if(headNode->getKey() < keyValue){
    return searchKey(keyValue, headNode->getRight());
  }
  else{
    return searchKey(keyValue, headNode->getLeft());
  }
}

node* avl::treeSearchKey(int keyValue){
  return(searchKey(keyValue, head));
}

void avl::treeInorderTraversal(){
  cout << "Node\tL Child\tR Child" << endl;
  inorderTraversal(head);
}



