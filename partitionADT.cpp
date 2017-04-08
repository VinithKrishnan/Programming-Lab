#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class partitionADT {
    public:
    int n;
    int *parent;
    int *rank;
    partitionADT(int n);
    void better_union(int x,int y);         //rank union
    int better_find(int x);                //path compression
    void printPartition();
};

partitionADT :: partitionADT (int n){
    this->n = n;
    parent = (int*) malloc(sizeof(int)*n);
    rank = (int*) malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int partitionADT :: better_find(int x)  {
    if(parent[x] == x)  return x;
    else    {
        int result = better_find(parent[x]);
        parent[x] = result;
        return result;
    }
}

void partitionADT :: better_union(int x,int y)  {
    int rep_x = better_find(x);
    int rep_y = better_find(y);
    
    if(rank[rep_x] < rank[rep_y])   {
        parent[rep_x] = rep_y;
        rank[rep_x] = 0;
    }
    else if (rank[rep_x] == rank[rep_y])   {
        parent[rep_y] = rep_x;
        rank[rep_y] = 0;
        rank[rep_x] += 1;
    }
    if(rank[rep_x] > rank[rep_y])   {
        parent[rep_y] = rep_x;
        rank[rep_y] = 0;
    }
}

void partitionADT :: printPartition ()    {
    int a[this->n],i,j;
    for(i=0;i<n;i++)    {
        a[i] = better_find(i);
    }
    int count = 0,p,flag = 0;
    while(count!=n)  {
        flag = 0;
        for(i=0;i<n;i++)  {
            if(a[i]!=-1 and !flag)    {
                p = a[i];
                flag = 1;
            }
            if(a[i] == p)   {
                cout<<i<<" ";
                a[i] = -1;
                count++;
            }
        }
        cout<<endl; 
    }   
}

int main(){
    partitionADT p = partitionADT(8);
    p.better_union(5,7);
    p.better_union(7,1);
    p.better_union(6,4);
    p.better_union(6,1);
    cout<<"Root of 4 is: "<<p.better_find(4)<<endl;
    p.printPartition();
    return 0;
}
