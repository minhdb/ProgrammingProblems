/**
 * Given a binary tree return all the values you'd be able to see if you were
 * standing on the left side of it with values ordered from top to bottom.
 */

#include "../data_structures/bst_node.h"

#include <cassert>
#include <vector>
#include <queue>
#include <memory>
#include <utility>

using data_structures::BSTNode;

using std::vector;
using std::queue;
using std::make_shared;
using std::shared_ptr;
using std::pair;

using pBSTNode = shared_ptr<BSTNode<int>>;

vector<int> visible_values(pBSTNode root)
{
    vector<int> res_values;

    /**
     * Solution: Use a recursive algorithm.
     *
     * Base case 1: The current node is null, return empty list.
     * Base case 2: The current node is not null, but has no children, return
     *  a list containing the current node.
     *
     * Inductive case: Let p be the current node's parent. 2 cases can happen
     *  Case 1: Current node is a left node. Check by p->left_ == cur_node. Add it to the list.
     *  Case 2: Current node is a right node. Check by p->left_ != cur_node.
     */


    /**
     * Use level order tree traversal. Take the first node at the beginning of each level.
     *
     * Time complexity: O(n) where n is the number of nodes.
     * Space complexity: O(n) + O(lg(n)) = O(n)
     *  We know we need a queue and a list to store nodes. The list is at most O(lg(n)) because
     *  we only need to store the nodes that are visible (which is the height of the tree).
     */

    queue<pair<pBSTNode, int>> q;

    q.emplace(make_pair(root, 0));

    pair<pBSTNode, int> cur_pair;

    while( !q.empty() ) {
        cur_pair = q.front();
        q.pop();

        pBSTNode cur_node = cur_pair.first;
        int cur_level = cur_pair.second;

        if (cur_level >= static_cast<int>(res_values.size())) {
            res_values.emplace_back(cur_node->data_);
        } else {
            // Do nothing here because we want the leftest node. It already exists.
        }
        
        if (cur_node->left_ != nullptr) {
            q.emplace(make_pair(cur_node->left_, cur_level + 1));
        }

        if (cur_node->right_ != nullptr) {
            q.emplace(make_pair(cur_node->right_, cur_level + 1));
        }
    }

    return res_values;
}

int main()
{
    // Test case 1:
    pBSTNode tc1_root   (new BSTNode<int>);
    pBSTNode tc1_l      (new BSTNode<int>);
    pBSTNode tc1_r      (new BSTNode<int>);

    tc1_root->data_     = 4;
    tc1_l->data_        = 2;
    tc1_r->data_        = 7;

    tc1_root->left_     = tc1_l;
    tc1_root->right_    = tc1_r;

    vector<int> tc1_res {4, 2};
    assert(visible_values(tc1_root) == tc1_res);

    // Test case 2:
    pBSTNode tc2_root   (new BSTNode<int>);
    pBSTNode tc2_l      (new BSTNode<int>);
    pBSTNode tc2_r      (new BSTNode<int>);
    pBSTNode tc2_ll     (new BSTNode<int>);
    pBSTNode tc2_lr     (new BSTNode<int>);
    pBSTNode tc2_rl     (new BSTNode<int>);
    pBSTNode tc2_rr     (new BSTNode<int>);
    pBSTNode tc2_rrr    (new BSTNode<int>);

    tc2_root->data_     = 7;
    tc2_l->data_        = 4;
    tc2_r->data_        = 9;
    tc2_ll->data_       = 1;
    tc2_lr->data_       = 4;
    tc2_rl->data_       = 9;
    tc2_rr->data_       = 9;
    tc2_rrr->data_      = 9;

    tc2_root->left_     = tc2_l;
    tc2_root->right_    = tc2_r;
    tc2_l->left_        = tc2_ll;
    tc2_l->right_       = tc2_lr;
    tc2_r->left_        = tc2_rl;
    tc2_r->right_       = tc2_rr;
    tc2_rr->right_      = tc2_rrr;
    
    vector<int> tc2_res {7, 4, 1, 9};
    assert(visible_values(tc2_root) == tc2_res);

    // Test case 3:
    pBSTNode tc3_root   (new BSTNode<int>);
    pBSTNode tc3_r      (new BSTNode<int>);
    pBSTNode tc3_rr     (new BSTNode<int>);
    pBSTNode tc3_rrr    (new BSTNode<int>);
    pBSTNode tc3_rrrr   (new BSTNode<int>);

    tc3_root->data_     = 1;
    tc3_r->data_        = 2;
    tc3_rr->data_       = 3;
    tc3_rrr->data_      = 4;
    tc3_rrrr->data_     = 5;

    tc3_root->right_    = tc3_r;
    tc3_r->right_       = tc3_rr;
    tc3_rr->right_      = tc3_rrr;
    tc3_rrr->right_     = tc3_rrrr;

    vector<int> tc3_res {1, 2, 3, 4, 5};
    assert(visible_values(tc3_root) == tc3_res);

    return 0;
}
