/// SaoST - Le Huu Nghia - IOI22
#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=(l); i<=(r); ++i)
#define REP(i,l,r) for(int i=(l); i<(r); ++i)
#define FORD(i,r,l) for(int i=(r); i>=(l); --i)
#define REPD(i,r,l) for(int i=(r)-1; i>=(l); --i)
using namespace std;
const int N = 2e3 + 5;
int n, step, a[N], id[N][N];

void Enter() {
    cin >> n >> step;
    FOR(i, 1, n) cin >> a[i];
}

vector<long long> solve(int l, int r, int val) {
    if (l > r || val > step) return vector<long long>{0};
    int pos = id[l][r];
    vector<long long> pL = solve(l, pos - 1, a[pos]);
    vector<long long> pR = solve(pos + 1, r, a[pos]);
    vector<long long> Q(pL.size() + pR.size() + 1, 0x3c3c3c3c);
    Q[0] = 0;
    REP(i, 0, pL.size()) REP(j, 0, pR.size())
        Q[i + j + 1] = min(Q[i + j + 1], pL[i] + pR[j] + a[pos] - val);
    while (Q.back() > step) Q.pop_back();
    return Q;
}

void Process() {
    FOR(i, 1, n) {
        int mini = i;
        FOR(j, i, n) {
            if (a[mini] > a[j]) mini = j;
            id[i][j] = mini;
        }
    }
    cout << solve(1, n, 0).size() - 1;
}

int main()
{
    #define file "game"
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    if (fopen(file".inp","r")) {
        freopen(file".inp","r",stdin);
        freopen(file".out","w",stdout);
    }
    Enter();
    Process();
}
