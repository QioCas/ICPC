// Rabin Miller.

using ull = unsigned long long;

ull mult(ull x, ull y, ull mod) {
    return __int128_t(x) * y % mod;
}

ull powMod(ull x, ull p, ull mod) {
    ull ret = 1;
    for(; p; p >>= 1, x = mult(x, x, mod))
        if(p & 1) ret = mult(ret, x, mod);
    return ret;
}

bool checkMillerRabin(ull x, ull mod, ull s, int k) {
    x = powMod(x, s, mod);
    if (x == 1) return true;
    while(k--) {
        if (x == mod - 1) return true;
        x = mult(x, x, mod);
        if (x == 1) return false;
    }
    return false;
}

bool is_prime(ull x) {
    for(ull z : {2, 3, 5, 7}) 
        if(x % z == 0) return x == z;
    if (x < 121) return x > 1;

    ull s = x - 1;
    int k = 0;

    while (s % 2 == 0) {
        s /= 2;
        k++;
    }

    if (x < 1LL << 32) {
        for (ull z : {2, 7, 61}) {
            if (!checkMillerRabin(z, x, s, k)) return false;
        }
    } else {
        for (ull z : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if (!checkMillerRabin(z, x, s, k)) return false;
        }
    }
    return true;
}
