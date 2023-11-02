
// Line Container

inline namespace _LineContainer {
    typedef long long ll;
    const ll LINF = LLONG_MAX;
    bool _Line_Comp;

    struct Line {
        // k is slope, m is intercept, p is intersection point
        mutable ll k, m, p;
        bool operator<(const Line &o) const { return _Line_Comp ? p < o.p : k < o.k; }
    };

    struct LineContainer : multiset<Line> {
        ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
        bool isect(iterator x, iterator y) {
            if (y == end()) return (x->p = LINF, false);
            if (x->k == y->k) x->p = (x->m > y->m ? LINF : -LINF);
            else x->p = div(y->m - x->m, x->k - y->k);
            return (x->p >= y->p);
        }
        void add(ll k, ll m) {
            auto z = insert({k, m, 0}), y = z++, x = y;
            while (isect(y, z)) z = erase(z);
            if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
            while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
        }
        ll query(ll x) {
            assert(!empty());
            _Line_Comp = 1;
            auto l = *lower_bound({0, 0, x});
            _Line_Comp = 0;
            return l.k * x + l.m;
        }
    };
}  // namespace _LineContainer
