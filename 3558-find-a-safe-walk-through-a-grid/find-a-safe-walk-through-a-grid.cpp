class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> maxHealth(m, vector<int>(n, -1));
        queue<tuple<int,int,int>> q;
        q.push({0,0,health - grid[0][0]});
        maxHealth[0][0] = health - grid[0][0];
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        while(!q.empty()){
            auto [x,y,h] = q.front(); q.pop();
            if(h <= 0) continue;
            if(x == m-1 && y == n-1 && h >= 1) return true;
            for(auto& d:dirs){
                int nx = x + d[0], ny = y + d[1];
                if(nx>=0 && ny>=0 && nx<m && ny<n){
                    int nh = h - grid[nx][ny];
                    if(nh > maxHealth[nx][ny]){
                        maxHealth[nx][ny] = nh;
                        q.push({nx,ny,nh});
                    }
                }
            }
        }
        return false;
    }
};
