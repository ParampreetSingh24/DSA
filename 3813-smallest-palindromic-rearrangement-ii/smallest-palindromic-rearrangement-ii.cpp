class Solution {
public:
    using ll = long long;
    const ll LIM = 1000000;

    ll countWays(vector<int>& cnt, int rem) {
        ll res = 1;
        int left = rem;
        for (int c : cnt) {
            if (!c) continue;
            ll cur = 1;
            for (int i = 1; i <= c; i++) {
                cur = min(LIM + 1, cur * (left - c + i) / i);
            }
            res = min(LIM + 1, res * cur);
            left -= c;
            if (res > LIM) return LIM + 1;
        }
        return res;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> half(26, 0);
        string mid = "";
        int m = 0;
        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            m += half[i];
            if (freq[i] & 1) mid.push_back(char('a' + i));
        }

        if (countWays(half, m) < k) return "";

        string left = "";
        for (int pos = 0; pos < m; pos++) {
            for (int c = 0; c < 26; c++) {
                if (!half[c]) continue;
                half[c]--;
                ll ways = countWays(half, m - pos - 1);
                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }
                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());
        return left + mid + right;
    }
};