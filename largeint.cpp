#include<bits/stdc++.h>

using namespace std;



void printnumber(vector<int> a)
{for(int i=0;i<a.size();i++)
cout<<a[i];
cout<<endl;
}

int comp(vector<int> &a,vector<int> &b)//compares two numbers
{if(a.size()>b.size())
return 1;
else if(a.size()==b.size())
{int i=0;
while(i<a.size() && a[i]==b[i] )
i++;
if(i==a.size())
return 0;
else if(a[i]>b[i])
return 1;
else
return -1;
}
else
return -1;	
}


vector<int> add(vector<int> &p,vector<int> &q)

{
vector<int> a;
vector<int> b;
if(q.size()>p.size())
{a=q;
b=p;
}
else
{a=p;
b=q;
}
vector<int> c(a.size()+1,0);

int carry=0;
int k=a.size()-b.size();
for(int i=a.size()-1;i>=k;i--)
{
c[i+1]=(a[i]+b[b.size()-a.size()+i]+carry)%10;
carry=(a[i]+b[b.size()-a.size()+i]+carry)/10;
}

if(a.size()!=b.size())
{
for(int j=a.size()-b.size()-1;j>=0;j--)
{c[j+1]=(a[j]+carry)%10;
carry=(a[j]+carry)/10;
}
}
if(carry>0)
{
c[0]=carry;
}
else
c.erase(c.begin());
return c;

}

vector<int> sub(vector<int> &p,vector<int> &q)
{vector<int> a;
vector<int> b;
if(q.size()>p.size())
{a=q;
b=p;
}
else
{a=p;
b=q;
}
vector<int> c(a.size(),0);
int i=a.size()-1;
int j=b.size()-1;
while(i>=0 && j>=0)
{if(a[i]>=b[j])
c[i]=a[i]-b[j];
else
{c[i]=a[i]-b[j]+10;
int t=i-1;
while(t>=0&&a[t]==0 )
{a[t]=9;
t--;
}
a[t]-=1;
}
i--;
j--;	
}
while(i>=0)
{c[i]=a[i];
i--;
}
while(c[0]==0 && c.size()>1)
{c.erase(c.begin());
}
return c;
}

vector<int> mul(vector<int> &p,vector<int> &q)
{vector<int> a;
vector<int> b;
if(q.size()>p.size())
{a=q;
b=p;
}
else
{a=p;
b=q;
}
vector<int> ans(a.size()+1,0);
for(int j=b.size()-1;j>=0;j--)
{int carry=0;
vector<int> temp(a.size()+1,0);
for(int i=a.size()-1;i>=0;i--)
{temp[i+1]=(a[i]*b[j]+carry)%10;
carry=(a[i]*b[j]+carry)/10;
}
if(carry>0)
{
temp[0]=carry;
}
else
temp.erase(temp.begin());
for(int t=0;t<b.size()-1-j;t++)
temp.push_back(0);

ans=add(ans,temp);
while(ans[0]==0 && ans.size()>1)
{ans.erase(ans.begin());
}
}
return ans;
}

vector<int> div(vector<int> &a,vector<int> &b)
{vector<int> q;
int i=b.size()-1;
if(b.size()>a.size())//if size of b is greater than size of a,the quotient must be 0
{vector<int> q(1,0);
return q;
}
vector<int> prod;
vector<int> rem(a.begin(),a.begin()+b.size()-1);
while(i<=a.size()-1)
{
int j=0;
rem.push_back(a[i]);//brings down the next integer in a
while(rem[0]==0 && rem.size()>1)//removes leading zeroes
{rem.erase(rem.begin());
}


while(true)//multiplies b from 1 to 9 until the product becomes greater than rem
{
vector<int> t(1,j);
 prod= mul(b,t);

if(comp(prod,rem)>0)
break;
else
j++;
}


q.push_back(j-1);//adds j-1 to the quotient
vector<int> t(1,j-1);
prod=mul(b,t);    //multiplies b with j-1 
rem=sub(rem,prod);//rem stores rem-b*(j-1)

i++;
}
while(q[0]==0 && q.size()>1)//removes leading zeroes
{q.erase(q.begin());
}
return q;
}


int main()
{string a;
string b;
cout<<"Enter the two numbers:";
cin>>a;
cin>>b;
vector<int> n(a.size(),0);
vector<int> m(b.size(),0);
for(int i=0;i<a.size();i++)
n[i]=a[i]-'0';
for(int i=0;i<b.size();i++)
m[i]=b[i]-'0';
//printnumber(n);
//printnumber(m);
l1:
cout<<"Choose one of the following options:\n";
cout<<"1.Addition\n";
cout<<"2.Subtraction\n";
cout<<"3.Multiplication\n";
cout<<"4.Division\n";
int choice;
cin>>choice;
switch(choice)
{case 1:printnumber(add(n,m));
break;
case 2:printnumber(sub(n,m));
break;
case 3:printnumber(mul(n,m));
break;
case 4:printnumber(div(n,m));
break;
default:cout<<"\nEnter a valid choice";
goto l1;

}


}
