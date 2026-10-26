/**
 * The Daily Byte 06/05/2021
 *
 * Given a non-empty linked list, return the middle node of the list. If the
 * linked list contains an even number of elements, return the node closer to
 * the end.
 */

#include <cassert>
#include <vector>
#include <cstdio>

#include "../data_structures/singly_linked_node.h"

using std::vector;
using data_structures::Node;
using data_structures::construct_linked_list;
using data_structures::free_linked_list;
using data_structures::linked_lists_equal;

Node<int>* return_mid_node(Node<int>*& head)
{
    Node<int>* tmp_node = head;
    
    // First count the number of node.
    size_t n = 0;
    while (tmp_node != nullptr) {
        n++;
        tmp_node = tmp_node->next_;
    }

    // printf("Count %zu\n", n);
    if (n == 1) return head;

    n >>= 1;
    // printf("Mid %zu\n", n);
    size_t i = 0; 
    tmp_node = head;
    while (i < n) {
        tmp_node = tmp_node->next_;
        i++;
    }
    return tmp_node;
}

int main()
{
    vector<int> tc1 {1, 2, 3};
    int tc1_res = 2;
    Node<int>* tc1_list = construct_linked_list(tc1);
    assert(return_mid_node(tc1_list)->data_ == tc1_res);
    free_linked_list(tc1_list);

    vector<int> tc2 {1, 2, 3, 4};
    int tc2_res = 3;
    Node<int>* tc2_list = construct_linked_list(tc2);
    assert(return_mid_node(tc2_list)->data_ == tc2_res);
    free_linked_list(tc2_list);

    vector<int> tc3;
    tc3.push_back(1);
    int tc3_res = 1;
    Node<int>* tc3_list = construct_linked_list(tc3);
    assert(return_mid_node(tc3_list)->data_ == tc3_res);
    free_linked_list(tc3_list);

    vector<int> tc4 {1, 2, 3, 4, 5};
    int tc4_res = 3;
    Node<int>* tc4_list = construct_linked_list(tc4);
    assert(return_mid_node(tc4_list)->data_ == tc4_res);
    free_linked_list(tc4_list);

    vector<int> tc5 {1, 2, 3, 4, 5, 6};
    int tc5_res = 4;
    Node<int>* tc5_list = construct_linked_list(tc5);
    assert(return_mid_node(tc5_list)->data_ == tc5_res);
    free_linked_list(tc5_list);

    return 0;
}
