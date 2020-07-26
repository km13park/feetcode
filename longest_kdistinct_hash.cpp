#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

int longest_kdistinct(string s, int k) {
    map<char, int> map;
    int maxsize = 0;
    string maxstring = "";
    for (int i = 0; i < s.size(); i++) {
        if (map.find(s[i]) == map.end()) {
            if (map.size() == k) {
                map.erase(map.begin());
            }
        }
        map[s[i]] += 1;
        int len = 0;
        string tmp = "";
        for (auto x: map) {
            len += x.second;
            for (int j=0; j < x.second; j++)
                tmp += x.first;
        }
        if (len > maxsize) {
            maxsize = len;
            maxstring = tmp;
        }
    }
    return maxsize;
}

int main()
{
    cout << "ans: " << longest_kdistinct("aabcdefff", 3);
}
