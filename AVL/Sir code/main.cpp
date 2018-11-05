#include <iostream>
#include "node.h"
#include "avl.h"

using namespace std;

int main()
{
    avl* tree = NULL;
    int key;
    int choice;
    node* n1 = NULL;
    bool result;

    do{
    	  cout << "1. Create new tree" << endl;
      	  cout << "2. Add new key to the tree" << endl;
    	  cout << "3. Search a key in the tree" << endl;
      	  cout << "4. Delete a key from the tree" << endl;
      	  cout << "5. Inorder traversal of the tree" << endl;
      	  cout << "Any other choice to exit" << endl;
      	  cout << "Enter your choice:";
      	  cin >> choice;
      	  cout << "You entered " << choice << endl;
        
        switch(choice){
          case 1:
            if(tree != NULL){
              delete tree;
            }
            tree = new avl();
            break;

          case 2:
            if(tree == NULL){
              cout << "Create a new tree first" << endl;
              break;
            }
            cout << "Enter key to add ";
            cin >> key;
            n1 = new node(key);
            result = tree->treeInsertNode(n1);
            if(result == false){
              cout << "Could not insert key" << endl;
            }else{
              cout << "Inserted key " << key << endl;
            }
            break;

          case 3:
            if(tree == NULL){
              cout << "Create a new tree first" << endl;
              break;
            }
            cout << "Enter key to search";
            cin >> key;
            n1 = tree->treeSearchKey(key);
            if(n1 == NULL){
              cout << "Key " << key <<" not found." << endl;
            }else{
              cout << "Key " << key << "found" << endl;
            }
            break;

          case 4:
            if(tree == NULL){
              cout << "Create a new tree first" << endl;
              break;
            }
            cout << "Enter key to delete";
            cin >> key;
            n1 = tree->treeSearchKey(key);
            if(n1 == NULL){
              cout << "Key " << key << " not found." << endl;
            }else{
              tree->deleteNode(n1);
            }
            break;

          case 5:
            if(tree == NULL){
              cout << "Create a new tree first" << endl;
              break;
            }
            tree->treeInorderTraversal();
            break;

          default:
            return(0);
        }
      }
      while(true);
        return 0;
}

