class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        
        vector<int> suf(n + 1, 0);
        int j = m - 1;
        
        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j]) {
                --j;
            }
            suf[i] = m - 1 - j;
        }
        
        vector<int> ans;
        int p = 0, mismatches = 0;
        
        for (int i = 0; i < n && p < m; ++i) {
            if (word1[i] == word2[p]) {
                ans.push_back(i);
                ++p;
            } else if (mismatches == 0 && suf[i + 1] >= m - p - 1) {
                ans.push_back(i);
                ++p;
                mismatches = 1;
            }
        }
        
        if (p == m) return ans;
        return {};
    }
};