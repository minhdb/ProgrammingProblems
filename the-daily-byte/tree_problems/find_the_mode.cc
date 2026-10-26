/**
 * The Daily Byte - 06/23/2021
 *
 * Given a BST, return its mode (you may assume the answer is unique). If the
 * tree is empty, return -1. Note: the mode is the most frequently occurring
 * value in the tree.
 */

#include "../data_structures/bst_node.h"

#include <cassert>
#include <unordered_map>
#include <memory>
#include <limits>

using std::unordered_map;
using std::make_shared;
using std::shared_ptr;
using std::numeric_limits;
using data_structures::BSTNode;
using pBSTNode = shared_ptr<BSTNode<int>>;

void inorder_traversal(pBSTNode& bst, unordered_map<int, int>& freq_map)
{
    if (bst == nullptr) {
        return;
    } else {
        inorder_traversal(bst->left_, freq_map);
        if (freq_map.count(bst->data_) == 0)
            freq_map[bst->data_] = 1;
        else
            freq_map[bst->data_]++;
        inorder_traversal(bst->right_, freq_map);
    }
}

int find_mode_bst(pBSTNode& bst)
{
    unordered_map<int, int> freq;

    inorder_traversal(bst, freq);

    if (freq.size() == 0) return -1;

    int most_frequent_value = 0;
    int f = numeric_limits<int>::min();

    for (const auto& e : freq) {
        if (e.second > f) {
            most_frequent_value = e.first;
            f = e.second;
        }
    }

    return most_frequent_value;

}

int main()
{
    // Test case 1
    pBSTNode tc1_root   (new BSTNode<int>);
    pBSTNode tc1_l      (new BSTNode<int>);
    pBSTNode tc1_r      (new BSTNode<int>);

    tc1_root->left_     = tc1_l;
    tc1_root->right_    = tc1_r;

    tc1_root->data_     = 2;
    tc1_l->data_        = 1;
    tc1_r->data_        = 2;

    assert(find_mode_bst(tc1_root) == 2);

    // Test case 2.
    pBSTNode tc2_root   (new BSTNode<int>);
    pBSTNode tc2_l      (new BSTNode<int>);
    pBSTNode tc2_r      (new BSTNode<int>);
    pBSTNode tc2_ll     (new BSTNode<int>);
    pBSTNode tc2_lr     (new BSTNode<int>);
    pBSTNode tc2_rl     (new BSTNode<int>);
    pBSTNode tc2_rr     (new BSTNode<int>);
    pBSTNode tc2_rrr    (new BSTNode<int>);

    tc2_root->data_     = 7;
    tc2_l->data_        = 4;
    tc2_r->data_        = 9;
    tc2_ll->data_       = 1;
    tc2_lr->data_       = 4;
    tc2_r->data_        = 9;
    tc2_rl->data_       = 8;
    tc2_rr->data_       = 9;
    tc2_rrr->data_      = 9;

    tc2_root->left_     = tc2_l;
    tc2_root->right_    = tc2_r;
    tc2_l->left_        = tc2_ll;
    tc2_l->right_       = tc2_lr;
    tc2_r->left_        = tc2_rl;
    tc2_r->right_       = tc2_rr;
    tc2_rr->right_      = tc2_rrr;

    assert(find_mode_bst(tc2_root) == 9);

    return 0;
}
