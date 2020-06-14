#include <iostream>
#include "Animal.h"
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution {
    vector<int> _rows;
    vector<int> _cols;
    int _diagonal;
    int _rdiagonal;
    int _size;
public:
    Solution(int n) {
        _rows.resize(n, 0);
        _cols.resize(n, 0);
        _diagonal = 0;
        _rdiagonal = 0;
        _size = n;
    }
    int tictactoe(int x, int y, int player) {
        int add;
        if (player == 1)
            add = 1;
        else
            add = -1;
        _rows[x] += add;
        _cols[y] += add;
        if (x == y)
            _diagonal += add;
        else if (x + y == _size - 1) {
            _rdiagonal += add;
        }
        if (abs(_rows[x]) == _size ||
            abs(_cols[y]) == _size ||
            abs(_diagonal) == _size ||
            abs(_rdiagonal) == _size)
            return 1;
        return 0;
    }
};

int main()
{
    Solution sol(3);
    cout << sol.tictactoe(0, 0, 1) << endl;
    cout << sol.tictactoe(0, 2, 2) << endl;;
    cout << sol.tictactoe(2, 2, 1) << endl;
    cout << sol.tictactoe(1, 1, 2) << endl;
    cout << sol.tictactoe(2, 0, 1) << endl;
    cout << sol.tictactoe(1, 0, 2) << endl;
    cout << sol.tictactoe(2, 1, 1) << endl;
}