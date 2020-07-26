#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

int findTime(vector<int> arr, int k)
{
    int time  = 1;
    unordered_map<int, int> map;
    vector<pair<int, int>> heap;
    for (int i = 0; i < arr.size(); i++) {
        map[arr[i]] += 1;
    }
    unordered_map<int, int>::iterator it;
    for (it = map.begin(); it != map.end(); it++) {
        heap.push_back({it->first, it->second});
    }

    while (heap.size() != 0) {
        vector<pair<int, int>> tmp_list;
        
        for (auto p: heap) {
            auto tmp = heap.back();
            heap.pop_back();

            if (tmp.second == 1) break;
            tmp_list.push_back({tmp.first, tmp.second - 1});
        }
        heap = tmp_list;
        time += k;
    }
    return time;
}

int main()
{
    cout << "ans: " << findTime({1, 2, 1, 1}, 2);
}
