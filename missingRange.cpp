#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>

using namespace std;

vector<pair<int, int>> missingRange(vector<int>nums, int low, int high) {
    vector<pair<int, int>> res;
    int prev = low - 1;
    int curr;
    for (int i=0; i<=nums.size(); i++) {
        if (i == nums.size())
            curr = high + 1;
        else
            curr = nums[i];
        if ((curr - prev) >= 2) {
            if ((curr - prev) == 2)
                res.push_back({prev+1, prev+1});
            else
                res.push_back({prev+1, curr-1});
        }
        prev = curr;
    }
    return res;
}

int main()
{
    vector<int> nums = {1,3,5,10};
    vector<pair<int, int>> res = missingRange(nums, 1, 10);
    for (auto x: res) {
        cout << x.first << " " << x.second << endl;
    }
}
