#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string trim(string& str)
    {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, last-first+1);
    }
    bool isNumber(string str) {
        if (str == " ")
            return false;
        bool numSeen = false, eSeen = false, dotSeen = false;
        string tmp = str;
        string s = trim(tmp);
          
        for (int i = 0; i < s.length(); i++) {
            if (isdigit(s[i]))
                numSeen = true;
            else if (s[i] == 'e') {
                if (eSeen || !numSeen)
                    return false;
                eSeen = true;
                numSeen = false;
            }
            else if (s[i] == '.') {
                if (dotSeen || eSeen)
                    return false;
                dotSeen = true;
            }
            else if (s[i] == '-' || s[i] == '+') {
                if (i != 0 && s[i-1] != 'e')
                    return false;
            }
            else
                return false;
        }
        return numSeen;
    }
};

int main() {
    string s = "  -90e3   ";
    Solution sol;
    cout << sol.isNumber(s);
    return 0;
}