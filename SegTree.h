
// Segment tree

template<class S, S (*op)(S, S), S (*e)()> struct segtree {
  private:
    int _n, _size;
    vector<S> d;
    void pull(int k) { d[k] = op(d[k << 1], d[k << 1 | 1]); }
  public:
    segtree() : segtree(0) {}
    segtree(int n) : segtree(vector<S>(n, e())) {}
    segtree(const vector<S> &v) : _n(sz(v)) {
        _size = (_n == 1 ? 1 : 1 << (32 - __builtin_clz(_n - 1)));
        d = vector<S>(_size << 1, e());
        for (int i = 0; i < _n; i++) d[i + _size] = v[i];
        for (int i = _size - 1; i >= 1; i--) pull(i);
    }

    void replace(int p, S x) {
        assert(0 <= p && p < _n);
        d[p + _size] = x;
        for (p = (p + _size) >> 1; p > 0; p >>= 1) pull(p);
    }

    S query(int p) const {
        assert(0 <= p && p < _n);
        return d[p + _size];
    }

    S query(int l, int r) const { // [l, r)
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        for (l += _size, r += _size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
        }
        return op(sml, smr);
    }

    S query_all() const { return d[1]; }

    template<bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template<class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n); assert(f(e()));
        if (l == _n) return _n;
        l += _size;
        S sm = e(), v;
        do {
            l >>= __builtin_ctz(l);
            if (!f(op(sm, d[l]))) {
                while (l < _size) {
                    l <<= 1, v = op(sm, d[l]);
                    if (f(v)) sm = v, l++;
                }
                return l - _size;
            }
            sm = op(sm, d[l++]);
        } while (l != (l & -l));
        return _n;
    }

    template<bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template<class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n); assert(f(e()));
        if (r == 0) return 0;
        r += _size;
        S sm = e(), v;
        do {
            r--; r >>= __builtin_ctz(~r); if (!r) r = 1;
            if (!f(op(d[r], sm))) {
                while (r < _size) {
                    r = r << 1 | 1, v = op(d[r], sm);
                    if (f(v)) sm = v, r--;
                }
                return r + 1 - _size;
            }
            sm = op(d[r], sm);
        } while (r != (r & -r));
        return 0;
    }
};
