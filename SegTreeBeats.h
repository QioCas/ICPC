// Segment Tree Beats (Cây phân đoạn hai max)
template<class T = int, T starto = -1>
struct stb {
private:
    struct Node {
        T max1 = T(), max2 = starto, cmax = 1, sune = T(), lz = starto;
        Node(T val = T()): max1(val), sune(val) {}
        void setMin(T val) { // Minimize a[i] with val, i: [l, r]
            assert(T(max2) < T(val));
            if(T(max1) <= T(val)) return;
            sune -= (max1 - val) * cmax;
            lz = max1 = val;
        }
        Node operator+ (const Node& P) {
            Node res;
            res.max1 = max(max1, P.max1), res.max2 = max(max2, P.max2);
            res.cmax = 0, res.lz = starto, res.sune = sune + P.sune;
            if(max1 != res.max1) res.max2 = max(res.max2, max1);
            else res.cmax += cmax;
            if(P.max1 != res.max1) res.max2 = max(res.max2, P.max1);
            else res.cmax += P.cmax;
            return res;
        }
    };
    Node it[8 * N];

    void down(int id) {
        if(it[id].lz == starto) return;
        it[id << 1].setMin(it[id].lz);
        it[id << 1 | 1].setMin(it[id].lz);
        it[id].lz = starto;
    }

public:
    void Init(int id, int left, int right, T *a) {
        if(left > right) return;
        if(left == right) return it[id] = Node(a[left]), void();
        int mid = (left + right) >> 1;
        Init(id << 1, left, mid, a);
        Init(id << 1 | 1, mid + 1, right, a);
        it[id] = it[id << 1] + it[id << 1 | 1];
    }
    // Minimize a[i] with c, i: [l, r]
    void UpdateMin(int id, int left, int right, int sta, int endo, T c) {
        if(left > endo or right < sta or it[id].max1 <= c) return;
        if(sta <= left and right <= endo and it[id].max2 < c) return it[id].setMin(c), void();
        down(id);
        int mid = (left + right) >> 1;
        UpdateMin(id << 1, left, mid, sta, endo, c);
        UpdateMin(id << 1 | 1, mid + 1, right, sta, endo, c);
        it[id] = it[id << 1] + it[id << 1 | 1];
    }
    // Return sum of a[i], i: [l, r]
    T GetSum(int id, int left, int right, int sta, int endo) {
        if(left > endo or right < sta) return 0;
        if(sta <= left and right <= endo) return it[id].sune;
        down(id);
        int mid = (left + right) >> 1;
        return GetSum(id << 1, left, mid, sta, endo) + GetSum(id << 1 | 1, mid + 1, right, sta, endo);
    }
    T GetMax(int id, int left, int right, int sta, int endo) {
        if(left > endo or right < sta) return -1;
        if(sta <= left and right <= endo) return it[id].max1;
        down(id);
        int mid = (left + right) >> 1;
        return max(GetMax(id << 1, left, mid, sta, endo), GetMax(id << 1 | 1, mid + 1, right, sta, endo));
    }
};
