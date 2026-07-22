class SparseTable {
    int n;
    vector<vector<int>> st;
public:
    SparseTable(const vector<int>& nums) : n(nums.size()) {
        if (n == 0) return;
        int max_log = 32 - __builtin_clz(n);
        st.assign(max_log, vector<int>(n));
        for (int i = 0; i < n; ++i) st[0][i] = nums[i];
        for (int i = 1; i < max_log; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) return 0;
        int i = 31 - __builtin_clz(r - l + 1);
        return max(st[i][l], st[i][r - (1 << i) + 1]);
    }
};

class Solution {
    struct Group {
        int start;
        int length;
    };

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int ones = 0;
        for (char c : s) {
            if (c == '1') ones++;
        }

        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex(n, -1);
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, 1});
                }
            }
            zeroGroupIndex[i] = zeroGroups.size() - 1;
        }

        int m = zeroGroups.size();
        vector<int> adjacentSum(max(0, m - 1));
        for (int i = 0; i < m - 1; ++i) {
            adjacentSum[i] = zeroGroups[i].length + zeroGroups[i + 1].length;
        }

        SparseTable st(adjacentSum);
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];

            int leftGroupIdx = zeroGroupIndex[l];
            int rightGroupIdx = zeroGroupIndex[r];

            int firstFull = (s[l] == '0') ? leftGroupIdx + 1 : leftGroupIdx + 1;
            int lastFull = (s[r] == '0') ? rightGroupIdx - 1 : rightGroupIdx;

            int leftPart = 0;
            if (s[l] == '0') {
                leftPart = zeroGroups[leftGroupIdx].length - (l - zeroGroups[leftGroupIdx].start);
            }

            int rightPart = 0;
            if (s[r] == '0') {
                rightPart = r - zeroGroups[rightGroupIdx].start + 1;
            }

            int activeSections = ones;

            if (s[l] == '0' && s[r] == '0' && leftGroupIdx == rightGroupIdx) {
                activeSections = max(activeSections, ones);
            } else if (s[l] == '0' && s[r] == '0' && leftGroupIdx + 1 == rightGroupIdx) {
                activeSections = max(activeSections, ones + leftPart + rightPart);
            } else {
                int startAdj = firstFull;
                int endAdj = lastFull - 1;
                if (startAdj <= endAdj) {
                    activeSections = max(activeSections, ones + st.query(startAdj, endAdj));
                }

                if (s[l] == '0' && leftGroupIdx + 1 <= lastFull) {
                    activeSections = max(activeSections, ones + leftPart + zeroGroups[leftGroupIdx + 1].length);
                }

                if (s[r] == '0' && firstFull <= rightGroupIdx - 1) {
                    activeSections = max(activeSections, ones + rightPart + zeroGroups[rightGroupIdx - 1].length);
                }
            }

            ans.push_back(activeSections);
        }

        return ans;
    }
};