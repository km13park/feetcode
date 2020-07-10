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

vector<int> sorting_window_range(vector<int> nums)
{
    vector<int> res;
    int maxvalue, minvalue;
    int size = nums.size();
    int maxindex = size - 1;
    int minindex = 0;

    for (int i = 0; i < size - 1; i++) {
        if (nums[i+1] < nums[i]) {
            minindex = i;
            break;
        }
    }

    for (int i = size - 1; i > 0; i--) {
        if (nums[i] < nums[i-1]) {
            maxindex = i;
            break;
        }
    }

    minvalue = nums[minindex];
    maxvalue = nums[minindex];

    for (int i=minindex+1; i <= maxindex; i++) {
        if (nums[i] < minvalue) {
            minvalue = nums[i];
        }
        if (nums[i] > maxvalue) {
            maxvalue = nums[i];
        }
    }

    for (int i=0; i < minindex; i++) {
        if (nums[i] > minvalue) {
            minindex = i;
            break;
        }
    }

    for (int i=size-1; i > 0; i--) {
        if (nums[i] < maxvalue) {
            maxindex = i;
            break;
        }
    }
    res.push_back(minindex);
    res.push_back(maxindex);
    return res;
}


int main() {
    vector<int> nums = {2, 4, 7, 5, 6, 8, 9};
    vector<int> res = sorting_window_range(nums);
    for (auto x: res)
        cout << x << " ";
    cout << endl;
    return 0;
}