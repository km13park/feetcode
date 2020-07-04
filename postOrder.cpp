#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int v): val(v), left(NULL), right(NULL){}
};

struct TreeNode* dfs(vector<int> postorder, int *index, int key, int min, int max)
{
    if (*index < 0)
        return NULL;

    TreeNode* root = NULL;

    if (key < max && key >= min) {
        root = new TreeNode(key);
        *index = *index - 1;
        root->right = dfs(postorder, index, postorder[*index], key, max);
        root->left = dfs(postorder, index, postorder[*index], min, key);
    }
    return root;
}

struct TreeNode* createTree(vector<int> postorder)
{
    int index = postorder.size() - 1;
    return dfs(postorder, &index, postorder[index], INT_MIN, INT_MAX);
}

void preorder(TreeNode* root)
{
    if (!root)
        return;
    preorder(root->left);
    cout << root->val << " ";
    preorder(root->right);
}

int main()
{
    vector<int> postorder = {1, 4, 3, 7, 10, 8, 6};
    TreeNode* root = createTree(postorder);
    preorder(root);
    cout << endl;
}
