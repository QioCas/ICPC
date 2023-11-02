const ll inf = 1LL << 60;
const int N = 100100;

struct Line {
    ll a = 0, b = -inf;
    Line() = default;
    Line(ll a, ll b): a(a), b(b) {}
    ll eval(ll x) {
        return a * x + b;
    }
} IT[N << 2];

void update(int id, int l, int r, int s, int t, Line val) {
    if(l > t || r < s) return;
    int m = (l + r) >> 1;
    if(s <= l && r <= t) {
        if(IT[id].eval(l) >= val.eval(l) && IT[id].eval(r) >= val.eval(r)) return;
        if(IT[id].eval(l) <= val.eval(l) && IT[id].eval(r) <= val.eval(r)) return void(IT[id] = val);
        if(IT[id].eval(l) >= val.eval(l) && IT[id].eval(m) >= val.eval(m)) 
            return update(id << 1 | 1, m + 1, r, s, t, val);
        if(IT[id].eval(l) <= val.eval(l) && IT[id].eval(m) <= val.eval(m)) {
            update(id << 1 | 1, m + 1, r, s, t, IT[id]); IT[id] = val;
            return;
        }
        if(IT[id].eval(m + 1) >= val.eval(m + 1) && IT[id].eval(r) >= val.eval(r))
            return update(id << 1, l, m, s, t, val);

        if(IT[id].eval(m + 1) <= val.eval(m + 1) && IT[id].eval(r) <= val.eval(r)) {
            update(id << 1, l, m, s, t, IT[id]); IT[id] = val;
            return;
        }
    }
    update(id << 1, l, m, s, t, val);
    update(id << 1 | 1, m + 1, r, s, t, val);
}

ll query(int id, int l, int r, int x) {
    if(l > x || r < x) return -inf;
    if(l == r) return IT[id].eval(x);
    int m = (l + r) >> 1;
    return max({IT[id].eval(x), query(id << 1, l, m, x), query(id << 1 | 1, m + 1, r, x)});
}
