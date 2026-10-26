/**
 * The Daily Byte 06/18/2021
 *
 * Given a binary search tree that contains unique values and 2 nodes within
 * the tree, a, and b, return the lowest common ancestor.
 *
 * Note: The lowest common ancestor of 2 nodes is the deepest node within
 * the tree such that both nodes are descendants of it.
 */

#include "../data_structures/bst_node.h"

#include <vector>
#include <cassert>
#include <cstdio>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using data_structures::BSTNode;

using pBSTNode = shared_ptr<BSTNode<int>>;

void get_ancestors(pBSTNode& root, int val, vector<pBSTNode>& ancestors )
{
    if (root == nullptr) return;

    ancestors.emplace_back(root);

    if (val < root->data_) get_ancestors(root->left_, val, ancestors);
    else if (val > root->data_) get_ancestors(root->right_, val, ancestors);
}

void print_vect(const vector<pBSTNode>& v)
{
    for (const auto& e : v) {
        printf("%d ", e->data_);
    }
    printf("\n");
}

/**
 * Time complexity: O(logn)
 */
pBSTNode LCA( pBSTNode& root, int a, int b )
{
    vector<pBSTNode> a_ancestors;
    vector<pBSTNode> b_ancestors;

    get_ancestors(root, a, a_ancestors);
    get_ancestors(root, b, b_ancestors);

    // print_vect(a_ancestors);
    // print_vect(b_ancestors);

    int a_ans_len = a_ancestors.size();
    int b_ans_len = b_ancestors.size();

    int k = a_ans_len > b_ans_len ? b_ans_len : a_ans_len;
    
    for (int i = k - 1; i >= 0; i--) {
        if ( a_ancestors[i]->data_ == b_ancestors[i]->data_ )
            return a_ancestors[i];
    }
    return nullptr;
}

int main()
{
    // Test case 1.
    pBSTNode tc1_root = make_shared<BSTNode<int>>();
    pBSTNode tc1_l = make_shared<BSTNode<int>>();
    pBSTNode tc1_r = make_shared<BSTNode<int>>();
    pBSTNode tc1_ll = make_shared<BSTNode<int>>();
    pBSTNode tc1_lr = make_shared<BSTNode<int>>();

    tc1_root->data_ = 7;
    tc1_root->left_ = tc1_l;
    tc1_root->right_ = tc1_r;

    tc1_l->data_ = 2;
    tc1_l->left_ = tc1_ll;
    tc1_l->right_ = tc1_lr;

    tc1_ll->data_ = 1;
    tc1_lr->data_ = 5;

    tc1_r->data_ = 9;

    pBSTNode lca_res1 = LCA(tc1_root, 1, 9);
    assert( lca_res1->data_ == tc1_root->data_);

    // Test case 2.

    pBSTNode tc2_root = make_shared<BSTNode<int>>();
    pBSTNode tc2_l = make_shared<BSTNode<int>>();
    pBSTNode tc2_r = make_shared<BSTNode<int>>();
    pBSTNode tc2_ll = make_shared<BSTNode<int>>();
    pBSTNode tc2_lr = make_shared<BSTNode<int>>();

    tc2_root->data_ = 8;
    tc2_root->left_ = tc2_l;
    tc2_root->right_ = tc2_r;

    tc2_l->data_ = 3;
    tc2_l->left_ = tc2_ll;
    tc2_l->right_ = tc2_lr;

    tc2_ll->data_ = 2;
    tc2_lr->data_ = 6;

    tc2_r->data_ = 9;

    pBSTNode lca_res2 = LCA(tc2_root, 2, 6);
    assert( lca_res2->data_ == tc2_l->data_);

    // Test case 3.
    pBSTNode tc3_root = make_shared<BSTNode<int>>();
    pBSTNode tc3_l = make_shared<BSTNode<int>>();
    pBSTNode tc3_r = make_shared<BSTNode<int>>();

    tc3_root->data_ = 8;
    tc3_root->left_ = tc3_l;
    tc3_root->right_ = tc3_r;
    
    tc3_l->data_ = 6;
    tc3_r->data_ = 9;

    pBSTNode lca_res3 = LCA(tc3_root, 6, 8);
    assert(lca_res3->data_ == tc3_root->data_);

    // Test case 4
    pBSTNode tc4_root = make_shared<BSTNode<int>>();
    pBSTNode tc4_r = make_shared<BSTNode<int>>();
    pBSTNode tc4_rr = make_shared<BSTNode<int>>();
    pBSTNode tc4_rrr = make_shared<BSTNode<int>>();
    pBSTNode tc4_rrrr = make_shared<BSTNode<int>>();
    pBSTNode tc4_rrrrr = make_shared<BSTNode<int>>();

    tc4_root->data_ = 1;
    tc4_r->data_ = 2;
    tc4_rr->data_ = 3;
    tc4_rrr->data_ = 4;
    tc4_rrrr->data_ = 5;
    tc4_rrrrr->data_ = 6;
    
    tc4_root->right_ = tc4_r;
    tc4_r->right_ = tc4_rr;
    tc4_rr->right_ = tc4_rrr;
    tc4_rrr->right_ = tc4_rrrr;
    tc4_rrrr->right_ = tc4_rrrrr;
    
    pBSTNode lca_res4 = LCA(tc4_root, 3, 6);
    assert(lca_res4->data_ == tc4_rr->data_);
    return 0;
}
