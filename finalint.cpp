#include<bits/stdc++.h>

using namespace std;



class LargeInt
{public:
vector<int> a;//stores largeInt
LargeInt(vector<int> b)//Constructor
{for(int i=0;i<b.size();i++)
a.push_back(b[i]);             //MSB is assigned 0 index while LSB is assigned index 
}
void printnumber();//function to print vector as number
int comp(vector<int> b);//function to compare two numbers
vector<int> add(vector<int> b);//adds two numbers
vector<int> sub(vector<int> b);//subtracts two numbers
vector<int> mul(vector<int> b);//multiplies two numbers
void div(vector<int> b);//divides two numbers
};



void LargeInt :: printnumber()//function to print vector as number
{for(int i=0;i<a.size();i++)
cout<<a[i];
cout<<endl;
}

int LargeInt :: comp(vector<int> b)//compares two numbers
{if(a.size()>b.size())//if size of a is greater than b then a is a bigger number
return 1;
else if(a.size()==b.size())//if sizes of both numbers are same
{int i=0;
while(i<a.size() && a[i]==b[i] )
i++;
if(i==a.size())
return 0;      //both are same
else if(a[i]>b[i])
return 1;       //a is bigger than b
else
return -1;      //b is bigger than a
}
else
return -1;	//if size of b is greater than a then b is a bigger number
}


vector<int> LargeInt :: add(vector<int> b)

{
vector<int> p;
vector<int> q;
if(b.size()>a.size())    //This if-else loop assigns bigger number to p and smaller number to q
{p=b;
q=a;
}
else
{p=a;
q=b;
}
vector<int> c(p.size()+1,0);

int carry=0;
int k=p.size()-q.size();
for(int i=p.size()-1;i>=k;i--)
{
c[i+1]=(p[i]+q[q.size()-p.size()+i]+carry)%10;
carry=(p[i]+q[q.size()-p.size()+i]+carry)/10;
}

if(p.size()!=q.size())                 //if size of p is greater than q then the follwing loop runs
{
for(int j=p.size()-q.size()-1;j>=0;j--)
{c[j+1]=(p[j]+carry)%10;
carry=(p[j]+carry)/10;
}
}
if(carry>0)
{
c[0]=carry;
}
else
c.erase(c.begin());//    erases leading zeroes
return c;

}

vector<int> LargeInt :: sub(vector<int> b)
{
vector<int> p;
vector<int> q;
if(b.size()>a.size())            //This if-else loop assigns bigger number to p and smaller number to q
{p=b;
q=a;
}
else
{p=a;
q=b;
}
vector<int> c(p.size(),0);
int i=p.size()-1;
int j=q.size()-1;
while(i>=0 && j>=0)
{if(p[i]>=q[j])    //if p[i]>q[i] normal subtractin is done
c[i]=p[i]-q[j];
else
{c[i]=p[i]-q[j]+10;//else 10 is added to the subtracted number
int t=i-1;
while(t>=0&&p[t]==0 )  // the zeroes to the left of the index sre chenged to 9
{p[t]=9;
t--;
}
p[t]-=1;//the first number that is not a zero is subtracted by 1
}
i--;
j--;	
}
while(i>=0)// if size of p is greater than q,remaining elements of p are directly copied to answer
{c[i]=p[i];
i--;
}
while(c[0]==0 && c.size()>1)
{c.erase(c.begin());                 //removes leading zeroes
}
return c;
}

vector<int> LargeInt:: mul(vector<int> b)
{vector<int> p;
vector<int> q;
if(b.size()>a.size())                    //This if-else loop assigns bigger number to p and smaller number to q
{p=b;
q=a;
}
else
{p=a;
q=b;
}
vector<int> z(p.size()+1,0);
LargeInt ans(z);
for(int j=q.size()-1;j>=0;j--)
{int carry=0;
vector<int> temp(p.size()+1,0);
for(int i=p.size()-1;i>=0;i--)
{temp[i+1]=(p[i]*q[j]+carry)%10;
carry=(p[i]*q[j]+carry)/10;
}
if(carry>0)
{
temp[0]=carry;
}
else
temp.erase(temp.begin());   //if carry is zero it erases first index
for(int t=0;t<q.size()-1-j;t++)
temp.push_back(0);              //left shifts the product


ans.a=ans.add(temp);        //adds the new product with old product

while(ans.a[0]==0 && ans.a.size()>1)
{ans.a.erase(ans.a.begin());                  //removes leading zeroes
}
}
return ans.a;
}

void LargeInt::div(vector<int> b)
{vector<int> q;
int i=b.size()-1;
if(b.size()>a.size())            //if divisor is bigger than dividend then quotient is zero,remainder is dividend itself
{vector<int> q(1,0);
LargeInt Quo(q);
cout<<"Quotient is:";
Quo.printnumber();
cout<<endl;

cout<<"Remainder is:";

printnumber();

return;
}
vector<int> prod;
vector<int> rem(a.begin(),a.begin()+b.size()-1); //selects first l digits from dividend where l is size of divisor
while(i<=a.size()-1)
{
int j=0;
rem.push_back(a[i]);                   //pushes back the next integer from dividend
while(rem[0]==0 && rem.size()>1)      //removes leading zeroes
{rem.erase(rem.begin());
}


while(true) // multiplies dividend from j=0 to 9 until the product is greater than selected l digits
{
vector<int> t(1,j); 
LargeInt m(t);
 prod= m.mul(b);
LargeInt temp(prod);
 
if(temp.comp(rem)>0)
break;
else
j++;
}


q.push_back(j-1);   //j-1 is added to qoutient
vector<int> t(1,j-1);  
LargeInt n(t);
 prod= n.mul(b);
 LargeInt temp(rem);

rem=temp.sub(prod);   //remainder is calculated

i++;
}
while(q[0]==0 && q.size()>1)
{q.erase(q.begin());                       //removes leading zeroes
}
LargeInt Quo(q);
cout<<"Quotient is:";
Quo.printnumber();
LargeInt t(rem);
cout<<"Remainder is:";
t.printnumber();

}


int main()
{string a;
string b;
cout<<"Enter the two numbers:";
cin>>a;
cin>>b;
vector<int> p(a.size(),0);
vector<int> q(b.size(),0);
for(int i=0;i<a.size();i++)
p[i]=a[i]-'0';
for(int i=0;i<b.size();i++)
q[i]=b[i]-'0';
LargeInt n(p);
LargeInt m(q);

l1:
cout<<"Choose one of the following options:\n";
cout<<"1.Addition\n";
cout<<"2.Subtraction\n";
cout<<"3.Multiplication\n";
cout<<"4.Division\n";
int choice;
LargeInt c(p);
cin>>choice;
switch(choice)
{case 1:c.a=n.add(m.a);
c.printnumber();
break;
case 2:c.a=n.sub(m.a);
c.printnumber();
break;
case 3:c.a=n.mul(m.a);
c.printnumber();
break;

case 4:
n.div(m.a);
break;



}


}
