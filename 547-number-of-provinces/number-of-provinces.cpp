class Solution {
private:
    void dfs(int nd, vector<int> adj[], vector<int> &vs) {
        vs[nd] = 1;
        for (auto it : adj[nd]) {
            if (!vs[it]) {
                dfs(it, adj, vs);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int v = isConnected.size();
        vector<int> vL[v];

        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (isConnected[i][j] && i != j) {
                    vL[i].push_back(j);
                }
            }
        }

        vector<int> vs(v, 0);
        int cnt = 0;

        for (int i = 0; i < v; i++) {
            if (!vs[i]) {
                cnt++;
                dfs(i, vL, vs);
            }
        }

        return cnt;
    }
};