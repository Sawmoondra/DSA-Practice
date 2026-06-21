// LC 207 - Course Schedule


// There are numCourses courses labeled 0 to numCourses - 1. You are given an
// array prerequisites where prerequisites[i] = [a, b] means you must take
// course b before course a. Return true if you can finish all courses
// (i.e., the prerequisite graph has no cycle), otherwise return false.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    // ---------- Approach 1: DFS (cycle detection via coloring) ----------
    bool canFinishDFS(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        for (auto& p : prerequisites) {
            adj[p[0]].push_back(p[1]); // p[0] depends on p[1]
        }

        // 0 = unvisited, 1 = visiting (in current path), 2 = fully processed
        vector<int> state(numCourses, 0);

        for (int i = 0; i < numCourses; i++) {
            if (state[i] == 0) {
                if (hasCycle(i, adj, state)) return false;
            }
        }
        return true;
    }

    // ---------- Approach 2: BFS (Kahn's algorithm / topological sort) ----------
    bool canFinishBFS(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        for (auto& p : prerequisites) {
            adj[p[1]].push_back(p[0]); // b -> a (b must come before a)
            indegree[p[0]]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        int visited = 0;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            visited++;

            for (int next : adj[curr]) {
                indegree[next]--;
                if (indegree[next] == 0) q.push(next);
            }
        }

        return visited == numCourses;
    }

private:
    bool hasCycle(int node, vector<vector<int>>& adj, vector<int>& state) {
        state[node] = 1; // mark as visiting

        for (int next : adj[node]) {
            if (state[next] == 1) return true;       // back edge -> cycle
            if (state[next] == 0 && hasCycle(next, adj, state)) return true;
        }

        state[node] = 2; // mark as fully processed
        return false;
    }
};

// ---------- Helper to print results ----------
void runTest(int numCourses, vector<vector<int>> prereqs, bool expected, int testNum, bool useBFS) {
    Solution sol;
    bool result = useBFS ? sol.canFinishBFS(numCourses, prereqs) : sol.canFinishDFS(numCourses, prereqs);
    cout << "Test " << testNum << " (" << (useBFS ? "BFS" : "DFS") << "): "
         << (result == expected ? "PASS" : "FAIL")
         << " | expected=" << expected << " got=" << result << endl;
}

int main() {
    // 2 courses, 0 depends on 1 -> no cycle -> true
    vector<vector<int>> p1 = {{0, 1}};

    // 2 courses, 0 depends on 1 and 1 depends on 0 -> cycle -> false
    vector<vector<int>> p2 = {{0, 1}, {1, 0}};

    // 4 courses, linear chain -> true
    vector<vector<int>> p3 = {{1, 0}, {2, 1}, {3, 2}};

    // 4 courses, cycle buried in the middle -> false
    vector<vector<int>> p4 = {{1, 0}, {2, 1}, {3, 2}, {1, 3}};

    // no prerequisites at all -> true
    vector<vector<int>> p5 = {};

    // DFS tests
    runTest(2, p1, true, 1, false);
    runTest(2, p2, false, 2, false);
    runTest(4, p3, true, 3, false);
    runTest(4, p4, false, 4, false);
    runTest(3, p5, true, 5, false);

    // BFS tests
    runTest(2, p1, true, 1, true);
    runTest(2, p2, false, 2, true);
    runTest(4, p3, true, 3, true);
    runTest(4, p4, false, 4, true);
    runTest(3, p5, true, 5, true);

    return 0;
}