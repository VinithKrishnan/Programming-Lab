
#include<bits/stdc++.h>
using namespace std;

struct Node
{
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};




int height(struct Node *N)
{
	if (N == NULL)
		return -1;
	return N->height;
}


int max(int a, int b)
{
	return (a > b)? a : b;
}


struct Node* newNode(int key)
{
	struct Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 0; 
	return(node);
}


struct Node *rightRotate(struct Node *y)
{
	struct Node *x = y->left;
	struct Node *z = x->right;

	
	x->right = y;
	y->left = z;

	
	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	
	return x;
}


struct Node *leftRotate(struct Node *x)
{
	struct Node *y = x->right;
	struct Node *z = y->left;

	
	y->left = x;
	x->right = z;


	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;


	return y;
}


int getBalance(struct Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}



struct Node* insert(struct Node* node, int key)
{

	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else 
		return node;


	node->height = 1 + max(height(node->left),
						height(node->right));

	
	int balance = getBalance(node);



	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}


	return node;
}


struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

struct Node* deleteNode(struct Node* root, int key)
{
   
 
    if (root == NULL)
        return root;
 
    
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
 
    
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
 
   
    else
    {
      
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;
 
            
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp; 
            delete temp;
        }
        else
        {
            
            struct Node* temp = minValueNode(root->right);
 
            
            root->key = temp->key;
 
    
            root->right = deleteNode(root->right, temp->key);
        }
    }
 
  
    if (root == NULL)
      return root;
 
   
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    
    int balance = getBalance(root);
 
    
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
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
        printf("%d ",head->key);
    }
    else if(level>1)  {
        printGivenLevel(head->left,level-1);
        printGivenLevel(head->right,level-1);
    }
}


void printTree(Node* head)    {
    int i,lvl=max_lvl(head,1);
    
    for(i=1;i<=lvl;i++)    {
     
        printGivenLevel(head,i);
        puts("");
    }
}

int main()
{
struct Node *root = NULL;
 
  /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);
 
    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
 
    printf("Tree structure of the constructed AVL "
           "tree is \n");
    printTree(root);
 
    root = deleteNode(root, 10);
 
    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */
 
    printf("\nTree structure after deletion of 10 \n");
    printTree(root);
 
    return 0;
}

