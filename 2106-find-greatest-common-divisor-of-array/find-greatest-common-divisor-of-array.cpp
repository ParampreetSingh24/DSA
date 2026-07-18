class Solution {
public:
    int findGCD(vector<int>& nums) {
        int mn = INT_MAX, mx = INT_MIN;

        for (int x : nums) {
            mn = min(mn, x);
            mx = max(mx, x);
        }

        return __gcd(mn, mx);
    }
};