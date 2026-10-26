/**
 * EPI Chapter 15 Binary Search Trees
 *
 * 15.5 Reconstruct a BST from traversal data.
 *
 * There are many different binary trees that yield the same sequence of
 * visited nodes in an inorder traversal. This is also true for preorder and
 * postorder traversals. Given the sequence of nodes that an inorder traversal
 * visits and either of the other 2 traversal sequences, there exists a unique
 * binary tree that yields those sequences. Here we study if it's possible to
 * reconstruct the tree with less traversal information when the tree is known
 * to be a BST.
 *
 * It is critical that the elements stored in the tree be unique. If the root
 * contains key v and the tree contains more occurrences of v, we cannot always
 * identify from the sequence whether the subsequent vs are in the left subtree
 * or right subtree.
 *
 * Suppose you are given the sequence in which keys are visited in an inorder
 * traversal of a BST, and all keys are distinct. Can you reconstruct the BST
 * from the sequence? If so, write a program to do so. Solve the same problem
 * for preorder and postorder traversal sequences.
 *
 * Hint: Draw the 5 BSTs on the key 1, 2, 3, and the corresponding traversal
 * orders.
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
    for (const auto& e : v)
        printf("%d ", e);
    printf("\n");
}

void Preorder(const pBSTNode& tree, vector<int>& preorder)
{
    if (tree != nullptr) {
        preorder.emplace_back(tree->data_);
        Preorder(tree->left_, preorder);
        Preorder(tree->right_, preorder);
    }
}

void Postorder(const pBSTNode& tree, vector<int>& postorder)
{
    if (tree != nullptr) {
        Postorder(tree->left_, postorder);
        Postorder(tree->right_, postorder);
        postorder.emplace_back(tree->data_);
    }
}

bool Equals(const pBSTNode& tree1, const pBSTNode& tree2)
{
    if (tree1 == nullptr && tree2 == nullptr) {
        return true;
    } else if (tree1 != nullptr && tree2 != nullptr) {
        if (tree1->data_ != tree2->data_)
            return false;
        return Equals(tree1->left_, tree2->left_) &&
            Equals(tree1->right_, tree2->right_);
    } else {
        return false;
    }
}

/**
 * Idea: From the hint, it's clear that we cannot reconstruct our BST just from
 * inorder traversal. Since 3 different BSTs can have the same inorder
 * traversal.
 *
 * We attempt with preorder. The first node is always root.
 * The next k nodes that are less than the root are the nodes from
 * the left subtree. The rest of n - 1 - k nodes are the nodes from
 * the right subtree. We can build our binary search tree recursively
 * using this method.
 *
 * Time complexity: Worst case is when the BST is left-skewed: O(n^2)
 * Best case is when the BST is right skewed: O(n)
 * Average case: O(nlogn)
 * Space complexity: O(logn) since we have 2 recursive calls.
 */
pBSTNode RebuildBSTFromPreorder(const vector<int>& preorder, int start, int end)
{
    int n = static_cast<int>(preorder.size());
    if (start < 0 || end >= n || start >= n || end < 0 || start > end) 
        return nullptr;

    int root = preorder[start];
    int left_idx = -1;
    if (start + 1 <= end && preorder[start+1] < root) {
        left_idx = start + 1;
    }

    int right_idx = end + 1;
    for (int i = start + 1; i <= end; i++) {
        if (preorder[i] > root) {
            right_idx = i;
            break;
            
        }
    }
    
    return make_shared<BinaryTreeNode<int>>(
        root,
        RebuildBSTFromPreorder(preorder, left_idx, right_idx - 1),
        RebuildBSTFromPreorder(preorder, right_idx, end)
            );
}


pBSTNode RebuildBSTFromPreorder(const vector<int>& preorder)
{
    return RebuildBSTFromPreorder(preorder, 0, preorder.size() - 1);
}

/**
 * Idea: Iterating over the traversal array jsut to find the transition point
 * is wasteful.
 *
 * Builds a BST on the subtree rooted at root_idx from the preorder sequence on
 * keys in (lower_bound, upper_bound).
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
pBSTNode RebuildBSTFromPreorderOnValueRange(const vector<int>& preorder
        , int lower_bound, int upper_bound, int* root_idx_ptr)
{
    int& root_idx = *root_idx_ptr;
    if (root_idx == preorder.size()) return nullptr;

    int root = preorder[root_idx];
    if (root < lower_bound || root > upper_bound) return nullptr;

    root_idx++;

    // Note that RebuildBSTFromPreorderOnValueRange updates root_idx. So the
    // order of following 2 calls are critical.
    auto left_subtree = RebuildBSTFromPreorderOnValueRange(preorder, 
            lower_bound, root, root_idx_ptr);
    auto right_subtree = RebuildBSTFromPreorderOnValueRange(preorder,
            root, upper_bound, root_idx_ptr);
    return make_shared<BinaryTreeNode<int>>(
            root,
            left_subtree, right_subtree
            );
}

pBSTNode RebuildBSTFromPreorderEPI(const vector<int>& preorder)
{
    int root_idx = 0;
    return RebuildBSTFromPreorderOnValueRange(preorder, 
            numeric_limits<int>::min(), numeric_limits<int>::max(), &root_idx);
}

/**
 * Variant: Rebuild BST from postorder traversal data using the same idea.
 */
pBSTNode RebuildBSTFromPostorderOnValueRange(const vector<int>& postorder,
        int lower_bound, int upper_bound, int* root_idx_ptr)
{
    int& root_idx = *root_idx_ptr;
    if (root_idx < 0) return nullptr;

    int root = postorder[root_idx];
    if (root < lower_bound || root > upper_bound) return nullptr;
    root_idx--;

    auto right_subtree = RebuildBSTFromPostorderOnValueRange(postorder,
            root, upper_bound, &root_idx);
    auto left_subtree = RebuildBSTFromPostorderOnValueRange(postorder,
            lower_bound, root, &root_idx);
    return make_shared<BinaryTreeNode<int>>(root, left_subtree, right_subtree);
}

pBSTNode RebuildBSTFromPostorder(const vector<int>& postorder)
{
    int root_idx = static_cast<int>(postorder.size()-1);
    return RebuildBSTFromPostorderOnValueRange(postorder, 
            numeric_limits<int>::min(), numeric_limits<int>::max(), &root_idx);
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

    vector<int> tc1_preorder{19, 7, 3, 2, 5, 11, 17, 13, 43, 23, 37, 29, 31, 41, 47, 53};
    // pBSTNode tc1_res = RebuildBSTFromPreorder(tc1_preorder);
    pBSTNode tc1_res = RebuildBSTFromPreorderEPI(tc1_preorder);

    PrintVect(tc1_preorder);
    vector<int> tc1_res_preorder;
    Preorder(tc1_res, tc1_res_preorder);
    PrintVect(tc1_res_preorder);
    // assert(Equals(tc1_A, tc1_res));

    vector<int> tc1_postorder{2, 5, 3, 13, 17, 11, 7, 3, 31, 29, 41, 37, 23, 53, 47, 43, 19};
    pBSTNode tc1_res_post = RebuildBSTFromPostorder(tc1_postorder);
    PrintVect(tc1_postorder);

    vector<int> tc1_res_post_vect;
    Postorder(tc1_res_post, tc1_res_post_vect);
    PrintVect(tc1_res_post_vect);
    // assert(Equals(tc1_A, tc1_res_post));


    return 0;
}
