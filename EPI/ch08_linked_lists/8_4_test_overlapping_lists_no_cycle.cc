/**
 * EPI Chapter 08 Linked Lists
 *
 * Test for overlapping lists - lists are cycle-free
 *
 * Write a program that takes 2 cycle-free singly linked lists, and determines
 * if there exists a node that is common to both lists.
 *
 * Hint: Solve the simple case first.
 */

#include <memory>
#include <cassert>

#include "../data_structures/singly_linked_list.hpp"

using std::shared_ptr;
using std::make_shared;

using data_structures::ListNode;

using pListNode = shared_ptr<ListNode<int>>;

/**
 * First solution using a hash table: traverse the first list. Adding
 * nodes to the hash table.
 *
 * Traverse the second list. Check for the node existence in the hash table.
 * If there is, return it.
 *
 * Time complexity: O(max(n, m))
 * Space complexity: O(n)
 */


/**
 * Observation: 2 lists overlap if and only if the last node belongs to both
 * lists.
 *
 * If 2 lists overlap, the first node that's common to both list is at
 *
 * If the lengths of 2 list are equal: the common node to both list can be
 * acquired by traversing the list until 2 pointers are the same.
 *
 * If the length of 2 list are different: The common node to both list can
 * be acquired by first traversing the longer list by
 * (larger_len - smaller_len) nodes. And then traverse both lists together.
 *
 *
 * Time complexity: O(max(n, m))
 * Space complexity: O(1)
 */
pListNode OverlappingNoCycleLists(pListNode head1, pListNode head2)
{
    size_t len1 = 0;
    size_t len2 = 0;
    size_t diff = 0;
    pListNode pTmp = nullptr;
    for (pTmp = head1; pTmp != nullptr; pTmp = pTmp->getNext())
        len1++;
    for (pTmp = head2; pTmp != nullptr; pTmp = pTmp->getNext())
        len2++;

    pListNode pStart1 = head1;
    pListNode pStart2 = head2;

    if (len2 > len1) {
        diff = len2 - len1;
        while (diff--) pStart2 = pStart2->getNext();
    } else if (len2 < len1) {
        diff = len1 - len2;
        while (diff--) pStart1 = pStart1->getNext();
    } else {

    }

    while (pStart1 != nullptr && pStart2 != nullptr) {
        if (pStart1 == pStart2) return pStart1;
        pStart1 = pStart1->getNext();
        pStart2 = pStart2->getNext();
    }

    return nullptr;
}

int main()
{
    // Test case 1.
    pListNode tc1_head1     (new ListNode<int>(0x1));
    pListNode tc1_head2     (new ListNode<int>(0x2));
    pListNode tc1_1n1       (new ListNode<int>(0x3));
    pListNode tc1_2n1       (new ListNode<int>(0x4));
    pListNode tc1_I1        (new ListNode<int>(0x5));
    pListNode tc1_I2        (new ListNode<int>(0x6));
    pListNode tc1_I3        (new ListNode<int>(0x7));

    tc1_head1->setNext(tc1_1n1);
    tc1_head2->setNext(tc1_2n1);
    tc1_1n1->setNext(tc1_I1);
    tc1_2n1->setNext(tc1_I1);
    tc1_I1->setNext(tc1_I2);
    tc1_I2->setNext(tc1_I3);

    assert(OverlappingNoCycleLists(tc1_head1, tc1_head2) == tc1_I1);

    return 0;
}


