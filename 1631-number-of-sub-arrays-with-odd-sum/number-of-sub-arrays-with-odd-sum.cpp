class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        constexpr int MOD = 1e9 + 7;long long ans = 0;int cnt[2] = {1, 0};
        int parity = 0;
        for (int num : arr) {
            parity ^= (num & 1);ans += cnt[parity ^ 1];cnt[parity]++;
        }return ans % MOD;
    }
};