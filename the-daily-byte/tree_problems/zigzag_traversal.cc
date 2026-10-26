/**
 * The Daily Byte - 06/28/2021
 *
 * Given a binary tree, return its zig-zag level order traversal (i.e. its level
 * order traversal from left to right the first level, right to left the level
 * of the second, etc)
 */

#include <vector>
#include <queue>
#include <cassert>
#include <memory>
#include <utility>
#include <cstdio>
#include <algorithm>

#include "../data_structures/bst_node.h"

using std::vector;
using std::pair;
using std::queue;
using std::make_pair;
using std::make_shared;
using std::shared_ptr;
using std::reverse;

using data_structures::BSTNode;

using pBSTNode = shared_ptr<BSTNode<int>>;

void print_matrix(const vector< vector<int>>& m)
{
    printf("[");
    for (const auto& v : m) {
        printf("[");
        for (const auto& e : v) {
            printf("%d, ", e);
        }
        printf("], ");
    }
    printf("]\n");
}


/**
 * Use level order tree traversal,
 *
 * If the current height is odd, traverse from right to left.
 * If the current height is even, traverse from left to right.
 */
vector< vector<int> > zigzag_level_order(const pBSTNode& tree)
{
    vector< vector<int> > zigzag;

    queue< pair<pBSTNode, int> > q;

    q.emplace(make_pair(tree, 0));

    pair<pBSTNode, int> cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();

        pBSTNode cur_node = cur.first;
        int cur_level = cur.second;

        if (cur_level >= static_cast<int>(zigzag.size())) {
            vector<int> new_level{cur_node->data_};
            zigzag.emplace_back(new_level);
        } else {
            zigzag[cur_level].emplace_back(cur_node->data_);
        }
        /*
         * if (cur_level % 2 == 0) {
         *     if (cur_node->left_ != nullptr) {
         *         q.emplace(make_pair(cur_node->left_, cur_level + 1));
         *     }
         *
         *     if (cur_node->right_ != nullptr) {
         *         q.emplace(make_pair(cur_node->right_, cur_level + 1));
         *     }
         * } else {
         *     if (cur_node->right_ != nullptr) {
         *         q.emplace(make_pair(cur_node->right_, cur_level + 1));
         *     }
         *
         *     if (cur_node->left_ != nullptr) {
         *         q.emplace(make_pair(cur_node->left_, cur_level + 1));
         *     }
         * }
         */

        if (cur_node->left_ != nullptr) {
            q.emplace(make_pair(cur_node->left_, cur_level + 1));
        }

        if (cur_node->right_ != nullptr) {
            q.emplace(make_pair(cur_node->right_, cur_level + 1));
        }
    }

    for (size_t i = 0; i < zigzag.size(); i++) {
        if (i % 2 == 1) reverse(zigzag[i].begin(), zigzag[i].end());
    }

    return zigzag;
}

int main()
{
    // Test case 1.
    pBSTNode tc1_root       (new BSTNode<int>);
    pBSTNode tc1_l          (new BSTNode<int>);
    pBSTNode tc1_r          (new BSTNode<int>);

    tc1_root->data_         = 1;
    tc1_l->data_            = 2;
    tc1_r->data_            = 3;

    tc1_root->left_         = tc1_l;
    tc1_root->right_        = tc1_r;

    vector<vector<int>> tc1_res {{1}, {3, 2}};
    print_matrix(zigzag_level_order(tc1_root));
    // assert(zigzag_level_order(tc1_root) == tc1_res);

    // Test case 2.
    pBSTNode tc2_root       (new BSTNode<int>);
    pBSTNode tc2_l          (new BSTNode<int>);
    pBSTNode tc2_r          (new BSTNode<int>);
    pBSTNode tc2_rl         (new BSTNode<int>);
    pBSTNode tc2_rr         (new BSTNode<int>);

    tc2_root->data_         = 8;
    tc2_l->data_            = 2;
    tc2_r->data_            = 29;
    tc2_rl->data_           = 3;
    tc2_rr->data_           = 9;

    tc2_root->left_         = tc2_l;
    tc2_root->right_        = tc2_r;
    tc2_r->left_            = tc2_rl;
    tc2_r->right_           = tc2_rr;

    vector<vector<int>> tc2_res {{8}, {29, 2}, {3, 9}};
    print_matrix(zigzag_level_order(tc2_root));
    // assert(zigzag_level_order(tc2_root) == tc2_res);

    // Test case 3.
    pBSTNode tc3_root       (new BSTNode<int>);
    pBSTNode tc3_l          (new BSTNode<int>);
    pBSTNode tc3_r          (new BSTNode<int>);
    pBSTNode tc3_lr         (new BSTNode<int>);
    pBSTNode tc3_ll         (new BSTNode<int>);
    pBSTNode tc3_rl         (new BSTNode<int>);
    pBSTNode tc3_rr         (new BSTNode<int>);
    pBSTNode tc3_lll        (new BSTNode<int>);
    pBSTNode tc3_rrr        (new BSTNode<int>);

    tc3_root->data_         = 1;
    tc3_l->data_            = 2;
    tc3_r->data_            = 3;
    tc3_ll->data_           = 4;
    tc3_lr->data_           = 5;
    tc3_rl->data_           = 6;
    tc3_rr->data_           = 7;
    tc3_lll->data_          = 8;
    tc3_rrr->data_          = 9;

    tc3_root->left_         = tc3_l;
    tc3_root->right_        = tc3_r;
    tc3_l->left_            = tc3_ll;
    tc3_l->right_           = tc3_lr;
    tc3_r->left_            = tc3_rl;
    tc3_r->right_           = tc3_rr;
    tc3_ll->left_           = tc3_lll;
    tc3_rr->right_          = tc3_rrr;

    vector<vector<int>> tc3_res {{1}, {3, 2}, {4, 5, 6, 7}, {9, 8}};
    print_matrix(zigzag_level_order(tc3_root));
    // assert(zigzag_level_order(tc3_root) == tc3_res);

    return 0;
}
