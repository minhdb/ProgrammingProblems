/**
 * EPI Chapter 09 Stacks and Queues
 *
 * 9.1 Max Stack
 *
 * Design a stack that includes a max operation, in addition to push and pop.
 * The max method should return the maximum valud stored in the stack.
 */

#include <utility>
#include <limits>
#include <cassert>
#include <cstdio>
#include <stack>
#include <stdexcept>

using std::stack;

enum class StatusCode
{
    SUCCESS,
    FAILED,
    EMPTY
};

/**
 * MaxStack that keeps track of the maximum element.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Push() on average is O(1) and worst case O(n) due to copying + extension.
 * Pop() on average is O(n) due to mostly keeping track of the maximum element
 *  and copying + shrinkage the stack size.
 * Top() is O(1)
 * Empty() is O(1)
 */
template<class T>
class MaxStack
{
public:
    MaxStack()
        : n_(0)
        , max_size_(0x1 << 2)
        , items_(new T[max_size_])
    {}

    MaxStack(const MaxStack& s) = delete;
    MaxStack& operator=(const MaxStack& s) = delete;
    ~MaxStack() { delete[] items_; }

    StatusCode Push(T item)
    {
        StatusCode statusCode = StatusCode::SUCCESS;
        if (n_ + 1 == std::numeric_limits<std::size_t>::max()) {
            statusCode = StatusCode::FAILED;
        } else {
            items_[n_++] = item;
            if (n_ == 1) cur_max_ = item;
            else if (item > cur_max_) cur_max_ = item;

            if (n_ == max_size_ - 1) {
                extendArray();
            }
        }

        return statusCode;
    }

    StatusCode Pop()
    {
        StatusCode statusCode = StatusCode::EMPTY;
        if (!Empty()) statusCode = StatusCode::SUCCESS;
        if (items_[n_ - 1] == cur_max_) {
            // Find the next max.
            cur_max_ = std::numeric_limits<std::size_t>::min();
            for (std::size_t i = 0; i < n_ - 1; i++) {
                if (cur_max_ < items_[i]) cur_max_ = items_[i];
            }
        }
        n_--;
        if (n_ > 0 && n_ < max_size_ >> 0x1) {
            shrinkArray();
        }

        return statusCode;
    }

    std::pair<StatusCode, T> Top()
    {
        StatusCode statusCode = StatusCode::EMPTY;
        if (!Empty()) statusCode = StatusCode::SUCCESS;
        return std::make_pair(statusCode, items_[n_-1]);
    }

    std::pair<StatusCode, T> Max()
    {
        StatusCode statusCode = StatusCode::EMPTY;
        if (!Empty()) statusCode = StatusCode::SUCCESS;
        return std::make_pair(statusCode, cur_max_);
    }

    bool Empty()
    {
        return n_ == 0;
    }

    std::size_t Size()
    {
        return n_;
    }

    std::size_t MaxSize()
    {
        return max_size_;
    }

private:
    StatusCode extendArray()
    {
        T* new_array = new T[max_size_ << 0x1];
        if (new_array == nullptr)
            return StatusCode::FAILED;

        for(std::size_t i = 0; i < n_; i++) {
            new_array[i] = items_[i];
        }

        delete[] items_;
        items_ = new_array;
        max_size_ <<= 0x1;
        return StatusCode::SUCCESS;
    }

    StatusCode shrinkArray()
    {
        T* new_array = new T[max_size_ >> 0x1];
        if (new_array == nullptr)
            return StatusCode::FAILED;

        for (std::size_t i = 0; i < n_; i++) {
            new_array[i] = items_[i];
        }

        delete[] items_;
        items_ = new_array;
        max_size_ >>= 0x1;
        return StatusCode::SUCCESS;
    }

    std::size_t n_;
    std::size_t max_size_;
    T cur_max_;
    T* items_;
};

/**
 * MaxStack solution from EPI hint. Maintain a cache to cache the maximum value
 * in the stack.
 *
 * Time complexity: O(1) - worst case is O(n) due to extension/shrinkage + copying.
 * Space complexity: O(n)
 */
template<class T>
class MaxStackEPI
{
public:
    bool Empty() const { return element_with_cached_max_.empty(); }

    T Max() const
    {
        if (Empty()) {
            throw std::length_error("Max(): empty stack");
        }

        return element_with_cached_max_.top().max_;
    }

    T Pop()
    {
        if (Empty()) {
            throw std::length_error("Pop(): empty stack");
        }

        T pop_element = element_with_cached_max_.top().element_;
        element_with_cached_max_.pop();
        return pop_element;
    }

    void Push(T x)
    {
        element_with_cached_max_.emplace(
                ElementWithCachedMax{x, max(x, Empty() ? x : Max())}
                );
    }

private:
    struct ElementWithCachedMax {
        T element_, max_;
    };
    stack<ElementWithCachedMax> element_with_cached_max_;
};

/**
 */
template<class T>
class MaxStackEPIOpt
{
public:
    bool Empty() const { return element_.empty(); }

    T Max() const 
    {
        if (Empty()) {
            throw std::length_error("Max(): empty stack");
        }
        return cached_max_with_count_.top().max_;
    }

    T Pop() 
    {
        if (Empty()) {
            throw std::length_error("Pop(): empty stack");
        }

        T pop_element = element_.top();
        element_.pop();
        const T current_max = cached_max_with_count_.top().max_;
        if (pop_element == current_max) {
            int& max_frequency = cached_max_with_count_.top().count_;
            max_frequency--;
            if (max_frequency == 0) {
                cached_max_with_count_.pop();
            }
        }
        return pop_element;
    }

    void Push(T x)
    {
        element_.emplace(x);
        if (cached_max_with_count_.empty()) {
            cached_max_with_count_.emplace(MaxWithCount{x, 1});
        } else {
            const T current_max = cached_max_with_count_.top().max_;
            if (x == current_max) {
                int& max_frequency = cached_max_with_count_.top().count_;
                max_frequency++;
            } else if (x > current_max) {
                cached_max_with_count_.emplace(MaxWithCount{x, 1});
            }
        }
    }
private:
    stack<T> element_;

    struct MaxWithCount {
        T max_;
        size_t count_;
    };

    stack<MaxWithCount> cached_max_with_count_;
};

int main()
{
    MaxStack<int> test_stack;
    assert(test_stack.Empty());
    assert(test_stack.MaxSize() == 4);

    test_stack.Push(1);
    assert(test_stack.Top().second == 1);
    assert(test_stack.Max().second == 1);
    assert(test_stack.Size() == 1);
    assert(!test_stack.Empty());

    test_stack.Push(0);
    assert(test_stack.Top().second == 0);
    assert(test_stack.Max().second == 1);
    assert(test_stack.Size() == 2);
    assert(!test_stack.Empty());

    test_stack.Pop();
    assert(test_stack.Top().second == 1);
    assert(test_stack.Max().second == 1);
    assert(test_stack.Size() == 1);
    assert(!test_stack.Empty());

    test_stack.Push(5);
    assert(test_stack.Top().second == 5);
    assert(test_stack.Max().second == 5);

    test_stack.Push(3);
    assert(test_stack.Top().second == 3);
    assert(test_stack.Max().second == 5);

    test_stack.Pop();
    assert(test_stack.Top().second == 5);
    assert(test_stack.Max().second == 5);

    test_stack.Pop();
    assert(test_stack.Top().second == 1);
    assert(test_stack.Max().second == 1);

    test_stack.Pop();
    assert(test_stack.Top().first == StatusCode::EMPTY);
    assert(test_stack.Max().first == StatusCode::EMPTY);

    test_stack.Push(5);
    test_stack.Push(3);
    test_stack.Push(123);
    test_stack.Push(234234);
    test_stack.Push(-23);
    test_stack.Push(43);
    test_stack.Push(0);
    test_stack.Push(5);
    assert(test_stack.Top().second == 5);
    assert(test_stack.Max().second == 234234);
    assert(test_stack.Size() == 8);
    assert(test_stack.MaxSize() == 16);

    test_stack.Pop();
    assert(test_stack.Top().second == 0);
    assert(test_stack.Max().second == 234234);
    assert(test_stack.Size() == 7);
    assert(test_stack.MaxSize() == 8);

    test_stack.Pop();
    test_stack.Pop();
    test_stack.Pop();
    test_stack.Pop();
    assert(test_stack.Top().second == 123);
    assert(test_stack.Max().second == 123);
    assert(test_stack.Size() == 3);
    assert(test_stack.MaxSize() == 4);

    return 0;
}
