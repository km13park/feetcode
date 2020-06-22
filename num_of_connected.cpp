#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution {
private:
    int count;
public:
    int num_of_connected(int n, vector<pair<int, int>> edges) {
        count = n;
        vector<int> root(n+1, -1);
        for (int i = 1; i < root.size(); i++) {
            root[i] = i;
        }
        for (auto edge: edges) {
            unions(root, edge.first, edge.second);
        }
        return count;
    }
    int find(vector<int> root, int i) {
        if (root[i] == i)
            return i;
        return find(root, root[i]);
    }
    void unions(vector<int> root, int src, int dst) {
        int srcroot = find(root, src);
        int dstroot = find(root, dst);
        if (srcroot != dstroot) {
            root[srcroot] = dstroot;
            count -= 1;
        }
    }
};

int main()
{
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {4, 1}, {5, 6}};
    Solution sol;
    cout << sol.num_of_connected(6, edges) << endl;
}