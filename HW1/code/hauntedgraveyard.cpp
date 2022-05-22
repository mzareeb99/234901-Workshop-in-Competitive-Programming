#include <iostream>
#include <deque>
#include <functional>
#include <map>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector<vector<pair<pair<int, int>, int> >> vviii;
typedef vector<vviii> vvviii;
typedef vector<bool> vb;
#define INF 100000000

bool BellmanFord(const vvviii& g, pii s, vvi& d, int W, int H) {
    d.assign(W,vector<int>(H, INF));
    d[s.first][s.second] = 0;
    bool changed = false;
    for (int i = 0; i < W*H; ++i) {
        changed = false;
        for (int u = 0; u < W; ++u) {
            for (int z = 0; z < H; z++) {
                for (pair<pii, int> e: g[u][z]) {
                    pii v = e.first;
                    int w = e.second;
                    if (d[u][z] < INF && d[u][z] + w < d[v.first][v.second] && w<INF) {
                        d[v.first][v.second] = d[u][z] + w;
                        changed = true;
                    }
                }
            }
        }
    }
    return changed;
}

void fun( vvviii& tree,vb &b,int W,int H ){
    for (int i=0;i<W;i++){
        for(int j=0; j<H; j++){
            if(!b[W*j+i]) {
                if (i + 1 < W && !b[W*j+i+1] )
                    tree[i][j].push_back(pair<pii, int>(pair<int, int>(i + 1, j), 1));
                if (j + 1 < H && !b[W*(j+1)+i])
                    tree[i][j].push_back(pair<pii, int>(pair<int, int>(i, j + 1), 1));
                if (i-1>=0 && !b[W*j+i-1])
                    tree[i][j].push_back(pair<pii, int>(pair<int, int>(i -1 , j), 1));
                if (j-1>=0 && !b[W*(j-1)+i])
                    tree[i][j].push_back(pair<pii, int>(pair<int, int>(i , j-1), 1));

            }
        }
    }

}


int main() {
    int W,H;
    while (cin>>W>>H && (W!=0 || H!=0)){
        vvviii wtree = vvviii(W, vviii(H)) ;
        int G,E;
        vb bad(W*H , false);
        cin>>G;
        while (G--){
            int x,y;
            cin>>x>>y;
            bad[W*y+x]=true;
        }

        fun(wtree,bad,W,H);
        cin>>E;
        while (E--){
            int x1,y1,x2,y2,t;
            cin>>x1>>y1>>x2>>y2>>t;
            wtree[x1][y1].clear();
            wtree[x1][y1].push_back(pair<pii,int>(pair<int,int>(x2,y2) ,t)) ;
        }
        wtree[W-1][H-1].clear();
        vvi v;
        if (BellmanFord(wtree,pii(0,0),v,W,H))
            cout<<"Never"<<endl;
        else {
            if (v[W-1][H-1]>=INF)
                cout << "Impossible" <<endl ;
            else
                cout<< v[W-1][H-1] <<endl;
        }
    }
}
