/**
 * EPI Chapter 13 Hash tables
 *
 * 13.7 Find the smallest subarray covering all values
 *
 * When you type keywords in a search engine, the search engine will return
 * results, and each result contains a digest of the web page, i.e., a
 * highlighting within that page of the keywords that you searched for.
 * For example, a search for the keywords "Union" and "save" on a page with
 * the text of the Emancipation Proclamation should return
 *
 * My paramount object in this struggle is to <b><u>save</u> the <u>Union</u>
 * </b>, and is not either to save or to destroy slavery. If I could save the
 * Union without freeing any slave I would do it, and if I could save it by
 * freeing all the slaves I would do it; and if I could save it by freeing some
 * and leaving others alone I would also do that.
 *
 * The digest for this page is the text in boldface, with the keywords
 * underlined for emphasis. It is the shortest substring of the page which
 * contains all the keywords in the search. The problem of computing the digest
 * is abstracted as follows.
 *
 * Write a program which takes an array of strings and a set of strings, and
 * return the indices of the starting and ending index of a shortest subarray
 * of the given array that "covers" the set, i.e., contains all string in the
 * set.
 *
 * Hint: What's the maximum number of minimal subarray that can cover the
 * query? The size of the set.
 */

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using std::string;
using std::vector;
using std::unordered_set;
using std::unordered_map;

struct Indices
{
    bool operator==(const Indices& id) const
    {
        return start == id.start && end == id.end;
    }

    bool operator<(const Indices& id) const
    {
        return this->Distance() < id.Distance();
    }

    Indices(size_t s, size_t e)
        : start(s), end(e)
    {}

    int Distance() const
    {
        return end - start;
    }

    int start;
    int end;
};


void PrintSet(const unordered_set<string>& s)
{
    for (const auto& e : s)
        std::cout << e << " ";
    std::cout << "\n";
}

/**
 * Hash table solution but O(n^2) time complexity.
 *
 * Idea: Growing the subarrays incrementally. Specifically, we can consider
 * all subarrays starting at i in order of increasing length, stopping as soon
 * as the set is covered. Use a hash table to record which strings in the set
 * remain to be covered. Each time we increment the subarray length, we need
 * O(1) time to update the set of remaining strings.
 *
 * Time complexity: O(n^2)
 */
Indices ShortestSubarrayCoveringSetSquare(const vector<string>& text,
        const unordered_set<string>& key_words)
{
    Indices res(-1, -1);
    return res;
}

/**
 * Hash table solution: Same as the O(N^2) solution but optimized.
 *
 * Time complexity: O(n)
 */
Indices ShortestSubarrayCoveringSet(const vector<string>& text, 
        const unordered_set<string>& key_words)
{
    unordered_map<string, int> keywords_to_cover;
    for (const string& keyword : key_words) {
        keywords_to_cover[keyword]++;
    }

    Indices res(-1, -1);
    int i = 0, j = 0, remaining = key_words.size();
    while (j < text.size()) {
        if (keywords_to_cover.count(text[j]) > 0) {
            keywords_to_cover[text[j]]--;
            remaining--;
        }

        while (remaining == 0) {
            if (res.start != -1 && res.Distance() < (j - i)) {
                res.start = i;
                res.end = j;
            }

            // Keep advancing left and give back.
            if (key_words.count(text[i]) != 0) {
                keywords_to_cover[text[i]]++;
                remaining++;
            }
            i++;
        }
        j++;
    }
    return res;
}


/**
 * BF solution: For every subarray of text, check if the subarray covers
 * the whole key_words. The time complexity is O(n^2 s) where n is the
 * size of the text array and s is the size of the set.
 *
 * Time complexity: O(n^3)
 * Space complexity: O(n)
 */
Indices ShortestSubarrayCoveringSetBF(const vector<string>& text,
        const unordered_set<string>& key_words)
{
    Indices res(-1, -1);
    for (size_t i = 0; i < text.size(); i++) {
        for (size_t j = i; j < text.size(); j++) {
            unordered_set<string> subarray_set(text.begin() + i, text.begin() + j + 1);
            bool all = true;
            for (const auto& key_word : key_words) {
                if (subarray_set.find(key_word) == subarray_set.end()) {
                    all = false;
                    break;
                }
            }

            if (all) {
                if (res.Distance() <= 0)
                    res = Indices(i, j);
                else
                    res = std::min(res, Indices(i, j));
            }
        }
    }

    return res;
}

int main()
{
    vector<string> tc1{"My" ,"paramount", "object", "in", "this", "struggle",
        "is", "to", "save", "the", "Union", "and", "is", "not", "either", "to",
        "save", "or", "to", "destroy", "slavery", "If", "I", "could", "save", "the",
        "Union", "without", "freeing", "any", "slave", "I", "would", "do", "it", "and",
        "if", "I", "could", "save", "it", "by", "freeing", "all", "the", "slaves", "I", 
        "would", "do", "it", "and", "if", "I", "could", "save", "it", "by", "freeing",
        "some", "and", "leaving", "others", "alone", "I", "would", "also", "do", "that"};

    unordered_set<string> tc1_set{"Union", "save"};

    assert(ShortestSubarrayCoveringSetBF(tc1, tc1_set) == Indices(8, 10) ||
            ShortestSubarrayCoveringSetBF(tc1, tc1_set) == Indices(24, 26));

    return 0;
}
