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
#include <sstream>
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

const int BOARD_SIZE = 5;


struct Jumper{
    ii from;
    ii via;
    ii to;

    Jumper(ii from, ii via, ii to): from(move(from)), via(move(via)), to(move(to)) {}
};


class Board{
    vvi board;
    ll score;
    int turn_sign;
public:
    explicit Board(ll score=0, int turn_sign=1): board(BOARD_SIZE, vi(BOARD_SIZE, 0)), score(score), turn_sign(turn_sign){}

    void fillUserInput(){
        for (int i=0; i<BOARD_SIZE; ++i){
            for (int j=0; j<=i; ++j){
                cin >> board[i][j];
            }
        }
    }

    static bool isLegalCoordinate(const ii& coor){
        auto i = coor.first;
        auto j = coor.second;
        return (i >= 0) && (i < BOARD_SIZE) && (j >= 0) && (j <= i);
    }

    int boardVal(const ii& coor){
        return board[coor.first][coor.second];
    }

    bool tryAddJumper(vector<Jumper>& jumpers, const Jumper& jumper){
        if (!isLegalCoordinate(jumper.from) || !isLegalCoordinate(jumper.via) || !isLegalCoordinate(jumper.to)){
            return false;
        }
        if (boardVal(jumper.from)==0 || boardVal(jumper.via)==0 || boardVal(jumper.to)!=0){
            return false;
        }

        jumpers.emplace_back(jumper);
        return true;
    }

    vector<Jumper> getJumpers(int i, int j){
        vector<Jumper> jumpers;

        tryAddJumper(jumpers, Jumper({i, j-2}, {i, j-1}, {i, j}));
        tryAddJumper(jumpers, Jumper({i, j+2}, {i, j+1}, {i, j}));
        tryAddJumper(jumpers, Jumper({i+2, j}, {i+1, j}, {i, j}));
        tryAddJumper(jumpers, Jumper({i+2, j+2}, {i+1, j+1}, {i, j}));
        tryAddJumper(jumpers, Jumper({i-2, j}, {i-1, j}, {i, j}));
        tryAddJumper(jumpers, Jumper({i-2, j-2}, {i-1, j-1}, {i, j}));

        return jumpers;
    }

    ll value(){
        vector<ll> scores = {};

        for (int i=0; i<BOARD_SIZE; ++i){
            for (int j=0; j<=i; ++j){
                auto jumpers = getJumpers(i, j);

                for (const auto& jumper : jumpers){
                    ll score_diff = boardVal(jumper.from) * boardVal(jumper.via);

                    Board curr_option(score + turn_sign*score_diff, -turn_sign);
                    curr_option.board = board;
                    curr_option.board[jumper.to.first][jumper.to.second] = boardVal(jumper.from);
                    curr_option.board[jumper.from.first][jumper.from.second] = 0;
                    curr_option.board[jumper.via.first][jumper.via.second] = 0;

                    scores.emplace_back(curr_option.value());
                }
            }
        }

        if (scores.empty()){
            return score;
        }

        if (turn_sign >= 0){
            return *max_element(scores.begin(), scores.end());
        } else{
            return *min_element(scores.begin(), scores.end());
        }
    }
};



int main(){
    fastIO;

    Board b;
    b.fillUserInput();
    cout << b.value() << endl;
    return 0;
}
