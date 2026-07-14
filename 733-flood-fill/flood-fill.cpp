class Solution {
public:
    void dfs(int sr, int sc, vector<vector<int>> &rs, vector<vector<int>> &image,
             int color, int dr[], int dc[], int ic) {
        rs[sr][sc] = color;
        int n = image.size();
        int m = image[0].size();

        for (int i = 0; i < 4; i++) {
            int nr = sr + dr[i];
            int nc = sc + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                image[nr][nc] == ic && rs[nr][nc] != color) {
                dfs(nr, nc, rs, image, color, dr, dc, ic);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (image[sr][sc] == color)
            return image;

        vector<vector<int>> rs = image;

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        int ic = image[sr][sc];

        dfs(sr, sc, rs, image, color, dr, dc, ic);

        return rs;
    }
};