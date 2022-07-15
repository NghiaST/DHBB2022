/// SaoST - Le Huu Nghia - IOI22
#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=(l); i<=(r); ++i)
#define REP(i,l,r) for(int i=(l); i<(r); ++i)
#define FORD(i,r,l) for(int i=(r); i>=(l); --i)
#define REPD(i,r,l) for(int i=(r)-1; i>=(l); --i)
#define getbit(x, i) (((x) >> (i)) & 1)
using namespace std;
const int N = 1e6 + 5, N4 = N * 4, INF = 0x3c3c3c3c;
int n, m, cntx, cnty;
int px[N], py[N], pu[N], pv[N];
int qx[N], qy[N], qu[N], qv[N];
int it[N4 * 4];
int high[N], parent[N], p[N][20], id[N * 2];
vector<int> ADD[N4], REM[N4], ASK[N4];
vector<int> S[N];

void Enter() {
    cin >> n >> m;
    FOR(i, 1, n) cin >> px[i] >> py[i] >> pu[i] >> pv[i];
    FOR(i, 1, m) cin >> qx[i] >> qy[i] >> qu[i] >> qv[i];
}

int Compress(int *arr1, int *arr2, int *arr3, int *arr4) {
    vector<int*> Q;
    FOR(i, 1, n) Q.push_back(&arr1[i]);
    FOR(i, 1, n) Q.push_back(&arr2[i]);
    FOR(i, 1, m) Q.push_back(&arr3[i]);
    FOR(i, 1, m) Q.push_back(&arr4[i]);
    sort(Q.begin(), Q.end(), [] (int *x, int *y) { return *x < *y; });
    int sz = 0, pre_val = INF;
    for(int *v : Q) {
        if (*v != pre_val) sz++, pre_val = *v;
        *v = sz;
    }
    return sz;
}

void Init() {
    cntx = Compress(px, pu, qx, qu);
    cnty = Compress(py, pv, qy, qv);

    FOR(i, 1, n) {
        ADD[px[i]].push_back(i);
        REM[pu[i]].push_back(i);
    }
    FOR(i, 1, m) {
        ASK[qx[i]].push_back(i);
        ASK[qu[i]].push_back(i + m);
    }
}

void update(int x, int y, int val, int l = 1, int r = cnty, int pos = 1) {
    if (x > y || x > r || y < l) return;
    if (x <= l && r <= y) {
        it[pos] = val;
        return;
    }
    if (it[pos] != -1) it[pos * 2] = it[pos * 2 + 1] = it[pos], it[pos] = -1;
    int mid = (l + r) / 2;
    update(x, y, val, l, mid, pos * 2);
    update(x, y, val, mid + 1, r, pos * 2 + 1);
}

int query(int x, int l = 1, int r = cnty, int pos = 1) {
    if (it[pos] != -1) return it[pos];
    int mid = (l + r) / 2;
    if (x <= mid) return query(x, l, mid, pos * 2);
    else return query(x, mid + 1, r, pos * 2 + 1);
}

void DFS(int u) {
    p[u][0] = parent[u];
    REP(i, 1, 20) p[u][i] = p[p[u][i - 1]][i - 1];
    for(int v : S[u]) high[v] = high[u] + 1, DFS(v);
}

int LCA(int u, int v) {
    if (high[u] > high[v]) swap(u, v);
    int diff = high[v] - high[u];
    REPD(i, 20, 0) if (getbit(diff, i)) v = p[v][i];
    if (u == v) return u;
    REPD(i, 20, 0) if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
    return p[u][0];
}

void Process() {
    FOR(i, 1, cntx) {
        for(int u : ADD[i]) {
            parent[u] = query(py[u]);
            update(py[u], pv[u], u);
        }
        for(int u : REM[i]) {
            int v = parent[u];
            update(py[u], pv[u], v);
        }
        for(int u : ASK[i]) {
            if (u <= m) id[u] = query(qy[u]);
            else id[u] = query(qv[u - m]);
        }
    }

    FOR(i, 1, n) S[parent[i]].push_back(i);
    DFS(0);
    FOR(i, 1, m) cout << high[id[i]] + high[id[i + m]] - high[LCA(id[i], id[i + m])] * 2 << '\n';
}

int main()
{
    #define file "archi"
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    if (fopen(file".inp","r")) {
        freopen(file".inp","r",stdin);
        freopen(file".out","w",stdout);
    }
    Enter();
    Init();
    Process();
}
