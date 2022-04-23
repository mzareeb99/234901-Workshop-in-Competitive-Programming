#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;



bool is_plandrom(string str){
    int i = 0;
    int j = str.length()-1;
    for(int i = 0 ; i< str.length();i++){

        str[i] = toupper(str[i]);
    }
    //(char)toupper(str);
    //toUp
    while(i < j) {
        if(str[i] != str[j]) return false;
        i++;
        j--;
    }
    return true;
}
int main(){
    string s;
    //cin >> s;
    //getline(s);
    string str;
    //isalpha(s,)
    //get >> s;
    getline(cin,s);
    //cout<<s.length()<<endl;
    while(s != "DONE"){
        for(int i = 0 ; i < s.length(); i++) {
            //‘.’, ‘,’, ‘!’, ‘?
            if (s[i] != '.' && s[i] != ',' && s[i] != '!' && s[i] != '?' && s[i] != ' ' && s[i]!= '\n') {
                str += s[i];
            }
        }
                if(is_plandrom(str)) {
                    cout <<"You won't be eaten!" << endl;
                    str ="";
                }else {
                    cout << "Uh oh.." << endl;
                    str="";
                }
        getline(cin,s);
            }
        return 0;
    }