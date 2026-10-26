/**
 * The Daily Byte 06/17/2021
 *
 * Given a binary search tree, rearrange the tree such that it forms
 * a linked list where all its values are in ascending order.
 */

#include <cassert>
#include <memory>
#include <cstdio>

#include "../data_structures/bst_node.h"

using std::make_shared;
using data_structures::BSTNode;
using pBSTNode = std::shared_ptr<data_structures::BSTNode<int>>;

pBSTNode bst_to_linked_list_aux(pBSTNode& root)
{
    if (root == nullptr) return nullptr;

    pBSTNode last = bst_to_linked_list_aux(root->left_);

    pBSTNode cur = make_shared<BSTNode<int>>();
    cur->data_ = root->data_;

    cur->right_ = bst_to_linked_list_aux(root->right_);
    if (last != nullptr) {
        pBSTNode res = last;
        while (last->right_ != nullptr) last = last->right_;
        last->right_ = cur;
        return res;
    }
    return cur;
}

void print_right_tree(pBSTNode& root)
{
    if (root != nullptr) {
        printf("%d ", root->data_);
        print_right_tree(root->right_);
    } else {
        printf("\n");
    }
}

void inorder_traversal(pBSTNode& root)
{
    if (root != nullptr) {
        inorder_traversal(root->left_);
        printf("%d ", root->data_);
        inorder_traversal(root->right_);
    } else {
    }
}

pBSTNode bst_to_linked_list(pBSTNode& root)
{
    pBSTNode ll = bst_to_linked_list_aux(root);
    // inorder_traversal(ll);
    print_right_tree(ll);
    return ll;
}


int main()
{
    // Test case 1
    pBSTNode tc1_root = make_shared<BSTNode<int>>();
    pBSTNode tc1_l = make_shared<BSTNode<int>>();
    pBSTNode tc1_r = make_shared<BSTNode<int>>();
    tc1_root->data_ = 5;
    tc1_l->data_ = 1;
    tc1_r->data_ = 6;
    tc1_root->left_ = tc1_l;
    tc1_root->right_ = tc1_r;

    pBSTNode tc1_sol_root = make_shared<BSTNode<int>>();
    pBSTNode tc1_sol_next1 = make_shared<BSTNode<int>>();
    pBSTNode tc1_sol_next2 = make_shared<BSTNode<int>>();
    tc1_sol_root->data_ = 1;
    tc1_sol_next1->data_ = 5;
    tc1_sol_next2->data_ = 6;

    tc1_sol_root->right_ = tc1_sol_next1;
    tc1_sol_next1->right_ = tc1_sol_next2;

    pBSTNode bst_ll1 = bst_to_linked_list(tc1_root);
    assert(bst_equals(bst_ll1, tc1_sol_root));

    // Test case 2
    pBSTNode tc2_root = make_shared<BSTNode<int>>();
    pBSTNode tc2_r = make_shared<BSTNode<int>>();
    tc2_root->data_ = 5;
    tc2_r->data_ = 6;
    tc2_root->right_ = tc2_r;

    pBSTNode bst_ll2 = bst_to_linked_list(tc2_root);
    assert(bst_equals(bst_ll2, tc2_root));

    // Test case 3
    pBSTNode tc3_sol_root  = make_shared<BSTNode<int>>();  
    pBSTNode tc3_sol_next1 = make_shared<BSTNode<int>>(); 
    pBSTNode tc3_sol_next2 = make_shared<BSTNode<int>>(); 
    pBSTNode tc3_sol_next3 = make_shared<BSTNode<int>>(); 
    pBSTNode tc3_sol_next4 = make_shared<BSTNode<int>>(); 

    tc3_sol_root->data_ = 1;
    tc3_sol_root->right_ = tc3_sol_next1;

    tc3_sol_next1->data_ = 2;
    tc3_sol_next1->right_ = tc3_sol_next2;

    tc3_sol_next2->data_ = 3;
    tc3_sol_next2->right_ = tc3_sol_next3;

    tc3_sol_next3->data_ = 5;
    tc3_sol_next3->right_ = tc3_sol_next4;

    tc3_sol_next4->data_ = 9;

    pBSTNode tc3_root  = make_shared<BSTNode<int>>(); 
    pBSTNode tc3_l     = make_shared<BSTNode<int>>(); 
    pBSTNode tc3_r     = make_shared<BSTNode<int>>(); 
    pBSTNode tc3_ll    = make_shared<BSTNode<int>>(); 
    pBSTNode tc3_lr    = make_shared<BSTNode<int>>(); 

    tc3_root->data_ = 5;
    tc3_root->left_ = tc3_l;
    tc3_root->right_ = tc3_r;

    tc3_l->data_ = 2;
    tc3_l->left_ = tc3_ll;
    tc3_l->right_ = tc3_lr;

    tc3_r->data_ = 9;
    tc3_ll->data_ = 1;
    tc3_lr->data_ = 3;

    pBSTNode bst_ll3 = bst_to_linked_list(tc3_root);
    assert(bst_equals(bst_ll3, tc3_sol_root));

}
