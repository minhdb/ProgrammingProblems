/**
 * EPI Chapter 08 Linked Lists
 *
 * Implement even-odd merge.
 *
 * Consider a singly linked list whose nodes are numbered starting from 0.
 * Define the even-odd merge of the list to be the list consisting of the even
 * numbered nodes followed by the odd-numbered nodes. Example
 *
 * Input:
 *  0 -> 1 -> 2 -> 3 -> 4
 *
 *  0 -> 2 -> 4 -> 1 -> 3
 *
 * Write a program that computes the even-odd merge.
 *
 * Hint: use temporary additional storage.
 */

#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <set>
#include <map>
#include <cstdio>

#include "../data_structures/singly_linked_list.hpp"

using std::vector;
using std::stack;
using std::queue;
using std::unordered_map;
using std::set;
using std::map;
using std::make_shared;
using std::shared_ptr;

using data_structures::ListNode;
using pListNode = shared_ptr<ListNode<int>>;

void PrintLinkedList(const pListNode& head)
{
    if (head == nullptr) printf("Empty list.");
    for (pListNode tmp = head; tmp != nullptr; tmp = tmp->getNext()) {
        printf("%d ", tmp->getData());
    }
    printf("\n");
}

/**
 * Solution from EPI: have an index and split the list into 2 lists: even and
 * odd lists. At the end append the odd list to the even list.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
void EvenOddMergeEPI(pListNode& head)
{
    pListNode evenList = head;
    pListNode oddList = head->getNext();

    if (oddList == nullptr || oddList->getNext() == nullptr) return;

    pListNode evenIter = evenList;
    pListNode oddIter = oddList;
    do {
        evenIter->setNext(oddIter->getNext());
        evenIter = evenIter->getNext();

        if (evenIter != nullptr) {
            oddIter->setNext(evenIter->getNext());
            oddIter = oddIter->getNext();
        }
    } while (evenIter != nullptr && oddIter != nullptr);

    pListNode pTmp = evenList;
    while (pTmp->getNext() != nullptr) pTmp = pTmp->getNext();
    pTmp->setNext(oddList);
}

/**
 * Singly storage solution: Unlink and store all odd nodes somewhere.
 * And re-append them at the end.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
void EvenOddMergeOpt(pListNode& head)
{
    vector<pListNode> storage;
    pListNode pTmp = head->getNext();
    pListNode pPrev = head;
    while (pTmp != nullptr) {
        // Add the current odd node to the storage.
        storage.emplace_back(pTmp);

        // Unlink the previous even node with the current odd node
        // and set its next node to be the next even node.
        pPrev->setNext(pTmp->getNext());
        pPrev = pTmp->getNext();

        if (pTmp->getNext() != nullptr) {
            pTmp = pTmp->getNext()->getNext();
        } else {
            pTmp = pTmp->getNext();
        }
    }
    
    pTmp = head;
    while (pTmp->getNext() != nullptr) pTmp = pTmp->getNext();
    for (auto oddNode : storage) {
        pTmp->setNext(oddNode);
        pTmp = oddNode;
    }
    pTmp->setNext(nullptr);
}


/**
 * Brute Force solution: iterate through the list and construct a new list
 * keeping tracked of odd-even nodes using an indexing variable.
 *
 * Time complexity: O(n) -- Traversing n nodes.
 * Space complexity: O(n) -- 1 more copy of the linked list + 1 array-based
 * storage.
 */
pListNode EvenOddMergeBF(pListNode head)
{
    pListNode pTmp = head;

    vector<pListNode> storage;
    while (pTmp != nullptr) {
        storage.emplace_back(pTmp);
        pTmp = pTmp->getNext();
    }

    pListNode newHead = make_shared<ListNode<int>>(ListNode<int>(head->getData()));
    pTmp = newHead;
    pListNode newNode = nullptr;
    for (size_t i = 2; i < storage.size(); i += 2) {
        newNode = make_shared<ListNode<int>>(ListNode<int>(storage[i]->getData()));
        pTmp->setNext(newNode);
        pTmp = newNode;
    }

    for (size_t i = 1; i < storage.size(); i += 2) {
        newNode = make_shared<ListNode<int>>(ListNode<int>(storage[i]->getData()));
        pTmp->setNext(newNode);
        pTmp = newNode;
    }

    return newHead;
}

int main()
{
    // Test case 1.
    pListNode tc1_head      (new ListNode<int>(0x0));
    pListNode tc1_n1        (new ListNode<int>(0x1));
    pListNode tc1_n2        (new ListNode<int>(0x2));
    pListNode tc1_n3        (new ListNode<int>(0x3));
    pListNode tc1_n4        (new ListNode<int>(0x4));
    pListNode tc1_n5        (new ListNode<int>(0x5));

    tc1_head->setNext(tc1_n1);
    tc1_n1->setNext(tc1_n2);
    tc1_n2->setNext(tc1_n3);
    tc1_n3->setNext(tc1_n4);
    tc1_n4->setNext(tc1_n5);

    printf("BF solution:\n");
    PrintLinkedList(tc1_head);
    pListNode tc1_res = EvenOddMergeBF(tc1_head);
    PrintLinkedList(tc1_res);

    // printf("Singly storage solution:\n");
    printf("EPI solution:\n");
    PrintLinkedList(tc1_head);
    EvenOddMergeEPI(tc1_head);
    PrintLinkedList(tc1_head);

    // Test case 2.
    pListNode tc2_head      (new ListNode<int>(0x0));

    printf("BF solution:\n");
    PrintLinkedList(tc2_head);
    pListNode tc2_res = EvenOddMergeBF(tc2_head);
    PrintLinkedList(tc2_res);

    // printf("Singly storage solution:\n");
    printf("EPI solution:\n");
    PrintLinkedList(tc2_head);
    EvenOddMergeEPI(tc2_head);
    PrintLinkedList(tc2_head);

    // Test case 3.
    pListNode tc3_head      (new ListNode<int>(0x0));
    pListNode tc3_n1        (new ListNode<int>(0x1));
    tc3_head->setNext(tc3_n1);

    printf("BF solution: \n");
    PrintLinkedList(tc3_head);
    pListNode tc3_res = EvenOddMergeBF(tc3_head);
    PrintLinkedList(tc3_res);

    // printf("Singly storage solution:\n");
    printf("EPI solution:\n");
    PrintLinkedList(tc3_head);
    EvenOddMergeEPI(tc3_head);
    PrintLinkedList(tc3_head);

    // Test case 4.
    pListNode tc4_head      (new ListNode<int>(0x0));
    pListNode tc4_n1        (new ListNode<int>(0x1));
    pListNode tc4_n2        (new ListNode<int>(0x2));
    tc4_head->setNext(tc4_n1);
    tc4_n1->setNext(tc4_n2);

    printf("BF solution: \n");
    PrintLinkedList(tc4_head);
    pListNode tc4_res = EvenOddMergeBF(tc4_head);
    PrintLinkedList(tc4_res);

    // printf("Singly storage solution:\n");
    printf("EPI solution:\n");
    PrintLinkedList(tc4_head);
    EvenOddMergeEPI(tc4_head);
    PrintLinkedList(tc4_head);

    // Test case 5.
    pListNode tc5_head      (new ListNode<int>(0x0));
    pListNode tc5_n1        (new ListNode<int>(0x1));
    pListNode tc5_n2        (new ListNode<int>(0x2));
    pListNode tc5_n3        (new ListNode<int>(0x3));
    pListNode tc5_n4        (new ListNode<int>(0x4));
    pListNode tc5_n5        (new ListNode<int>(0x5));
    pListNode tc5_n6        (new ListNode<int>(0x6));

    tc5_head->setNext(tc5_n1);
    tc5_n1->setNext(tc5_n2);
    tc5_n2->setNext(tc5_n3);
    tc5_n3->setNext(tc5_n4);
    tc5_n4->setNext(tc5_n5);
    tc5_n5->setNext(tc5_n6);

    printf("BF solution:\n");
    PrintLinkedList(tc5_head);
    pListNode tc5_res = EvenOddMergeBF(tc5_head);
    PrintLinkedList(tc5_res);

    // printf("Singly storage solution:\n");
    printf("EPI solution:\n");
    PrintLinkedList(tc5_head);
    EvenOddMergeEPI(tc5_head);
    PrintLinkedList(tc5_head);
    return 0;
}
