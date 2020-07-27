#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

void swap(vector<int> arr, int *i, int *j)
{
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

vector<int> sortInWave(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i = i + 2) {
        if (i > 0 && arr[i-1] > arr[i]) {
            swap(arr, &arr[i], &arr[i-1]);
        }
        if (i < arr.size() && arr[i] < arr[i+1]) {
            swap(arr, &arr[i], &arr[i+1]);
        }
    }
    return arr;
}

int main()
{
    vector<int> arr = {34, 8, 5, 3, 2, 80, 30, 33, 1};
    vector<int> res = sortInWave(arr);
    for (auto x: res)
        cout << x << " ";
    cout << endl;
}
