#include <iostream>
#include <vector>
#include <string>
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int v): val(v), left(NULL), right(NULL){}
};

class Solution {
private:
    unordered_map<int, int> hmap;
public:
    void inorder(struct TreeNode* root) {
        if (!root)
            return;
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
    TreeNode* buildTree(vector<int> inorder, vector<int> postorder) {
        for (int i = 0; i < inorder.size(); i++)
            hmap[inorder[i]] = i;
        return dfs(inorder, 0, inorder.size(), postorder, 0, postorder.size());
    }
    TreeNode* dfs(vector<int> inorder, int i, int j, vector<int> postorder, int ii, int jj)
    {
        if (i >= j)
            return NULL;

        TreeNode* root = new TreeNode(postorder[jj-1]);

        int dis = hmap[root->val] - i;

        root->right = dfs(inorder, i + dis + 1, j, postorder, ii + dis, jj - 1);
        root->left = dfs(inorder, i, i + dis, postorder, ii, ii + dis);
        return root;
    }
};

int main() {
    Solution sol;
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    TreeNode* root = sol.buildTree(inorder, postorder);
    sol.inorder(root);
    return 0;
}