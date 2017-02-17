#include<bits/stdc++.h>
using namespace std;

struct node
{char data;
struct node* next;
};


class Stack
{public:
	struct node* head;
     Stack();
     void push(char data);
     void pop();
     char top();
};

Stack::Stack()
{head=NULL;
}

void Stack::push(char data)
{struct node* newnode = new node();
newnode->data=data;
newnode->next=head;
head=newnode;
}

void Stack::pop()
{ if (head == NULL)
      {cout<<"\n Paranthesis are imperfectly matched";
      exit(0);
	  }
struct node* temp= head;
head=temp->next;
delete temp;
}

char Stack::top()
{if(head!=NULL)
return head->data;
else
return '0';
}




int main()
{
Stack stack=Stack();
string s;
int flag=0;
cout<<"\n Enter string of paranthesis";
cin>>s;
for(int i=0;i<s.size();i++)
{if(s[i]=='{')
stack.push('{');
else if(s[i]=='}')
{if(stack.top()=='{')
stack.pop();
else
{
cout<<"\n Paranthesis are imperfectly matched";
flag=1;
break;
}
}
}
if(stack.head==NULL && flag==0) 
cout<<"\n Parenthesis match perfectly";

}
