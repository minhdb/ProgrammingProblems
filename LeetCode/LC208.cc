/**
 * Implement Trie (Prefix Tree)
 *
 * A trie or a prefix tree is a tree data structure used to efficiently
 * store and retrieve keys in a dataset of strings. There are various
 * applications of this data structure, such as autocomplete and
 * spellchecker.
 *
 * Implement the trie class.
 *
 * ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 *
 * [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 *
 * Output:
 * [null, null, true, false, true, null, true]
 *
 * Constraints:
 * 1 <= word.length, prefix.length <= 2000
 * word and prefix consist only of lowercase English letters.
 * At most 3 * 10^4 calls in total will be made to insert, search, and
 * startsWith.
 */

#include <memory>
#include <unordered_map>
#include <string>

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::make_shared;

class Trie
{
public:
    struct TrieNode
    {
        TrieNode():children{}, is_word{false} {}

        unordered_map<char, shared_ptr<TrieNode>> children;
        bool is_word;
    };

    Trie() : root{make_shared<TrieNode>()}
    {

    }

    void insert(string word)
    {
        // Go down insert each character into the trie.
        // If the character exists, move down.
        // Otherwise, create a new TrieNode with that character.
        shared_ptr<TrieNode> node = root;
        for (const char& c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = make_shared<TrieNode>();
            }
            node = node->children.at(c);
        }
        node->is_word = true;
    }

    bool search(string word) const
    {
        shared_ptr<TrieNode> node = root;
        for (const char& c : word) {
            if (node->children.find(c) == node->children.end())
                return false;
            node = node->children.at(c);
        }
        return node->is_word;
    }

    bool startsWith(string prefix) const
    {
        shared_ptr<TrieNode> node = root;
        for (const char& c : prefix) {
            if (node->children.find(c) == node->children.end())
                return false;
            node = node->children.at(c);
        }
        return true;
    }

private:
    shared_ptr<TrieNode> root;
};

int main()
{
    /*
     * ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
     *
     * [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
     */
    Trie trie1;
    trie1.insert("apple");
    assert(trie1.search("apple"));

    assert(!trie1.search("app"));
    assert(trie1.startsWith("app"));
    
    trie1.insert("app");
    assert(trie1.search("app"));

    return 0;
}
