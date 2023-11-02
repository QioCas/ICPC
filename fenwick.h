template<class Tp>
struct fenwick {
    fenwick() = default;
    // Construct BIT in range [1, n). 
    fenwick(int n) {
        f.assign(n, 0);
    }

    // a[id] += val.
    void update(int id, Tp val) {
        for(; id < (int) f.size(); id += id&-id)
            f[id] += val;
    }

    // return a[1] + a[2] + ... + a[id].
    Tp query(int id) {
        Tp ret = 0;
        for(; id > 0; id -= id&-id)
            ret += f[id];
        return ret;
    }

    // return a[l] + a[l + 1] + ... + a[r].
    Tp query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Minimum idx st: a[1] + a[2] + ... + a[idx] >= sum.
    int lower_bound(Tp sum) {
        int n = f.size(), i = 0;
        for(int k = 31 - __builtin_clz(n - 1); k >= 0; --k)
            if(i + (1 << k) <= n && f[i + (1 << k)] < sum) sum -= f[i += (1 << k)];
        return i + 1;
    }

    // Minimum idx st: a[1] + a[2] + ... + a[idx] > sum.
    int upper_bound(Tp sum) {
        int n = f.size(), i = 0;
        for(int k = 31 - __builtin_clz(n - 1); k >= 0; --k) 
            if(i + (1 << k) <= n && f[i + (1 << k)] <= sum) sum -= f[i += (1 << k)];
        return i + 1;
    }

private:
    vector<int> f;
};