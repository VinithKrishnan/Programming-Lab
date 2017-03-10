#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
    int key;
    node* left;
    node* right;
    node* p;
    char colour;
};

node* nullNode =(node*) new node();
node* root;

int max(int i,int j){
    return ((i>j)?i:j);
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
        printf("(%d,%c)",head->key,head->colour);
    }
    else if(level>1)  {
        printGivenLevel(head->left,level-1);
        printGivenLevel(head->right,level-1);
    }
}

//print full tree
void printTree(node* head)    {
    int i,lvl=max_lvl(head,1);
    //if(head==NULL)  printf("asdfa");
    for(i=1;i<=lvl;i++)    {
        //printf("%d %d\n ",i,lvl);
        printGivenLevel(head,i);
        puts("");
    }
}


node* left_rotate(node* root,node* x)    {
    node* y = x->right;
    x->right = y->left;
    if(y->left!= nullNode)
        y->left->p = x;
    y->p = x->p;
    if(x == root)
        root = y;
    else if(x = x->p->right)
        x->p->right = y;
    else
        x->p->left = y;
    y->left = x;
    x->p = y;
    return root;
}

node* right_rotate(node* root,node* y)    {
    node* x = y->left;
    y->left = x->right;
    if(x->right!=nullNode)
        x->right->p = y;
    x->p = y->p;
    if(y == root)    
        root = x;
    else if(y == y->p->left )
        y->p->left = x;
    else
        y->p->right = x;
    x->right = y;
    y->p = x;
    return root;
}

node* insert_fixup(node* root,node* z)    {
    while(z->p->colour!='B')    {
        cout<<"Inside while loop and my key is: "<<z->key<<endl;
        //printTree(root);
        if(z->p == z->p->p->left)    {
            node* y = z->p->p->right;
            cout<<"Inside if loop!\n";
            if(y->colour == 'R') {
                cout<<"Uncle is red with key: "<<y->key<<" and my parent is the left child"<<endl;
                y->colour = 'B';
                z->p->colour = 'B';
                z->p->p->colour = 'R';
                z = z->p->p;
            }
            else    { 
                if (z == z->p->right)  {
                cout<<"My parent is the left child and I am the right child.\n";
                z = z->p;
                root = left_rotate(root,z);
                }
                cout<<"My parent is the left child and I am the left child\n";
                z->p->colour = 'B';
                z->p->p->colour = 'R';
                root = right_rotate(root,z->p->p);
            }
        }
        else    {
            cout<<"Inside else loop\n";
            node* y = z->p->p->left;
            if(y->colour == 'R') {
                cout<<"Uncle is red and my parent is the right child\n";
                y->colour = 'B';
                z->p->colour = 'B';
                z->p->p->colour = 'R';
                z = z->p->p;
            }
            else    { 
                cout<<"My parent is the right child and I am the right child.\n";
                if (z == z->p->left)  {
                z = z->p;
                root = right_rotate(root,z);
                }
                cout<<"My parent is the right child and I am the left child.\n";
                z->p->colour = 'B';
                z->p->p->colour = 'R';
                root = left_rotate(root,z->p->p);
            }
        }
    }
    root->colour = 'B';
    return root;
}

node* RB_Insert(node* root,node* z)   {
    node* y = nullNode;
    node* x = root;
    while(x!=nullNode)  {
        y = x;
        if(z->key<x->key)   
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == nullNode)   {   root = z;   }
    else if(z->key<y->key) {   y->left  = z;   }
    else                {   y->right = z;   }
    z->left = nullNode;
    z->right = nullNode;
    z->colour = 'R';
    root = insert_fixup(root,z);
    cout<<endl;
    printTree(root);
    cout<<endl;
    return root;
}

node* RB_Insert_num(node* root, int num)   {
    node* z =(node*) new node();
    z->key = num;
    node* y = nullNode;
    node* x = root;
    while(x!=nullNode)  {
        y = x;
        if(z->key<x->key)   
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == nullNode)   {   root = z;   }
    else if(z->key<y->key) {   y->left  = z;   }
    else                {   y->right = z;   }
    z->left = nullNode;
    z->right = nullNode;
    z->colour = 'R';
    root = insert_fixup(root,z);
    cout<<endl;
    printTree(root);
    cout<<endl;
    return root;
}

int main() {
    nullNode->colour = 'B';
    nullNode->left = NULL;
    nullNode->right = NULL;
    nullNode->p = NULL;
    nullNode->key = -1;
    node* root = nullNode;
    root->p = nullNode;
    
    /*for(int i=3;i<6;i++)    
    {
        node* newNode = (node*)new node();
        newNode->key = i;
        root = RB_Insert(root,newNode);
    }
    node* newNode = (node*) new node();
    newNode->key = 2;
    root = RB_Insert(root,newNode);
    printTree(root);
    */
    
    //Tree as in Cormen
    node* root1 = nullNode;
    root1->p = nullNode;
    root1 = RB_Insert_num(root1,11);
    root1 = RB_Insert_num(root1,2);
    root1 = RB_Insert_num(root1,14);
    root1 = RB_Insert_num(root1,1);
    root1 = RB_Insert_num(root1,7);
    root1 = RB_Insert_num(root1,15);
    root1 = RB_Insert_num(root1,5);
    root1 = RB_Insert_num(root1,8);
    //root1 = RB_Insert_num(root1,4);
    
    printTree(root1);
    //cout<<"Inserting 4"<<endl;
    //root1 = RB_Insert_num(root1,9);
    //printTree(root1);
 return 0;
}
