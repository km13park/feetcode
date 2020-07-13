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
public:
    vector<int> list_cousins(TreeNode* root, int val) {
        int flag = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i=0; i < size; i++) {
                TreeNode* tmp = q.front(); q.pop();
                if ((tmp->left && tmp->left->val == val) || (tmp->right && tmp->right->val == val)) {
                    flag = 1;
                }
                else {
                    if (tmp->left) q.push(tmp->left);
                    if (tmp->right) q.push(tmp->right);
                }
            }
            if (flag) {
                vector<int> res;
                int qsize = q.size();
                for (int i = 0; i < qsize; i++) {
                    res.push_back(q.front()->val);
                    q.pop();
                }
                return res;
            }
        }
        return {};
    }
};

int main() {
    struct TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(6);
    root->right->right = new TreeNode(5);
    vector<int> res;
    Solution sol;
    res = sol.list_cousins(root, 5);
    for (auto x: res)
        cout << x << " ";
}