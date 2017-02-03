#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

typedef struct node{
    int coeff;
    int exp;
    struct node* next;
}Node;
bool shiftAndCut(Node* ptr);
void reverseList(Node* head,Node*& listHead);
Node* getNode(int coeff,int exp);
Node* makePoly(Node* head,int coeff,int exp);
void printPoly(Node* head);
Node* polyAdd(Node* head1,Node* head2);
Node* polySub(Node* head1,Node* head2);
Node* polyMultiply(Node* head1,Node* head2);
void printPolyAsDigit(Node* head);
int cmp(Node* head1,Node* head2);
int getLength(Node* head);
Node* getNumAsList();
void printPolyAsDigitInOrder(Node* head);
void convertPolyToDigit(Node* head);
int checkEqual(Node* head1,Node* head2);

Node* getNode(int coeff,int exp)    {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->exp = exp;
    newNode->coeff = coeff;
    newNode->next = NULL;
    return newNode;
}

//LSB is stored first followed by other digits
Node* makePoly(Node* head,int coeff,int exp)    {
    Node* newNode = getNode(coeff,exp);
    Node* s = head;
    if(s == NULL)    {
        head = newNode;
    }
    else if(s->exp>exp)  {
        newNode->next = s;
        head = newNode;
    }
    else if(s->exp<exp) {
        while(s->next!=NULL && s->next->exp<exp)
            s = s->next;
        if(s->next!=NULL)   {
            if(s->next->exp == exp)
                s->next->coeff += coeff;
            else    {
                newNode->next = s->next;
                s->next = newNode;
            }
        }
        else    {
            s->next = newNode;
        }
    }
    else    {
        s->coeff += coeff;
    }
    return head;
}

Node* makePoly1(Node*& head,int coeff,int exp)    {
    Node* newNode = getNode(coeff,exp);
    Node* s = head;
    if(s == NULL)    {
        head = newNode;
    }
    else if(s->exp<exp)  {
        newNode->next = s;
        head = newNode;
    }
    else if(s->exp>exp) {
        while(s->next!=NULL && s->next->exp>exp)
            s = s->next;
        if(s->next!=NULL)   {
            if(s->next->exp == exp)
                s->next->coeff += coeff;
            else    {
                newNode->next = s->next;
                s->next = newNode;
            }
        }
        else    {
            s->next = newNode;
        }
    }
    else    {
        s->coeff += coeff;
    }
    return head;
}


void printPoly(Node* head)   {
    if(head!=NULL)
        cout<<head->coeff<<" ";
    //cout<<" + "<<(head->coeff)<<"x^"<<(head->exp);
    if(head->next!=NULL)
        printPoly(head->next);

}

Node* polyAdd(Node* head1, Node* head2)    {
    Node* s = head1;
    Node* head = NULL;
    while(s->next!=NULL)    {
        head = makePoly(head,s->coeff,s->exp);
        s = s->next;
    }
    head = makePoly(head,s->coeff,s->exp);
    s = head2;
    while(s->next!=NULL)    {
        head = makePoly(head,s->coeff,s->exp);
        s = s->next;
    }
    head = makePoly(head,s->coeff,s->exp);

    convertPolyToDigit(head);
    return head;
}

Node* polySub(Node* head1,Node* head2)  {
    Node* s1;
    Node* s2;
    Node* head = NULL;
    int len3,carry = 0,place = 0;
    if(cmp(head1,head2)>=0)  {
        s1 = head1;
        s2 = head2;
    }
    else {
        s1 = head2;
        s2 = head1;
    }
    while(s1!=NULL and s2!=NULL)    {
        if(s1->coeff+carry>=s2->coeff)  {
           head = makePoly(head,s1->coeff+carry-s2->coeff,place++);
            carry = 0;
        }
        else    {
            head = makePoly(head,s1->coeff+carry-s2->coeff+10,place++);
            carry = -1;
            /*Node* temp = s1->next;
            while(temp!=NULL and temp->coeff == 0)  {
                temp->coeff = 9;
                temp = temp->next;
            }
            temp->coeff -= 1;
            */
        }
        s1 = s1->next;
        s2 = s2->next;
    }


    while(s1!=NULL) {
        //head = makePoly(head,s1->coeff,place++);
        //s1 = s1->next;
        if(s1->coeff+carry>=0)  {
           head = makePoly(head,s1->coeff+carry,place++);
            carry = 0;
        }
        else    {
            head = makePoly(head,s1->coeff+carry+10,place++);
            carry = -1;
        }
        s1 = s1->next;

    }
    return head;

}

//Ensure no leading zeros
int getLength(Node* head)  {
    int most = 0;
    while(head!=NULL)   {
            if(head->exp+1 >most)
            most = head->exp + 1;
            head = head->next;
    }
        return most;
}

/* Returns  1)List is NULL -> 0
          2) Num1 <= Num2 -> 1
          3) Num1 > Num2 -> -1
*/

int cmp(Node* head1,Node* head2)  {
    Node* s1 = head1;
    Node* s2 = head2;

    int len_s1 = 0,len_s2 = 0;
    len_s1 = getLength(s1);
    len_s2 = getLength(s2);
    //cout<<"\n"<<len_s1<<" "<<len_s1;
    if(len_s1<len_s2)
            return -1;
    else if(len_s1>len_s2)
            return 1;
    else
    {
    return checkEqual(head1,head2);
    }
}

int checkEqual(Node* head1,Node* head2) {
        if(head1==NULL or head2==NULL)          return 0;
        int temp = checkEqual(head1->next,head2->next);
        if(temp)                                return temp;
        if(head1->coeff<head2->coeff)           return -1;
        else if(head1->coeff>head2->coeff)      return 1;
        else                                    return 0;
}


Node* polyMultiply(Node* head1,Node* head2) {
    Node* s1 = head1;
    Node* s2 = head2;
    Node* head = NULL;
    while(s1!=NULL)   {
        while(s2!=NULL) {
            head = makePoly(head,s1->coeff*s2->coeff,s1->exp+s2->exp);
            s2 = s2->next;
        }
        s2 = head2;
        s1 = s1->next;
    }
    convertPolyToDigit(head);
    return head;
}



void convertPolyToDigit(Node* head) {
    Node* s = head;
    int carry = 0;
    while(s!=NULL){
        int val = s->coeff+carry;
        s->coeff = val%10;
        carry = val/10;
        if(s->next==NULL and carry){
            s->next = getNode(carry,s->exp+1);
            carry=0;
        }
        s = s->next;
    }
}


void printPolyAsDigit(Node* head)   {
    if(head->next!=NULL)
        printPolyAsDigit(head->next);
    cout<<head->coeff<<'('<<head->exp<<')';
}

//A function to accept a number as string and then convert it into a linkedList with each coefficient representing a digit
Node* getNumAsList()  {
    Node* head = NULL;
    int i,j;
    string n;
    cout<<"Enter a number\n";
    cin>>n;
    for(i=0;i<n.size();++i) {
        head = makePoly(head,n[i]-'0',n.size()-i-1);
    }
    return head;
}

void reverseList(Node* head, Node*& listHead)    {
    if(head->next == NULL)  {
        listHead = head;
        return;
    }
    reverseList(head->next,listHead);
    head->next->next = head;
    head->next = NULL;
}

Node* polyDivide()  {
    Node* head1 = NULL;
    Node* head2 = NULL;
    Node* quo = NULL;
    Node* rem = NULL;
    Node* pro = NULL;
    int i,j;
    string n;
    cout<<"Enter a number\n";
    cin>>n;
    for(i=0;i<n.size();++i) {
        head1 = makePoly1(head1,n[i]-'0',n.size()-i-1);
    }
    cout<<"Enter a number\n";
    cin>>n;
    for(i=0;i<n.size();++i) {
        head2 = makePoly1(head2,n[i]-'0',n.size()-i-1);
    }

    int l1 = getLength(head1);
    int l2 = getLength(head2);
    int place = 0;
    if(l1<l2)   {
        quo = makePoly(quo,0,place++);
        return quo;
    }
    ///////////////////////////////////////////
    int rem_len = l2-1;
    while(rem_len>=0)    {
        rem = makePoly(rem,head1->coeff,rem_len);
        head1 = head1->next;
        rem_len--;
    }
    cout<<"REMAINDER 1 : ";
    printPolyAsDigit(rem);
    j = 1;
    while(true) {
        pro = polyMultiply(head2,makePoly(NULL,j,0));
        if(cmp(rem,pro)<0)
            break;
        else
            j++;
    }
    cout<<"\nPRO greater ";
    printPolyAsDigit(pro);
    quo = makePoly(quo,j-1,place++);
    cout<<"\n QUO "<<j-1;
    pro = polyMultiply(head2,makePoly(NULL,j-1,0));
    cout<<"\nACTUAL PRO ";
    printPolyAsDigit(pro);
    //////////////////////////////////////////////////
    rem = polySub(rem,pro);
    cout<<"\nREM now : ";
    printPolyAsDigit(rem);
    cout<<endl;
    shiftAndCut(rem);
    printPolyAsDigit(rem);
    cout<<endl;
    if(head1==NULL) cout<<"NULL HEAD\n";
    ///////////////////////////
    while(head1!=NULL)   {
    rem_len = 0;
    Node* temp = rem;
    while(temp !=NULL)  {
        temp->exp += 1;
        temp = temp->next;
        rem_len++;
    }
    rem = makePoly(rem,head1->coeff,0);
    cout<<"\nNEW REMAINDER AFTER DOWN :";
    printPolyAsDigit(rem);
    cout<<endl;
    shiftAndCut(rem);
    int j = 1;
    while(true) {
        pro = polyMultiply(head2,makePoly(NULL,j,0));
        printPolyAsDigit(rem);
        cout<<" ";
        printPolyAsDigit(pro);
        cout<<" "<<cmp(rem,pro)<<endl;
        if(cmp(rem,pro)<=0)
            break;
        else
            j++;
    }
    cout<<"J IS "<<j-1<<endl;
    quo = makePoly(quo,j-1,place++);
    cout<<"got quo"<<endl;
    printPolyAsDigit(quo);
    //shiftAndCut(quo);
    pro = polyMultiply(head2,makePoly(NULL,j-1,0));
    cout<<"\nPRO IS ";
    shiftAndCut(pro);
    printPolyAsDigit(pro);
    cout<<endl;
    printPolyAsDigit(rem);
    cout<<endl<<" quotient ";
    printPolyAsDigitInOrder(quo);
    cout<<endl;
    rem = polySub(rem,pro);
    printPolyAsDigit(rem);
    cout<<endl;
    head1 = head1->next;
    shiftAndCut(rem);
    }
    cout<<"REMAINDER: ";
    printPolyAsDigit(rem);
    cout<<endl<<"quotienT: ";
    printPolyAsDigitInOrder(quo);
    cout<<endl;
    return quo;
}

bool shiftAndCut(Node* ptr){
    if(ptr==NULL)           return true;
    bool oTrail = shiftAndCut(ptr->next);
    if(oTrail){
        ptr->next=NULL;
        if(ptr->coeff)      return false;
        else                return true;
    }
    return false;
}

void printPolyAsDigitInOrder(Node* head)    {
    if(head == NULL)    return;
    cout<<head->coeff<<'('<<head->exp<<')'<<" ";
    printPolyAsDigitInOrder(head->next);
}


int main()  {
    int n,i;
    int digit;
    Node* head1 = NULL;
    Node* head2 = NULL;
    Node* head3 = NULL;
    Node* head4 = NULL;
    Node* head5 = NULL;
    /*head1 = getNumAsList();
    shiftAndCut(head1);
    printPolyAsDigit(head1);
    /*head2 = getNumAsList();
    head3 = polySub(head1,head2);
    printPolyAsDigit(head3);
    head4 = polyMultiply(head1,head2);
    cout<<endl;
    printPolyAsDigit(head4);
    cout<<endl<<cmp(head1,head2)<<endl;
    */
    polyDivide();
    return 1;
}
