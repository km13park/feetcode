#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

int maxIndexDiff(vector<int> arr)
{
    int res = -1;
    int size = arr.size();
    vector<int> L(size, 0);
    vector<int> R(size, 0);
    L[0] = arr[0];
    R[size-1] = arr[size-1];

    for (int i = 1; i < arr.size(); i++) {
        L[i] = min(L[i-1], arr[i]);
    }

    for (int i = size - 2; i >= 0; i--) {
        R[i] = max(R[i+1], arr[i]);
    }

    int i = 0;
    int j = 0;
    while (i < size && j < size) {
        if (L[i] < R[j]) {
            res = max(res, j - i);
            j++;
        }
        else {
            i++;
        }
    }
    return res;
}

int main()
{
    vector<int> arr = {34, 8, 10, 3, 2, 80, 30, 33, 1};
    cout << "ans: " << maxIndexDiff(arr) << endl;
    vector<int> arr2 = {5,4,3,2,1};
    cout << "ans: " << maxIndexDiff(arr2);
}
