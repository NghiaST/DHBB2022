/// SaoST - Le Huu Nghia - IOI22
#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=(l); i<=(r); ++i)
#define REP(i,l,r) for(int i=(l); i<(r); ++i)
#define FORD(i,r,l) for(int i=(r); i>=(l); --i)
#define REPD(i,r,l) for(int i=(r)-1; i>=(l); --i)
using namespace std;
const int N = 2005;
int m, n, q;
long long a[N][N], it[4][N][N];

void Enter() {
    cin >> m >> n >> q;
    FOR(i, 1, m) FOR(j, 1, n) {
        cin >> a[i][j];
        a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
}

void updatebit(int o, int x, int y, long long val) {
    for(int yy = y; x <= m; x += x&-x)
        for(y = yy; y <= n; y += y&-y)
            it[o][x][y] += val;
}

long long querybit(int o, int x, int y) {
    long long val = 0;
    for(int yy = y; x; x -= x&-x)
        for(y = yy; y; y -= y&-y)
            val += it[o][x][y];
    return val;
}

void updaterec(int x, int y, long long w) {
    updatebit(0, x, y, w);
    updatebit(1, x, y, -w * (y - 1));
    updatebit(2, x, y, -w * (x - 1));
    updatebit(3, x, y, w * (x - 1) * (y - 1));
}

long long queryrec(int x, int y) {
    long long val = a[x][y];
    val += querybit(0, x, y) * x * y;
    val += querybit(1, x, y) * x;
    val += querybit(2, x, y) * y;
    val += querybit(3, x, y);
    return val;
}

void update(int x, int y, int u, int v, long long w) {
    updaterec(x, y, w);
    updaterec(x, v + 1, -w);
    updaterec(u + 1, y, -w);
    updaterec(u + 1, v + 1, w);
}

long long query(int x, int y, int u, int v) {
    return queryrec(u, v) - queryrec(u, y - 1) - queryrec(x - 1, v) + queryrec(x - 1, y - 1);
}

void Process() {
    while (q--) {
        int type, x, y, u, v, w;
        cin >> type >> x >> y >> u >> v;
        if (type == 1) {
            cin >> w;
            update(x, y, u, v, w);
        }
        else {
            cout << query(x, y, u, v) << '\n';
        }
    }
}

int main()
{
    #define file "table"
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    if (fopen(file".inp","r")) {
        freopen(file".inp","r",stdin);
        freopen(file".out","w",stdout);
    }
    Enter();
    Process();
}
