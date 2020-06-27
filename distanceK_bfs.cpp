#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Solution {
public:
    unordered_map<TreeNode*, TreeNode*> parent;
    unordered_set<TreeNode*> visited;
    queue<TreeNode*> q;
    vector<int> ans;

    void findParent(TreeNode* root) {
        if (root == NULL) return;
        if (root->left) {
            parent[root->left] = root;
            findParent(root->left);
        }
        if (root->right) {
            parent[root->right] = root;
            findParent(root->right);
        }
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (root == NULL)
            return {};
        findParent(root);
        q.push(target);

        while (!q.empty() && K>=0) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* cur = q.front(); q.pop();
                visited.insert(cur);
                if (K==0)
                    ans.push_back(cur->val);
                if (!visited.count(cur->left) && cur->left)
                    q.push(cur->left);
                if (!visited.count(cur->right) && cur->right)
                    q.push(cur->right);
                if (!visited.count(parent[cur]) && parent[cur])
                    q.push(parent[cur]);
            }
            K--;
        }
        return ans;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    Solution sol;
    vector<int> ans = sol.distanceK(root, root->left, 2);

    for (auto x: ans)
        cout << x << " ";
    cout << endl;
}