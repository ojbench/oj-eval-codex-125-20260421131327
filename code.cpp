// Optimized streaming solution with DSU and fast input
#include <bits/stdc++.h>
using namespace std;

struct FastInput {
    static const size_t BUFSIZE = 1 << 20; // 1MB
    int idx = 0, size = 0;
    char buf[BUFSIZE];
    inline char read() {
        if (idx >= size) {
            size = (int)fread(buf, 1, BUFSIZE, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return buf[idx++];
    }
    template<typename T>
    bool nextInt(T &out) {
        char c = read();
        if (!c) return false;
        while (c != '-' && (c < '0' || c > '9')) { c = read(); if (!c) return false; }
        long long sign = 1; long long val = 0;
        if (c == '-') { sign = -1; c = read(); }
        for (; c >= '0' && c <= '9'; c = read()) val = val * 10 + (c - '0');
        out = (T)(val * sign);
        return true;
    }
} In;

struct DSU {
    vector<int> parent, sz;
    int addNode() {
        int id = (int)parent.size();
        parent.push_back(id);
        sz.push_back(1);
        return id;
    }
    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
};

struct HasherLL {
    size_t operator()(long long x) const noexcept {
        unsigned long long z = (unsigned long long)x + 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        z ^= (z >> 31);
        return (size_t)z;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; if (!In.nextInt(t)) return 0;
    while (t--) {
        int n; In.nextInt(n);
        DSU dsu; dsu.parent.reserve(n * 2 + 8); dsu.sz.reserve(n * 2 + 8);
        unordered_map<long long,int,HasherLL> id;
        id.reserve((size_t)min<long long>(max(1024, n), 2000000));
        vector<pair<int,int>> ineq; ineq.reserve(n);

        auto get_id = [&](long long x) -> int {
            auto it = id.find(x);
            if (it != id.end()) return it->second;
            int nid = dsu.addNode();
            id.emplace(x, nid);
            return nid;
        };

        for (int k = 0; k < n; ++k) {
            long long i, j; int e;
            In.nextInt(i); In.nextInt(j); In.nextInt(e);
            int a = get_id(i), b = get_id(j);
            if (e == 1) dsu.unite(a, b);
            else ineq.emplace_back(a, b);
        }

        bool ok = true;
        for (auto &p : ineq) {
            if (dsu.find(p.first) == dsu.find(p.second)) { ok = false; break; }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
