// Expect: AC
#include<algorithm>
#include<numeric>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int n, k, p;
   scanf("%d%d%d", &n, &k, &p);
   vector<int> h(n);
   for(int i=0; i<n; ++i){
      scanf("%d", h.data()+i);
   }
   sort(h.begin(), h.end());
   adjacent_difference(h.begin(), h.end(), h.begin());
   h.erase(h.cbegin()); --k;
   bool jump = k >= 2;
   if(jump){
      for(size_t i=0; i+1<h.size(); ++i){
         h[i] += h[i+1];
      }
      h.pop_back();
      --k;
   }
   int lb = *min_element(h.cbegin(), h.cend())-1, ub = *max_element(h.cbegin(), h.cend());
   auto ok = [&](int x){
      int cnt = 0;
      for(size_t i=0, j=0; i<h.size(); ++i){
         if(h[i] > x){
            j = i+1;
         }else if(i-j+1 == k){
            ++cnt;
            i += 1+jump; j = i+1;
         }
      }
      return cnt >= p;
   };
   while(ub-lb > 1){
      int mid = lb + (ub-lb)/2;
      (ok(mid)? ub: lb) = mid;
   }
   printf("%d\n", ub);
}
