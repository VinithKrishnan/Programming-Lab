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
#define TOTAL_CHARACTERS 256 

using namespace std;


void fill_bad_character_table(char* pat, int m, int* badchar)  {
    int i;
    for(i=0;i<TOTAL_CHARACTERS;i++)    {
        badchar[i] = -1;
    }
    for(i=0;i<m;i++)    {
        badchar[(int)pat[i]] = i;
    }
}

void search_pattern(char* text, char* pat, int n, int m) {
    int* badchar = (int*) malloc(sizeof(int)*TOTAL_CHARACTERS);
    
    fill_bad_character_table(pat, m, badchar);
    
    int i=m-1,j=m-1,start_index = i,shift = 0,flag = 0;
    
    while(i <= n-1) {
    
        while(text[i] == pat[j])    {   
            --i;    
            --j;  
            if(start_index-i == m -1) break; ;
        }
        
       
        if(start_index-i == m-1)    {
            shift = 1;
            cout<<"Match found at index = "<<i<<endl;
            flag = 1;
        }
        else if(badchar[text[i]] != -1 and badchar[text[i]] < j)  {
            shift = j - badchar[text[i]];
        }
        else    {
            shift = 1;
        }
        i = start_index + shift;
        j = m-1;
        start_index = i;

    }
    if(!flag) cout<<"No match found!"<<endl;

}

int main(){
    char text[100];
    char pat[100];
    //cout<<"Enter the text: "<<endl;
    cin>>text;
    //cout<<"Enter a pattern:"<<endl;
    cin>>pat;
    int n = strlen(text);
    int m = strlen(pat);
    search_pattern(text,pat,n,m);
    return 0;
}
