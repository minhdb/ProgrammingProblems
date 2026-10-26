/**
 * The Daily Byte
 * 07/02/2021
 *
 * Given a binary tree, return a list of strings containing all root to leaf
 * paths.
 */

#include "../data_structures/bst_node.h"

#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <iostream>

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;

using data_structures::BSTNode;

using pTreeNode = shared_ptr<BSTNode<int>>;

void print_vect(const vector<string>& v)
{
    printf("[");
    for (const auto& e : v) {
        printf("%s, ", e.c_str());
    }
    printf("]\n");
}

void root_to_leaf_paths_aux(const pTreeNode& root, vector<string>& res, string cur_path)
{
    if (root == nullptr) {

    } else {
        cur_path += std::to_string(root->data_) + "->";
        
        if (root->left_ == nullptr && root->right_ == nullptr) {
            cur_path.pop_back();
            cur_path.pop_back();
            res.emplace_back(cur_path);
        }
        
        if (root->left_ != nullptr)
            root_to_leaf_paths_aux(root->left_, res, cur_path);

        if (root->right_ != nullptr)
            root_to_leaf_paths_aux(root->right_, res, cur_path);
    }
}

vector<string> root_to_leaf_paths(const pTreeNode& root)
{
    vector<string> res;

    root_to_leaf_paths_aux(root, res, "");

    // print_vect(res);

    return res;
}

int main()
{
    // Test case 1.
    pTreeNode tc1_root      (new BSTNode<int>(1));
    pTreeNode tc1_l         (new BSTNode<int>(2));
    pTreeNode tc1_r         (new BSTNode<int>(3));
    tc1_root->left_         = tc1_l;
    tc1_root->right_        = tc1_r;

    vector<string> tc1_res {"1->2", "1->3"};
    root_to_leaf_paths(tc1_root);
    assert(root_to_leaf_paths(tc1_root) == tc1_res);

    // Test case 2.
    pTreeNode tc2_root      (new BSTNode<int>(8));
    pTreeNode tc2_l         (new BSTNode<int>(2));
    pTreeNode tc2_r         (new BSTNode<int>(29));
    pTreeNode tc2_rl        (new BSTNode<int>(3));
    pTreeNode tc2_rr        (new BSTNode<int>(9));

    tc2_root->left_         = tc2_l;
    tc2_root->right_        = tc2_r;
    tc2_r->left_            = tc2_rl;
    tc2_r->right_           = tc2_rr;

    vector<string> tc2_res {"8->2", "8->29->3", "8->29->9"};
    root_to_leaf_paths(tc2_root);
    assert(root_to_leaf_paths(tc2_root) == tc2_res);
    
    return 0;
}

