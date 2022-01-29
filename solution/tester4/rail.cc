#include<cstdio>
using namespace std;

using i64 = long long;
constexpr int MOD = 1'000'000'007;

struct Mat3{
   Mat3() = default;
   constexpr Mat3(int a, int b, int c, int d, int e, int f, int g, int h, int i) noexcept: e11_((a%MOD+MOD)%MOD), e12_((b%MOD+MOD)%MOD), e13_((c%MOD+MOD)%MOD), e21_((d%MOD+MOD)%MOD), e22_((e%MOD+MOD)%MOD), e23_((f%MOD+MOD)%MOD), e31_((g%MOD+MOD)%MOD), e32_((h%MOD+MOD)%MOD), e33_((i%MOD+MOD)%MOD){}
#define GET(i, j) constexpr int e##i##j() const noexcept{return e##i##j##_;}
   GET(1, 1)
   GET(1, 3)
#undef GET
   Mat3 &operator*=(Mat3 const &rhs) noexcept{
      int f11 = ((i64)e11_*rhs.e11_ + (i64)e12_*rhs.e21_ + (i64)e13_*rhs.e31_) % MOD;
      int f12 = ((i64)e11_*rhs.e12_ + (i64)e12_*rhs.e22_ + (i64)e13_*rhs.e32_) % MOD;
      int f13 = ((i64)e11_*rhs.e13_ + (i64)e12_*rhs.e23_ + (i64)e13_*rhs.e33_) % MOD;
      int f21 = ((i64)e21_*rhs.e11_ + (i64)e22_*rhs.e21_ + (i64)e23_*rhs.e31_) % MOD;
      int f22 = ((i64)e21_*rhs.e12_ + (i64)e22_*rhs.e22_ + (i64)e23_*rhs.e32_) % MOD;
      int f23 = ((i64)e21_*rhs.e13_ + (i64)e22_*rhs.e23_ + (i64)e23_*rhs.e33_) % MOD;
      int f31 = ((i64)e31_*rhs.e11_ + (i64)e32_*rhs.e21_ + (i64)e33_*rhs.e31_) % MOD;
      int f32 = ((i64)e31_*rhs.e12_ + (i64)e32_*rhs.e22_ + (i64)e33_*rhs.e32_) % MOD;
      int f33 = ((i64)e31_*rhs.e13_ + (i64)e32_*rhs.e23_ + (i64)e33_*rhs.e33_) % MOD;
      e11_ = f11; e12_ = f12; e13_ = f13;
      e21_ = f21; e22_ = f22; e23_ = f23;
      e31_ = f31; e32_ = f32; e33_ = f33;
      return *this;
   }
private:
   int e11_{}, e12_{}, e13_{}, e21_{}, e22_{}, e23_{}, e31_{}, e32_{}, e33_{};
};

int ans(i64 n){
   if(n == 1) return 0;
   if(n == 2) return 1;
   n -= 2;
   Mat3 a(2, 0, 1, 1, 0, 0, 0, 1, 0), res(1, 0, 0, 0, 1, 0, 0, 0, 1);
   for(; n; n/=2){
      if(n%2){
         res *= a;
      }
      a *= a;
   }
   return (res.e11()+res.e13())%MOD;
}

int main(){
   i64 n; scanf("%lld", &n);
   printf("%d\n", ans(n));
}
