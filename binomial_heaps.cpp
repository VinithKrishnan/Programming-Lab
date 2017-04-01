#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct node {
    int key;
    node* child;        //Left most child pointer
    node* sibling;      //Adjacent right child pointer
    node* p;            //Parent pointer
    int degree;
};

class heap {
    public:
    list<node> root_list;
    node* head;
};

//Creating a new binomial heap
class heap MAKE_BINOMIAL_HEAP() {
    heap newHeap;
    newHeap.head = NULL;
    return newHeap;
}

//Finding the minimum key
node* BINOMIAL_HEAP_MINIMUM( heap H) {
    node* y = NULL;
    node* x = H.head;
    int min = INT_MAX;
    while(x!=NULL)  {
        if(x->key<min)  {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

//Linking two binomial trees of same degree
void BINOMIAL_LINK(node* y, node* z)    {
    y->sibling = z->child;
    y->p = z;
    z->child = y;
    z->degree += 1;
}

//Merging the two root lists
node* BINOMIAL_HEAP_MERGE(heap H1, heap H2)    {
    node* x = H1.head;
    node* y = H2.head;
    node* head = NULL;
    node* temp = NULL;
    node* prev_temp = NULL;
    
    while(x!=NULL and y!=NULL)   {
        if(x->degree<y->degree)   {
            if(head == NULL)    head = x;
            prev_temp = temp;
            temp = x;
            x = x->sibling;
        }
        else    {
            if(head == NULL)    head = y;
            prev_temp = temp;
            temp = y;
            y = y->sibling;
        }
        if(prev_temp != NULL)   prev_temp->sibling = temp;
    }
    
    if(x == NULL)   {
        while(y!=NULL)   {
            if(head == NULL)    head = y;
            prev_temp = temp;
            temp = y;
            y = y->sibling;
            if(prev_temp != NULL)   prev_temp->sibling = temp;
        }
    }
    else  {
        while(x!=NULL)   {
            if(head == NULL)    head = x;
            prev_temp = temp;
            temp = x;
            x = x->sibling;
            if(prev_temp != NULL)   prev_temp ->sibling = temp;
        }
    }
    return head;
}

//Union of two binomial heaps
class heap BINOMIAL_HEAP_UNION(heap H1,heap H2)    {
    heap H = MAKE_BINOMIAL_HEAP();
    H.head = BINOMIAL_HEAP_MERGE(H1, H2);
    if(H.head == NULL)   return H;
    node* prev_x = NULL;
    node* x = H.head;
    node* next_x = x->sibling;
    while(next_x!=NULL) {
        //case 1: degree of x != degree of next_x 
        if(x->degree != next_x->degree) {
            prev_x = x;
            x = next_x;
        }
        //case 2: degree of x == degree of next_x == degree of sibling_next_x 
        else if(next_x->sibling!=NULL and x->degree == next_x->sibling->degree)    {
            prev_x = x;
            x = next_x;
        }
        //case 3: degree of x == degree of next_x  
        else    {
            //case a: key[x]<key[next_x] 
            if(x->key<next_x->key)  {
                x->sibling = next_x->sibling;
                BINOMIAL_LINK(next_x,x);
            }
            //case b: key[x]>key[next_x]
            else   {
                //case 1: x is the root
                if(prev_x == NULL)    { H.head = next_x; }
                //case 2: x is not the root
                else    {   prev_x->sibling = next_x; }
                BINOMIAL_LINK(x,next_x);
                x = next_x;
            }
        }
        next_x = x-> sibling;
    }
    return H;
}

//Inserting a node
heap BINOMIAL_HEAP_INSERT(heap H, int key)  {
    heap H1 = MAKE_BINOMIAL_HEAP();
    node* x = (node*) new node();
    x->key = key;
    x->p = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1.head = x;
    heap H2 = BINOMIAL_HEAP_UNION(H,H1);
    return H2;
}

//Print Binomial heap roots 
void BINOMIAL_HEAP_PRINT_ROOTS(heap H)    {
    node* temp = H.head;
    cout<<endl;
    while(temp!=NULL)   {
        if(temp->sibling!=NULL) cout<<temp->key<<"->";
        else cout<<temp->key<<endl;
        temp = temp->sibling;
    }
    cout<<endl;
}   

int main(){
    heap H = MAKE_BINOMIAL_HEAP();
    H = BINOMIAL_HEAP_INSERT(H,4);
    H = BINOMIAL_HEAP_INSERT(H,2);
    H = BINOMIAL_HEAP_INSERT(H,6);
    H = BINOMIAL_HEAP_INSERT(H,1);
    H = BINOMIAL_HEAP_INSERT(H,10);
    H = BINOMIAL_HEAP_INSERT(H,5);
    H = BINOMIAL_HEAP_INSERT(H,7);
    H = BINOMIAL_HEAP_INSERT(H,9);
    BINOMIAL_HEAP_PRINT_ROOTS(H);
    //You can verify the binomial heap by traversing to each node manually since you know the structure!
    return 0;
}
