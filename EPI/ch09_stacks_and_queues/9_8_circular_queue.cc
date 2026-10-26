/**
 * EPI Chapter 09 Stacks and Queues
 *
 * Implement a circular queue.
 *
 * A queue can be implemented using an array and 2 additional fields, the
 * beginning and the end indices. This structure is sometimes referred to
 * as a circular queue. Both enqueue and dequeue have O(1) time complexity.
 * If the array is fixed, there is a maximum number of entries that can be
 * stored. If the array is dynamically resized, the total time for m combined
 * enqueue and dequeue operations is O(m).
 *
 * Implement a queue API using an array for storing elements. Your API should
 * include a constructor function, which takes as argument the initial capacity
 * of the queue, enqueue and dequeue functions, and a function which returns
 * the number of elements stored. Implement dynamic resizing to support storing
 * an arbitrarily large number of elements.
 *
 * Hint: Track the head and tail. How can you differentiate a full queue from
 * an empty one?
 */

#include <vector>
#include <stdexcept>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <random>

using std::vector;

template <class T>
class CircularQueue
{
public:
    CircularQueue(size_t init_cap = 0x8) 
        : inner_(vector<T>(init_cap))
        , front_(0)
        , back_(0)
    {}

    /**
     * O(1) on average.
     */
    void Enqueue(T x)
    { 
        inner_[back_] = x;
        // std::cout << back_ << " " << x << "\n";
        back_++;
        // Check for boundaries.
        if (back_ == inner_.size()) {
            // Can't rely on Size() here to check for full queue
            // if back_ == front_.
            if (back_ == front_)
                Resize(true);
            else
                back_ = 0;
        } else {
            
        }

        if (back_ == front_)
            Resize(true);
    }

    /**
     * O(1) on average.
     */
    T Dequeue()
    {
        if (Empty())
            throw std::length_error("Dequeue(): empty queue");
        T res = inner_[front_];
        front_++;

        if (front_ == static_cast<long>(inner_.size())) front_ = 0;

        if (Size() < inner_.size() >> 0x1 && inner_.size() > 0x8) {
            Resize(false); 
        }

        return res;
    }

    T Front()
    {
        if (Empty())
            throw std::length_error("Front(): empty queue");
        return inner_[front_];
    }

    T Back()
    {
        if (Empty())
            throw std::length_error("Back(): empty queue");
        return back_ == 0 ? inner_[inner_.size() - 1] : inner_[back_-1];
    }

    /**
     * front_ and back_ might wrap around.
     */
    size_t Size() const
    {
        if (back_ >= front_) return back_ - front_;
        else return (static_cast<long>(inner_.size()) - front_ + back_);
    }

    /**
     * Queue is empty when front_ == back_.
     * This should never happen when we enqueue even when back_ wraps arround.
     */
    bool Empty() const
    {
        return front_ == back_;
    }

    void PrintQueueDebug()
    {
        std::cout << "## PRINT_QUEUE_DEBUG ##\n";
        if (Empty()) {
            std::cout << "Empty queue.";
        } else {
            for (const auto& e : inner_) {
                std::cout << e << " ";
            }
        }
        std::cout << "\n";
        std::cout << "Front idx: " << front_ << "\n";
        std::cout << "Back idx: " << back_ << "\n";
        std::cout << "Front: " << Front() << "\n";
        std::cout << "Back: " << Back() << "\n";
        std::cout << "Size: " << Size() << "\n";
        std::cout << "## END PRINT_QUEUE_DEBUG ##\n\n";
    }

    void PrintQueueContent()
    {
        std::cout << "## PRINT_QUEUE_CONTENT ##\n";
        if (Empty()) std::cout << "Empty queue.";
        else if (front_ < back_) {
            for (long i = front_; i < back_; i++) {
                std::cout << inner_[i] << " ";
            }
        } else {
            for (long i = front_; i < static_cast<long>(inner_.size()); i++) {
                std::cout << inner_[i] << " ";
            }

            for (long i = 0; i < back_; i++) {
                std::cout << inner_[i] << " ";
            }

        }
        std::cout << "\n";
        std::cout << "Maximum size: " << inner_.size() << "\n";
        std::cout << "## END PRINT_QUEUE_CONTENT ##\n\n";
    }

private:
    void Resize(bool is_extend)
    {
        if (is_extend) {
            // Only happens when back_ == front_.
            size_t i = 0;
            vector<T> new_inner(inner_.size() << 0x1);
            for (long j = front_; j < static_cast<long>(inner_.size()); j++) {
                new_inner[i++] = inner_[j];
            }
            
            if (back_ <= front_) {
                for (long j = 0; j < back_; j++) {
                    new_inner[i++] = inner_[j];
                }
            }

            inner_ = new_inner;
            front_ = 0;
            back_ = i;
        } else {
            // We shrinking.
            size_t i = 0;
            vector<T> new_inner(inner_.size() >> 0x1);
            if (front_ < back_) {
                for (long j = front_; j < back_; j++) {
                    new_inner[i++] = inner_[j];
               }
            } else {
                for (long j = front_; j < static_cast<long>(inner_.size()); j++) {
                    new_inner[i++] = inner_[j];
                }

                for (long j = 0; j < back_; j++) {
                    new_inner[i++] = inner_[j];
                }
            }

            inner_ = new_inner;
            front_ = 0;
            back_ = i;
        }
    }


    vector<T> inner_;

    // Queue is full when back_ == front_;
    // Normally, front_ is at least 1 behind/in front of
    // back_.
    //
    // Queue is empty when front_ < back_ and front == back_ - 1;
    //
    long front_;
    long back_;
};

int main()
{
    CircularQueue<int> q(4);
    assert(q.Empty());
    assert(q.Size() == 0);

    printf("Enqueue 1\n");
    q.Enqueue(1);
    assert(!q.Empty());
    assert(q.Size() == 1);
    assert(q.Front() == 1);
    // q.PrintQueueDebug();
    q.PrintQueueContent();

    printf("Enqueue 2\n");
    q.Enqueue(2);
    assert(!q.Empty());
    assert(q.Size() == 2);
    // q.PrintQueueDebug();
    q.PrintQueueContent();

    printf("Dequeue 1\n");
    assert(q.Dequeue() == 1);
    assert(!q.Empty());
    assert(q.Size() == 1);
    // q.PrintQueueDebug();
    q.PrintQueueContent();

    printf("Enqueue 3\n");
    q.Enqueue(3);
    // q.PrintQueueDebug();
    q.PrintQueueContent();

    printf("Enqueue 4\n");
    q.Enqueue(4);
    // q.PrintQueueDebug();
    q.PrintQueueContent();

    printf("Enqueue 5\n");
    q.Enqueue(5);
    // q.PrintQueueDebug();
    assert(q.Size() == 4);
    q.PrintQueueContent();

    printf("Dequeue 2\n");
    assert(q.Dequeue() == 2);
    assert(q.Size() == 3);
    // q.PrintQueueDebug();
    q.PrintQueueContent();
    
    printf("Dequeue 3\n");
    assert(q.Dequeue() == 3);
    assert(q.Size() == 2);
    q.PrintQueueContent();

    printf("Dequeue 4\n");
    assert(q.Dequeue() == 4);
    assert(q.Size() == 1);
    q.PrintQueueContent();

    printf("Dequeue 5\n");
    assert(q.Dequeue() == 5);
    assert(q.Size() == 0);
    assert(q.Empty());
    q.PrintQueueContent();

    std::default_random_engine seed((std::random_device())());
    for (size_t i = 0; i < 20; i++) {
        // int x = std::uniform_int_distribution<int>(0, 100)(seed);
        int x = i;
        printf("Enqueue %d\n", x);
        q.Enqueue(x);
        q.PrintQueueContent();
    }
    
    for (int i = 0; i < 20; i++) {
        int x = q.Front();
        printf("Dequeue %d\n", x);
        assert(q.Dequeue() == i);
        // q.PrintQueueDebug();

        q.PrintQueueContent();
    }
    
    assert(q.Empty());
    assert(q.Size() == 0);

    return 0;
}
