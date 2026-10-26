/**
 * EPI Chapter 11 Heaps
 *
 * 07/20/2021
 * Implement a queue API using a heap.
 *
 * We discussed the notion of reduction when describing problem solving
 * patterns. Usually, reductions are used to solve more complex problem
 * using a solution to a simpler problem as a subroutine.
 * Ocassionally it makes sense to go the other way--for example, if we need
 * the functionality of a heap, we can use a BST library, which is more
 * commonly available, with modest performance penalties with respect, for
 * example, to an array-based implementation of a heap.
 *
 * How would you implement a queue API using a heap?
 */

#include <queue>
#include <vector>
#include <stdexcept>
#include <cassert>

using std::priority_queue;
using std::vector;

/**
 * Idea: We store our customized data structure within our priority queue.
 *
 * Our customized data structure has a T field, which is the actual object
 * that we push onto the stack.
 * The other field is possibly an integer that encode the priority of the
 * pushed object.
 *
 * When we insert new object, we get the priority of the current top.
 * Add 1 to it. And set it to be the priority score of the new object.
 *
 * Use a max_heap here. A min_heap is also possible.
 */

template <class T>
class HeapQueue
{
public:
    struct QueueObject
    {
        bool operator<(const QueueObject& so) const
        {
            return priority < so.priority;
        }

        T object;
        size_t priority;
    };

    HeapQueue() : timestamp_(0) {}

    /**
     * Time complexity: O(1)
     */
    T Top()
    {
        if (Empty())
            throw std::length_error("Top(): Empty stack");
        T cur_top = pq.top().object;
        return cur_top;
    }

    /**
     * Time complexity: O(logn)
     */
    void Pop()
    {
        if (Empty())
            throw std::length_error("Pop(): Empty stack");

        pq.pop();
    }

    /**
     * Time complexity: O(logn)
     */
    void Push(T obj)
    {
        pq.emplace(QueueObject{obj, timestamp_ + 1});
    }

    size_t Size() { return pq.size(); }

    bool Empty() { return pq.empty(); }
private:
    size_t timestamp_;
    priority_queue<QueueObject, vector<QueueObject>, std::less<>> pq;
};

int main()
{
    HeapQueue<char> tc1_so;
    assert(tc1_so.Empty());
    assert(tc1_so.Size() == 0);

    tc1_so.Push('a');
    assert(!tc1_so.Empty());
    assert(tc1_so.Size() == 1);
    assert(tc1_so.Top() == 'a');
    
    tc1_so.Pop();
    assert(tc1_so.Empty());
    assert(tc1_so.Size() == 0);

    tc1_so.Push('a');
    tc1_so.Push('b');
    tc1_so.Push('c');
    assert(tc1_so.Size() == 3);

    assert(tc1_so.Top() == 'a');
    tc1_so.Pop();
    assert(tc1_so.Top() == 'b');
    tc1_so.Pop();
    assert(tc1_so.Top() == 'c');
    tc1_so.Pop();

    assert(tc1_so.Empty());
    assert(tc1_so.Size() == 0);
    
    return 0;
}
