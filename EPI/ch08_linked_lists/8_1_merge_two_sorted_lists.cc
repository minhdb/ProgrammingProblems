/**
 * EPI Chapter 08 Linked Lists
 *
 * Consider 2 singly linked lists in which each nodes holds a number. Assume
 * the lists are sorted, i.e., numbers in the lists appear in ascending order
 * within each list. The merge of the 2 lists is a list consisting of the nodes
 * of the 2 lists in which numbers appear in ascending order.
 *
 * Write a program that takes 2 lists, assumed to be sorted, and return their
 * merge. The only field your program can change in a node is its next field.
 *
 * Hint: 2 sorted arrays can be merged using 2 indices. For lists, take care
 * when one iterator reaches the end.
 */

#include <memory>
#include <cassert>
#include <cstdio>

#include "../data_structures/singly_linked_list.hpp"

using std::shared_ptr;
using std::make_shared;

using data_structures::SinglyLinkedList;
using data_structures::ListNode;

using pListNode = shared_ptr<ListNode<int>>;

void printList(const pListNode ll)
{
    pListNode tmp = ll;
    while (tmp != nullptr) {
        printf("%d ", tmp->getData());
        tmp = tmp->getNext();
    }
    printf("\n");
}

/**
 * Time complexity: O(l1 + l2)
 * Space complexity: O(max(l1, l2))
 */
pListNode MergeTwoSortedList(pListNode l1, pListNode l2)
{
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    pListNode new_head;
    if (l1->getData() < l2->getData()) {
        new_head = l1;
        new_head->setNext(MergeTwoSortedList(l1->getNext(), l2));
    } else {
        new_head = l2;
        new_head->setNext(MergeTwoSortedList(l1, l2->getNext()));
    }

    return new_head;
}

pListNode MergeTwoSortedListIter(pListNode l1, pListNode l2)
{
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    pListNode new_head = make_shared<ListNode<int>>();
    pListNode tail = new_head;

    pListNode p1 = l1;
    pListNode p2 = l2;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->getData() < p2->getData()) {
            tail->setNext(p1);
            tail = p1;            
            p1 = p1->getNext();
        } else {
            tail->setNext(p2);
            tail = p2;
            p2 = p2->getNext();
        }
    }

    // Add the rest of the remaining nodes from either l1 or l2.
    if (p1 != nullptr) tail->setNext(p1);
    if (p2 != nullptr) tail->setNext(p2);

    return new_head->getNext();

}

int main()
{
    pListNode l11       (new ListNode<int>);
    pListNode l12       (new ListNode<int>);
    pListNode l13       (new ListNode<int>);
    l11->setData(2);
    l12->setData(5);
    l13->setData(7);

    l11->setNext(l12);
    l12->setNext(l13);

    pListNode l21       (new ListNode<int>);
    pListNode l22       (new ListNode<int>);
    l21->setData(3);
    l22->setData(11);

    l21->setNext(l22);

    // pListNode mergedl1l2 = MergeTwoSortedList(l11, l21);
    pListNode mergedl1l2 = MergeTwoSortedListIter(l11, l21);
    printList(mergedl1l2);

    return 0;
}
