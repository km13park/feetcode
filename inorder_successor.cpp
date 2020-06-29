#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
    TreeNode(int data) : data(data), left(NULL), right(NULL), parent(NULL) {}
};

int minValue(TreeNode* node) {
    while (node->left)
        node = node->left;
    return node->data;
}

int inOrderSuccessor(TreeNode *node) {
    if (node == NULL)
        return -1;
    if (node->right)
        return minValue(node->right);
    TreeNode *p = node->parent;
    while (p) {
        if (node != p->right)
            break;
        node = p;
        p = p->parent;
    }
    return p->data;
}

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->parent = root;
    root->right->parent = root;
    root->left->right = new TreeNode(3);
    root->left->right->parent = root->left;
    root->right->right = new TreeNode(6);
    root->right->right->parent = root->right;

    cout << inOrderSuccessor(root->left->right) << endl;
    cout << inOrderSuccessor(root->right) << endl;
    return 0;
}