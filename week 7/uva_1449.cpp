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
#include <iomanip>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ull> vull;
typedef vector<vll> vvll;
typedef vector<vull> vvull;
typedef pair<int, int> pii;
typedef pii ii;
typedef vector<pii> vii;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)


string KMP_str; // The string to search in
string KMP_pat; // The pattern to search
vi lps;

// KMP Init
void KMP_init(){
    int m = KMP_pat.length();
    lps.resize(m+1,0);
    lps[0]=-1;
    int i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
ull KMP_search() {
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int i = 0, j = 0;
    ull counter = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        if (j == m) { // Pattern found
            ++counter;
            j = lps[j];
        }
    }
    return counter;
}


int main() {
    fastIO;
    ull N;
    while (cin >> N && N!=0){
        vector<string> p(N);
        string text;
        for (ull i=0; i<N; ++i){
            cin >> p[i];
        }
        cin >> text;
        KMP_str = text;
        ull max_count = 0;
        vector<string> max_words;
        ull curr_count;
        vull curr_indices;
        for (ull i=0; i<N; ++i){
            KMP_pat = p[i];
            KMP_init();
            curr_count = KMP_search();
            if (max_count == curr_count){
                max_words.emplace_back(p[i]);
            } else if (max_count < curr_count){
                max_count = curr_count;
                max_words = {p[i]};
            }
        }

        cout << max_count << endl;
        for (const auto& s : max_words){
            cout << s << endl;
        }
    }
    return 0;
}
