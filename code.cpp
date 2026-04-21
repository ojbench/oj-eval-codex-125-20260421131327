#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union with path compression and union by size.
struct DSU {
    vector<int> parent, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    // Reserve capacity estimates to reduce rehashing for large inputs
    while (t--) {
        int n; cin >> n;
        vector<tuple<long long,long long,int>> eq, neq;
        eq.reserve(n); neq.reserve(n);
        vector<long long> keys; keys.reserve(2LL * n + 4);
        for (int k = 0; k < n; ++k) {
            long long i, j; int e; cin >> i >> j >> e;
            if (e == 1) eq.emplace_back(i, j, e);
            else neq.emplace_back(i, j, e);
            keys.push_back(i); keys.push_back(j);
        }
        // Coordinate compression on variable ids because ids can be up to 1e9
        sort(keys.begin(), keys.end());
        keys.erase(unique(keys.begin(), keys.end()), keys.end());
        auto idx = [&](long long x) {
            return (int)(lower_bound(keys.begin(), keys.end(), x) - keys.begin());
        };
        DSU dsu((int)keys.size());

        // First apply all equality constraints
        for (auto &tp : eq) {
            long long i, j; int e; tie(i, j, e) = tp;
            dsu.unite(idx(i), idx(j));
        }
        // Then check inequality constraints
        bool ok = true;
        for (auto &tp : neq) {
            long long i, j; int e; tie(i, j, e) = tp;
            if (dsu.find(idx(i)) == dsu.find(idx(j))) { ok = false; break; }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
