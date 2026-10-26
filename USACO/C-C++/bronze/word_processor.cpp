/**
 * https://usaco.org/index.php?page=viewproblem2&cpid=987
 */

#include <fstream>
#include <deque>
using namespace std;

int main()
{
    ifstream fin("word.in");
    ofstream fout("word.out");
    int n, k;
    fin >> n >> k;
    deque<string> words;
    for (int i = 0; i < n; i++) {
        string cur_word;
        fin >> cur_word;
        words.push_back(cur_word);
    }

    int chars_left_this_line = k;
    while (!words.empty()) {
        int cur_word_len = static_cast<int>(words.front().size());
        if (cur_word_len <= chars_left_this_line) {
            fout << words.front();
            words.pop_front();
            chars_left_this_line -= cur_word_len;
            if (chars_left_this_line == 0) {
                fout << "\n";
                chars_left_this_line = k;
            } else if (!words.empty() && static_cast<int>(words.front().size()) <= chars_left_this_line) {
                fout << " ";
            }
        } else {
            fout << "\n";
            chars_left_this_line = k;
        }
    }
    return 0;
}
