#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Rectanle {
    int min_x, min_y;
    int max_x, max_y;
    Rectanle(int min_x, int min_y, int max_x, int max_y): min_x(min_x), min_y(min_y), max_x(max_x), max_y(max_y){}
};

int rectangleIntersection(Rectanle* rect1, Rectanle* rect2)
{
    int left = max(rect1->min_x, rect2->min_x);
    int right = min(rect1->max_x, rect2->max_x);
    int top = min(rect1->max_y, rect2->max_y);
    int bottom = max(rect1->min_y, rect2->min_y);

    if (left < right && bottom < top)
        return (right - left) * (top - bottom);
    return 0;
}

int main()
{
    Rectanle rect1(0, 0, 3, 2);
    Rectanle rect2(1, 1, 3, 3);
    cout << rectangleIntersection(&rect1, &rect2) << endl;
}
