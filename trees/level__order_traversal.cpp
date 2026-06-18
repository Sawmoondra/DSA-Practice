#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// O(n) time, O(n) space
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            currentLevel.push_back(node->val);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(currentLevel);
    }
    return result;
}

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j != result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i != result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    //       3
    //      / \
    //     9  20
    //        / \
    //       15  7
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    cout << "Test 1: ";
    printResult(levelOrder(root1));
    cout << "Expected: [[3],[9,20],[15,7]]" << endl;

    cout << "Test 2 (empty): ";
    printResult(levelOrder(nullptr));
    cout << "Expected: []" << endl;

    TreeNode* root3 = new TreeNode(1);
    cout << "Test 3 (single node): ";
    printResult(levelOrder(root3));
    cout << "Expected: [[1]]" << endl;

    return 0;
}