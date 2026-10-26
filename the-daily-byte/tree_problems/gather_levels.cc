/**
 * The Daily Byte 06/24/2021
 *
 * Given a binary tree, return its level order traversal where the nodes in
 * each level are ordered from left to right.
 */

#include "../data_structures/bst_node.h"

#include <vector>
#include <cassert>
#include <cstdio>
#include <memory>
#include <queue>
#include <utility>

using std::vector;
using std::queue;
using std::make_shared;
using std::shared_ptr;
using std::make_pair;
using std::pair;

using data_structures::BSTNode;

using pBSTNode = shared_ptr<BSTNode<int>>;

void print_matrix(const vector< vector<int>>& m )
{
    printf("[");
    for (const auto& r : m) {
        printf("[");
        for (const auto& e : r) {
            printf("%d, ", e);
        }
        printf("], ");
    }
    printf("]\n");
}

vector<vector<int>> gather_levels(pBSTNode& tree)
{
    vector<vector<int>> levels;

    queue<pair<pBSTNode, int>> q;

    q.push(make_pair(tree, 0));

    vector<int> root_level {tree->data_};

    levels.emplace_back(root_level);

    pair<pBSTNode, int> cur_pair;

    pBSTNode cur = nullptr;

    while (!q.empty()) {
        cur_pair = q.front();
        cur = cur_pair.first;
        q.pop();

        if (cur->left_ == nullptr && cur->right_ == nullptr) continue;

        if (cur_pair.second+1 >= static_cast<int>(levels.size())) {
            vector<int> new_level;
            if (cur->left_ != nullptr) {
                new_level.emplace_back(cur->left_->data_);
                q.push(make_pair(cur->left_, cur_pair.second+1));
            }

            if (cur->right_ != nullptr) {
                new_level.emplace_back(cur->right_->data_);
                q.push(make_pair(cur->right_, cur_pair.second+1));
            }

            levels.push_back(new_level);
        } else {
            if (cur->left_ != nullptr) {
                levels[cur_pair.second+1].emplace_back(cur->left_->data_);
                q.push(make_pair(cur->left_, cur_pair.second+1));
            }

            if (cur->right_ != nullptr) {
                levels[cur_pair.second+1].emplace_back(cur->right_->data_);
                q.push(make_pair(cur->right_, cur_pair.second+1));
            }
        }
    }

    return levels;
}

int main()
{
    // Test case 1.
    pBSTNode tc1_root   (new BSTNode<int>);
    pBSTNode tc1_l      (new BSTNode<int>);
    pBSTNode tc1_r      (new BSTNode<int>);

    tc1_root->data_     = 4;
    tc1_l->data_        = 2;
    tc1_r->data_        = 7;

    tc1_root->right_    = tc1_r;
    tc1_root->left_     = tc1_l;

    vector<vector<int>> res1 = gather_levels(tc1_root);
    print_matrix(res1);

    // Test case 2.
    pBSTNode tc2_root   (new BSTNode<int>);
    pBSTNode tc2_l      (new BSTNode<int>);
    pBSTNode tc2_r      (new BSTNode<int>);
    pBSTNode tc2_rr     (new BSTNode<int>);

    tc2_root->data_     = 2;
    tc2_l->data_        = 10;
    tc2_r->data_        = 15;
    tc2_rr->data_       = 20;

    tc2_root->left_     = tc2_l;
    tc2_root->right_    = tc2_r;
    tc2_r->right_       = tc2_rr;

    vector<vector<int>> res2 = gather_levels(tc2_root);
    print_matrix(res2);

    // Test case 3.
    pBSTNode tc3_root   (new BSTNode<int>);
    pBSTNode tc3_l      (new BSTNode<int>);
    pBSTNode tc3_r      (new BSTNode<int>);
    pBSTNode tc3_ll     (new BSTNode<int>);
    pBSTNode tc3_rr     (new BSTNode<int>);

    tc3_root->data_     = 1;
    tc3_l->data_        = 9;
    tc3_r->data_        = 32;
    tc3_ll->data_       = 3;
    tc3_rr->data_       = 78;

    tc3_root->left_     = tc3_l;
    tc3_root->right_    = tc3_r;
    tc3_l->left_        = tc3_ll;
    tc3_r->right_       = tc3_rr;

    vector<vector<int>> res3 = gather_levels(tc3_root);
    print_matrix(res3);

    // Test case 4.
    pBSTNode tc4_root   (new BSTNode<int>);
    pBSTNode tc4_l      (new BSTNode<int>);
    pBSTNode tc4_r      (new BSTNode<int>);
    pBSTNode tc4_ll     (new BSTNode<int>);
    pBSTNode tc4_lr     (new BSTNode<int>);
    pBSTNode tc4_rl     (new BSTNode<int>);
    pBSTNode tc4_rr     (new BSTNode<int>);

    
    tc4_root->data_     = 1;
    tc4_l->data_        = 2;
    tc4_r->data_        = 3;
    tc4_ll->data_       = 4;
    tc4_lr->data_       = 5;
    tc4_rl->data_       = 6;
    tc4_rr->data_       = 7;

    tc4_root->left_     = tc4_l;
    tc4_root->right_    = tc4_r;
    tc4_l->left_        = tc4_ll;
    tc4_l->right_       = tc4_lr;
    tc4_r->left_        = tc4_rl;
    tc4_r->right_       = tc4_rr;

    vector<vector<int>> res4 = gather_levels(tc4_root);
    print_matrix(res4);

    return 0;
}
