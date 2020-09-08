#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <algorithm>

#define NUM_OF_ALPHA 26

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left = NULL;
	TreeNode* right = NULL;
	TreeNode(int val): val(val), left(NULL), right(NULL){};
};

vector<vector<int> > findAllSeq(TreeNode *ptr)
{
    if (ptr == NULL) {
        vector<int> seq;
        vector<vector<int> > v;
        v.push_back(seq);
        return v;
    }


    if (ptr -> left == NULL && ptr -> right == NULL) {
        vector<int> seq;
        seq.push_back(ptr -> val);
        vector<vector<int> > v;
        v.push_back(seq);
        return v;
    }

    vector<vector<int> > results, left, right;
    left  = findAllSeq(ptr->left);
    right = findAllSeq(ptr->right);
    int size = left[0].size() + right[0].size() + 1;
	cout << "ptr val: " << ptr->val << endl;
	cout << "size: " << size << endl;
    vector<bool> flags(left[0].size(), 0);
    for (int k = 0; k < right[0].size(); k++)
        flags.push_back(1);
	//cout << "left size: " << left[0].size() << endl;
	//cout << "right size: " << right[0].size() << endl;
    for (int i = 0; i < left.size(); i++) {
        for (int j = 0; j < right.size(); j++) {
            do {
                vector<int> tmp(size);
                tmp[0] = ptr->val;
                int l = 0, r = 0;
                for (int k = 0; k < flags.size(); k++) {
                    tmp[k+1] = (flags[k]) ? right[j][r++] : left[i][l++];
                }
                results.push_back(tmp);
            } while (next_permutation(flags.begin(), flags.end()));
        }
    }
    return results;
}

int main()
{
	TreeNode* root = new TreeNode(20);
	root->left = new TreeNode(10);
	root->right = new TreeNode(25);
	root->left->left = new TreeNode(5);
	root->left->right = new TreeNode(15);
	vector<vector<int>> res;
	res = findAllSeq(root);
	for (int i = 0; i < res.size(); i++)
		for (int j=0; j<res[i].size(); j++)
			cout << res[i][j] << " ";
		cout << endl;
}