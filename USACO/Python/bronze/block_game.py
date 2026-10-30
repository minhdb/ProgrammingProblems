"""
USACO - Block Game

https://usaco.org/index.php?page=viewproblem2&cpid=664
Farmer John is trying to teach his cows to read by giving them a set of N
spelling boards typically used with preschoolers (1≤N≤100). Each board has a
word and an image on each side. For example, one side might have the word
'cat' along with a picture of a cat, and the other side might have the word
'dog' along with a picture of a dog. When the boards are lying on the ground,
N words are therefore shown. By flipping over some of the boards, a different
set of N words can be exposed. To help the cows with their spelling, Farmer
John wants to fashion a number of wooden blocks, each embossed with a single
letter of the alphabet. He wants to make sufficiently many blocks of each
letter so that no matter which set of N words is exposed on the upward-facing
boards, the cows will be able to spell all of these words using the blocks.
For example, if N=3 and the words 'box', 'cat', and 'car' were facing upward,
the cows would need at least one 'b' block, one 'o' block, one 'x' block, two
'c' blocks, two 'a' blocks, one 't' block, and one 'r' block.

Please help the Farmer John determine the minimum number of blocks for each
letter of the alphabet that he needs to provide, so that irrespective of
which face of each board is showing, the cows can spell all N visible words.

INPUT FORMAT (file blocks.in):
Line 1 contains the integer N. The next N lines each contain 2 words
separated by a space, giving the two words on opposite sides of a board. Each
word is a string of at most 10 lowercase letters.

OUTPUT FORMAT (file blocks.out):
Please output 26 lines. The first output line should contain a number
specifying the number of copies of 'a' blocks needed. The next line should
specify the number of 'b' blocks needed, and so on.

SAMPLE INPUT:
3
fox box
dog cat
car bus

SAMPLE OUTPUT:
2
2
2
1
0
1
1
0
0
0
0
0
0
0
2
0
0
1
1
1
1
0
0
1
0
0

In this example, there are N=3 boards, giving 23=8 possibilities for the set
of upward-facing words:

fox dog car fox dog bus fox cat car fox cat bus box dog car box dog bus box
cat car box cat bus We need enough blocks for each letter of the alphabet so
that we can spell all three words, irrespective of which of these eight
scenarios occurs.
"""

def process_word(word, cur_state):
    for c in word:
        cur_state[ord(c) - ord('a')] += 1
    return cur_state

def search(boards, cur_idx, freq, words):
    '''
        Initial solution. This solution will give TLE.
    '''
    if cur_idx == len(boards):
        return freq
    else:
        word1, word2 = boards[cur_idx]
        m1 = search(boards, cur_idx + 1, process_word(word1, freq.copy()), words + [word1])
        m2 = search(boards, cur_idx + 1, process_word(word2, freq.copy()), words + [word2])

        required = freq.copy()
        for i in range(len(m1)):
            required[i] = max(m1[i], m2[i])
        return required

def get_min(boards):
    result = [0] * 26

    if len(boards) != 0:
        result = search(boards, 0, result, [])
    return result

def get_min(boards):
    result = [0] * 26
    if len(boards) != 0:
        for word1, word2 in boards:
            freq_word1 = process_word(word1, [0] * 26)
            freq_word2 = process_word(word2, [0] * 26)

            for i in range(len(result)):
                result[i] += max(freq_word1[i], freq_word2[i])

    return result

boards = []
with open("blocks.in") as f:
    n = int(f.readline())
    for line in f:
        pairs = line.split()
        boards.append(pairs)

result = get_min(boards)

with open("blocks.out", "w") as f:
    for alpha_count in result:
        f.write(f"{alpha_count}\n")
