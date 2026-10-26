/**
 * EPI Chapter 13 Hash tables
 *
 * 13.6 Find the nearest repeated entries in an array.
 *
 * People do not like reading text in which a word is used multiple times in a
 * short paragraph. Write a program which helps identify such a problem.
 *
 * Write a program which takes as input an array and finds the distance between
 * a closet pair of equal entries.
 *
 * For example, if
 *
 * s = <"All", "work", "and", "no", "play", "makes", "for", "no", "work", "no",
 * "fun", "and", "no", "results">
 *
 * then the second and third occurences of "no" is the closest pair.
 */

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cassert>

using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;


/**
 * Idea: Since we only care about the minimum distance of 2 closest pair of
 * equal entries, we will have a variable min_dist that tracks the minimum
 * distance between any 2 equal entries. We'll also have a hash table that
 * stores the last accessed index for each unique entry.
 *
 * Iterate through the words in the paragraph, keeping track of the min_dist.
 *
 * Time complexity: O(n) provided that there are n words in the paragraph.
 * Space complexity: O(d) where d is the number of distinct entry in the array.
 */
int FindNearestRepeatedEntriesInArray(const vector<string>& paragraph)
{
    int min_dist = std::numeric_limits<int>::max();
    unordered_map<string, size_t> words_indices;

    for (size_t i = 0; i < paragraph.size(); i++) {
        auto it = words_indices.find(paragraph[i]);
        if (it == words_indices.end()) {
            words_indices.emplace(paragraph[i], i);
        } else {
            min_dist = std::min(min_dist, 
                    static_cast<int>(i - words_indices[paragraph[i]]));
            words_indices[paragraph[i]] = i;
        }
    }
    return min_dist;
}

int main()
{
    vector<string> tc1{"All", "work", "and", "no", "play", "makes", "for", 
        "no", "work", "no", "fun", "and", "no", "results"};
    assert(FindNearestRepeatedEntriesInArray(tc1) == 2);

    return 0;
}
