class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> v(n, vector<int>(m, 0));
        vector<vector<int>> d(n, vector<int>(m, 0));
        queue<pair<pair<int, int>, int>> q;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j]==0){
                    q.push({{i,j}, 0});
                    v[i][j]=1;
                }
                else{
                    v[i][j]=0;
                }

            }
        }
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};
        while(!q.empty()){
            int r = q.front().first.first;
            int c = q.front().first.second;
            int di = q.front().second;
            d[r][c]=di;
            q.pop();
            for(int i=0;i<4;i++){
                int nr=r+dr[i];
                int nc = c+dc[i];
                if(nc>=0&&nc<m&&nr>=0&&nr<n&&v[nr][nc]==0){
                    v[nr][nc]=1;
                    q.push({{nr, nc}, di+1});

                }
            }


        }
        return d;
        
    }
};