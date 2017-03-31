#include<bits/stdc++.h>
using namespace std;
 
struct node
{int data;
int rank;
struct node* left;
struct node* right;
};

struct node* CreateTree(int x)
{struct node* nod= new node();
nod->data=x;
nod->left=NULL;
nod->right=NULL;
nod->rank=0;
}

int Rank(struct node* n)
{
	if(n==NULL)
	return -1;
	else
	return n->rank;
}

struct node* meld(struct node* a,struct node* b)
{if(a==NULL)
return b;
if(b==NULL)
return a;
if(b->data>a->data)
swap(a,b);
a->right=meld(a->right,b);
if(Rank(a->right)>Rank(a->left))
swap(a->right,a->left);
if(a->right==NULL)
a->rank=0;
else
a->rank=1+Rank(a->right);
return a;
}

struct node* insert(struct node*a,int x)
{
	struct node*b = CreateTree(x);
	a=meld(a,b);
	return a;
}

struct node* deletemax(struct node* a)
{cout<<"\n Deleted item is"<<a->data;
a=meld(a->left,a->right);
return a;
}


int max_lvl(node* nd,int lvl){
    if(nd==NULL)    return 0;
    int ans = lvl;
    if(nd->left !=NULL)
        ans = max(ans,max_lvl(nd->left,lvl+1));
    if(nd->right !=NULL)
        ans = max(ans,max_lvl(nd->right,lvl+1));
    return ans;
}

void printGivenLevel(node* head,int level)  {

    if(head == NULL && level>=1)    {
        int i,m=pow(2,level-1);
        for(i=0;i<m;i++) {
            printf("X ");
        }
    }
    else if(level == 1 && head!=NULL)  {
        printf("%d ",head->data);
    }
    else if(level>1)  {
        printGivenLevel(head->left,level-1);
        printGivenLevel(head->right,level-1);
    }
}


void printTree(node* head)    {
    int i,lvl=max_lvl(head,1);
    
    for(i=1;i<=lvl;i++)    {
     
        printGivenLevel(head,i);
        puts("");
    }
}

int main()
{
struct node *root = NULL;
 
 
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 2);
   
 
 
    printf(" \n");
    printTree(root);
 
 
   
   struct node *Root = NULL;
   Root=insert(Root, 10);
   Root=insert(Root, 1);
   Root=insert(Root, 4);
 cout<<"\n";
   printTree(Root);
   
   
   struct node*mer=meld(root,Root);
   cout<<"\n";
   printTree(mer);
   
   struct node*del=deletemax(mer);
   cout<<"\n";
   printTree(del);
   
   
   
 
    return 0;
}

