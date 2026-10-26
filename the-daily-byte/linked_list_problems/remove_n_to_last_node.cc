/**
 * The Daily Byte 06/03/2021
 *
 * Remove Nth to last node
 * Given a linked list and a value n, remove the nth to last node and return
 * the resulting list.
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


Node<int>* remove_n_to_last_node(Node<int>*& head, int n)
{
    // Find the length of the linked list.
    int list_len = 0;
    Node<int>* tmp = head;
    while (tmp != nullptr) {
        list_len++;
        tmp = tmp->next_;
    }

    // Delete the node in the list_len - n.
    if (list_len < n) {
        // Do nothing if n > list_len.
    }
    else if ( list_len == n ) {
        // Delete head.
        Node<int>* tmp = head;
        head = head->next_;
        delete tmp;
    } else {
        // Delete the nth node from the last node.
        int pos = list_len - n;
        int index = 0;
        Node<int>* tmp = head;
        Node<int>* prev = nullptr;
        while (index < pos) {
            prev = tmp;
            tmp = tmp->next_;
            index++;
        }

        prev->next_ = tmp->next_;
        delete tmp;
    }

    return head;
}

int main()
{
    vector<int> tc1{1, 2, 3};
    vector<int> tc1_res{1, 2};
    int tc1_n = 1;

    Node<int>* tc1_l = construct_linked_list(tc1);
    Node<int>* tc1_rl = construct_linked_list(tc1_res);

    Node<int>* tc1_re = remove_n_to_last_node(tc1_l, tc1_n);
    assert( linked_lists_equal(tc1_re, tc1_rl) );
    
    vector<int> tc2{1, 2, 3};
    vector<int> tc2_res{1, 3};
    int tc2_n = 2;

    Node<int>* tc2_l = construct_linked_list(tc2);
    Node<int>* tc2_rl = construct_linked_list(tc2_res);

    Node<int>* tc2_re = remove_n_to_last_node(tc2_l, tc2_n);
    assert( linked_lists_equal(tc2_re, tc2_rl) );

    vector<int> tc3{1, 2, 3};
    vector<int> tc3_res{2, 3};
    int tc3_n = 3;

    Node<int>* tc3_l = construct_linked_list(tc3);
    Node<int>* tc3_rl = construct_linked_list(tc3_res);

    Node<int>* tc3_re = remove_n_to_last_node(tc3_l, tc3_n);
    assert( linked_lists_equal(tc3_re, tc3_rl) );


    vector<int> tc4{1, 2, 3, 4, 5, 6};
    vector<int> tc4_res{1, 2, 3, 4, 5};
    int tc4_n = 1;

    Node<int>* tc4_l = construct_linked_list(tc4);
    Node<int>* tc4_rl = construct_linked_list(tc4_res);

    Node<int>* tc4_re = remove_n_to_last_node(tc4_l, tc4_n);
    assert( linked_lists_equal(tc4_re, tc4_rl) );
    return 0;
}
