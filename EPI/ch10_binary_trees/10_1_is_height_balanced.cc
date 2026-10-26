/**
 * EPI Chapter 10 Binary trees
 *
 * 07/11/2021
 * A binary tree is said to be height-balanced if for each node in the tree,
 * the difference in the height of its left and right subtrees is at most one.
 * A perfect binary tree is height-balanced, as is a complete binary tree. A
 * height-balanced binary tree does not have to be perfect or complete.
 *
 * Write a program that takes as input the root of a binary tree and checks
 * whether the tree is height-balanced.
 *
 * Hint: Think of a classic binary tree algorithm.
 */

/*
 * Idea: We can traverse the tree, keeping the height for each subtree.
 * If the difference in height of either left or right subtree is more than
 * 1, return false.
 */

#include <cstdio>
#include <memory>
#include <cassert>
#include <algorithm>

#include "../data_structures/binary_tree.hpp"

using std::shared_ptr;
using std::make_shared;
using std::shared_ptr;
using std::make_shared;

using data_structures::BinaryTreeNode;

struct BalancedStatusWithHeight
{
    int height;
    bool balanced;
};

BalancedStatusWithHeight checkBalanced(const shared_ptr<BinaryTreeNode<int>>& tree)
{
    if (tree == nullptr) {
        return BalancedStatusWithHeight{0, true};
    } else {
        int height_left = 0;
        int height_right = 0;

        if (tree->left_ != nullptr) {
            BalancedStatusWithHeight left_info = checkBalanced(tree->left_);
            height_left = left_info.height + 1;
            if (!left_info.balanced) return BalancedStatusWithHeight{height_left, false};
        }

        if (tree->right_ != nullptr) {
            BalancedStatusWithHeight right_info = checkBalanced(tree->right_);
            height_right = right_info.height + 1;
            if (!right_info.balanced) return BalancedStatusWithHeight{height_right, false};
        }

        if (abs(height_left - height_right) > 1) 
            return BalancedStatusWithHeight{std::max(height_right, height_left), false};
        return BalancedStatusWithHeight{std::max(height_right, height_left), true};
    }
}

bool isBalanced(const shared_ptr<BinaryTreeNode<int>>& tree)
{
    return checkBalanced(tree).balanced;
}

int main()
{
    shared_ptr<BinaryTreeNode<int>> tc1_root          (make_shared<BinaryTreeNode<int>>('A'));

    tc1_root->left_                              =     (make_shared<BinaryTreeNode<int>>('B'));
    tc1_root->right_                             =     (make_shared<BinaryTreeNode<int>>('K'));

    tc1_root->left_->left_                       =     (make_shared<BinaryTreeNode<int>>('C'));
    tc1_root->left_->right_                      =     (make_shared<BinaryTreeNode<int>>('H'));
    tc1_root->right_->left_                      =     (make_shared<BinaryTreeNode<int>>('L'));
    tc1_root->right_->right_                     =     (make_shared<BinaryTreeNode<int>>('O'));

    tc1_root->left_->left_->left_                =     (make_shared<BinaryTreeNode<int>>('D'));
    tc1_root->left_->left_->right_               =     (make_shared<BinaryTreeNode<int>>('G'));
    tc1_root->left_->right_->left_               =     (make_shared<BinaryTreeNode<int>>('I'));
    tc1_root->left_->right_->right_              =     (make_shared<BinaryTreeNode<int>>('J'));
    tc1_root->right_->left_->left_               =     (make_shared<BinaryTreeNode<int>>('M'));
    tc1_root->right_->left_->right_              =     (make_shared<BinaryTreeNode<int>>('N'));

    tc1_root->left_->left_->left_->left_         =     (make_shared<BinaryTreeNode<int>>('E'));
    tc1_root->left_->left_->left_->right_        =     (make_shared<BinaryTreeNode<int>>('F'));

    assert(isBalanced(tc1_root));
    return 0;
}
