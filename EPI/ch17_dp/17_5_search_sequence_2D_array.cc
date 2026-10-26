/**
 * EPI Chapter 17 DP
 *
 * 17.5 Search for a sequence in a 2D array.
 *
 * Suppose you are given a 2D array of integers (the "grid") and a 1D array of
 * integers (the "pattern"). We say the pattern occurs in the grid if it is
 * possible to start from some entry in the grid and traverse adjacent entries
 * in the order specified by the pattern till all entries in the pattern have
 * been visited. The entries adjacent to an entry are the ones directly above,
 * below, to the left, and to the right, assuming they exist. For example, the
 * entries adjacent to (3, 4) are (3, 3), (3, 5), (4, 4), and (5, 4). It is
 * acceptable to visit an entry in the grid more than once.
 *
 * As an example, if the grid is
 *
 * {
 *  {1, 2, 3},
 *  {3, 4, 5},
 *  {5, 6, 7}
 * }
 *
 * and the pattern is {1, 3, 4, 6}, then the pattern occurs in the grid -
 * consider the entries {{0,0}, {1,0}, {1,1}, {2,1}}. However, {1, 2, 3, 4}
 * does not occur in the grid.
 *
 * Write a program that takes as arguments a 2D array and a 1D array, and
 * checks whether the 1D array occurs in the 2D array.
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <array>
#include <tuple>
#include <unordered_set>

using std::vector;
using std::array;
using std::tuple;
using std::hash;
using std::get;
using std::unordered_set;

const array<array<int, 2>, 4> kDirections{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

/**
 * Idea: Similar to depth first search.
 *
 * Time complexity: O(nm)
 * Space complexity: O(nm)
 */

bool IsMovable(const vector<vector<int>>& grid, int row, int col, int pattern_element)
{
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    return !(row < 0 || row >= n || col < 0 || col >= m || 
            grid[row][col] != pattern_element);
}

bool DirectedContainsPattern(const vector<vector<int>>& grid, 
        const vector<int>& pattern, int idx, int row, int col)
{
    if (idx >= pattern.size()) {
        return true;
    } else {
        // Constraint: The adjacent cell (repeatable) must match the next
        // element in the sequence.
        // Choice: Check other adjacent cells, we proceed if it equals the next
        // element in the pattern.
        // Goal: idx == pattern.size().
        if (IsMovable(grid, row, col, pattern[idx])) {
            for (const auto& d : kDirections) {
                if (DirectedContainsPattern(grid, pattern, idx+1, row+d[0], col+d[1]))
                    return true;
            }
        }
        return false;
    }
}

bool ContainsPattern(const vector<vector<int>>& grid, const vector<int>& pattern)
{
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (pattern[0] == grid[i][j]) {
                if (DirectedContainsPattern(grid, pattern, 0, i, j))
                    return true;
            }
        }
    }
    return false;
}

/// EPI Solution
struct HashTuple {
    size_t operator()(const tuple<int, int, int>& t) const {
        // (x, y, z)
        // Hash function: x ^ y * prime[172] ^ z * prime[82025]
        return hash<int>()(get<0>(t) ^ get<1>(t) * 1021 ^ get<2>(t) * 1048573);
    }
};

bool IsPatternSuffixContainedStartingAtXY(
        const vector<vector<int>>& grid, int x, int y, const vector<int>& pattern,
        int offset,
        unordered_set<tuple<int, int, int>, HashTuple>& previous_attempts
        )
{
    if (pattern.size() == offset) {
        // Nothing left to complete.
        return true;
    }

    // Check if (x, y) lies outside the grid.
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size() ||
            previous_attempts.find({x, y, offset}) != previous_attempts.cend())
        return false;

    if (grid[x][y] == pattern[offset] &&
        (IsPatternSuffixContainedStartingAtXY(grid, x-1, y, pattern, offset+1, previous_attempts) ||
         IsPatternSuffixContainedStartingAtXY(grid, x+1, y, pattern, offset+1, previous_attempts) ||
         IsPatternSuffixContainedStartingAtXY(grid, x, y-1, pattern, offset+1, previous_attempts) ||
         IsPatternSuffixContainedStartingAtXY(grid, x, y+1, pattern, offset+1, previous_attempts)))
        return true;
    previous_attempts.emplace(x, y, offset);
    return false;
}

bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                                const vector<int>& pattern)
{
    // Each entry in previous_attempts is a point in the grid and suffix
    // of pattern (identified by its offset). Presence in previous_attempts
    // indicates the suffix is not contained in the grid starting from that
    // point.
    unordered_set<tuple<int, int, int>, HashTuple> previous_attempts;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (IsPatternSuffixContainedStartingAtXY(grid, i, j, pattern, 0, previous_attempts))
                return true;
        }
    }
    return false;
}

int main()
{
    vector<vector<int>> tc1{
        {1, 2, 3},
        {3, 4, 5},
        {5, 6, 7}
    };

    vector<int> tc1_p1{1, 3, 4, 6};
    vector<int> tc1_p2{1,2,3,4};

    assert(ContainsPattern(tc1, tc1_p1));
    assert(!ContainsPattern(tc1, tc1_p2));


    vector<vector<int>> tc2{
        {1,2}
    };

    vector<int> tc2_p1{1,2,1,2,1};
    vector<int> tc2_p2{1,2,2};
    
    assert(ContainsPattern(tc2, tc2_p1));
    assert(!ContainsPattern(tc2, tc2_p2));
    return 0;
}
