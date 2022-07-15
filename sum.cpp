/// SaoST - Le Huu Nghia - IOI22
#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=(l); i<=(r); ++i)
#define REP(i,l,r) for(int i=(l); i<(r); ++i)
#define FORD(i,r,l) for(int i=(r); i>=(l); --i)
#define REPD(i,r,l) for(int i=(r)-1; i>=(l); --i)
using namespace std;
const int N = 1e6 + 5, MOD = 1e9 + 7;
long long n, a, b;

void Enter() {
    cin >> n >> a >> b;
}

void Process() {
    a %= MOD; b %= MOD;
    long long res1 = (n % MOD) * ((n + 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD * a % MOD;
    long long res2 = 0;
    for(long long i=1; i*i<=n; ++i)
        (res2 += (min((i + 1) * (i + 1), n + 1) - i * i) * i % MOD) %= MOD;
    res2 = res2 * b % MOD;
    cout << (res1 + res2) % MOD;
}

int main()
{
    #define file "sum"
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    if (fopen(file".inp","r")) {
        freopen(file".inp","r",stdin);
        freopen(file".out","w",stdout);
    }
    Enter();
    Process();
}
