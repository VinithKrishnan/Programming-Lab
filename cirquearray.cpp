#include<bits/stdc++.h>
using namespace std;
#define MAX 4
class Cirqueue
{public:
	int front;
	int rear;
	int cnt;
	int que[MAX];
	int isFull();
	int isEmpty();
	void insert(int item);
	void del();
	void disp();
	Cirqueue();
};

Cirqueue::Cirqueue()
{front=0;
rear=-1;
cnt=0;
}

int Cirqueue::isFull()
{if(cnt==MAX)
return 1;
else
return 0;
}

int Cirqueue::isEmpty()
{
if(cnt==0)
return 1;
else
return 0;
}

void Cirqueue::insert(int data)
{if(isFull())
{cout<<"Overflow";
return;
}
rear=(rear+1)%MAX;
que[rear]=data;
cnt++;
}


void Cirqueue::del()
{if(isEmpty())
{//cout<<"Underflow";
return;
}
cout<<"\n Deleted element is"<<que[front]<<" ";
front=(front+1)%MAX;
cnt--;
}

void Cirqueue::disp()
{if(isEmpty())
{cout<<"Empty";
return;
}
else
{int i=0;
if(rear>=front)
{while(i<front)
{
cout<<"-"<<" ";
i++;
}
cout<<"("<<" ";
for(i=front;i<=rear && i<=MAX-1;i++)
{cout<<que[i]<<" ";
}
cout<<")"<<" ";
}
else
{while(i<=rear)
{cout<<que[i]<<" ";
i++;
}
cout<<")"<<" ";
while(i<front)
{cout<<"-"<<" ";
i++;
}
cout<<"("<<" ";
while(i<=MAX-1)
{cout<<que[i]<<" ";
i++;
}
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
