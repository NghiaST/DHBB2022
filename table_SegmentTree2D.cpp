/// O(MN * log^2 MN)
/** only Segment Tree 2D update + query when
    update 1 cell -> query range
    update range -> query 1 cell
    update range max_value -> query range max_value
    update range add_value -> query range sum_value
*/
/// https://lqdoj.edu.vn/problem/dhbb2022table
#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=(l); i<=(r); ++i)
#define REP(i,l,r) for(int i=(l); i<(r); ++i)
#define FORD(i,r,l) for(int i=(r); i>=(l); --i)
#define REPD(i,r,l) for(int i=(r)-1; i>=(l); --i)
using namespace std;

struct SegmentTree2D {
    int nx, ny;
    vector<vector<long long>> isum, lazy, lazyx, lazyy;
    vector<int> Ux, Uy;
    vector<int> leftx, rightx, lefty, righty;

    void init(int _nx, int _ny) {
        nx = _nx; ny = _ny;
        int sz_x = 1 << (33 - __builtin_clz(nx)), sz_y = 1 << (33 - __builtin_clz(ny));
        isum = lazy = lazyx = lazyy = vector<vector<long long>>(sz_x, vector<long long>(sz_y));
        leftx = rightx = vector<int>(sz_x);
        lefty = righty = vector<int>(sz_y);
        buildlr(leftx, rightx, 0, nx - 1);
        buildlr(lefty, righty, 0, ny - 1);
    }
    void buildlr(vector<int> &left, vector<int> &right, int l, int r, int pos = 1) {
        left[pos] = l; right[pos] = r;
        if (l == r) return;
        int mid = (l + r) / 2;
        buildlr(left, right, l, mid, pos * 2);
        buildlr(left, right, mid + 1, r, pos * 2 + 1);
    }
    void getrange(vector<int> &List, int x, int y, int l, int r, int pos = 1) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) return void(List.push_back(pos));
        int mid = (l + r) / 2;
        getrange(List, x, y, l, mid, pos * 2);
        getrange(List, x, y, mid + 1, r, pos * 2 + 1);
        List.push_back(pos);
    }
    void add(int xl, int xr, int yl, int yr, long long val) {
        Ux.clear();
        Uy.clear();
        getrange(Ux, xl, xr, 0, nx - 1);
        getrange(Uy, yl, yr, 0, ny - 1);
        for(int px : Ux) {
            bool inx = (xl <= leftx[px] && rightx[px] <= xr);
            int rangex = min(xr, rightx[px]) - max(xl, leftx[px]) + 1;
            for(int py : Uy) {
                bool iny = (yl <= lefty[py] && righty[py] <= yr);
                int rangey = min(yr, righty[py]) - max(yl, lefty[py]) + 1;

                isum[px][py] += val * rangex * rangey;
                if (inx == 1 && iny == 1) lazy[px][py] += val;
                else if (inx == 0 && iny == 1) lazyx[px][py] += val * rangex;
                else if (inx == 1 && iny == 0) lazyy[px][py] += val * rangey;
            }
        }
    }
    long long querysum(int xl, int xr, int yl, int yr) {
        Ux.clear();
        Uy.clear();
        getrange(Ux, xl, xr, 0, nx - 1);
        getrange(Uy, yl, yr, 0, ny - 1);
        long long tmp_sum = 0;
        for(int px : Ux) {
            bool inx = (xl <= leftx[px] && rightx[px] <= xr);
            int rangex = min(xr, rightx[px]) - max(xl, leftx[px]) + 1;
            for(int py : Uy) {
                bool iny = (yl <= lefty[py] && righty[py] <= yr);
                int rangey = min(yr, righty[py]) - max(yl, lefty[py]) + 1;

                if (inx == 1 && iny == 1) tmp_sum += isum[px][py];
                else {
                    if (inx == 0 && iny == 1) tmp_sum += lazyy[px][py] * rangex;
                    else if (inx == 1 && iny == 0) tmp_sum += lazyx[px][py] * rangey;
                    tmp_sum += lazy[px][py] * rangex * rangey;
                }
            }
        }
        return tmp_sum;
    }
};

long long a[505][505];

long long querysum(int xl, int xr, int yl, int yr) {
    return a[xr][yr] - a[xl - 1][yr] - a[xr][yl - 1] + a[xl - 1][yl - 1];
}

SegmentTree2D seg;

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int m, n, q;
    cin >> m >> n >> q;
    seg.init(m + 1, n + 1);
    FOR(i, 1, m) FOR(j, 1, n) cin >> a[i][j], a[i][j] += a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1];
    while (q--) {
        int type, xl, xr, yl, yr;
        long long val;
        if (xl>xr) swap(xl,xr); if (yl>yr) swap(yl,yr);
        cin >> type >> xl >> yl >> xr >> yr;
        if (type == 1) cin >> val, seg.add(xl, xr, yl, yr, val);
        else cout << querysum(xl, xr, yl, yr) + seg.querysum(xl, xr, yl, yr) << '\n';
    }
}
