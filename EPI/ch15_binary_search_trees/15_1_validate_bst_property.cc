/**
 * EPI Chapter 15 - Binary Search Trees
 *
 * 07/31/2021
 *
 * Write a program that takes as input a binary tree and checks if the tree
 * satisfies the BST property.
 *
 * Hint: Is it correct to check for each node that its key is greater than or
 * equal to the key at its left child and less than or equal to the key at its
 * right child? No. This is a global property. If it applies to every single
 * node, it doesn't mean it apply to the whole tree.
 */

#include <cstdio>
#include <memory>
#include <cassert>
#include <limits>

#include "../data_structures/binary_tree.hpp"

using std::make_shared;
using std::shared_ptr;
using std::numeric_limits;

using data_structures::BinaryTreeNode;

using pBSTNode = std::shared_ptr<BinaryTreeNode<int>>;

/**
 * Idea: Use recursion. Keep track of the values that left and right keys
 * are allowed to be greater / smaller than or equal to.
 */
bool isBSTHelper(const pBSTNode& root, int min, int max)
{
    if (root == nullptr) {
        return true;
    } else {
        if (root->data_ < min || root->data_ > max)
            return false;
        return isBSTHelper(root->left_, min, root->data_) &&
            isBSTHelper(root->right_, root->data_, max);
    }
}

bool isBST(const pBSTNode& root)
{
   return isBSTHelper(root, numeric_limits<int>::min(), numeric_limits<int>::max()); 
}

int main()
{
    pBSTNode tc1_A      (make_shared<BinaryTreeNode<int>>(19));
    pBSTNode tc1_B      (make_shared<BinaryTreeNode<int>>(7));
    pBSTNode tc1_C      (make_shared<BinaryTreeNode<int>>(3));
    pBSTNode tc1_D      (make_shared<BinaryTreeNode<int>>(2));
    pBSTNode tc1_E      (make_shared<BinaryTreeNode<int>>(5));
    pBSTNode tc1_F      (make_shared<BinaryTreeNode<int>>(11));
    pBSTNode tc1_G      (make_shared<BinaryTreeNode<int>>(17));
    pBSTNode tc1_H      (make_shared<BinaryTreeNode<int>>(13));
    pBSTNode tc1_I      (make_shared<BinaryTreeNode<int>>(43));
    pBSTNode tc1_J      (make_shared<BinaryTreeNode<int>>(23));
    pBSTNode tc1_K      (make_shared<BinaryTreeNode<int>>(37));
    pBSTNode tc1_L      (make_shared<BinaryTreeNode<int>>(29));
    pBSTNode tc1_N      (make_shared<BinaryTreeNode<int>>(41));
    pBSTNode tc1_M      (make_shared<BinaryTreeNode<int>>(32));
    pBSTNode tc1_O      (make_shared<BinaryTreeNode<int>>(47));
    pBSTNode tc1_P      (make_shared<BinaryTreeNode<int>>(53));

    tc1_A->left_        = tc1_B;
    tc1_A->right_       = tc1_I;
    tc1_B->left_        = tc1_C;
    tc1_B->right_       = tc1_F;
    tc1_C->left_        = tc1_D;
    tc1_C->right_       = tc1_E;
    tc1_F->right_       = tc1_G;
    tc1_G->left_        = tc1_H;

    tc1_I->left_        = tc1_J;
    tc1_I->right_       = tc1_O;
    tc1_J->right_       = tc1_K;
    tc1_K->left_        = tc1_L;
    tc1_K->right_       = tc1_N;
    tc1_L->right_       = tc1_M;

    tc1_O->right_       = tc1_P;
    assert(isBST(tc1_A));

    return 0;
}
