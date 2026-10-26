/**
 * Implementation of Closest Points agorithm in 2D space.
 * Minimum C++ version: C++11.
 * Author: Minh Bui
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <cassert>

struct Point
{
    Point(float _x, float _y)
        : x(_x), y(_y)
    {}
    Point() = default;
    Point(const Point& p)
        : x(p.x), y(p.y)
    {}
    Point& operator=(const Point& p) = default;
    ~Point() = default;

    bool operator<(const Point& p) const
    {
        if (this->x == p.x) return this->y < p.y;
        return this->x < p.x;
    }

    bool operator==(const Point& p) const
    {
        return this->x == p.x && this->y == p.y;
    }
    
    float x;
    float y;
};

struct CmpX
{
    bool operator()(const Point& p1, const Point& p2)
    {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    }
};

struct CmpY
{
    bool operator()(const Point& p1, const Point& p2)
    {
        return p1.y < p2.y;
    }
};

void PrintPoints(const std::vector<Point>& points)
{
    for (size_t i = 0; i < points.size(); i++) {
        printf("%d %d\n", (int) points[i].x, (int) points[i].y);
    }
}


float EuclideanDistance(const Point& p1, const Point& p2)
{
    return sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float GetMinPoints(const Point& p1, const Point& p2, float& min_dist, std::vector<Point>& result)
{
    float d = EuclideanDistance(p1, p2);
    if (d < min_dist) {
        min_dist = d;
        if (result.empty()) {
            result.push_back(p1);
            result.push_back(p2);
        } else {
            result[0] = p1;
            result[1] = p2;
        }
    }
    return min_dist;
}

float ClosestPointsBF(std::vector<Point>& points, int l, int r, float& min_d, std::vector<Point>& result)
{
    Point p1, p2;
    for (int i = l; i < r; i++) {
        for (int j = i + 1; j < r; j++) {
            min_d = GetMinPoints(points[i], points[j], min_d, result);
        }
    }
    std::sort(begin(points) + l, begin(points) + r, CmpY());
    return min_d;
}


float ClosestHelper(std::vector<Point>& points, int l, int r, float& min_dist, std::vector<Point>& result, std::vector<Point>& tmp)
{
    if (r - l <= 3) {
        min_dist = ClosestPointsBF(points, l, r, min_dist, result);
        return min_dist;
    }

    int m = l + ((r - l) >> 1);
    int mid_x = points[m].x;
    min_dist = ClosestHelper(points, l, m, min_dist, result, tmp);
    min_dist = ClosestHelper(points, m, r, min_dist, result, tmp);

    std::merge(begin(points) + l, begin(points) + m, begin(points) + m, begin(points) + r, begin(tmp), CmpY());
    std::copy(begin(tmp), begin(tmp) + r - l, begin(points) + l);

    int temp_sz = 0;
    for (int i = l; i < r; i++) {
        if (fabs(points[i].x - mid_x) < min_dist) {
            for (int j = temp_sz - 1; j >= 0 && (points[i].y - tmp[j].y) < min_dist; j--) {
                min_dist = GetMinPoints(points[i], tmp[j], min_dist, result);
            }
            tmp[temp_sz++] = points[i];
        }
    }
    return min_dist;
}

bool FloatEquals(float f1, float f2)
{
    return (std::fabs(f1 - f2) <= std::numeric_limits<float>::epsilon() * std::fmax(std::fabs(f1), std::fabs(f2)));
}

float ClosestPoints(std::vector<Point>& points, std::vector<Point>& result)
{
    std::vector<Point> tmp;
    tmp.resize(points.size());

    std::sort(begin(points), end(points), CmpX());
    float min_dist = std::numeric_limits<float>::max();
    ClosestHelper(points, 0, points.size(), min_dist, result, tmp);
    return min_dist;
}

int main()
{
    float x, y;
    std::vector<Point> points;
    while (scanf("%f %f", &x, &y) != EOF) {
        points.emplace_back(Point(x, y));
    }
    
    std::vector<Point> closestPointsBF_result;
    std::vector<Point> closestPointsDiv_result;

    float ddaq = std::numeric_limits<float>::max();
    float dbf = std::numeric_limits<float>::max();

    ClosestPointsBF(points, 0, points.size(), dbf, closestPointsBF_result);
    ddaq = ClosestPoints(points, closestPointsDiv_result);

    assert((closestPointsBF_result == closestPointsDiv_result) || [&]() {
        std::reverse(std::begin(closestPointsBF_result), std::end(closestPointsBF_result));
        return closestPointsBF_result == closestPointsDiv_result;
    }());
    

    assert(FloatEquals(ddaq, dbf));
    printf("Divide and conquer result: %f\n", ddaq);
    PrintPoints(closestPointsDiv_result);
    printf("\n");
    printf("Brute force result: %f\n", dbf);
    PrintPoints(closestPointsBF_result);

    return 0;
}
