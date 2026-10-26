/**
 * EPI Chapter 19 Graphs
 *
 * 19.7 Transform one string to another.
 *
 * Let s and t be strings and D a dictionary, i.e. a set of strings. Define s
 * to produce t if there exists a sequence of strings from the dictionary
 * P = <s0, s1, ..., s_{n-1}> such that the first string is s, the last string
 * is t, and adjacent strings have the same length and differ in exactly one
 * character. The sequence P is called a production sequence. For example,
 * if the dictionary is {bat, cot, dog, dag, dot, cat}, then
 * {cat, cot, dot, dog} is production sequence.
 *
 * Given a dictionary D and 2 strings s and t, write a program to determine if
 * s produces t. Assume that all characters are lowercase alphabets. If s does
 * produce t, output the length of a shortest production sequence; otherwise,
 * output -1.
 *
 * Hint: Treat strings as vertices in an undirected graph, with an edge between
 * u and v iff the corresponding strings differ in one character.
 */

#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <cassert>
#include <iostream>

using std::unordered_set;
using std::vector;
using std::queue;
using std::string;

void PrintVector(const vector<string>& v)
{
    for (const auto& e : v) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}

/**
 * Idea: Treat every string in the dictionary as a vertex in a graph.
 * 2 vertices are connected if 2 corresponding strings differ in only one
 * character. We perform BFS to find the shortest number of steps to transform
 * a string s into t.
 *
 * Time complexity: O(D^2 + D^2) because we need to compare 2 strings if they
 *  differ in only one character.
 * Space complexity: O(D) where D is the size of the dictionary.
 */

bool differOneChar(const string& s, const string& t)
{
    if (s.size() != t.size()) return false;
    int c = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != t[i]) c++;
        if (c > 1) return false;
    }
    return true;
}

int TransformString(unordered_set<string>& D, const string& s, const string& t)
{
    vector<string> path{s};

    queue<vector<string>> q;
    
    q.emplace(path);

    unordered_set<string> visited{s};

    D.erase(s);

    while (!q.empty()) {
        vector<string> p = q.front();
        string curr = p.back();
        q.pop();

        if (curr == t) {
            PrintVector(p);
            return static_cast<int>(p.size());
        }

        // Get all possible strings in the set that differ in only 1 character.
        // Check if it's already visited. If it's not, add it to the queue.
        for (const string& str : D) {
            if (visited.count(str) == 0 && differOneChar(str, curr)) {
                visited.emplace(str);
                vector<string> new_path{p};
                new_path.emplace_back(str);
                q.emplace(new_path);
            }
        }
    }
    
    // There's no transformation between s and t. Output -1.
    return -1;
}

int main()
{
    unordered_set<string> tc{"bat", "cot", "dog", "dag", "dot", "cat"};
    vector<string> tc_path{"cat", "cot", "dot", "dog"};
    assert(TransformString(tc, "cat", "dog") == tc_path.size());
    return 0;
}
