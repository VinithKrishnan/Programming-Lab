#include<bits/stdc++.h>
using namespace std;
#define MAX 100
class Stack
{public:
	char*stack;
	 int stackptr;
     Stack();
     void push(char data);
     void pop();
     char top();
};

Stack::Stack()
{stack=new char(MAX);
stackptr=-1;
}

void Stack::push(char data)
{if(stackptr>=-1 && stackptr<MAX-1)
stack[++stackptr]=data;
else
{
cout<<"\n Overflow";
exit(0);
}
}

void Stack::pop()
{if(stackptr>=0 && stackptr<MAX)
stackptr-=1;
else
cout<<"Underflow";
}

char Stack::top()
{if(stackptr>=0 && stackptr<MAX)
return stack[stackptr];
else return '0';
}


int main()
{
Stack s=Stack();
int sp=-1;
string str;
cout<<"\n Enter string of paranthesis";
cin>>str;
int flag=0;
for(int i=0;i<str.size();i++)
{

if(str[i]=='{')
s.push('{');
else if(str[i]=='}')
{if(s.top()=='{')
s.pop();
else
{
cout<<"\n Paranthesis are imperfectly matched";
flag=1;
break;
}
}

}
if(s.stackptr==-1 && flag==0)
cout<<"\n Parenthesis match perfectly";


}
