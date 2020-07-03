#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    string create_palindrome(string word) {
        int oddCount = 0;
        char oddChar;
        string center;
        string left;
        
        unordered_map<char, int> map;
        unordered_map<char, int>::iterator it;

        for (int i = 0; i < word.size(); i++) {
            map[word[i]] += 1;
        }
        
        /* check if it's palindormable */
        for (it = map.begin(); it != map.end(); it++) {
            if (it->second % 2 == 1) {
                oddCount += 1;
                oddChar = it->first;
            }

            if (oddCount > 1 || (oddCount == 1 && word.size() % 2 == 0))
                return "";
        }
        
        for (int i = 0; i < map[oddChar]; i++)
            center += oddChar;

        map.erase(oddChar);
        for (it = map.begin(); it != map.end(); it++) {
            for (int i=0; i < it->second / 2; i++)
                left += it->first;
        }
        string right = left;
        reverse(right.begin(), right.end());
        return left + center + right;
    }
};

int main()
{
    Solution sol;
    cout << sol.create_palindrome("abcabc");
}
