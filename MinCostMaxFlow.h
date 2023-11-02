// Mincost-Maxflow

template<class F, class C> struct MCMF {
  private:
    template<class T> bool ckmin(T &u, T v) { return u > v ? (u = v, 1) : 0; }
    struct edge { int v; F flow, cap; C cost; };
    int _n;
    vector<C> p, dist;
    vector<int> prv;
    vector<vector<int>> adj;
    vector<edge> el;

  public:
    MCMF(int n) : _n(n), p(n), dist(n), prv(n), adj(n) {}

    void add_edge(int u, int v, F cap, C cost) {
        assert(cap > 0);
        adj[u].push_back(sz(el)); el.push_back({ v, 0, cap, cost });
        adj[v].push_back(sz(el)); el.push_back({ u, 0, 0, -cost });
    }

    bool path(int s, int t) {
        const C INF = numeric_limits<C>::max();
        fill(all(dist), INF);
        using T = pair<C, int>;
        priority_queue<T, vector<T>, greater<T>> pq; pq.emplace(dist[s] = 0, s);
        while (!pq.empty()) {
            T u = pq.top(); pq.pop();
            if (u.first > dist[u.second]) continue;
            for (auto i : adj[u.second]) {
                const edge &e = el[i];
                if (e.flow < e.cap && 
                ckmin(dist[e.v], u.first + e.cost + p[u.second] - p[e.v]))
                    prv[e.v] = i, pq.emplace(dist[e.v], e.v);
            }
        }
        return dist[t] != INF;
    }

    pair<F, C> calc(int s, int t) {
        assert(s != t);
        for (int i = 0; i < _n; i++) for (int j = 0; j < sz(el); j++) {
            const edge &e = el[j];
            if (e.cap) ckmin(p[e.v], p[el[j ^ 1].v] + e.cost);
        }
        F totFlow = 0;
        C totCost = 0;
        while (path(s, t)) {
            for (int i = 0; i < _n; i++) p[i] += dist[i];
            F df = numeric_limits<F>::max();
            for (int i = t; i != s; i = el[prv[i] ^ 1].v) {
                const edge &e = el[prv[i]];
                ckmin(df, e.cap - e.flow);
            }
            totFlow += df, totCost += (p[t] - p[s]) * df;
            for (int x = t; x != s; x = el[prv[x] ^ 1].v)
                el[prv[x]].flow += df, el[prv[x] ^ 1].flow -= df;
        }
        return { totFlow, totCost };
    }
};
