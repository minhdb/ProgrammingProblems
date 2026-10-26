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
}

pListNode ReverseLinkedListHelper(pListNode head, pListNode& new_head, pListNode prev)
{
    if (head == nullptr) return nullptr;
    if (head->getNext() == nullptr) new_head = head;
    pListNode reversed_next_list = ReverseLinkedListHelper(head->getNext(), new_head, prev);
    if (reversed_next_list != nullptr) reversed_next_list->setNext(head);
    return head;
}

void ReverseLinkedListRecursive(pListNode head)
{
    ReverseLinkedListHelper(head, head, nullptr);
}

void ReverseLinkedListIterative(pListNode& head)
{
    if (head == nullptr) return;

    pListNode prev = nullptr;
    pListNode idx1 = head;
    pListNode idx2 = idx1->getNext();

    while (idx1 != nullptr) {
        idx1->setNext(prev);
        prev = idx1;
        idx1 = idx2;

        if (idx2 != nullptr)
            idx2 = idx2->getNext();
    }

    head = prev;
}

int main()
{
    /*
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
    return 0;
}
