/**
 * EPI Chapter 15 Binary Search Trees
 *
 * 15.4 Compute the LCA in a BST.
 *
 * Since a BST is a specialized binary tree, the notion of LCA holds.
 *
 * In general, computing the LCA of 2 nodes in a BST is no easier than
 * computing the LCA in a binary tree, since structurally a binary tree
 * can be viewed as a BST where all keys are equal. However, when the keys
 * are distinct, it is possible to improve on the LCA algorithms for binary
 * trees.
 *
 * Design an algorithm that takes as input a BST and 2 nodes, and returns
 * the LCA of the 2 nodes.
 * Assume all keys are distinct. Nodes do not have references to their parents.
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

/**
 * Idea: Traverse to node s and node b, recording the path in 2 arrays.
 *
 * Time complexity: O(d1 + d2) where d1 is the depth of node s and d2 is the
 *  depth of node b.
 * Space complexity: O(d1 + d2) for 2 arrays.
 */
pBSTNode FindLCAMySolution(const pBSTNode& root, const pBSTNode& s, const pBSTNode& b)
{
    pBSTNode lca(root);
    vector<pBSTNode> path_to_s;
    vector<pBSTNode> path_to_b;

    pBSTNode pIter(root);
    while (pIter != s) {
        path_to_s.emplace_back(pIter);
        if (pIter->data_ < s->data_) {
            pIter = pIter->right_;
        } else if (pIter->data_ > s->data_) {
            pIter = pIter->left_;
        } else {
            break;
        }
    }

    pIter = root;
    while (pIter != b) {
        path_to_b.emplace_back(pIter);
        if (pIter->data_ < b->data_) {
            pIter = pIter->right_;
        } else if (pIter->data_ > s->data_) {
            pIter = pIter->left_;
        } else {
            break;
        }
    }
    
    size_t min_len = path_to_s.size() < path_to_b.size() ? path_to_s.size() : path_to_b.size();

    for (size_t i = 1; i < min_len; i++) {
        if (path_to_s[i] != path_to_b[i])
            break;
        else
            lca = path_to_s[i];
    }

    return lca;
}
/**
 * Idea: Assume s < b, without loss of generality, since s != b. There are 4 scenarios.
 *
 * 1. If either s == root or b == root, the LCA is the root.
 * 2. If s < root and b > root, the LCA is the root.
 * 3. If s < root and b < root, the LCA is in root->left;
 * 4. If s > root and b > root, the LCA is in root->right;
 */
pBSTNode FindLCAEPIHelper(const pBSTNode& root, const pBSTNode& s, const pBSTNode& b)
{
    pBSTNode lca(nullptr);
    pBSTNode pIter(root);

    while (pIter != s && pIter != b) {
        if (s->data_ < pIter->data_ && b->data_ > pIter->data_) {
            break;
        }

        if (s->data_ < pIter->data_ && b->data_ < pIter->data_) {
            pIter = pIter->left_;
        } else if (s->data_ > pIter->data_ && b->data_ > pIter->data_) {
            pIter = pIter->right_;
        }
    }

    lca = pIter;
    return lca;
}

pBSTNode FindLCAEPI(const pBSTNode& root, const pBSTNode& s, const pBSTNode& b)
{
    return s->data_ < b->data_ ? FindLCAEPIHelper(root, s, b) : 
        FindLCAEPIHelper(root, b, s);
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

    assert(FindLCAMySolution(tc1_A, tc1_C, tc1_G) == tc1_B);
    assert(FindLCAEPI(tc1_A, tc1_C, tc1_G) == tc1_B);
    return 0;
}
