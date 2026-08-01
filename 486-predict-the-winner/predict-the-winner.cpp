class Solution {
public:
    int dp[21][21];

    int solve(vector<int>& nums, int i, int j) {
        if (i == j) return nums[i];
        if (dp[i][j] != -1) return dp[i][j];

        return dp[i][j] = max(nums[i] - solve(nums, i + 1, j),
                              nums[j] - solve(nums, i, j - 1));
    }

    bool predictTheWinner(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solve(nums, 0, nums.size() - 1) >= 0;
    }
};