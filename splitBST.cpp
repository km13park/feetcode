#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<TreeNode*> split_bst(struct TreeNode* root, int val) {
        vector<TreeNode*> res = {NULL, NULL};
        if (root == NULL)
            return res;
        if (root->val <= val) {
            res = split_bst(root->right, val);
            root->right = res[0];
            res[0] = root;
        } else {
            res = split_bst(root->left, val);
            root->left = res[1];
            res[1] = root;
        }
        return res;
    }
};

int main() {
    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(7);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(2);
    root->left->right->right = new TreeNode(4);

    vector<TreeNode*> res = {NULL, NULL};
    Solution sol;
    res = sol.split_bst(root, 2);
    cout << res[0]->val << endl;
    cout << res[1]->val << endl;
}