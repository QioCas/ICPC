
// Maxflow

template<class S> struct flow_network {
  private:
    int _n;
    template<class T> struct edge { int to, rev; T f, c; };

    vector<vector<edge<S>>> g;
    vector<S> xs;
    vector<stack<int>> ovfl;
    vector<int> h, cnt_h;
    vector<edge<S> *> cur;
  public:
    flow_network() : _n(0) {}
    flow_network(int n) : _n(n), g(n), xs(n), 
        ovfl(n << 1), h(n), cnt_h(n << 1), cur(n) {}

    void add_edge(int u, int v, S cap, S rcap = S(0)) {
        assert(0 <= u && u < _n && 0 <= v && v < _n);
        assert(S(0) <= cap);
        if (u == v) return;
        g[u].push_back({v, sz(g[v]), 0, cap});
        g[v].push_back({u, sz(g[u]) - 1, 0, rcap});
    }

    void push(edge<S> &e, S delta) {
        edge<S> &r = g[e.to][e.rev];
        if (!xs[e.to] && delta) ovfl[h[e.to]].push(e.to);
        e.f += delta, e.c -= delta, xs[e.to] += delta;
        r.f -= delta, r.c += delta, xs[r.to] -= delta;
    }

    S calc(int s, int t) {
        assert(0 <= s && s < _n && 0 <= t && t < _n);
        h[s] = _n, xs[t] = 1, cnt_h[0] = _n - 1;
        for (int i = 0; i < _n; i++) cur[i] = g[i].data();
        for (auto &e : g[s]) push(e, e.c);

        for (int cur_h = 0;;) {
            while (ovfl[cur_h].empty()) if (!cur_h--) return -xs[s];
            int u = ovfl[cur_h].top(); ovfl[cur_h].pop();

            while (xs[u] > 0) { // discharge u
                if (cur[u] == g[u].data() + sz(g[u])) {
                    h[u] = (_n << 1);
                    for (auto &e : g[u]) if (e.c && h[u] > h[e.to] + 1)
                        h[u] = h[e.to] + 1, cur[u] = &e;
                    if (++cnt_h[h[u]], !--cnt_h[cur_h] && cur_h)
                        for (int i = 0; i < _n; i++)
                            if (cur_h < h[i] && h[i] < _n)
                                cnt_h[h[i]]--, h[i] = _n + 1;
                    cur_h = h[u];
                } else if (cur[u]->c && h[u] == h[cur[u]->to] + 1)
                    push(*cur[u], min(xs[u], cur[u]->c));
                else ++cur[u];
            }
        }
    }

    bool left_of_min_cut(int u) { return h[u] >= _n; }
};

