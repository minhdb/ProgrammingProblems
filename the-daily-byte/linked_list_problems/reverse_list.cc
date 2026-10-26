/**
 * The Daily Byte 06/08/2021
 * Given a linked list containing unique values, reverse it, and return the result.
 * Note: Reverse in place. Do not create a new node. Return the reference to
 * the new head node.
 */


#include <vector>
#include <cassert>
#include <stack>

#include "../data_structures/singly_linked_node.h"

using std::vector;

using data_structures::Node;
using data_structures::construct_linked_list;
using data_structures::free_linked_list;
using data_structures::print_list;

Node<int>* reverse_list_iterative(Node<int>*& head)
{
    Node<int>* tmp = head;
    vector<Node<int>*> s;
    while (tmp != nullptr) {
        s.push_back(tmp);
        tmp = tmp->next_;
    }

    if (s.empty()) return nullptr;

    tmp = s[s.size() - 1];

    for (int i = s.size() - 2; i >= 0; i--) {
        tmp->next_ = s[i];
        tmp = s[i];
    }
    
    tmp->next_ = nullptr;
    head = s[s.size() - 1];
    return head;
}

// Node<int>* reverse_list_recursive_aux(Node<int>* node)
// {
//    if (node == nullptr) return nullptr;
//    if (node->next_ == nullptr) return node;
//    Node<int>* tmp = reverse_list_recursive_aux(node->next_);
//    node->next_ = nullptr;
//    tmp->next_ = node;
//    return tmp;
// }
//
// Node<int>* reverse_list_recursive(Node<int>*& head)
// {
//    head = reverse_list_recursive_aux(head);
//    return head;
// }

int main()
{   
    vector<int> tc1 {1, 2, 3};
    Node<int>* tc1_list = construct_linked_list(tc1);
    vector<int> tc1_res {3, 2, 1};
    Node<int>* tc1_resl = construct_linked_list(tc1_res);
    // reverse_list_iterative(tc1_list);
    // print_list(tc1_list);
    // assert(linked_lists_equal(tc1_resl, reverse_list_recursive(tc1_list)));
    assert(linked_lists_equal(tc1_resl, reverse_list_iterative(tc1_list)));
    free_linked_list(tc1_list);
    free_linked_list(tc1_resl);

    vector<int> tc2 {7, 15 ,9 ,2};
    Node<int>* tc2_list = construct_linked_list(tc2);
    vector<int> tc2_res {2, 9, 15, 7};
    Node<int>* tc2_resl = construct_linked_list(tc2_res);
    // assert(linked_lists_equal(tc2_resl, reverse_list_recursive(tc2_list)));
    assert(linked_lists_equal(tc2_resl, reverse_list_iterative(tc2_list)));
    free_linked_list(tc2_list);
    free_linked_list(tc2_resl);

    vector<int> tc3 { 1 };
    Node<int>* tc3_list = construct_linked_list(tc3);
    vector<int> tc3_res {1};
    Node<int>* tc3_resl = construct_linked_list(tc3_res);
    // assert(linked_lists_equal(tc3_resl, reverse_list_recursive(tc3_list)));
    assert(linked_lists_equal(tc3_resl, reverse_list_iterative(tc3_list)));
    free_linked_list(tc3_list);
    free_linked_list(tc3_resl);
    return 0;
}
