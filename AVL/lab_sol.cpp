#include <bits/stdc++.h>
using namespace std;

vector<int> ans;
int count4;

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
    void insert(int x);
    bool imbalanced(node *root);
    int max(int lheight,int rheight);
    node * R(node *root);
    node * L(node *root);
    void inorder(node* root);
    bool search(int x);
    node *giveroot();
    int updateHeights(node* root);
    int nodes_left_tree(node* root);
    int nodes_right_tree(node* root);
    int diff_inorder(node* root);
    avl()
    {
        root=NULL;
    }
};

int avl::diff_inorder(node* root)
{
    if(root!=NULL)
    {
        diff_inorder(root->left);
        // if(root->data!=k)
            count4++;
        // else
        //     return count;
        diff_inorder(root->right);
    }
    return count4;
}

int avl::nodes_left_tree(node* root)
{
    
    if(root->left==NULL)
        return 0;
    else
    {  
        count4=0;
        count4=diff_inorder(root->left);
        return count4;
    }
}

int avl::nodes_right_tree(node* root)
{
    
    if(root->right==NULL)
        return 0;
    else
    {  
        count4=0;
        count4=diff_inorder(root->right);
        return count4;
    }
}

struct Node 
{ 
    int data; 
    Node* left,  *right; 
};

Node* newNode(int data) 
{ 
    Node* node = new Node; 
    node->data = data; 
    node->left = node->right = NULL; 
    return (node); 
} 

Node* buildTreeUtil(vector<int> &arr, int start, int end)
                    
{ 
    if (start > end) 
        return NULL; 
  
   
    int mid = (start + end)/2; 
    Node *poof = newNode(arr[mid]);
    ans.push_back(arr[mid]); 
    poof->right = buildTreeUtil(arr, mid+1, end); 
    poof->left  = buildTreeUtil(arr, start, mid-1); 
    
    return poof; 
} 

int avl::updateHeights(node *n){
  int height = 0;
  if (n != NULL){
    int l_height = updateHeights(n->left);
    int r_height = updateHeights(n->right);
    int max_height;
    
    if(l_height>r_height)
        max_height=l_height;
    else
        max_height=r_height;

    height = 1 + max_height;
    n->lheight=l_height;
    n->rheight=r_height;
  }
  return height;
}


void avl::inorder(node *root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        updateHeights(root);

        cout<<"Node: "<<root->data<<" | "<<"Parent = ";
        if(root->parent!=NULL)
            cout<<root->parent->data<<" | ";
        else
            cout<<"NULL | ";
        if(root->left)
            cout<<"Left child = "<<root->left->data<<" | ";
        else 
            cout<<"Left child= NULL | ";
        cout<<"nodes in left subtree = "<<nodes_left_tree(root)<<" | ";
        if(root->right)
           cout<<"Right child = "<<root->right->data<<" | ";
        else 
            cout<<"Right child = NULL | ";
        cout<<"nodes in right subtree = "<<nodes_right_tree(root);
        cout<<endl;
        cout<<endl;

        inorder(root->right);
    }
}

void avl::insert(int x)
{
    //if(search(x)) return false;
    node *p=this->root;
    node *temp=new node(x);
    node *q=NULL;
    if(p==NULL)
    {
        this->root=temp;
        return ;
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
}

int main()
{
    vector<int> arr;
    int a;
    while(cin>>a)
    {
        arr.push_back(a);
    }

    sort(arr.begin(),arr.end());
    Node* poof=NULL;
    poof=buildTreeUtil(arr,0,arr.size()-1);

    cout<<"Sequence of insertions: ";
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<" ";
    cout<<endl;

/* ---------------------------------------------------------------------------------------------------*/

    cout<<"Tree structure"<<endl;
    cout<<endl;

    avl *tree=NULL;
    tree=new avl();
    for(int i=0;i<ans.size();i++)
        tree->insert(ans[i]);

    // printing the result of this tree's BFS will give you the correct sequence of insertions

    // tree->inorder(tree->root);
/* ----------------------------------------------------------------------------------------*/
}