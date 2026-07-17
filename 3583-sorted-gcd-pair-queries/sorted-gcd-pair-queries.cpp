class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {

        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1);

        for (int x : nums)
            freq[x]++;

        vector<long long> divisible(mx + 1);

        for (int g = 1; g <= mx; g++) {
            for (int j = g; j <= mx; j += g)
                divisible[g] += freq[j];
        }

        vector<long long> exact(mx + 1);

        for (int g = mx; g >= 1; g--) {

            exact[g] = divisible[g] * (divisible[g] - 1) / 2;

            for (int j = 2 * g; j <= mx; j += g)
                exact[g] -= exact[j];
        }

        vector<long long> prefix(mx + 1);

        for (int g = 1; g <= mx; g++)
            prefix[g] = prefix[g - 1] + exact[g];

        vector<int> ans;

        for (long long q : queries) {

            int g = lower_bound(prefix.begin() + 1,
                                prefix.end(),
                                q + 1) - prefix.begin();

            ans.push_back(g);
        }

        return ans;
    }
};