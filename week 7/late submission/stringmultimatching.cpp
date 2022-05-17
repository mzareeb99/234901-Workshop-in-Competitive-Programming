#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
void help(vector<string>& s, string l){
            for(auto &i : s){
                ll a = 0;
                while (true) {
                    a = l.find(i, a);
                    if (a == -1) break;
                    else cout << a++ << " ";
                }
                cout<<endl;
            }
}
int main() {
    int i;
    while (cin >>i){
        vector<string> words(i);
        int j=0;
        string s;
        getline(cin,s);
        while (i--){
            getline(cin,words[j]);
            j++;
        }
        string lookup;
        getline(cin,lookup);
        help(words,lookup);
        }
    return 0;
}