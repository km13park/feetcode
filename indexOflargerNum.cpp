#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findIndexNextLarge(vector<int>& vec) {
        vector<int> res(vec.size(), 0);
        stack<pair<int, int>> st;
        st.push({vec[0], 0});
        for (int i=1; i<vec.size(); i++) {
            while (!st.empty() && st.top().first < vec[i]) {
                res[st.top().second] = i;
                st.pop();
            }
            st.push({vec[i], i});
        }
        while (!st.empty()) {
            res[st.top().second] = -1;
            st.pop();
        }
        return res;
    }
};

int main()
{
    vector<int> vec = {3,2,5,6,9,8};
    for (int i=0; i<vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;
    Solution sol;
    vector<int> res;
    res = sol.findIndexNextLarge(vec);

    for (int i=0; i<res.size(); i++)
        cout << res[i] << " ";
    cout << endl;
    return 0;
}