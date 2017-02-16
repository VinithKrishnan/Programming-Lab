#include<bits/stdc++.h>
using namespace std;


struct node
{int data;
struct node* next;
};

class Cirqueue
{ public:
	struct node* rear;
	void insert(int item);
	void del();
	void disp();
	Cirqueue();
};

Cirqueue::Cirqueue()
{
rear=NULL;
}

void Cirqueue::insert(int data)
{	
struct node* newnode= new node();
if(rear==NULL)
{newnode->data=data;
newnode->next=newnode;
rear=newnode;
}
else
{
newnode->data=data;
newnode->next=rear->next;
rear->next=newnode;
rear=newnode;
}
}

void Cirqueue::del()
{if(rear==NULL)
{//cout<<"Underflow";
return;
}
else if(rear->next==rear)
{struct node* temp=rear;
delete temp;
rear=NULL;
}
else
{struct node* temp=rear->next;
rear->next=temp->next;
delete temp;
}
}

void Cirqueue::disp()
{if(rear==NULL)
{cout<<"Empty";
return;
}
else
{struct node*temp=rear->next;
cout<<temp->data;
temp=temp->next;
while(temp!=rear->next)
{cout<<"->"<<temp->data;
temp=temp->next;
}
}
}

int main()
{
Cirqueue q=Cirqueue();
int choice;
int ele;
l1:
cout<<"\n Choose one of the following options";
cout<<"\n 1.Insert";
cout<<"\n 2.Delete";
cout<<"\n 3.Exit";

cin>>choice;
switch(choice)
{case 1:cout<<"\n Enter element that you wish to insert";
cin>>ele;
q.insert(ele);
q.disp();
break;
case 2: q.del();
q.disp();
break;
default:exit(0);
}

goto l1;

}

