#include<bits/stdc++.h>
using namespace std;

typedef struct node{
	int data;
	struct node* left;
	struct node* right;
}Node;

int max(int i,int j){
    return ((i>j)?i:j);
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
	return root;
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
    printTree(root);
    cout<<endl;
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
