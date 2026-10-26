/**
 * EPI Chapter 14 Sorting
 *
 * 07/31/2021
 * 14.6 Compute the union of intervals.
 *
 * In this problem we consider sets of intervals with integers endpoints;
 * the intervals may be open or closed at either end. We want to compute the
 * union of the intervals in such sets.
 *
 * Design an algorithm that takes as input a set of intervals, and outputs their
 * union expressed as a set of disjoint intervals.
 *
 * Hint: Do a case analysis.
 */

#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>

using std::vector;
using std::max;
using std::min;
using std::sort;

struct Interval;
void PrintIntervals(const vector<Interval>&);

struct Interval
{
    struct EndPoint
    {
        bool operator==(const EndPoint& ep) const
        {
            return val == ep.val && isClosed == ep.isClosed;
        }
        int val;
        bool isClosed;
    };

    bool operator<(const Interval& i) const
    {
        if (start.val != i.start.val) {
            return start.val < i.start.val;
        } else {
            return start.isClosed && !i.start.isClosed;
        }
    }

    bool operator==(const Interval& i) const
    {
        return start == i.start && end == i.end;
    }

    EndPoint start, end;
};

/**
 * Idea: Sort the intervals based on the starting point. Do a case by case
 * merging.
 *
 * 2 intervals intersect iff interval1.end >= interval2.start
 *
 * Time complexity: O(nlogn)
 * Space complexity: O(n)
 */
vector<Interval> UnionOfIntervals(vector<Interval> intervals)
{
    vector<Interval> res;
    sort(intervals.begin(), intervals.end());

    // When do we know 2 intervals intersect?
    // When interval1.end >= interval2.start
    // If interval1.end == interval2.start && (interval1.end.isClosed || interval2.start.isClosed)
    // MergeInterval will have
    // start = min(interval1.start, interval2.start)
    // start.isClosed = interval1.start < interval2.start ? interval1.isClosed : interval2.isClosed.
    //
    // end = max(interval1.end, interval2.end)
    // end.isClosed = interval1.end > interval2.end ? interval1.isClosed : interval2.isClosed.
    //
    //
    //

    // PrintIntervals(intervals);
    
    for (auto interval : intervals) {
        if (res.empty() || res.back().end.val < interval.start.val) {
            // Result interval list is empty or the previous and the next
            // interval don't intersect.
            res.emplace_back(interval);
        } else {
            // Mergeable.
            Interval& prev = res.back();

            // If they share same start point.
            if (prev.start.val == interval.start.val) {
                prev.start.isClosed |= interval.start.isClosed;
            }
            
            
            if (prev.end.val <= interval.end.val) {
                if (prev.end.val == interval.end.val)
                    prev.end.isClosed |= interval.end.isClosed;
                else
                    prev.end.isClosed = interval.end.isClosed;
                prev.end.val = interval.end.val;
            }
        }

        // PrintIntervals(res);
    }

    return res;
}

void PrintIntervals(const vector<Interval>& intervals)
{
    for (const auto& interval : intervals) {
        printf("%d %d %d %d\n", interval.start.val, interval.start.isClosed,
                interval.end.val, interval.end.isClosed);
    }
    printf("\n");
}

int main()
{
    Interval i1 = {{0, false}, {3, false}};
    Interval i2 = {{1, true}, {1, true}};
    Interval i3 = {{3, true}, {4, false}};
    Interval i4 = {{2, true}, {4, true}};
    Interval i5 = {{5, true}, {7, false}};
    Interval i6 = {{7, true}, {8, false}};
    Interval i7 = {{8, true}, {11, false}};
    Interval i8 = {{9, false}, {11, true}};
    Interval i9 = {{12, true}, {14, true}};
    Interval i10 = {{12, false}, {16, true}};
    Interval i11 = {{13, false}, {15, false}};
    Interval i12 = {{16, false}, {17, false}};

    vector<Interval> tc1 = {i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12};

    Interval i_res1 = {{0, false}, {4, true}};
    Interval i_res2 = {{5, true}, {11, true}};
    Interval i_res3 = {{12, true}, {17, false}};

    vector<Interval> tc1_res{i_res1, i_res2, i_res3};
    assert(UnionOfIntervals(tc1) == tc1_res);

    return 0;
 }
