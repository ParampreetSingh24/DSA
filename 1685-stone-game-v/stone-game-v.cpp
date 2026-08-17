class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + stoneValue[i];

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;

                for (int k = l; k < r; k++) {
                    long long left = pref[k + 1] - pref[l];
                    long long right = pref[r + 1] - pref[k + 1];

                    if (left < right) {
                        dp[l][r] = max(dp[l][r],
                                       (int)(left + dp[l][k]));
                    }
                    else if (left > right) {
                        dp[l][r] = max(dp[l][r],
                                       (int)(right + dp[k + 1][r]));
                    }
                    else {
                        dp[l][r] = max(dp[l][r],
                                       (int)(left +
                                       max(dp[l][k], dp[k + 1][r])));
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};