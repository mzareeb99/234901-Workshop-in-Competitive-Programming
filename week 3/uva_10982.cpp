#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <set>
using namespace std;


//// TroubleMakers
//input
//2                                     Case #1: 3
//4 3                                   1 3 4
//1 2                                   Case #2: 2
//2 3                                   1 2
//3 4
//4 6           ====> output
//1 2
//1 3
//1 4
//2 3
//2 4
//3 4

int main(){

    int N;
    int n,m;
    cin >>N;
    int cases = 0;
    while(N--){
        cin>>n>>m;
        vector<set<int>> kids(n+2, set<int>());

        int x1,x2;
        for(int i = 0 ; i < m ; i++) {
            cin >> x1 >> x2;
            kids[x1].insert(x2);
            kids[x2].insert(x1);
        }
        set<int> cA;
        set<int> cB;


        for(int i =1; i< n+2;++i){
            int a1=0,a2=0;
           for(auto k : kids[i]) {
               if (cA.find(k) != cA.end())
                   a1++;
               if (cB.find(k) != cB.end())
                   a2++;
           }
           if(a1 < a2)
               cA.insert(i);
           else
               cB.insert(i);
        }
            printf("Case #%d: %d\n",++cases, cA.size());
            for(auto i : cA)
                printf("%d ",i);
            printf("\n");
    }
    return 0;
}








////    lucky number
//firstly need to create the vector
// How to now if the number is lucky?
// completely?

//
//
//void first(vector<int>& vec,int m){
//    int k=1;
//    for(int i=0;i < m;i++) {
//        vec.push_back(k);
//        k += 2;
//    }
//}
//
//
//void clear(vector<int>& vec){
//    vector<int> temp;
//    for(int i : vec)
//        if(i !=0)
//            temp.push_back(i);
//        vec.clear();
//    for(int i : temp)
//        vec.push_back(i);
//
//}
//void iter(vector<int>& vec,int x){
//   for(int i = x-1; i < vec.size();i*=x-1)
//       vec[i] = 0;
//   clear(vec);
//}
//
//
//
//int main() {
//    vector<int> a;
//    int max = 0;
//    int x;
//    int n ;
//    cin>>n;
////    while(cin>>x){
////        if(x > max) max = x;
////            a.push_back(x);
////    }
////    n=max;
//    vector<int> vec;
//    first(vec,n/2 +1);
//
//    for(int i =1; ;i++){
//        if(i == vec.size()) break;
//        iter(vec,vec[i]);
//    }
//    a.push_back(n);
//    for(int i : a) {
//        bool f = false;
//        set<int> t = {vec.begin(),vec.end()} ;
//
//        auto low = t.lower_bound(i);
//        auto hei = t.lower_bound(i);
//        while (*low < *hei){
//            if(*low + *hei == i) {
//                printf("%d is the sum of %d and %d", i, *low, *hei);
//                f = true;
//                break;
//            }else if(*low + *hei > i){
//                hei--;
//            }else{
//                low--;
//            }
//        }
//        if(!f){
//            printf("%d is not the sum of two luckies!", i);
//        }
//    }
//    return 0;
//}