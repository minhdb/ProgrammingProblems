/**
 * EPI - Chapter 08 Linked Lists
 *
 * Without knowing the length of a linked list, it is not trivial to delete the
 * kth last element in a singly linked list.
 *
 * Given a singly linked list and an integer k, write a program to remove the
 * kth last element from the list. Your algorithm cannot use more than a few
 * words of storage, regardless of the length of the list. In particular, you
 * cannot assume that it is possible to record the length of the list.
 *
 * Hint: If you know the length of the list, can you find the kth last node
 * using 2 iterators?
 */

#include <memory>
#include <cassert>
#include <vector>
#include <cstdio>

#include "../data_structures/singly_linked_list.hpp"

using std::shared_ptr;
using std::make_shared;

using data_structures::ListNode;

using pListNode = std::shared_ptr<ListNode<int>>;

void PrintLinkedList(const pListNode& head)
{
    if (head == nullptr) printf("Empty list.");
    for (pListNode it = head; it != nullptr; it = it->getNext()) {
        printf("%d ", it->getData());
    }
    printf("\n");
}

/**
 * EPI solution
 * Have 2 iterators. The first one is kth node ahead of the second one.
 * When the first iterator reaches the end of the linked list, the second
 * one is around the kth lastest node.
 *
 * Have to add code to deal with the case k is larger than or equals to the
 * length of the linked list.
 */
void DeleteKthLastElementEPI(pListNode& head, size_t k)
{
    pListNode p_first = head;

    // This is the node immediately precedes the kth lastest node.
    // Use a dummy node in case the node we want to delete is the
    // head node.
    pListNode dummy = make_shared<ListNode<int>>();
    dummy->setNext(head);
    pListNode p_second = dummy;


    while (k-- && p_first != nullptr) {
        p_first = p_first->getNext();
    }

    while (p_first != nullptr) {
        p_first = p_first->getNext();
        p_second = p_second->getNext();
    }

    // if (p_second == dummy) {
    //    head = head->getNext();
    // } else {
        p_second->setNext(p_second->getNext()->getNext());
    // }
}

/**
 * Calculating the length of the linked list here. Slow because we need to
 * traverse the linked list twice. Assuming we have 1000000 list nodes and
 * and k 92139th, it's not fast enough.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
void DeleteKthLastElement(pListNode& head, size_t k)
{
    pListNode p_first = head;
    pListNode p_second = head;

    // Assuming we have the length of the linked list by traversing
    // the list.
    size_t len = 0;
    while (p_first != nullptr) {
        len++;
        p_first = p_first->getNext();
    }

    // The kth last element is simply at l - k th position from the beginning.
    p_first = head;
    len = len - k;
    while (len--) {
        p_second = p_first;
        p_first = p_first->getNext();
    }

    // Remove the node from the linked list.
    if (p_first == head) {
        head = head->getNext();
    } else {
        p_second->setNext(p_first->getNext());
    }
}

int main()
{
    // Test case 1.
    pListNode tc1_head      (new ListNode<int>(0x1));
    pListNode tc1_n1        (new ListNode<int>(0x2));
    pListNode tc1_n2        (new ListNode<int>(0x3));
    pListNode tc1_n3        (new ListNode<int>(0x4));
    pListNode tc1_n4        (new ListNode<int>(0x5));

    tc1_head->setNext(tc1_n1);
    tc1_n1->setNext(tc1_n2);
    tc1_n2->setNext(tc1_n3);
    tc1_n3->setNext(tc1_n4);

    size_t tc1_k = 5;
    // DeleteKthLastElement(tc1_head, tc1_k);
    DeleteKthLastElementEPI(tc1_head, tc1_k);
    PrintLinkedList(tc1_head);
    
    // Test case 2.
    pListNode tc2_head      (new ListNode<int>(0x1));
    pListNode tc2_n1        (new ListNode<int>(0x2));

    tc2_head->setNext(tc2_n1);

    size_t tc2_k = 1;
    DeleteKthLastElementEPI(tc2_head, tc2_k);
    PrintLinkedList(tc2_head);

    // Test case 3.
    pListNode tc3_head      (new ListNode<int>(0x1));
    size_t tc3_k = 1;
    DeleteKthLastElementEPI(tc3_head, tc3_k);
    PrintLinkedList(tc3_head);

    return 0;
}
