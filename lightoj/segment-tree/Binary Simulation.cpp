#include "bits/stdc++.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        string s;
        cin >> s;
        int n = (int)s.size();
        vector<int> tree(n * 4, 0);

        function<void(int, int, int, int, int)> update = [&](int node, int st, int ed, int i, int j) {
            if (ed < st || ed < i || j < st) return;
            if (st >= i && ed <= j) {
                tree[node]++;
                return;
            }
            int mid = (st + ed) >> 1;
            update(node * 2, st, mid, i, j);
            update(node * 2 + 1, mid + 1, ed, i, j);
        };

        function<int(int, int, int, int)> query = [&](int node, int st, int ed, int pos) {
            if (ed < st) return 0;
            if (st == ed) return tree[node];
            int mid = (st + ed) >> 1;
            return tree[node] + (pos <= mid ? query(node * 2, st, mid, pos) : query(node * 2 + 1, mid + 1, ed, pos));
        };

        cout << "Case " << tc << ":\n";
        int q;
        cin >> q;
        while (q--) {
            char type;
            cin >> type;
            if (type == 'I') {
                int i, j;
                cin >> i >> j;
                update(1, 1, n, i, j);
            } else {
                int pos;
                cin >> pos;
                cout << (query(1, 1, n, pos) & 1 ? (s[pos - 1] - '0') ^ 1 : (s[pos - 1] - '0')) << "\n";
            }
        }
    }

    return 0;
}