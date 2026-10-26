#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using std::vector;
using std::string;

template <typename T>
void PrintVector(const vector<T>& v) {
    for (const auto& e : v) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}

template <typename T>
void PrintMatrix(const vector<vector<T>>& m) {
    for (const auto& v : m) {
        PrintVector(v);
    }
}

bool DirectedFindWords(vector<vector<char>>& board, const string& word,
                     string& cur_word, int row, int col, int letter_idx) {
        /**
         * Choice: We can go vertically or horizontally to match a letter in a word.
         * Constraints: The same letter cell may not be used more than once in a word.
         * Goal: Match all possible words.
         */
    if (cur_word == word) {
        return true;
    } else {
        int m = board.size();
        int n = board[0].size();
            
        if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] == '.' ||
            letter_idx >= word.size() || board[row][col] != word[letter_idx])
            return false;

        char matching_char = board[row][col];
        board[row][col] = '.';
        cur_word += matching_char;
        int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int k = 0; k < 4; k++) {
            if (DirectedFindWords(board, word, cur_word, row + d[k][0],
                                     col + d[k][1], letter_idx + 1))
            {
                return true;
            }
            cur_word.pop_back();
            board[row][col] = matching_char;
        }
            
        return false;
    }
}
    
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    vector<string> res;
    int m = static_cast<int>(board.size());
    int n = static_cast<int>(board[0].size());
    for (const auto& word : words) {
        bool found = false;
        string cur_word("");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (DirectedFindWords(board, word, cur_word, i, j, 0)) {
                    res.emplace_back(word);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }
    return res;
}

int main()
{
    vector<vector<char>> tc{{'a', 'a'}};
    vector<string> tc_words{"aaa"};
    vector<string> tc_res = findWords(tc, tc_words);
    printf("Size tc_res: %zu\n", tc_res.size());
    return 0;
}
