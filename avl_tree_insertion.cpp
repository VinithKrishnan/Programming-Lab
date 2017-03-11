#include<bits/stdc++.h>
using namespace std;

typedef struct node{
	int data;
	int height;
	struct node* left;
	struct node* right;
}Node;

int height(Node* root)
{
    if (root == NULL)
        return 0;
    else 
    return root->height;
}
 

int max(int a, int b)
{
    return (a > b)? a : b;
}

int max_lvl(Node* nd,int lvl){
    if(nd==NULL)    return 0;
    int ans = lvl;
    if(nd->left !=NULL)
        ans = max(ans,max_lvl(nd->left,lvl+1));
    if(nd->right !=NULL)
        ans = max(ans,max_lvl(nd->right,lvl+1));
    return ans;
}

void printGivenLevel(Node* head,int level)  {

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

//print full tree
void printTree(Node* head)    {
    int i,lvl=max_lvl(head,1);
    //if(head==NULL)  printf("asdfa");
    for(i=1;i<=lvl;i++)    {
        //printf("%d %d\n ",i,lvl);
        printGivenLevel(head,i);
        puts("");
    }
}

int getHeight(Node* root){

          if(!root) {
              return -1;
          }
          int leftDepth = getHeight(root->left);
          int rightDepth = getHeight(root->right);

          return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;

      }

 Node* rightRotate( Node* x)
{
     Node* y = x->left;
     Node* T2 = y->right;
 
    
    y->right = x;
    x->left = T2;
 
   
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 	
 	//x->height= getHeight(x);
 	//y->height= getHeight(y);
    
    return y;
}

 Node* leftRotate( Node* x)
{
     Node* y = x->right;
     Node* T2 = y->left;
 
    
    y->left = x;
    x->right = T2;
 
    
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
  //   x->height= getHeight(x);
    // y->height= getHeight(y);
    // Return new root
    return y;
}

int BalanceNumber(Node* root){
	if(root==NULL) return 0;
	return height(root->left) - height(root->right);
}

Node* insert(Node* root, int d){
	if(root==NULL){
		root=new Node;
		root->data=d;
		root->left=NULL;
		root->right=NULL;
	}
	else if(d<root->data){
		root->left=insert(root->left,d);
	}
	else{ 
		root->right=insert(root->right,d);
	}
	root->height = 1 + max(height(root->left),height(root->right));
	//root->height= getHeight(root);
	int balance=BalanceNumber(root);
	
	if (balance > 1 && d < root->left->data)
        return rightRotate(root);
 
     
    if (balance < -1 && d >root->right->data)
        return leftRotate(root);
 
    if (balance > 1 && d > root->left->data)
    {
     	root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
  
    if (balance < -1 && d < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    
    return root;
}
	


void PreorderTraversal(Node* root){
	if(root == NULL) return;

	cout<<root->data<<" ";
	PreorderTraversal(root->left);
	PreorderTraversal(root->right);
}


int main(){
	int i,n,h,d;
	Node* root=NULL;
	cout<<"enter the data(0 to stop) :";

     d=1;
	for(i=0;d!=0;i++){
		
		cin>>d;
		if(d!=0) 
		root=insert(root,d);
	}
    
	printTree(root);
    cout<<endl;
	
}
