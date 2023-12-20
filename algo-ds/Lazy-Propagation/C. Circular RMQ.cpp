    #include "bits/stdc++.h"
    using namespace std;
     
    int main() {
     
        int n;
        scanf("%d", &n);
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
        }
     
        vector<long long> tree(n * 4, 0);
        vector<long long> lazy(n * 4, 0);
     
        auto process = [&](int node) {
            tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        };
     
        auto process_lazy = [&](int node) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
            tree[node * 2] += lazy[node];
            tree[node * 2 + 1] += lazy[node];
            lazy[node] = 0;
        };
     
        function<void(int, int, int)> build = [&](int node, int st, int ed) {
            if (st == ed) {
                tree[node] = v[st];
                return;
            }
            int mid = (st + ed) >> 1;
            build(node * 2, st, mid);
            build(node * 2 + 1, mid + 1, ed);
            process(node);
        };
     
        function<void(int, int, int, int, int, int)> update = [&](int node, int st, int ed, int lf, int rt, int value) {
            if (ed < lf || rt < st) {
                return;
            }
            if (st >= lf and ed <= rt) {
                tree[node] += value;
                lazy[node] += value;
                return;
            }
            if (lazy[node]) {
                process_lazy(node);
            }
            int mid = (st + ed) >> 1;
            update(node * 2, st, mid, lf, rt, value);
            update(node * 2 + 1, mid + 1, ed, lf, rt, value);
            process(node);
        };
     
        const long long int INF = 1e18;
        function<long long(int, int, int, int, int)> query = [&](int node, int st, int ed, int i, int j) {
            if (ed < i || j < st) return INF;
            if (st >= i and ed <= j) return tree[node];
            if (lazy[node]) process_lazy(node);
            int mid = (st + ed) >> 1;
            return min(query(node * 2, st, mid, i, j), query(node * 2 + 1, mid + 1, ed, i, j));
        };
     
        build(1, 0, n - 1);
     
        int q;
        scanf("%d\n", &q);
        while (q--) {
            string str;
            getline(cin, str);
            int cnt = count(str.begin(), str.end(), ' ');
            int L, R, value;
            if (cnt == 1) {
                sscanf(str.c_str(), "%d %d", &L, &R);
                long long ans;
                if (L <= R) {
                    ans = query(1, 0, n - 1, L, R);
                } else {
                    ans = min(query(1, 0, n - 1, L, n - 1), query(1, 0, n - 1, 0, R));
                }
                cout << ans << "\n";
            } else {
                sscanf(str.c_str(), "%d %d %d", &L, &R, &value);
                if (L <= R) {
                    update(1, 0, n - 1, L, R, value);
                } else {
                    update(1, 0, n - 1, L, n - 1, value);
                    update(1, 0, n - 1, 0, R, value);
                }
            }
        }
     
        return 0;
    }
