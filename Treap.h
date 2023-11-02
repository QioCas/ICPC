mt19937 rd(time(NULL));
int randint(int l, int r) { 
    return uniform_int_distribution<int>(l, r) (rd); 
}
struct Tnode {
    Tnode *l = NULL, *r = NULL;
    char key; bool rev = false;
    int size = 1, prior = 0;
    Tnode(char key = char(), int prior = randint(-1 << 30, 1 << 30)): key(key), prior(prior) {}
};
 
using Pnode = Tnode*;
 
int SIZE(Pnode u) {
    return (u ? u->size : 0);
}
 
Pnode FIX(Pnode u) {
    if(u) u->size = 1 + SIZE(u->l) + SIZE(u->r);
    return u;
}
 
void Down(Pnode t) {
    if(t->rev) {
        swap(t->l, t->r);
        if(t->l) t->l->rev ^= 1;
        if(t->r) t->r->rev ^= 1;
        t->rev ^= 1;
    }
}
 
Pnode merge(Pnode l, Pnode r) {
    if(!l || !r) return (l ? l : r);
    Down(l); Down(r);
    if(l->prior > r->prior) {
        l->r = merge(l->r, r); 
        return FIX(l);
    } else {
        r->l = merge(l, r->l);
        return FIX(r);
    }
}
pair<Pnode, Pnode> split(Pnode t, int k) {
    if(!t) return {NULL, NULL};
    else Down(t);
    Pnode l = NULL, r = NULL;
    if(k <= SIZE(t->l)) tie(l, t->l) = split(t->l, k), r = t;
    else                tie(t->r, r) = split(t->r, k - 1 - SIZE(t->l)), l = t;
    FIX(t);
    return {l, r};
}
 
tuple<Pnode, Pnode, Pnode> split(Pnode t, int u, int v) {
    if(!t) return {NULL, NULL, NULL};
    Pnode l = NULL, m = NULL, r = NULL;
    tie(t, r) = split(t, v + 1);
    tie(l, m) = split(t, u);
    return {l, m, r};
}
 
void DFS(Pnode t) {
    if(!t) return;
    else Down(t);
    DFS(t->l);
    cout << t->key;
    DFS(t->r);
}
 
Pnode root = NULL;
