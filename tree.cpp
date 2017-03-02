#include<bits/stdc++.h>							
using namespace std;

typedef struct node{
	int data;
	struct node* left;
	struct node* right;
}Node;

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
}

void PreorderTraversal(Node* root){
	if(root == NULL) return;

	cout<<root->data<<" "; 
	PreorderTraversal(root->left);     
	PreorderTraversal(root->right);  
}

void InorderTraversal(Node* root){
	if(root == NULL) return;
	
	InorderTraversal(root->left);
	cout<<root->data<<" ";
	InorderTraversal(root->right);
}

void PostorderTraversal(Node* root){
	if(root == NULL) return;
	
	PostorderTraversal(root->left);
	PostorderTraversal(root->right);
	cout<<root->data<<" ";	
}

 int getHeight(Node* root){
          
          if(!root) {
              return -1;
          }
          int leftDepth = getHeight(root->left);
          int rightDepth = getHeight(root->right);
  
          return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;

      }

int main(){
	int i,n,h,d;
	Node* root=NULL;
	cout<<"enter the data(0 to stop) :";
//	cin>>n;
     d=1;
	for(i=0;d!=0;i++){
		
		cin>>d;
		if(d!=0) 
		root=insert(root,d);
	}
	
    h=	getHeight(root);
	cout<<"height of the tree is "<<h<<endl;
	cout<<"preorder:";
	PreorderTraversal(root);
	cout<<endl;
	cout<<"inorder:";
	InorderTraversal(root);
	cout<<endl;
	cout<<"postorder:";
	PostorderTraversal(root);
	cout<<endl;
	
}
