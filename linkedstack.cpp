#include<bits/stdc++.h>
using namespace std;

struct node
{char data;
struct node* next;
};

void  push(struct node** head,char data)
{struct node* newnode = new node();
newnode->data=data;
newnode->next=*head;
*head=newnode;

}

void pop(struct node** head)
{ if (*head == NULL)
      {cout<<"\n Paranthesis are imperfectly matched";
      exit(0);
	  }
struct node* temp= *head;
*head=temp->next;
delete temp;
}






int main()
{

struct node* head=NULL;
string s;
cout<<"\n Enter string of paranthesis";
cin>>s;
for(int i=0;i<s.size();i++)
{if(s[i]=='{')
push(&head,'{');
else if(s[i]=='}')
pop(&head);
}
if(head==NULL)
cout<<"\n Parenthesis match perfectly";
else
cout<<"\n Paranthesis are imperfectly matched";
}
