#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

//Declare precedence and associativity of operators

// Operators : =, -, /, *, ++, --

//associativity and precedence taken care of
bool check_precedence_associativity(string op, string top)    {
    if (op == "++" or op == "--") {
        return true;
    }
    else if(op == "+" or op == "-")   {
        if(top == "(") return true;
        else return false;

    }
    else if(op == "*" or op == "/")   {
        if(top == "+" or top == "-" or top == "(") return true;
        else return false;
    }
}

int evaluate(vector<string> post_fix)   {
    stack<int> numbers;
    string temp;
    int num1,num2;
    for(int i=0;i<post_fix.size();i++)  {
        temp = post_fix[i];
        num1 = num2 = 0;
        if( temp == "+")    {
            num1 = numbers.top();
            numbers.pop();
            num2 = numbers.top();
            numbers.pop();
            numbers.push(num2+num1);
        }
        else if(temp == "-")  {
            num1 = numbers.top();
            numbers.pop();
            num2 = numbers.top();
            numbers.pop();
            numbers.push(num2-num1);
        }
        else if(temp == "*")    {
            num1 = numbers.top();
            numbers.pop();
            num2 = numbers.top();
            numbers.pop();
            numbers.push(num2*num1);
        }
        else if(temp == "/")    {
            num1 = numbers.top();
            numbers.pop();
            num2 = numbers.top();
            numbers.pop();
            numbers.push(num2/num1);
        }
        else if(temp == "++")   {
            num1 = numbers.top();
            numbers.pop();
            numbers.push(num1+1);
        }
        else if(temp == "--")   {
            num1 = numbers.top();
            numbers.pop();
            numbers.push(num1-1);

        }
        else    {
            num1 = atoi(temp.c_str());
            numbers.push(num1);
        }

    }
    return numbers.top();
}

vector<string> getPostFix(vector<string> token_expr)    {
    vector<string> post_fix;
    stack<string> op_stack;
    string temp;
    for(int i=0;i<token_expr.size();i++)    {
        if(!op_stack.empty())   cout<<"Just Inside for loop: "<<op_stack.top()<<endl;
        else cout<<"For loop: Stack empty"<<endl;
        temp = token_expr[i];
        if(temp == "(") op_stack.push(temp);
        else if(temp == ")")    {
            while(op_stack.top()!= "(") {
                post_fix.push_back(op_stack.top());
                //post_fix.push_back(";");
                op_stack.pop();
            }
            op_stack.pop();
        }
        else if(temp == "/" or temp == "*" or temp == "-" or temp == "+" or temp == "--" or temp == "++" )
            {
                if(op_stack.empty())    op_stack.push(temp);
                else {
                    while(true) {
                        if(!op_stack.empty()) {
                            if(!(check_precedence_associativity(temp,op_stack.top())))
                               {
                                if(!op_stack.empty())   cout<<"Inside while loop before popping: "<<temp<<" "<<op_stack.top()<<endl;
                                else cout<<"while loop: Stack empty"<<endl;
                                post_fix.push_back(op_stack.top());
                                op_stack.pop();
                                //post_fix.push_back(";");
                                }
                            else
                                break;
                        }
                        else
                            break;
                    }
                    if(!op_stack.empty())   cout<<"Inside while loop before pushing: "<<temp<<" "<<op_stack.top()<<endl;
                    else cout<<"while loop: Stack empty"<<endl;
                    op_stack.push(temp);
                }
            }
        else    {
            post_fix.push_back(temp);
            //post_fix.push_back(";");
        }
    }
    while(!op_stack.empty())    {
        post_fix.push_back(op_stack.top());
        //post_fix.push_back(";");
        op_stack.pop();
    }

    return post_fix;
}


int main(){
enum Order {div,mul,add,sub};

string input_expr,temp = "",top;
int i = 0;
vector<string> postfix_expr;
cout<<"Enter an expression"<<endl;
cin>>input_expr;
stack<string> operator_stack;

while(i<input_expr.size())  {
    temp = input_expr.substr(i,1);
    if(temp == "+")
    {
        if(i<input_expr.size()-1)
        {
             if(input_expr[i+1] == '+')   {
                temp += input_expr.substr(i+1,1);
                i = i+2;
                postfix_expr.push_back(temp);
             }
             else   {
                i = i+1;
                postfix_expr.push_back(temp);
             }
        }
    }

    else if(temp == "-")
    {
        if(i<input_expr.size()-1)
        {
             if(input_expr[i+1] == '-')   {
                temp += input_expr.substr(i+1,1);
                i = i+2;
                postfix_expr.push_back(temp);
             }
             else   {
                i = i+1;
                postfix_expr.push_back(temp);
             }
        }
    }

    else if(temp == "*" or temp == "/" or temp == "(" or temp == ")")
    {
        postfix_expr.push_back(temp);
        i++;
    }

    else if(isdigit(input_expr[i]))
    {
            i++;
            while(isdigit(input_expr[i]))
            {
                temp += input_expr.substr(i,1);
                i++;
            }
            postfix_expr.push_back(temp);
    }

    else
    {
            cout<<"Incorrect Input";
    }

}

vector<string> post_fix = getPostFix(postfix_expr);

for(i=0;i<post_fix.size();i++)  {
    cout<<post_fix[i]<<" ";
}

cout<<"Answer = "<<evaluate(post_fix)<<endl;

/*cout<<endl;
int num = atoi("123");
stringstream  stream;
stream << num;
string num1 = stream.str();
cout<<num1<<endl;
*/
return 1;
}
