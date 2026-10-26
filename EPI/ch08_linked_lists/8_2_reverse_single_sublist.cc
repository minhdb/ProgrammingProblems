/**
 * EPI - Chapter 08 Linked Lists
 *
 * 06/27/2021
 *
 * This problem is concerned with reversing a sublist within a list.
 *
 * Write a program which takes a singly linked list L and 2 integers s and f
 * as arguments, and reverse the order of the nodes from the sth node to fth
 * node, inclusive. The numbering begins at 1, i.e., the head node is the first
 * node. Do not allocate additional nodes.
 *
 * 11 -> 3 -> 5 -> 7 -> 2
 *
 * 11 -> 7 -> 5 -> 3 -> 2
 *
 * Hint: Focus on the successor fields which needed to be updated.
 */

#include "../data_structures/singly_linked_list.hpp"

#include <cassert>
#include <cstdio>
#include <memory>
#include <stack>

using std::make_shared;
using std::shared_ptr;

using std::stack;

using data_structures::SinglyLinkedList;
using data_structures::ListNode;

using pListNode = shared_ptr<ListNode<int>>;

void PrintList(const pListNode& ll)
{
    pListNode tmp = ll;
    while (tmp != nullptr) {
        printf("%d ", tmp->getData());
        tmp = tmp->getNext();
    }
    printf("\n");
}

void ReverseSublist(pListNode& ll, int s, int f)
{
    pListNode first_prev = nullptr;
    pListNode second_next = nullptr;
    pListNode cur = nullptr;
    pListNode tmp = nullptr;
    pListNode prev = nullptr;
    pListNode first = nullptr;
    pListNode second = nullptr;

    // Find the first node.
    first = ll;
    while (s-- > 2) {
        first = first->getNext();
    }

    // Get the node before the first node.
    first_prev = first;

    first = first->getNext();

    // Find the second node.
    second = ll;
    while (f-- > 1) {
        second = second->getNext();
    }
    // Get the node after the second node.
    second_next = second->getNext();

    // Begin reversing.
    // Fix the previous node of first next pointer.
    if (first_prev != nullptr) first_prev->setNext(second);
    prev = first;
    cur = first->getNext();

    while (cur != second_next) {
        tmp = cur->getNext();
        cur->setNext(prev);
        prev = cur;
        cur = tmp;
    }

    // Fix the first node's pointer.
    first->setNext(second_next);
}

pListNode ReverseSublistSolution(pListNode LL, int start, int finish)
{
    if (start == finish) return LL;

    pListNode dummy_head = make_shared<ListNode<int>>(ListNode<int>());
    dummy_head->setNext(LL);
    pListNode sublist_head = dummy_head;

    int k = 1;
    while (k++ < start) {
        sublist_head = sublist_head->getNext();
    }

    // Reverse sublist.
    pListNode sublist_iter = sublist_head->getNext();
    while (start++ < finish) {
        pListNode tmp = sublist_iter->getNext();
        sublist_iter->setNext(tmp->getNext());
        tmp->setNext(sublist_head->getNext());
        sublist_head->setNext(tmp);
    }

    return dummy_head->getNext();
}

int main()
{
    /*
     * Test case 1.
     * 11 -> 3 -> 5 -> 7 -> 2
     *
     * 11 -> 7 -> 5 -> 3 -> 2
     */
    pListNode tc1_head      (new ListNode<int>(11));
    pListNode tc1_n1        (new ListNode<int>(3));
    pListNode tc1_n2        (new ListNode<int>(5));
    pListNode tc1_n3        (new ListNode<int>(7));
    pListNode tc1_n4        (new ListNode<int>(2));

    tc1_head->setNext(tc1_n1);
    tc1_n1->setNext(tc1_n2);
    tc1_n2->setNext(tc1_n3);
    tc1_n3->setNext(tc1_n4);
    PrintList(tc1_head);
    // ReverseSublist(tc1_head, 2, 4);
    ReverseSublistSolution(tc1_head, 2, 4);
    PrintList(tc1_head);
    printf("\n");

    /*
     * Test case 2.
     * 11 -> 3 -> 5 -> 7 -> 9 -> 2
     *
     * 11 -> 9 -> 7 -> 5 -> 3 -> 2
     */
    pListNode tc2_head      (new ListNode<int>(11));
    pListNode tc2_n1        (new ListNode<int>(3));
    pListNode tc2_n2        (new ListNode<int>(5));
    pListNode tc2_n3        (new ListNode<int>(7));
    pListNode tc2_n4        (new ListNode<int>(9));
    pListNode tc2_n5        (new ListNode<int>(2));

    tc2_head->setNext(tc2_n1);
    tc2_n1->setNext(tc2_n2);
    tc2_n2->setNext(tc2_n3);
    tc2_n3->setNext(tc2_n4);
    tc2_n4->setNext(tc2_n5);
    PrintList(tc2_head);
    // ReverseSublist(tc2_head, 2, 5);
    ReverseSublistSolution(tc2_head, 2, 5);
    PrintList(tc2_head);
    printf("\n");

    /*
     * Test case 3
     * 1 -> 2 -> 3
     */
    pListNode tc3_head      (new ListNode<int>(1));
    pListNode tc3_n1        (new ListNode<int>(2));
    pListNode tc3_n2        (new ListNode<int>(3));

    tc3_head->setNext(tc3_n1);
    tc3_n1->setNext(tc3_n2);
    PrintList(tc3_head);
    // ReverseSublist(tc3_head, 2, 3);
    ReverseSublistSolution(tc3_head, 2, 3);
    PrintList(tc3_head);

    return 0;
}
