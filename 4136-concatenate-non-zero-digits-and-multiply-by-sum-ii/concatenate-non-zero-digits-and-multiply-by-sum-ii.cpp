class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const int MOD = 1000000007;
        int n = s.size();

        vector<int> nzPos;
        vector<int> prefSum(1, 0);

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                nzPos.push_back(i);
                prefSum.push_back(prefSum.back() + (s[i] - '0'));
            }
        }

        int k = nzPos.size();
        vector<long long> pw10(k + 1, 1), prefHash(k + 1, 0);

        for (int i = 0; i < k; i++) {
            pw10[i + 1] = (pw10[i] * 10) % MOD;
            prefHash[i + 1] = (prefHash[i] * 10 + (s[nzPos[i]] - '0')) % MOD;
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int L = lower_bound(nzPos.begin(), nzPos.end(), l) - nzPos.begin();
            int R = upper_bound(nzPos.begin(), nzPos.end(), r) - nzPos.begin();

            if (L == R) {
                ans.push_back(0);
                continue;
            }

            int len = R - L;
            long long x = (prefHash[R] - prefHash[L] * pw10[len] % MOD + MOD) % MOD;
            long long sum = prefSum[R] - prefSum[L];
            ans.push_back(x * sum % MOD);
        }

        return ans;
    }
};