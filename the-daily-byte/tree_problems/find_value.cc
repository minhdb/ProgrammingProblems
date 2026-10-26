/**
 * The Daily's Byte 06/16/2021
 *
 * Given a reference to the root of a binary search tree and a search value,
 * return the reference to the node that contains the value if it exists
 * and null otherwise.
 *
 * Note: all values in the binary search tree will be unique.
 */

#include "../data_structures/bst_node.h"
#include <memory>
#include <cassert>

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using data_structures::BSTNode;
using std::move;
// using pBSTNode = shared_ptr<BSTNode<int>>;

/**
 * Find value in BST.
 * Time complexity: O(2^(h - 1))
 * Space complexity: O(h) - where h is the height of the tree.
 */
shared_ptr<BSTNode<int>> find_value(shared_ptr<BSTNode<int>>& root, int value)
{
    if (root == nullptr) return nullptr;

    if (value == root->data_) return root;
    else if (value < root->data_) return find_value(root->left_, value);
    else return find_value(root->right_, value);
}

int main()
{
    shared_ptr<BSTNode<int>> tc1 = make_shared<BSTNode<int>>();
    tc1->data_ = 3;
    shared_ptr<BSTNode<int>> tc1_l(new BSTNode<int>);
    tc1_l->data_ = 1;
    shared_ptr<BSTNode<int>> tc1_r(new BSTNode<int>);
    tc1_r->data_ = 4;

    tc1->left_ = tc1_l;
    tc1->right_ = tc1_r;

    assert(find_value(tc1, 4) == tc1_r);



    shared_ptr<BSTNode<int>> tc2 = make_shared<BSTNode<int>>();
    tc2->data_ = 7;
    shared_ptr<BSTNode<int>> tc2_l = make_shared<BSTNode<int>>();
    tc2_l->data_ = 5;
    shared_ptr<BSTNode<int>> tc2_r = make_shared<BSTNode<int>>();
    tc2_r->data_ = 9;

    tc2->left_ = tc2_l;
    tc2->right_ = tc2_r;

    shared_ptr<BSTNode<int>> tc2_r_l = make_shared<BSTNode<int>>();
    tc2_r_l->data_ = 8;
    shared_ptr<BSTNode<int>> tc2_r_r = make_shared<BSTNode<int>>();
    tc2_r_r->data_ = 10;

    assert(find_value(tc2, 9) == tc2_r);


    shared_ptr<BSTNode<int>> tc3 = make_shared<BSTNode<int>>();
    tc3->data_ = 8;
    shared_ptr<BSTNode<int>> tc3_l = make_shared<BSTNode<int>>();
    tc3_l->data_ = 6;
    shared_ptr<BSTNode<int>> tc3_r = make_shared<BSTNode<int>>();
    tc3_r->data_ = 9;

    tc3->left_ = tc3_l;
    tc3->right_ = tc3_r;

    assert(find_value(tc3, 7) == nullptr);

    return 0;
}
