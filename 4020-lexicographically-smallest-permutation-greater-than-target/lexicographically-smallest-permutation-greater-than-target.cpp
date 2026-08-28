class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        int n = s.size();
        string prefix;

        int i = 0;

        // Match target as long as possible
        while (i < n && cnt[target[i] - 'a'] > 0) {
            prefix += target[i];
            cnt[target[i] - 'a']--;
            i++;
        }

        // If mismatch occurred, start from i.
        // If complete match occurred, start from n-1.
        int j = min(i, n - 1);

        for (; j >= 0; j--) {

            // For positions that were already matched,
            // remove them from prefix and restore frequency.
            if (j < i) {
                cnt[prefix.back() - 'a']++;
                prefix.pop_back();
            }

            // Find smallest character greater than target[j]
            for (int c = target[j] - 'a' + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = prefix;
                    ans += char('a' + c);
                    cnt[c]--;

                    // Fill remaining positions with smallest characters
                    for (int k = 0; k < 26; k++) {
                        ans += string(cnt[k], char('a' + k));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};