// Strings 
vector<int> kmp(const string &s) {
    int _n = (int)s.size();
    vector<int> ret = vector<int>(_n);
    for (int i = 1, j = 0; i < _n; i++) {
        while (j && s[i] != s[j]) j = ret[j - 1];
        if (s[i] == s[j]) j++;
        ret[i] = j;
    }
    return ret;
}

vector<int> Z(const string &s) {
    int _n = (int)s.size();
    vector<int> ret = vector<int>(_n);
    for (int i = 1, l = 0, r = 0; i < _n; i++) {
        if (i <= r) ret[i] = min(ret[i - l], r - i + 1);
        while (i + ret[i] < _n && s[ret[i]] == s[i + ret[i]]) ret[i]++;
        if (i + ret[i] - 1 > r) l = i, r = i + ret[i] - 1;
    }
    return ret;
}

array<vector<int>, 2> manacher(const string &s) {
    int n = (int)s.size();
    array<vector<int>, 2> p = {vector<int>(n), vector<int>(n)};
    for (int z = 0; z < 2; z++) { // z = 0: even, z = 1: odd
        for (int i = 0, l = 0, r = 0; i < n; i++) { 
            if (i < r) p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
            if(R > r) l = L, r = R;
        }
        if (z) for (int i = 0; i < n; i++) p[z][i]++;
    }
    return p;
}
