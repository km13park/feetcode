#include <iostream> 
#include <algorithm>
#include <vector>
#include <queue>

using namespace std; 

struct Interval {
	int start;
 	int end;
 	Interval() : start(0), end(0) {}
 	Interval(int s, int e) : start(s), end(e) {}
 };

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
		if (intervals.size() == 0) return 0;
		sort(intervals.begin(), intervals.end(), [](const Interval& i1, const Interval& i2)
		{return i1.start < i2.start;});
		int res = 1;
		priority_queue<int, vector<int>, greater<int>> pq;
		pq.push(intervals[0].end);
		for (int i=1; i<intervals.size(); i++) {
			if (pq.top() > intervals[i].start) {
				res++;
			} else {
				pq.pop();
			}
			pq.push(intervals[i].end);
		}
		return res;
	}
};

int main()
{
	vector<Interval> intervals = {Interval(0, 50), Interval(20, 30), Interval(10, 20)};
	Solution sol;
	cout << sol.minMeetingRooms(intervals) << endl;
}


