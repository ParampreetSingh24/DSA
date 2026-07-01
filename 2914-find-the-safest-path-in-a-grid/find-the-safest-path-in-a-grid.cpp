class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int,int>> q;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    dist[i][j]=0;
                    q.push({i,j});
                }
            }
        }
        vector<int> dir={0,1,0,-1,0};
        while(!q.empty()){
            auto [x,y]=q.front(); q.pop();
            for(int k=0;k<4;k++){
                int nx=x+dir[k], ny=y+dir[k+1];
                if(nx>=0 && ny>=0 && nx<n && ny<n && dist[nx][ny]>dist[x][y]+1){
                    dist[nx][ny]=dist[x][y]+1;
                    q.push({nx,ny});
                }
            }
        }
        priority_queue<tuple<int,int,int>> pq;
        vector<vector<int>> best(n, vector<int>(n,-1));
        pq.push({dist[0][0],0,0});
        best[0][0]=dist[0][0];
        while(!pq.empty()){
            auto [sf,x,y]=pq.top(); pq.pop();
            if(x==n-1 && y==n-1) return sf;
            for(int k=0;k<4;k++){
                int nx=x+dir[k], ny=y+dir[k+1];
                if(nx>=0 && ny>=0 && nx<n && ny<n){
                    int nsf=min(sf,dist[nx][ny]);
                    if(nsf>best[nx][ny]){
                        best[nx][ny]=nsf;
                        pq.push({nsf,nx,ny});
                    }
                }
            }
        }
        return 0;
    }
};
