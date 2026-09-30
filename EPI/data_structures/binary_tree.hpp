#ifndef BINARY_TREE_HPP_
#define BINARY_TREE_HPP_

#include <memory>
#include <vector>
#include <stdexcept>
#include <utility>

namespace data_structures
{

template <typename T>
struct BinaryTreeNode
{
    BinaryTreeNode(T data) : data_(data), left_(nullptr), right_(nullptr), parent_() {}
    BinaryTreeNode(T data,
            std::shared_ptr<BinaryTreeNode<T>> l,
            std::shared_ptr<BinaryTreeNode<T>> r)
        : data_(data), left_(l), right_(r), parent_() {}

    BinaryTreeNode(T data,
            std::shared_ptr<BinaryTreeNode<T>> l,
            std::shared_ptr<BinaryTreeNode<T>> r,
            std::shared_ptr<BinaryTreeNode<T>> p)
        : data_(data), left_(l), right_(r), parent_(p) {}

    T data_;
    std::shared_ptr<BinaryTreeNode<T>> left_, right_;
    std::weak_ptr<BinaryTreeNode<T>> parent_;
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

    std::pair<std::shared_ptr<BinaryTreeNode<T>>, bool>
    Insert(T data)
    {
        if (Empty()) {
            root_ = std::make_shared<BinaryTreeNode<T>>(data);
            n_++;
            return std::make_pair(root_, true);
        } else {
            // Find a place to insert.
            std::shared_ptr<BinaryTreeNode<T>> pParent(nullptr);
            std::shared_ptr<BinaryTreeNode<T>> pTmp(root_);

            while (pTmp != nullptr) {
                pParent = pTmp;
                if (data < pTmp->data_) {
                    pTmp = pTmp->left_;
                } else if (data > pTmp->data_) {
                    pTmp = pTmp->right_;
                } else {
                    // Duplicate keys.
                    return std::make_pair(pTmp, false);
                }
            }

            std::shared_ptr<BinaryTreeNode<T>> new_node(std::make_shared<BinaryTreeNode<T>>(data));
            new_node->parent_ = pParent;
            if (pParent->data_ < data) {
                pParent->right_ = new_node;
            } else if (pParent->data_ > data) {
                pParent->left_ = new_node;
            }
            n_++;
            return std::make_pair(new_node, true);
        }
        return std::make_pair(nullptr, false);
    }

    bool
    Delete(T data)
    {
        std::shared_ptr<BinaryTreeNode<T>> pTmp(root_);
        std::shared_ptr<BinaryTreeNode<T>> pParent(nullptr);

        while (pTmp != nullptr && pTmp->data_ != data) {
            pParent = pTmp;
            if (data < pTmp->data_) {
                pTmp = pTmp->left_;
            } else {
                pTmp = pTmp->right_;
            }
        }

        // Can't find that node.
        if (pTmp == nullptr) return false;

        std::shared_ptr<BinaryTreeNode<T>> found_node = pTmp;

        if (found_node->right_ != nullptr) {
            // Find the minimum on the right subtree. i.e. the successor.
            std::shared_ptr<BinaryTreeNode<T>> successor = found_node->right_;
            std::shared_ptr<BinaryTreeNode<T>> successor_parent = found_node;

            while (successor->left != nullptr) {
                successor_parent = successor;
                successor = successor->left_;
            }

            // Set the found node's data to its successor's data.
            found_node->data_ = successor->data_;

            // Moves links to erase the successor.
            if (successor_parent->left_ == successor) {
                successor_parent->left_ = successor->right_;
            } else {
                successor_parent->right_ = successor->right_;
            }

        } else {
            // Update root_ link if needed.
            if (root_ == found_node) {
                root_ = found_node->left_;
            } else {
                if (pParent->left_ == found_node) {
                    pParent->left_ = found_node->left_;
                } else {
                    pParent->right_ = found_node->left_;
                }
            }
        }
        return true;
    }

    std::shared_ptr<BinaryTreeNode<T>>
    FindMin() const
    {
        return FindMin(root_);
    }

    std::shared_ptr<BinaryTreeNode<T>>
    FindMax() const
    {
        return FindMax(root_);
    }

    std::shared_ptr<BinaryTreeNode<T>>
    FindSuccessor(T data)
    {
        std::shared_ptr<BinaryTreeNode<T>> key_node = Find(data);
        std::shared_ptr<BinaryTreeNode<T>> successor(nullptr);
        if (key_node != nullptr) {
            if (key_node->right_ != nullptr) {
                successor = FindMin(key_node->right_);
            } else {
                std::shared_ptr<BinaryTreeNode<T>> pParent = key_node->parent;
                while (pParent != nullptr && pParent->right_ == successor) {
                    successor = pParent;
                    pParent = pParent->parent;
                }
                successor = pParent;
            }
        }

        return successor;
    }

    std::shared_ptr<BinaryTreeNode<T>>
    FindPredecessor(T data)
    {

    }

    size_t
    Size() const
    {
        return n_;
    }

    std::shared_ptr<BinaryTreeNode<T>>
    Find(T data) const
    {
        std::shared_ptr<BinaryTreeNode<T>> pTmp(root_);

        while (pTmp != nullptr && pTmp->data_ != data) {
            if (data < pTmp->data_) {
                pTmp = pTmp->left_;
            } else {
                pTmp = pTmp->right_;
            }
        }

        return pTmp;
    }

    bool
    Empty() const
    {
        return n_ == 0;
    }

    void
    Inorder(std::vector<T>& inorder)
    {
        InorderHelper(root_, inorder);
    }

    void
    Postorder(std::vector<T>& postorder)
    {
        PostorderHelper(root_, postorder);
    }

    void
    Preorder(std::vector<T>& preorder)
    {
        PreorderHelper(root_, preorder);
    }

private:
    void InorderHelper(std::shared_ptr<BinaryTreeNode<T>>& node, std::vector<T>& inorder)
    {
        if (node != nullptr) {
            InorderHelper(node->left_, inorder);
            inorder.emplace_back(node->data_);
            InorderHelper(node->right_, inorder);
        }
    }

    void PostorderHelper(std::shared_ptr<BinaryTreeNode<T>>& node, std::vector<T>& postorder)
    {
        if (node != nullptr) {
            PostorderHelper(node->left_, postorder);
            PostorderHelper(node->right_, postorder);
            postorder.emplace_back(node->data_);
        }
    }

    void PreorderHelper(std::shared_ptr<BinaryTreeNode<T>>& node, std::vector<T>& preorder)
    {
        if (node != nullptr) {
            preorder.emplace_back(node->data_);
            PreorderHelper(node->left_, preorder);
            PreorderHelper(node->right_, preorder);
        }
    }

    std::shared_ptr<BinaryTreeNode<T>> FindMin(const std::shared_ptr<BinaryTreeNode<T>>& tree)
    {
        std::shared_ptr<BinaryTreeNode<T>> min_node(tree);
        while (min_node->left_ != nullptr) {
            min_node = min_node->left_;
        }
        return min_node;
    }

    std::shared_ptr<BinaryTreeNode<T>> FindMax(const std::shared_ptr<BinaryTreeNode<T>>& tree)
    {
        std::shared_ptr<BinaryTreeNode<T>> max_node(tree);
        while (max_node->right_ != nullptr) {
            max_node = max_node->right_;
        }
        return max_node;
    }

    std::shared_ptr<BinaryTreeNode<T>> root_;
    size_t n_;
};
}
#endif
