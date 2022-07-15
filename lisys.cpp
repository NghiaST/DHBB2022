/// SaoST - Le Huu Nghia - IOI22
#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=(l); i<=(r); ++i)
#define REP(i,l,r) for(int i=(l); i<(r); ++i)
#define FORD(i,r,l) for(int i=(r); i>=(l); --i)
#define REPD(i,r,l) for(int i=(r)-1; i>=(l); --i)
using namespace std;
const int N = 2e6 + 5, MOD = 1e9 + 7;
int n, exist, cnt;
long long f[N], f2[N], f3[N];

void Enter() {
    cin >> n;
    exist = n * 2 - 2;
    FOR(i, 1, n) {
        int x;
        cin >> x;
        if (x == -1) ++cnt;
        else exist -= x;
    }
}

long long C(int n, int k) {
    if (n < k) return 0;
    return f[n] * f3[k] % MOD * f3[n - k] % MOD;
}

long long CK(int n, int k) {
    return C(n - 1, k - 1);
}

void Process() {
    if (cnt == 0) return void(cout << (exist == 0));
    f[0] = f[1] = f2[0] = f2[1] = f3[0] = f3[1] = 1;
    FOR(i, 2, n * 2) {
        f[i] = f[i - 1] * i % MOD;
        f2[i] = MOD - MOD/i * f2[MOD % i] % MOD;
        f3[i] = f3[i - 1] * f2[i] % MOD;
    }
    cout << (CK(exist, cnt) - CK(exist - n + 1, cnt) * cnt % MOD + MOD) % MOD;
}

int main()
{
    #define file "lisys"
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    if (fopen(file".inp","r")) {
        freopen(file".inp","r",stdin);
        freopen(file".out","w",stdout);
    }
    Enter();
    Process();
}
