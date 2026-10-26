/**
 * Implementation of Convex Hull (Graham Scan) in 2D space.
 * Minimum C++ version: C++98
 * Author: Minh Bui
 */

#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

struct Point
{
    Point(int _x, int _y) : x(_x), y(_y) {}
    float x;
    float y;
};

struct Vect2D
{
    Vect2D(float _x, float _y) : x(_x), y(_y), z(0.0f) {}
    Vect2D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vect2D(const Point& p1, const Point& p2)
        : x(p2.x - p1.x)
        , y(p2.y - p1.y)
        , z(0.0f)
    {}

    Vect2D CrossProduct2D(const Vect2D& v)
    {
        return Vect2D(0.0f, 0.0f, x * v.y - v.x * y);
    }

    float x;
    float y;
    float z;
};


struct CoordinateCmp
{
    bool operator()(const Point& lhs, const Point& rhs) const
    {
        if (lhs.y == rhs.y)
            return lhs.x < rhs.x;
        else
            return lhs.y < rhs.y;
    }
} CoordinateCmp;

struct CrossProductCmp
{
    CrossProductCmp(Point& _p) : p(_p) {}
    bool operator()(const Point& lhs, const Point& rhs) const
    {
        float cpz = Vect2D(p, lhs).CrossProduct2D(Vect2D(p, rhs)).z;
        return cpz > 0;
    }

    Point& p;
};

void PrintPoints(const std::vector<Point>& points)
{
    for (size_t i = 0; i < points.size(); i++) {
        printf("%d %d\n", (int) points[i].x, (int) points[i].y);
    }
}

/**
 * Time complexity: O(nlgn)
 * Space complexity: O(n)
 */
std::vector<Point> ConvexHull(std::vector<Point>& points)
{
    if (points.size() <= 2) return points;

    std::vector<Point> convex_hull_set;

    // Sort the points base on y-coordinate, if there are ties
    // pick the minimum x-coordinate.
    std::sort(points.begin(), points.end(), CoordinateCmp);

    // Aside the first point, sort the remaining points base on its polar
    // angle relative to the first point.
    std::sort(points.begin() + 1, points.end(), CrossProductCmp(points[0]));
    
    std::stack<Point> points_stack;
    points_stack.push(points[0]);
    points_stack.push(points[1]);
    points_stack.push(points[2]);

    for (size_t i = 3; i < points.size(); i++) {
        // If the P_next_top P_top x P_next_top P_new > 0, then P_new
        // is to the left.
        float cpz = 0;
        while (cpz <= 0) {
            Point top_point = points_stack.top();
            points_stack.pop();
            Point next_top_point = points_stack.top();
            points_stack.push(top_point);

            cpz = Vect2D(next_top_point, top_point)
                .CrossProduct2D(Vect2D(next_top_point, points[i])).z;
            if (cpz <= 0) points_stack.pop();
        }

        points_stack.push(points[i]);
    }

    while (!points_stack.empty()) {
        convex_hull_set.push_back(points_stack.top());
        points_stack.pop();
    }
    std::reverse(convex_hull_set.begin(), convex_hull_set.end());
    return convex_hull_set;
}

int main()
{
    float x, y;
    std::vector<Point> points;
    while (scanf("%f %f", &x, &y) != EOF) {
       points.push_back(Point(x, y));
    }

    // ConvexHull(points);
    PrintPoints(ConvexHull(points));

    return 0;
}
