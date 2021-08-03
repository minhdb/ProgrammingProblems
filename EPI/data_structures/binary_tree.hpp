#ifndef BINARY_TREE_HPP_
#define BINARY_TREE_HPP_

#include <memory>
#include <vector>
#include <stdexcept>
#include <utility>

using std::unique_ptr;
using std::weak_ptr;
using std::shared_ptr;
using std::pair;
using std::make_pair;
using std::make_shared;
using std::vector;

namespace data_structures
{

template <typename T>
struct BinaryTreeNode
{
    BinaryTreeNode(T data) : data_(data), left_(nullptr), right_(nullptr), parent_(nullptr) {}
    BinaryTreeNode(T data, 
            shared_ptr<BinaryTreeNode<T>> l,
            shared_ptr<BinaryTreeNode<T>> r)
        : data_(data), left_(l), right_(r), parent_(nullptr) {}

    BinaryTreeNode(T data,
            shared_ptr<BinaryTreeNode<T>> l,
            shared_ptr<BinaryTreeNode<T>> r,
            shared_ptr<BinaryTreeNode<T>> p)
        : data_(data), left_(l), right_(r), parent_(p) {}

    T data_;
    shared_ptr<BinaryTreeNode<T>> left_, right_, parent_;
};

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree()
        : root_(nullptr)
        , n_(0)
    {

    }

    BinarySearchTree(const BinarySearchTree& bst) = delete;
    ~BinarySearchTree() = default;
    BinarySearchTree& operator=(const BinarySearchTree& bst) = delete;

    pair<shared_ptr<BinaryTreeNode<T>>, bool>
    Insert(T data)
    {
        if (Empty()) {
            root_ = make_shared<BinaryTreeNode<T>>(data);
            n_++;
            return make_pair(root_, true);
        } else {
            // Find a place to insert.
            shared_ptr<BinaryTreeNode<T>> pParent(nullptr);
            shared_ptr<BinaryTreeNode<T>> pTmp(root_);

            while (pTmp != nullptr) {
                pParent = pTmp;
                if (data < pTmp->data_) {
                    pTmp = pTmp->left_;
                } else if (data > pTmp->data_) {
                    pTmp = pTmp->right_;
                } else {
                    // Duplicate keys.
                    return make_pair(pTmp, false);
                }
            }

            shared_ptr<BinaryTreeNode<T>> new_node(make_shared<BinaryTreeNode<T>>(data));
            if (pParent->data_ < data) {
                pParent->right_ = new_node;
            } else if (pParent->data_ > data) {
                pParent->left_ = new_node;
            }
            n_++;
            return make_pair(new_node, true);
        }
        return make_pair(nullptr, false);
    }

    bool
    Delete(T data)
    {
        return false;
    }

    size_t 
    Size() const
    {
        return n_;
    }

    bool 
    Empty() const
    {
        return n_ == 0;
    }

    void 
    Inorder(vector<T>& inorder)
    {
        InorderHelper(root_, inorder);
    }

    void
    Postorder(vector<T>& postorder)
    {
        PostorderHelper(root_, postorder);
    }

    void 
    Preorder(vector<T>& preorder)
    {
        PreorderHelper(root_, preorder);
    }

private:
    void InorderHelper(shared_ptr<BinaryTreeNode<T>>& node, vector<T>& inorder)
    {
        if (node != nullptr) {
            InorderHelper(node->left_, inorder);
            inorder.emplace_back(node->data_);
            InorderHelper(node->right_, inorder);
        }
    }

    void PostorderHelper(shared_ptr<BinaryTreeNode<T>>& node, vector<T>& postorder)
    {
        if (node != nullptr) {
            PostorderHelper(node->left_, postorder);
            PostorderHelper(node->right_, postorder);
            postorder.emplace_back(node->data_);
        }
    }

    void PreorderHelper(shared_ptr<BinaryTreeNode<T>>& node, vector<T>& preorder)
    {
        if (node != nullptr) {
            preorder.emplace_back(node->data_);
            PreorderHelper(node->left_, preorder);
            PreorderHelper(node->right_, preorder);
        }
    }

    shared_ptr<BinaryTreeNode<T>> root_;
    size_t n_;
};
}
#endif

