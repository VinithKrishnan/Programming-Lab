#include<bits/stdc++.h>
using namespace std;

struct node
{int data;
struct node* next;
};


int main()
{int maxsize=100;
char stack[maxsize];
int sp=-1;
string s;
cout<<"\n Enter string of paranthesis";
cin>>s;
for(int i=0;i<s.size();i++)
{if(sp==maxsize)
{
cout<<"Overflow";
break;
}
else
{if(s[i]=='{')
stack[++sp]='{';
else if(s[i]=='}')
sp=sp-1;
}
}
if(sp==-1)
cout<<"\n Parenthesis match perfectly";
else
cout<<"\n Paranthesis are imperfectly matched";

}
