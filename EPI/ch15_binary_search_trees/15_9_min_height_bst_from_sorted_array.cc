/**
 * EPI Chapter 15 Binary Search Trees
 *
 * Given a sorted array, the number of BSTs that can be built on the entries
 * in the array grows enormously with its size. Some of these trees are skewed,
 * and are closer to lists; others are more balanced.
 *
 * How would you build a BST of minimum possible height from a sorted array?
 *
 * Hint: Which element should be the root?
 */


#include <cstdio>
#include <memory>
#include <cassert>
#include <limits>
#include <vector>
#include <algorithm>

#include "../data_structures/binary_tree.hpp"

using std::make_shared;
using std::shared_ptr;
using std::numeric_limits;
using std::vector;
using std::max;

using data_structures::BinaryTreeNode;

using pBSTNode = std::shared_ptr<BinaryTreeNode<int>>;

void PrintVect(const vector<int>& v)
{
    for (const auto& e : v)
        printf("%d ", e);
    printf("\n");
}

void Inorder(const pBSTNode& root, vector<int>& inorder)
{
    if (root != nullptr) {
        Inorder(root->left_, inorder);
        inorder.emplace_back(root->data_);
        Inorder(root->right_, inorder);
    }
}

int GetHeightHelper(const pBSTNode& root, int cur_max, int cur_height)
{
    if (root != nullptr) {
        cur_max = max(cur_height, cur_max);
        cur_max = max(GetHeightHelper(root->left_, cur_max, cur_height + 1), cur_max);
        cur_max = max(GetHeightHelper(root->right_, cur_max, cur_height + 1), cur_max);
    }

    return cur_max;
}

int GetHeight(const pBSTNode& root)
{
    return GetHeightHelper(root, 0, 0);
}

/**
 * Idea: The root is the middle element of the array.
 * We recursively build the BST from both side of the array.
 *
 * This guarantees the minimum height BST since we basically
 * want the tree to be balanced.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
pBSTNode BuildMinHeightBSTFromSortedArrayHelper(const vector<int>& A,
        size_t start, size_t end)
{
    if (start > end) return nullptr;
    size_t root_idx = start + (end - start) / 2;
    return make_shared<BinaryTreeNode<int>>(
        A[root_idx],
        BuildMinHeightBSTFromSortedArrayHelper(A, start, root_idx-1),
        BuildMinHeightBSTFromSortedArrayHelper(A, root_idx+1, end)
            );
}
pBSTNode BuildMinHeightBSTFromSortedArray(const vector<int>& A)
{
    return BuildMinHeightBSTFromSortedArrayHelper(
            A, 0, A.size() - 1
            );
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
    
    assert(GetHeight(tc1_A) == 5);

    vector<int> tc1{2, 3, 5, 7, 11, 13, 17, 19, 23};

    pBSTNode tc1_res = BuildMinHeightBSTFromSortedArray(tc1);
    assert(GetHeight(tc1_res) == 4);

    vector<int> tc1_inorder;
    Inorder(tc1_res, tc1_inorder);
    PrintVect(tc1_inorder);
    return 0;
}
