// LC 200 - Number of Islands


// Given an m x n 2D binary grid representing a map of '1' (land) and '0' (water),
// return the number of islands. An island is surrounded by water and formed by
// connecting adjacent lands horizontally or vertically.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    // ---------- Approach 1: DFS ----------
    int numIslandsDFS(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int rows = grid.size(), cols = grid[0].size();
        int count = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    count++;
                    dfs(grid, r, c);
                }
            }
        }
        return count;
    }

    // ---------- Approach 2: BFS ----------
    int numIslandsBFS(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int rows = grid.size(), cols = grid[0].size();
        int count = 0;

        vector<vector<int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    count++;
                    grid[r][c] = '0';
                    queue<pair<int,int>> q;
                    q.push({r, c});

                    while (!q.empty()) {
                        auto [cr, cc] = q.front();
                        q.pop();

                        for (auto& d : dirs) {
                            int nr = cr + d[0];
                            int nc = cc + d[1];
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                                grid[nr][nc] = '0';
                                q.push({nr, nc});
                            }
                        }
                    }
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int rows = grid.size(), cols = grid[0].size();

        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1')
            return;

        grid[r][c] = '0'; // mark visited (sink the land)

        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }
};

// ---------- Helper to print results ----------
void runTest(vector<vector<char>> grid, int expected, int testNum, bool useBFS) {
    Solution sol;
    int result = useBFS ? sol.numIslandsBFS(grid) : sol.numIslandsDFS(grid);
    cout << "Test " << testNum << " (" << (useBFS ? "BFS" : "DFS") << "): "
         << (result == expected ? "PASS" : "FAIL")
         << " | expected=" << expected << " got=" << result << endl;
}

int main() {
    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };

    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };

    vector<vector<char>> grid3 = {
        {'0','0','0'},
        {'0','0','0'}
    };

    vector<vector<char>> grid4 = {
        {'1'}
    };

    // DFS tests (each call needs a fresh copy since grid is mutated)
    runTest(grid1, 1, 1, false);
    runTest(grid2, 3, 2, false);
    runTest(grid3, 0, 3, false);
    runTest(grid4, 1, 4, false);

    // BFS tests
    runTest(grid1, 1, 1, true);
    runTest(grid2, 3, 2, true);
    runTest(grid3, 0, 3, true);
    runTest(grid4, 1, 4, true);

    return 0;
}
