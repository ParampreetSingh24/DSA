class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> v = arr;
        sort(v.begin(), v.end());

        unordered_map<int, int> mp;
        int rank = 1;

        for (int x : v)
            if (!mp.count(x))
                mp[x] = rank++;

        for (int &x : arr)
            x = mp[x];

        return arr;
    }
};