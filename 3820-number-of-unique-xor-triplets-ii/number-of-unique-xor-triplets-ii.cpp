class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int LOG = 11;
        const int M = 1 << LOG;
        
        vector<bool> present(M, false);
        for (int x : nums) present[x] = true;
        
        vector<int> vals;
        for (int i = 0; i < M; i++) if (present[i]) vals.push_back(i);
        
        bitset<2048> pairXor;
        pairXor[0] = 1;
        
        int sz = vals.size();
        for (int i = 0; i < sz; i++) {
            for (int j = i; j < sz; j++) {
                pairXor[vals[i] ^ vals[j]] = 1;
            }
        }
        
        bitset<2048> result;
        for (int v : vals) {
            for (int x = 0; x < M; x++) {
                if (pairXor[x]) result[x ^ v] = 1;
            }
        }
        
        return result.count();
    }
};