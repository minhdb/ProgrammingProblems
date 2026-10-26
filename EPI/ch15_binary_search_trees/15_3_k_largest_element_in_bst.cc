/**
 * EPI Chapter 15 Binary Search Trees
 *
 * 15.3 Find the k largest elements in a BST
 * A BST is a sorted data structure, which suggests that it should be possible
 * to find the k largest keys easily.
 *
 * Write a program that takes as input a BST and an integer k, and returns the
 * k largest elements in the BST in decreasing order.
 *
 * Hint: What does an inorder traversal yield?
 *
 * A sorted list of keys.
 */

#include <cstdio>
#include <memory>
#include <cassert>
#include <limits>
#include <vector>

#include "../data_structures/binary_tree.hpp"

using std::make_shared;
using std::shared_ptr;
using std::numeric_limits;
using std::vector;

using data_structures::BinaryTreeNode;

using pBSTNode = std::shared_ptr<BinaryTreeNode<int>>;

void PrintVect(const vector<int>& v)
{
    for (const auto& e : v) {
        printf("%d ", e);
    }

    printf("\n");
}

/**
 * Idea: Perform partial inorder tree traversal. Decrease k every time
 * we go up from the right node until k equals 0.
 *
 * Time complexity: O(h + k)
 * Space complexity: O(1)
 */
void FindKLargestHelper(const pBSTNode& root, int k, vector<int>& res)
{
    if (root != nullptr && res.size() < static_cast<size_t>(k)) {
        FindKLargestHelper(root->right_, k, res);
        if (res.size() < static_cast<size_t>(k)) {
            res.emplace_back(root->data_);
            FindKLargestHelper(root->left_, k, res);
        }
    }
}

vector<int> FindKLargestInBST(const pBSTNode& root, int k )
{
    vector<int> res;
    FindKLargestHelper(root, k, res);
    return res;
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

    vector<int> tc1_res {53, 47, 43};
    int tc1_k           = 3;
    assert(FindKLargestInBST(tc1_A, tc1_k) == tc1_res);
    vector<int> tc1_debug = FindKLargestInBST(tc1_A, tc1_k);
    return 0;
}
