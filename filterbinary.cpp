#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>

using namespace std;

#define NUM_OF_ALPHABET 26

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x) : val(x){}
};

TreeNode* filter(TreeNode* tree, int k)
{
    if (tree == NULL)
        return NULL;

    tree->left = filter(tree->left, k);
    tree->right = filter(tree->right, k);

    if (tree->left == NULL && tree->right == NULL) {
        if (tree->val == k) {
            delete tree;
            return NULL;
        }
    }
    return tree;
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
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(2);
    root->right->left = new TreeNode(1);
    TreeNode* root2 = filter(root, 1);
    preorder(root2);
}
