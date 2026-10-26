/**
 * EPI Chapter 14 Sorting
 *
 * 14.9 Implement a fast sorting algorithm for lists.
 *
 * Implement a routine which sorts lists efficiently. It should be a stable
 * sort, i.e., the relative positions of equal elements must remain unchanged.
 *
 * Hint: In what respects are lists superior to arrays?
 */

#include <cassert>
#include <algorithm>
#include <memory>
#include <cstdio>

#include "../data_structures/doubly_linked_list.hpp"

using data_structures::ListNode;

using pListNode = shared_ptr<ListNode<int>>;

void PrintLinkedList(pListNode list)
{
    while (list != nullptr ) {
        printf("%d ", list->getData());
        list = list->getNext();
    }
    printf("\n");
}

pListNode MergeTwoSortedLists(pListNode l1, pListNode l2)
{
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    pListNode head = nullptr;
    pListNode next = nullptr;
    if (l1->getData() < l2->getData()) {
        head = l1;
        next = MergeTwoSortedLists(l1->getNext(), l2);
        l1->setNext(next);
        next->setPrev(head);
    } else {
        head = l2;
        next = MergeTwoSortedLists(l1, l2->getNext());
        l2->setNext(next);
        next->setPrev(head);
    }

    return head;
}

void SplitList(pListNode& head, pListNode* a, pListNode* b)
{
    pListNode fast = head->getNext();
    pListNode slow = head;
    
    while (fast != nullptr) {
        fast = fast->getNext();
        if (fast != nullptr) {
            fast = fast->getNext();
            slow = slow->getNext();
        }
    }

    *b = slow->getNext();
    slow->setNext(nullptr);
    (*b)->setPrev(nullptr);
    *a = head;
}

void MergeSortList(pListNode* head)
{
    if ( head == nullptr || *head == nullptr || (*head)->getNext() == nullptr) 
        return;
    pListNode a = nullptr, b = nullptr;
    SplitList(*head, &a, &b);
    MergeSortList(&a);
    MergeSortList(&b);
    *head = MergeTwoSortedLists(a, b);
}

int main()
{
    pListNode tc1_head      (make_shared<ListNode<int>>(4));
    pListNode tc1_1         (make_shared<ListNode<int>>(1));
    tc1_head->setNext(tc1_1);
    tc1_1->setPrev(tc1_head);

    pListNode tc1_2         (make_shared<ListNode<int>>(9));
    tc1_1->setNext(tc1_2);
    tc1_2->setPrev(tc1_1);

    pListNode tc1_3         (make_shared<ListNode<int>>(10));
    tc1_2->setNext(tc1_3);
    tc1_3->setPrev(tc1_2);

    pListNode tc1_4         (make_shared<ListNode<int>>(0));
    tc1_3->setNext(tc1_4);
    tc1_4->setPrev(tc1_3);

    PrintLinkedList(tc1_head);
    MergeSortList(&tc1_head);

    // pListNode a = nullptr;
    // pListNode b = nullptr;
    // SplitList(tc1_head, a, b);
    PrintLinkedList(tc1_head);
    return 0;
}
