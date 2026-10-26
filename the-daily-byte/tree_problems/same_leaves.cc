/**
 * The Daily Byte
 * 07/06/2021
 *
 * Given 2 binary trees, return whether or not both trees have the same leaf
 * sequence. Two trees have the same leaf sequence if both trees' leaves read
 * the same from left to right.
 */

#include <memory>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <utility>

#include "../data_structures/bst_node.h"

using std::string;
using std::queue;
using std::stack;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::pair;
using std::make_pair;

using data_structures::BSTNode;
using pTreeNode = shared_ptr<BSTNode<int>>;

/**
 * Do DFS, adding leaves node to the list.
 * And compare 2 lists.
 *
 * Time complexity: O(max(n, m)) where n and m are the number of leaves
 *  in 2 trees.
 * Space complexity: O(max(n, m)) if the tree's not balanced.
 */

void gatherLeavesDFS(const pTreeNode& tree, vector<int>& leaves)
{
    if (tree == nullptr) return;
    gatherLeavesDFS(tree->left_, leaves);
    if (tree->left_ == nullptr && tree->right_ == nullptr)
        leaves.emplace_back(tree->data_);
    gatherLeavesDFS(tree->right_, leaves);
}

bool sameLeaves(const pTreeNode& tree1, const pTreeNode& tree2)
{
    vector<int> tree1_leaves;
    vector<int> tree2_leaves;

    gatherLeavesDFS(tree1, tree1_leaves);
    gatherLeavesDFS(tree2, tree2_leaves);

    return tree1_leaves == tree2_leaves;
}

int main()
{
    // Test case 1.
    pTreeNode tc1_tree1_root    (new BSTNode<int>(1));
    pTreeNode tc1_tree1_left    (new BSTNode<int>(1));
    pTreeNode tc1_tree1_right   (new BSTNode<int>(3));
    tc1_tree1_root->left_       = tc1_tree1_left;
    tc1_tree1_root->right_      = tc1_tree1_right;

    pTreeNode tc1_tree2_root    (new BSTNode<int>(7));
    pTreeNode tc1_tree2_left    (new BSTNode<int>(1));
    pTreeNode tc1_tree2_right   (new BSTNode<int>(2));
    tc1_tree2_root->left_       = tc1_tree2_left;
    tc1_tree2_root->right_      = tc1_tree2_right;

    assert(!sameLeaves(tc1_tree1_root, tc1_tree2_root));

    // Test case 2.
    pTreeNode tc2_tree1_root    (new BSTNode<int>(8));
    pTreeNode tc2_tree1_left    (new BSTNode<int>(2));
    pTreeNode tc2_tree1_right   (new BSTNode<int>(29));
    pTreeNode tc2_tree1_ll      (new BSTNode<int>(2));
    pTreeNode tc2_tree1_rl      (new BSTNode<int>(3));
    pTreeNode tc2_tree1_rr      (new BSTNode<int>(9));
    pTreeNode tc2_tree1_rlr     (new BSTNode<int>(3));

    tc2_tree1_root->left_       = tc2_tree1_left;
    tc2_tree1_root->right_      = tc2_tree1_right;
    tc2_tree1_left->left_       = tc2_tree1_ll;
    tc2_tree1_right->left_      = tc2_tree1_rl;
    tc2_tree1_right->right_     = tc2_tree1_rr;
    tc2_tree1_rl->right_        = tc2_tree1_rlr;

    pTreeNode tc2_tree2_root    (new BSTNode<int>(8));
    pTreeNode tc2_tree2_left    (new BSTNode<int>(2));
    pTreeNode tc2_tree2_right   (new BSTNode<int>(29));
    pTreeNode tc2_tree2_rl      (new BSTNode<int>(3));
    pTreeNode tc2_tree2_rr      (new BSTNode<int>(9));

    tc2_tree2_root->left_       = tc2_tree2_left;
    tc2_tree2_root->right_      = tc2_tree2_right;
    tc2_tree2_right->left_      = tc2_tree2_rl;
    tc2_tree2_right->right_     = tc2_tree2_rr;

    assert(sameLeaves(tc2_tree2_root, tc2_tree1_root));

    return 0;
}
