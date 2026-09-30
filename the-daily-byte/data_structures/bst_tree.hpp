#ifndef BST_TREE_H_
#define BST_TREE_H_

#include "./bst_node.h"

namespace data_structures
{

template<class T>
class BSTree
{
public:
    BSTree()
        : root_(nullptr)
        , n_(0) {};

    BSTree(const BSTree<T>& tree) {
        // TODO: Copy another binary search tree.
    };

    BSTree& operator=(const BSTree<T>& tree)
    {
        // TODO: Copy another binary search tree.
    };

    ~BSTree() = default;


    void Insert(T value)
    {

    };

    void Delete(T value)
    {

    };

    std::shared_ptr<BSTNode<T>> Find(T value) const
    {
        return Find(value, root_);
    };

    bool Empty() const
    {
        return n_ == 0;
    };

    size_t Size() const
    {
        return n_;
    };

    bool Equals(const BSTree<T>& tree) const
    {
        // TODO: Implement this.
        return false;
    };

    T ExtractMin()
    {
        std::shared_ptr<BSTNode<T>> min = root_;
        while (min->left_ != nullptr) {
            min = min->left_;
        }
        return min->data_;
    }

    T ExtractMax()
    {
        std::shared_ptr<BSTNode<T>> max = root_;
        while (max->right_ != nullptr) {
            max = max->right_;
        }

        return max->data_;
    }

private:

    std::shared_ptr<BSTNode<T>> Find(T value, std::shared_ptr<BSTNode<T>> node) const
    {
        if (node == nullptr) return nullptr;
        if (value < node->data_) return Find(value, node->left_);
        else if (value > node->data_) return Find(value, node->right_);
        else return node;
    };

    std::shared_ptr<BSTNode<T>> FindIteratively(T value, std::shared_ptr<BSTNode<T>> node) const
    {
        while (node != nullptr && node->data_ != value) {
            if (value < node->data_) {
                node = node->left_;
            } else {
                node = node->right_;
            }
        }

        return node;
    }


    std::unique_ptr<BSTNode<T>> root_;
    size_t n_;
};
};

#endif // BST_TREE_H_
