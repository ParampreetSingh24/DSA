class Solution {
public:
    string makePalindrome(string half, char mid) {
        string rev = half;
        reverse(rev.begin(), rev.end());

        if (mid != '#')
            return half + mid + rev;

        return half + rev;
    }

    string lexPalindromicPermutation(
        string s, string target) {

        int n = s.size();
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        int odd = 0;
        char mid = '#';

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
            cnt[i] /= 2;
        }

        if (odd > 1)
            return "";

        int halfLen = n / 2;
        string prefix;
        int matched = 0;

        while (matched < halfLen &&
               cnt[target[matched] - 'a'] > 0) {

            prefix += target[matched];
            cnt[target[matched] - 'a']--;
            matched++;
        }

        // Complete first half matched
        if (matched == halfLen) {
            string candidate = makePalindrome(prefix, mid);

            if (candidate > target)
                return candidate;

            // n = 1 case: no half character exists to backtrack
            if (halfLen == 0)
                return "";

            matched--;
            cnt[prefix.back() - 'a']++;
            prefix.pop_back();
        }

        // Try increasing from right to left
        for (int j = matched; j >= 0; j--) {
            int x = target[j] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string half = prefix;
                    half += char('a' + c);
                    cnt[c]--;

                    for (int k = 0; k < 26; k++) {
                        half += string(cnt[k], char('a' + k));
                    }

                    return makePalindrome(half, mid);
                }
            }

            if (j > 0) {
                cnt[prefix.back() - 'a']++;
                prefix.pop_back();
            }
        }

        return "";
    }
};