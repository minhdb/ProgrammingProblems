# Changelog

## Unreleased

### Changed
- Documented the repo's C/C++ file naming standard (`.cpp` for judge submissions, `.cc` for personal/book solutions, `.hpp`/`.h` for header-only template data structures) and a short best-practices list in `README.md`.
- `EPI/data_structures/binary_tree.hpp`: changed `BinaryTreeNode::parent_` from `std::shared_ptr` to `std::weak_ptr`; removed header-scope `using std::...` declarations, qualifying all standard-library types with `std::` at the point of use instead.
- `the-daily-byte/data_structures/bst_node.h`: same two fixes — `BSTNode::parent_` (both the primary template and the `int` specialization) changed to `std::weak_ptr`; removed header-scope `using` declarations.
- `the-daily-byte/data_structures/bst_tree.hpp`: removed header-scope `using std::shared_ptr; using std::unique_ptr;`, qualifying with `std::` instead. (`BSTree` has no parent/back-pointer, so no `weak_ptr` change was needed here.)

### Why
- **Reference cycle:** each of these trees links a node down to its children with `shared_ptr` and back up to its parent with a second `shared_ptr`. That's a cycle — the reference counts of a node and its parent hold each other above zero, so the subtree is never freed even after the tree itself goes out of scope. `parent_`/back-pointers should never be owning; `weak_ptr` fixes that without changing any of the class' public API (assignment from a `shared_ptr` and comparisons against `nullptr` both still work; a dereference now needs `.lock()`, but no existing code in these two files reads through `parent_`, so nothing else had to change).
- **Header-scope `using`:** a `using std::shared_ptr;` at namespace scope in a `.hpp`/`.h` is injected into every translation unit that `#include`s it, which is exactly the kind of hidden coupling headers are supposed to avoid. Qualifying with `std::` at each use site is the standard fix; it's mechanical and doesn't change behavior.

## Code review notes (C/C++ only, not fixed in this change)

Found while making the above change; out of scope for it (pre-existing, none currently reachable — see each note), listed here for the record rather than silently fixed:

- **`EPI/data_structures/binary_tree.hpp`**
  - `BinarySearchTree::Delete`: `while (successor->left != nullptr)` should be `successor->left_` (missing trailing underscore) — as written this doesn't refer to a member of `BinaryTreeNode`.
  - `BinarySearchTree::FindSuccessor`: references `key_node->parent` / `pParent->parent`, which should be `parent_`; also compares/assigns between `shared_ptr` and what would need to be the `weak_ptr` `parent_` without a `.lock()`. Needs a rewrite to use `parent_.lock()`.
  - `BinarySearchTree::FindPredecessor`: declared to return `std::shared_ptr<BinaryTreeNode<T>>` but the body is empty — falls off the end of a non-`void` function (undefined behavior if ever called).
  - None of the three are currently instantiated anywhere in the repo, so the class template still compiles; they'll only surface the first time something actually calls `Delete`, `FindSuccessor`, or `FindPredecessor` on an instantiated `BinarySearchTree<T>`.

- **`the-daily-byte/data_structures/bst_tree.hpp`**
  - `root_` is declared `std::unique_ptr<BSTNode<T>>`, but `Find`, `ExtractMin`, and `ExtractMax` all copy it into a local `std::shared_ptr<BSTNode<T>>` (`return Find(value, root_);`, `shared_ptr<BSTNode<T>> min = root_;`). Copy-constructing a `shared_ptr` from a `unique_ptr` lvalue is deleted; this won't compile once any of those three methods is actually instantiated. Either `root_` should be `shared_ptr` to match how the rest of the class treats it, or the class needs to consistently use `unique_ptr` with `std::move`/raw-pointer traversal.
  - `Insert`, `Delete`, copy constructor, copy-assignment, and `Equals` are all unimplemented stubs (`// TODO`) — `BSTree` isn't usable yet independent of the above.

- **`the-daily-byte/data_structures/bst_node.h`**
  - Free functions `bst_equals`, `find`, and `insert` are defined directly in the header with no `inline`. Because they're ordinary (non-template) functions, including this header from more than one translation unit in the same binary will violate the One Definition Rule (ODR) — ordinarily a link error. Not currently hit because no `.cc`/`.cpp` includes it more than once, but it's fragile.
