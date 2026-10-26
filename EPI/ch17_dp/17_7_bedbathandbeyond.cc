/**
 * EPI Chapter 17 DP
 *
 * Suppose you are designing a search engine. In addition to getting keywords
 * from a page's content, you would like to get keywords from Uniform Resource
 * Locators (URLs). For example, bedbathandbeyond.com yields the keywords
 * "bed, bath, beyond, bat, hand": the first 2 coming from the decomposition
 * "bed bath beyond" and the latter 2 coming from the decomposition "bed bat
 * hand beyond".
 *
 * Given a dictionary, i.e., a set of strings, and a name, design an efficient
 * algorithm that checks whether the name is the concatenation of a sequence of
 * dictionary words. If such a concatenation exists, return it. A dictionary
 * word may appear more than once in the sequence. e.g., "a", "man", "a",
 * "plan", "a", "canal" is a valid sequence for "amanaplanacanal".
 *
 * Hint: Solve the generalized problem, i.e., determine for each prefix of the
 * name whether it is the concatenation of dictionary words.
 */

#include <unordered_set>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <iostream>

using std::unordered_set;
using std::string;
using std::vector;
using std::reverse;
using std::cout;

void PrintWords(const vector<string>& arr)
{
    for (const auto& e : arr)
        printf("%s\n", e.c_str());
}

template <typename T>
void PrintVect(const vector<T>& arr)
{
    for (const auto& e : arr)
        std::cout << e << " ";
    printf("\n");
}

template <typename T>
void PrintMatrix(const vector<vector<T>>& m)
{
    for (const auto& v : m)
        PrintVect(v);
    printf("\n");
}

/**
 * The BF solution: We can try to check if the given name is a substring of
 * every single concatenation of the words from the dictionary.
 * There are an order of 2^n such concatenations, given that we have n
 * words in our dictionary since we can choose to include a string
 * s_i in the concatenation or not. Searching for the name string will take
 * O(L) where L is the maximum possible length of the concatenation.
 * Thus, the time complexity of the BF solution is somewhere around O(L 2^n).
 *
 * It is inefficient because we try to generate all possible concatenations,
 * even for concatenations that are shorter than the given name string.
 *
 * We'll use recursion here. The idea is for every possible prefix, we check
 * if it's in the dictionary and recurse on the rest of the string.
 *
 * Key point: Similar to recursion and backtracking on ways to decompose
 * a string. But the constraint is that each decomposed string has to be in
 * the given dictionary.
 *
 * Time complexity: O(2^n)
 * Space complexity: O(n)
 */
bool DirectedDecomposeIntoDictionaryWordsBF(const string& domain,
        const unordered_set<string>& dictionary, vector<vector<string>>& res, 
        vector<string>& cur, int start)
{
    if (start == static_cast<int>(domain.size())) {
        res.emplace_back(cur);
        return true;
    } else {
        for (int end = start + 1; end <= static_cast<int>(domain.size()); end++) {
            if (dictionary.find(domain.substr(start, end - start)) != dictionary.cend()) {
                cur.emplace_back(domain.substr(start, end - start));
                if (DirectedDecomposeIntoDictionaryWordsBF(domain, dictionary, res, cur, end)) {
                    return true;
                }
                cur.pop_back();
            }
        }

        return false;
    }
}

vector<string> DecomposeIntoDictionaryWordsBF(const string& domain,
        const unordered_set<string>& dictionary)
{
    vector<vector<string>> res;
    vector<string> cur;
    DirectedDecomposeIntoDictionaryWordsBF(domain, dictionary, res, cur, 0);
    PrintMatrix(res);
    return !res.empty() ? res.back() : vector<string>();
}


/**
 * Recursion with memoization: If we observe the recursion tree we can see that
 * there are many overlapping subproblems, we can use a cache to store the
 * results and use these results to construct our solution to the whole
 * problem.
 *
 * We use the prefix of the string as our keys in the cache.
 *
 * Time complexity: O(n^3)
 * Space complexity: O(n)
 */
bool DirectedDecomposeIntoDictionaryWordsCache(const string& domain,
        const unordered_set<string>& dictionary, vector<vector<string>>& res,
        vector<string>& cur, vector<int>& cache, int start)
{
    int n = static_cast<int>(domain.size());
    if (start == n) {
        res.emplace_back(cur);
        return true;
    } else {
        if (cache[start] != -1) {
            return cache[start];
        } else {
            for (int end = start + 1; end <= n; end++) {
                if (dictionary.find(domain.substr(start, end - start)) != dictionary.cend()) {
                    cur.emplace_back(domain.substr(start, end - start));
                    if (DirectedDecomposeIntoDictionaryWordsCache(
                                domain, dictionary, res, cur, cache, end
                                )) {
                        return cache[start] = true;
                    }
                    cur.pop_back();
                }
            }
            return cache[start] = false;
        }
    }
}

vector<string> DecomposeIntoDictionaryWordsCache(const string& domain,
        const unordered_set<string>& dictionary)
{
    vector<vector<string>> res;
    vector<string> cur;
    vector<int> cache(domain.size() + 1, -1);
    DirectedDecomposeIntoDictionaryWordsCache(domain, dictionary, res, cur, cache, 0);
    return !res.empty() ? res.back() : vector<string>();
}


/**
 * Dynamic programming: Bottom-up without relying on recursion.
 *
 * TIme complexity: O(n^3)
 * Space complexity: O(n)
 */
vector<string> DecomposeIntoDictionaryWords(const string& domain, 
        const unordered_set<string>& dictionary)
{
    // When the algorithm finishes, last_length[i] != -1 indicates
    // domain.substr(0, i+1) has a valid decomposition, and the length of
    // the last string in the decomposition is last_length[i].
    vector<int> last_length(domain.size(), -1);
    for (int i = 0; i < domain.size(); i++) {
        // If domain.substr(0, i + 1) is a dictionary word, set last_length[i]
        // to the length of that word.
        if (dictionary.find(domain.substr(0, i + 1)) != dictionary.cend()) {
            last_length[i] = i + 1;
        }
        // If last_length[i] = -1 look for j < i such that domain.substr(0, j+1)
        // has a valid decomposition and domain.substr(j+1,i+1) is a dictionary
        // word. If so, record the length of that word in last_length[i].
        if (last_length[i] == -1) {
            for (int j = 0; j < i; j++) {
                if (last_length[j] != -1 &&
                        dictionary.find(domain.substr(j+1, i-j)) != 
                        dictionary.cend()) {
                    last_length[i] = i - j;
                    break;
                }
            }
        }
    }

    vector<string> decompositions;
    if (last_length.back() != -1) {
        // Domain can be assembled by dictionary words.
        int idx = static_cast<int>(domain.size()) - 1;
        while (idx >= 0) {
            decompositions.emplace_back(domain.substr(
                        idx + 1 - last_length[idx], last_length[idx]
                        ));
            idx -= last_length[idx];
        }

        reverse(decompositions.begin(), decompositions.end());
    }

    return decompositions;
}

int main()
{
    string domain("amanaplanacanal");
    unordered_set<string> dictionary{"a", "man", "plan", "canal"};    
    // PrintWords(DecomposeIntoDictionaryWords(domain, dictionary));
    PrintWords(DecomposeIntoDictionaryWordsBF(domain, dictionary));
    return 0;
}
