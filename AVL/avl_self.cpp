# include <iostream>
# include <cstdlib>
using namespace std;

class node
{
public:
	int data;
	node *parent;
	node *left;
	node *right;
	int lheight;
	int rheight;
	node(int x)
	{
		data=x;
		parent=left=right=NULL;
		lheight=rheight=0;
	}
};
class avl
{
public:
	node *root;
	bool insert(int x);
	bool imbalanced(node *root);
	int max(int lheight,int rheight);
	node * R(node *root);
	node * L(node *root);
	//void inorder();
	bool search(int x);
	node *giveroot();
	avl()
	{
		root=NULL;
	}
};
node *avl::giveroot()
{
	return this->root;
}
bool avl::imbalanced(node *root)
{
	if(root->lheight-root->rheight==1||root->lheight-root->rheight==0||root->lheight-root->rheight==-1) 
		return false;
	return true;
}
int avl::max(int lheight,int rheight)
{
	if(lheight>rheight) 
		return lheight;
	else 
		return rheight;
}
node * avl::R(node *root)
{
	node *a=root;
	node *b=root->left;
	a->left=b->right;
	a->lheight=b->rheight;
	if(b->right!=NULL)
		b->right->parent=a;
	b->right=a;
	(b->rheight)++;
	b->parent=a->parent;
	if(a->parent!=NULL)
	{
		if(a->parent->left==a) a->parent->left=b;
		else a->parent->right=b;
	}
	a->parent=b;
	return b;
}

node *avl::L(node *root)
{
	node *a=root;
	node *b=root->right;
	a->right=b->left;
	a->rheight=b->lheight;
	if(b->left!=NULL)b->left->parent=a;
	b->left=a;
	(b->lheight)++;
	b->parent=a->parent;
	if(a->parent!=NULL)
	{
		if(a->parent->left==a) a->parent->left=b;
		else a->parent->right=b;
	}
	a->parent=b;
	return b;
}
void inorder(node *root)
{
	if(root!=NULL)
	{
		inorder(root->left);

		cout<<root->data<<" ";
		if(root->left)
			cout<<root->left->data<<" ";
		else 
			cout<<"- ";
		if(root->right)
		   cout<<root->right->data<<" ";
		else 
			cout<<"- ";
		cout<<endl;

		inorder(root->right);
	}
}
void postorder(node *root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->data<<" ";
	}
}
void preorder(node *root)
{
	if(root!=NULL)
	{
		cout<<root->data<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}
bool avl::insert(int x)
{
	//if(search(x)) return false;
	node *p=this->root;
	node *temp=new node(x);
	node *q=NULL;
	if(p==NULL)
	{
		this->root=temp;
		return true;
	}
	while(p!=NULL)
	{
		q=p;
		if(p->data>x)
		{
			p=p->left;
		}
		else p=p->right;
	}
	if(q->data>x) 
	{
		q->left=temp;
		temp->parent=q;
		q->lheight++;
	}
	else
	{
		q->right=temp;
		temp->parent=q;
		q->rheight++;
	}
	while(!imbalanced(q))
	{
		if(q->parent==NULL) 
			return true;
		q=q->parent;
		if(q->left==NULL)
		   q->lheight=0;
		else 
			q->lheight=max(q->left->lheight,q->left->rheight)+1;
		if(q->right==NULL)
		   q->rheight=0;
		else 
			q->rheight=max(q->right->lheight,q->right->rheight)+1;
	}
	if(q->lheight-q->rheight>1)
	{
		if(q->left->lheight>q->left->rheight)
		{
			if(q==root)
			{
				root=R(q);
				q=root;
			}
			else q=R(q);
		}
		else
		{
			q->left=L(q->left);
			if(q==root)
			{
				root=R(q);
				q=root;
			}
			else q=R(q);
		}
	}
	else
	{
		if(q->right->rheight>q->right->lheight)
		{
			if(q==root)
			{
				root=L(q);
				q=root;
			}
			else q=L(q);
		}
		else
		{
			q->right=R(q->right);
			if(q==root)
			{
				root=L(q);
				q=root;
			}
			else q=L(q);
		}		
	}
	return true;
}
bool avl::search(int x)
{
	node *p=this->root;
	while(p!=NULL)
	{
		if(p->data==x) return true;
		if(p->data>x) p=p->left;
		else p=p->right;
	}
	return false;
}
int main()
{
	avl *tree=NULL;
	int key;
	int choice;
	bool result;

	do
	{
	    cout << "1. Create new tree" << endl;
	    cout << "2. Add new key to the tree" << endl;
	    cout << "3. Search a key in the tree" << endl;
	    cout << "5. Inorder traversal of the tree" << endl;
	    cout << "Any other choice to exit" << endl;
	    cout << "Enter your choice:";
	    cin >> choice;
	    cout << "You entered " << choice << endl;
     
    	switch(choice)
    	{
	      	case 1:
		        if(tree != NULL)
		        {
		          delete tree;
		        }
		        tree = new avl();
		        break;
	 
	      	case 2:
		        if(tree == NULL)
		        {
		          cout << "Create a new tree first" << endl;
		          break;
		        }
		        cout << "Enter key to add ";
		        cin >> key;
		        //n1 = new node(key);
		       	result = tree->insert(key);
		        if(result == false)
		        {
		          cout << "Could not insert key" << endl;
		        }
		        else
		        {
		          cout << "Inserted key " << key << endl;
		        }
		        break;
	 
	        case 3:
		        if(tree == NULL)
		        {
		          cout << "Create a new tree first" << endl;
		          break;
		        }
		        cout << "Enter key to search";
		        cin >> key;
		        result=tree->search(key);
		        if(result==false)
		        {
		          cout << "Key " << key <<" not found" << endl;
		        }else{
		          cout << "Key " << key << "found" << endl;
		        }
		        break;
	 
	      	/*case 4:
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
	 		*/
	      	case 5:
		        if(tree == NULL)
		        {
		          cout << "Create a new tree first" << endl;
		          break;
		        }
		        inorder(tree->root);
		        break;
	 
		    default:
	        	return(0);
   		}
   	}
	while(true);
	return 0;
}