#include <algorithm>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
int main(){
   double H,U,D,F;
   while(true) {
       cin >> H >> U >> D >> F;
       if(H==0) return 0;
        int day = 1;
        double x=U;
        double fac = F;
       while (true){
            if(H < x) {
                cout << "success on day " << day << endl;
                break;
            }
           x-=D;
           if(x<0) {
                cout<<"failure on day "<<day<<endl;
                break;
            }
                day++;
                x+=max(U-((U*fac)/100),0.0);
               fac += F;
       }
            }
       }