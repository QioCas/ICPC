int n;
// const int N = 200200;
vector<int> G[N];
array<int, 3> E[N];
int low[N], ord[N], id[N], timer = 0, scc = 0;
stack<int> stk;
#define ID(u) (u * 2 - 1)

void push(int u, int v) {
    G[u ^ 1].push_back(v);
    G[v ^ 1].push_back(u);
}

void dfs(int u) {
    low[u] = ord[u] = ++timer;
    stk.push(u);
    for(const int& v : G[u]) {
        if(ord[v]) low[u] = min(low[u], ord[v]);
        else {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if(low[u] == ord[u]) {
        for(++scc; ; ) {
            int v = stk.top(); stk.pop();
            ord[v] = 1 << 30;
            id[v] = scc;
            if(u == v) break;
        }
    }
}

vector<int> TwoSat() {
    for(int i = 0; i <= ID(n); ++i) 
        if(!ord[i]) dfs(i);
    for(int i = 1; i <= ID(n); i += 2) {
        if(id[i] == id[i ^ 1]) return {};
    }
    vector<int> ret;
    for(int i = 1; i <= ID(n); i += 2) {
        if(id[i] < id[i ^ 1]) 
            ret.push_back((i + 1) / 2);
    }

    return ret;
}