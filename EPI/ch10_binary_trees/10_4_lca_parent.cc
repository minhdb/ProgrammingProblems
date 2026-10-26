/**
 * Given 2 nodes in a binary tree, design an algorithm that computes their LCA.
 * Lowest common ancestor.
 * Assume that each node has a parent pointer.
 *
 * Hint: The problem is easy if both nodes are the same distance from root.
 */


#include <cstdio>
#include <memory>
#include <cassert>

#include "../data_structures/binary_tree.hpp"

using std::shared_ptr;
using std::make_shared;

using data_structures::BinaryTreeNode;

int getDepth(const shared_ptr<BinaryTreeNode<int>>& node)
{
    shared_ptr<BinaryTreeNode<int>> pNode = node;
    int depth = 0;
    while (pNode != nullptr) {
        pNode = pNode->parent_;
        depth++;
    }
    return depth;
}

/**
 * Time complexity: O(h)
 * Space complexity: O(1)
 */
shared_ptr<BinaryTreeNode<int>> GetLCA(const shared_ptr<BinaryTreeNode<int>>& node1,
                            const shared_ptr<BinaryTreeNode<int>>& node2)
{
    int node1_depth = getDepth(node1);
    int node2_depth = getDepth(node2);

    shared_ptr<BinaryTreeNode<int>> pTmp1 = node1;
    shared_ptr<BinaryTreeNode<int>> pTmp2 = node2;
    
    // Move up until 2 nodes have the same depth.
    while (node1_depth < node2_depth) {
        pTmp2 = pTmp2->parent_;
        node2_depth--;
    }
    
    while (node1_depth > node2_depth) {
        pTmp1 = pTmp1->parent_;
        node1_depth--;
    }

    while (pTmp1 != pTmp2) {
        pTmp1 = pTmp1->parent_;
        pTmp2 = pTmp2->parent_;
    }
    
    return pTmp1;
}

int main()
{
    shared_ptr<BinaryTreeNode<int>> tc1_root          (make_shared<BinaryTreeNode<int>>('A'));

    tc1_root->left_                              =     make_shared<BinaryTreeNode<int>>('B');
    tc1_root->left_->parent_ = tc1_root;

    tc1_root->right_                             =     make_shared<BinaryTreeNode<int>>('K');
    tc1_root->right_->parent_ = tc1_root;

    tc1_root->left_->left_                       =     make_shared<BinaryTreeNode<int>>('C');
    tc1_root->left_->left_->parent_ = tc1_root->left_;

    tc1_root->left_->right_                      =     make_shared<BinaryTreeNode<int>>('H');
    tc1_root->left_->right_->parent_ = tc1_root->left_; 

    tc1_root->right_->left_                      =     make_shared<BinaryTreeNode<int>>('L');
    tc1_root->right_->left_->parent_ = tc1_root->right_;

    tc1_root->right_->right_                     =     make_shared<BinaryTreeNode<int>>('O');
    tc1_root->right_->right_->parent_ = tc1_root->right_;

    tc1_root->left_->left_->left_                =     make_shared<BinaryTreeNode<int>>('D');
    tc1_root->left_->left_->left_->parent_ = tc1_root->left_->left_;

    tc1_root->left_->left_->right_               =     make_shared<BinaryTreeNode<int>>('G');
    tc1_root->left_->left_->right_->parent_ = tc1_root->left_->left_;

    tc1_root->left_->right_->left_               =     make_shared<BinaryTreeNode<int>>('I');
    tc1_root->left_->right_->left_->parent_ = tc1_root->left_->right_;

    tc1_root->left_->right_->right_              =     make_shared<BinaryTreeNode<int>>('J');
    tc1_root->left_->right_->right_->parent_ = tc1_root->left_->right_;

    tc1_root->right_->left_->left_               =     make_shared<BinaryTreeNode<int>>('M');
    tc1_root->right_->left_->left_->parent_ = tc1_root->right_->left_;

    tc1_root->right_->left_->right_              =     make_shared<BinaryTreeNode<int>>('N');
    tc1_root->right_->left_->right_->parent_ = tc1_root->right_->left_;

    tc1_root->left_->left_->left_->left_         =     make_shared<BinaryTreeNode<int>>('E');
    tc1_root->left_->left_->left_->left_->parent_ = tc1_root->left_->left_->left_;

    tc1_root->left_->left_->left_->right_        =     make_shared<BinaryTreeNode<int>>('F');
    tc1_root->left_->left_->left_->right_->parent_ = tc1_root->left_->left_->left_;

    // I and J. Should return B.
    assert(GetLCA(tc1_root->left_->left_->left_->left_,
                tc1_root->left_->right_->right_) == tc1_root->left_);
    // GetLCA(tc1_root->left_->left_->left_->left_, tc1_root->left_->right_->right_);

    return 0;
}
