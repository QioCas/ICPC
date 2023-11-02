
// Manhattan MST

struct pt {
    long long x, y;
    pt() {}
    pt(long long _x, long long _y) : x(_x), y(_y) {}
};

struct edge {
    int u, v; long long c;
    edge() {}
    edge(int _u, int _v, long long _c) : u(_u), v(_v), c(_c) {}
    bool operator<(const edge &rhs) const { return c < rhs.c; }
};
    
struct disjoint_set {
    vector<int> rt, rnk;
    disjoint_set(int _sz) : rt(_sz + 1), rnk(_sz + 1, 1) { iota(all(rt), 0); }
    int find(int x) { return (x == rt[x] ? x : rt[x] = find(rt[x])); }
    bool unite(int u, int v) {
        u = find(u), v = find(v); if (u == v) return false;
        if (rnk[u] < rnk[v]) swap(u, v);
        return rt[v] = u, rnk[u] += rnk[v], true;
    }
};

vector<edge> manhattan_mst(vector<pt> arr) {
    vector<edge> res1;
    vector<int> idx(arr.size()); iota(all(idx), 0);
    for (int dir = 0; dir < 4; dir++) {
        for (auto &it : arr) {
            if (dir & 1) swap(it.x, it.y);
            else if (dir == 2) it.x = -it.x;
        }
        sort(all(idx), [&arr](int u, int v) { return arr[u].x - arr[v].x < arr[v].y - arr[u].y; });

        map<long long, int> mp;
        for (int u : idx) {
            for (auto it = mp.lower_bound(-arr[u].y); it != mp.end(); it = mp.erase(it)) {
                int v = it->second;
                if (arr[u].x - arr[v].x < arr[u].y - arr[v].y) break;
                res1.emplace_back(u, v, arr[u].x - arr[v].x + arr[u].y - arr[v].y);
            }
            mp.emplace(-arr[u].y, u);
        }
    }

    sort(all(res1));
    disjoint_set conn(res1.size());
    vector<edge> res2;
    for (auto e : res1) if (conn.unite(e.u, e.v)) res2.push_back(e);
    return res2;
}
