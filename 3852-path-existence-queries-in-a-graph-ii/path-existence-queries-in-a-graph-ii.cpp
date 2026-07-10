class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> a;
        for (int i = 0; i < n; i++) a.push_back({nums[i], i});
        sort(a.begin(), a.end());

        vector<int> pos(n), comp(n);
        for (int i = 0; i < n; i++) pos[a[i].second] = i;

        int id = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first - a[i - 1].first > maxDiff) id++;
            comp[i] = id;
        }

        vector<int> nxt(n);
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j + 1 < n && a[j + 1].first - a[i].first <= maxDiff) j++;
            nxt[i] = j;
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = nxt;
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;
        for (auto &q : queries) {
            int l = pos[q[0]], r = pos[q[1]];
            if (l > r) swap(l, r);

            if (comp[l] != comp[r]) {
                ans.push_back(-1);
                continue;
            }

            if (l == r) {
                ans.push_back(0);
                continue;
            }

            int cur = l;
            int steps = 0;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < r) {
                    cur = up[k][cur];
                    steps += 1 << k;
                }
            }
            ans.push_back(steps + 1);
        }

        return ans;
    }
};