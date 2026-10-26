/**
 * The Daily Byte 06/02/2021
 *
 * Given two sorted linked lists, merge them together in ascending order
 * and return a reference to the merged list.
 */

#include <cassert>
#include <vector>
#include <string>

#include "../data_structures/singly_linked_node.h"

using std::vector;
using std::string;
using data_structures::construct_linked_list;
using data_structures::Node;
using data_structures::free_linked_list;


Node<int>* merge_linked_list(Node<int>* left, Node<int>* right)
{
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node<int>* head = nullptr;
    if ( left->data_ <= right->data_ ) {
        head = left;
        Node<int>* sorted_right = merge_linked_list(left->next_, right);
        left->next_ = sorted_right;
    } else {
        head = right;
        Node<int>* sorted_left = merge_linked_list(left, right->next_);
        right->next_ = sorted_left;
    }
    return head;
}

int main()
{
    vector<int> tc1_v1{1, 2, 3};
    vector<int> tc1_v2{4, 5, 6};
    vector<int> tc1_v3{1, 2, 3, 4, 5, 6};

    Node<int>* tc1_l1 = construct_linked_list(tc1_v1);
    Node<int>* tc1_l2 = construct_linked_list(tc1_v2);
    Node<int>* tc1_l3 = construct_linked_list(tc1_v3);

    assert( linked_lists_equal(merge_linked_list(tc1_l1, tc1_l2), tc1_l3) );
    // free_linked_list(tc1_l1);
    // free_linked_list(tc1_l2);
    // free_linked_list(tc1_l3);


    vector<int> tc2_v1{1, 3, 5};
    vector<int> tc2_v2{2, 4, 6};
    vector<int> tc2_v3{1, 2, 3, 4, 5, 6};

    Node<int>* tc2_l1 = construct_linked_list(tc2_v1);
    Node<int>* tc2_l2 = construct_linked_list(tc2_v2);
    Node<int>* tc2_l3 = construct_linked_list(tc2_v3);

    assert( linked_lists_equal(merge_linked_list(tc2_l1, tc2_l2), tc2_l3) );
    // free_linked_list(tc2_l1);
    // free_linked_list(tc2_l2);
    // free_linked_list(tc2_l3);

    vector<int> tc3_v1{4, 4, 7};
    vector<int> tc3_v2{1, 5, 6};
    vector<int> tc3_v3{1, 4, 4, 5, 6, 7};

    Node<int>* tc3_l1 = construct_linked_list(tc3_v1);
    Node<int>* tc3_l2 = construct_linked_list(tc3_v2);
    Node<int>* tc3_l3 = construct_linked_list(tc3_v3);

    assert( linked_lists_equal(merge_linked_list(tc3_l1, tc3_l2), tc3_l3) );
    // free_linked_list(tc3_l1);
    // free_linked_list(tc3_l2);
    // free_linked_list(tc3_l3);

    return 0;
}
