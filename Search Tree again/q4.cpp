#include <iostream>
#include <stdlib.h>
using namespace std;
#define N 100

typedef struct _node
{
	struct _node* next;
	struct _node* parent;
	string s;
	string file[N];
	int index;
}node;

node* new_fol(node* p,string a)
{
	node* new1=(node*)malloc(sizeof(struct _node));
	p->next=new1;
	new1->s=a;
	new1->parent=p;
	new1->next=NULL;
	new1->index=0;
	return new1;
}

node* back(node* p)
{
	node* q=(node*)malloc(sizeof(struct _node));
	q=p->parent;
	if(q==NULL)
		return NULL;
	else
	{
		q->next=NULL;
		free(p);
		return q;
	}
}

void make_file(node* p,string a)
{
	p->file[(p->index)++]=a;
	return ;
}

string delete_file(node* p)
{
	for(int j=0;j<p->index;j++)
	{
		if(p->file[j]!="")
		{
			string s=p->file[j];
			p->file[j]="";
			return s;
		}
	}

	return "-1";
}

int main()
{
	node* curr_folder=(node*)malloc(sizeof(struct _node));
	curr_folder->next=NULL;
	curr_folder->s="root";
	curr_folder->parent=NULL;

	string function="";

	while(function!="-1")
	{
		cin>>function;

		if(function=="NEW")
		{
			string a;
			cin>>a;
			cout<<"Made folder "<<a<<" in "<<curr_folder->s;
			curr_folder=new_fol(curr_folder,a);
		}

		else if(function=="BACK")
		{
			string blah=curr_folder->s;
			node* q=curr_folder;
			node* p;
			p=back(curr_folder);
			if(p==NULL)
			{
				cout<<"Cannot return from "<<blah;
				curr_folder=q;
			}
			else
			{
				cout<<"Back from "<<blah;
				curr_folder=p;
			}
		}

		else if(function=="CREATE")
		{
			string a;
			cin>>a;
			make_file(curr_folder,a);
			cout<<"Made file "<<a<<" in "<<curr_folder->s;
		}

		else if(function=="DELETE")
		{
			string b=delete_file(curr_folder);

			if(b=="-1") 
				cout<<"Cannot delete from "<<curr_folder->s;
			else
				cout<<"Deleted file "<<b<<" from "<<curr_folder->s;
		}

	}

}