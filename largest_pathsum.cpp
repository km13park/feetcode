#include <iostream>
#include <vector>
#include <string>
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
    TreeNode(int val) : val(val), left(NULL), right(NULL), parent(NULL) {}
};

class Solution {
    vector<int> res;
    int maxSum = INT_MIN;
    TreeNode* maxleaf = NULL;
public:
    void maxSumUtil(TreeNode* root, int sum)
    {
        if (root == NULL)
            return;
        sum += root->val;
        if (sum > maxSum && root->left == NULL && root->right == NULL) {
            maxSum = sum;
            maxleaf = root;
        }
        maxSumUtil(root->left, sum);
        maxSumUtil(root->right, sum);
    }
    bool printPath(TreeNode* root, TreeNode* leaf)
    {
        if (root == NULL)
            return false;
        if (root == leaf || printPath(root->left, leaf) || printPath(root->right, leaf)) {
            cout << root->val << " ";
            return true;
        }
        return false;
    }
    void largest_path_sum(TreeNode* root)
    {
        maxSumUtil(root, 0);
        //cout << "maxSum: " << maxSum << endl; 
        printPath(root, maxleaf);
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    Solution sol;
    sol.largest_path_sum(root);
    return 0;
}