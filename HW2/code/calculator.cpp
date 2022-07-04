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
#include <list>
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
typedef pair<int, ii> iii;
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


class Evaluator{
    string* s;
    size_t from;
    size_t to;
    size_t iter;

    enum operators {ADD=0, SUB, MUL, DIV};

    void cleanSpaces(){
        string res;
        for (auto c : *s){
            if (c != ' '){
                res += c;
            }
        }
        *s = res;
    }

    size_t closeBrackets(size_t open_idx){
        size_t brackets_counter = 1;
        size_t i=open_idx+1;
        for (; (i < s->size()) && (brackets_counter != 0); ++i){
            if ((*s)[i] == '('){
                ++brackets_counter;
            } else if ((*s)[i] == ')'){
                --brackets_counter;
            }
        }
        return i-1;
    }

    double getNextNum(){
        double num = 0;
        bool is_minus = false;
        if (iter < s->size()){
            if ((*s)[iter] == '-'){
                is_minus = true;
                ++iter;
            } else if ((*s)[iter] == '+'){
                is_minus = false;
                ++iter;
            }
        }
        if (iter < s->size()){
            if ((*s)[iter] == '('){
                auto close_idx = closeBrackets(iter);
                num = Evaluator(s, iter+1, close_idx).eval();
                iter = close_idx+1;
            } else{
                for (;iter<(*s).size() && isdigit((*s)[iter]); ++iter){
                    num = num*10 + ((*s)[iter] - '0');
                }
            }
        }
        if (is_minus){
            num = -num;
        }
        return num;
    }

    operators getNextOp(){
        char op_char = (*s)[iter++];
        switch(op_char){
            case '+':
                return ADD;
            case '-':
                return SUB;
            case '*':
                return MUL;
            case '/':
                return DIV;
            default:
                return ADD;
        }
    }

public:
    explicit Evaluator(string* s, size_t from, size_t to): s(s), from(from),
                                                            to(to), iter(from){}

    explicit Evaluator(string* s): s(s), from(0), to(0), iter(0){
        cleanSpaces();
        to = s->size();
    }

    double eval(){
        list<double> nums;
        list<operators> ops;
        nums.emplace_back(getNextNum());
        while (iter < to){
            ops.emplace_back(getNextOp());
            nums.emplace_back(getNextNum());
        }

        auto nums_it = nums.begin();
        auto ops_it = ops.begin();
        while (ops_it != ops.end()){
            if (*ops_it == MUL){
                auto deleted_num = *nums_it;
                nums_it = nums.erase(nums_it);
                *nums_it = *nums_it * deleted_num;
                ops_it = ops.erase(ops_it);
            } else if (*ops_it == DIV){
                auto deleted_num = *nums_it;
                nums_it = nums.erase(nums_it);
                *nums_it = deleted_num / *nums_it;
                ops_it = ops.erase(ops_it);
            } else{
                ++nums_it;
                ++ops_it;
            }
        }
        nums_it = nums.begin();
        ops_it = ops.begin();
        while (ops_it != ops.end()){
            if (*ops_it == ADD){
                auto deleted_num = *nums_it;
                nums_it = nums.erase(nums_it);
                *nums_it = *nums_it + deleted_num;
                ops_it = ops.erase(ops_it);
            } else if (*ops_it == SUB){
                auto deleted_num = *nums_it;
                nums_it = nums.erase(nums_it);
                *nums_it = deleted_num - *nums_it;
                ops_it = ops.erase(ops_it);
            } else{
                ++nums_it;
                ++ops_it;
            }
        }

        return *nums.begin();
    }


};


int main() {
    fastIO;

    string s;
    while(getline(cin, s)){
        Evaluator e(&s);
        cout << fixed << setprecision(2) << e.eval() << endl;
    }

    return 0;
}
