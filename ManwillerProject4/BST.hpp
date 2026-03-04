#ifndef BST_HPP
#define BST_HPP

// constructor for node (const reference)
template <typename T>
BST<T>::BSTNode::BSTNode(
    const T &e,
    typename BST<T>::BSTNode *l,
    typename BST<T>::BSTNode *r,
    int s
) {
    element = e;
    left = l;
    right = r;
    searchCount = s;
}

// constructor for node (rvalue reference)
template <typename T>
BST<T>::BSTNode::BSTNode(
    T &&e,
    typename BST<T>::BSTNode *l,
    typename BST<T>::BSTNode *r,
    int s
) {
    element = std::move(e);
    left = l;
    right = r;
    searchCount = s;
}

// default constructor
template <typename T>
BST<T>::BST(int th) {
    root = nullptr;
    threshold = th;
}

// constructor from input string
template <typename T>
BST<T>::BST(const std::string input, int th) {
    root = nullptr;
    threshold = th;
    buildFromInputString(input);
}

// copy constructor
template <typename T>
BST<T>::BST(const BST &other) {
    root = nullptr;
    threshold = other.threshold;
    root = clone(other.root);
}

// move constructor
template <typename T>
BST<T>::BST(BST &&other) noexcept {
    root = other.root;
    threshold = other.threshold;
    other.root = nullptr;
}

// destructor
template <typename T>
BST<T>::~BST() {
    makeEmpty(root);
}

// build tree from input string
template <typename T>
void BST<T>::buildFromInputString(const std::string input) {
    makeEmpty(root);
    std::istringstream iss(input);
    T value;
    while (iss >> value) {
        insert(value, root);
    }
}

// copy assignment
template <typename T>
const BST<T> &BST<T>::operator=(const BST &rhs) {
    if (this != &rhs) {
        makeEmpty(root);
        threshold = rhs.threshold;
        root = clone(rhs.root);
    }
    return *this;
}

// move assignment
template <typename T>
const BST<T> &BST<T>::operator=(BST &&rhs) noexcept {
    if (this != &rhs) {
        makeEmpty(root);
        root = rhs.root;
        threshold = rhs.threshold;
        rhs.root = nullptr;
    }
    return *this;
}

// check if tree is empty
template <typename T>
bool BST<T>::empty() const {
    return root == nullptr;
}

// print in-order
template <typename T>
void BST<T>::printInOrder() const {
    printInOrder(root);
    std::cout << std::endl;
}

// print level-order
template <typename T>
void BST<T>::printLevelOrder() const {
    printLevelOrder(root);
    std::cout << std::endl;
}

// get number of nodes
template <typename T>
int BST<T>::numOfNodes() const {
    return numOfNodes(root);
}

// get height in links
template <typename T>
int BST<T>::height() const {
    if (!root) return 0;
    return height(root) - 1;
}

// make tree empty
template <typename T>
void BST<T>::makeEmpty() {
    makeEmpty(root);
}

// insert public (const reference)
template <typename T>
void BST<T>::insert(const T &v) {
    insert(v, root);
}

// insert public (rvalue reference)
template <typename T>
void BST<T>::insert(T &&v) {
    // simple: reuse const-reference version
    insert(v, root);
}

// remove public
template <typename T>
void BST<T>::remove(const T &v) {
    remove(v, root);
}

// search public
template <typename T>
bool BST<T>::contains(const T &v) {
    return contains(v, root, true);
}

// print in-order from subtree
template <typename T>
void BST<T>::printInOrder(typename BST<T>::BSTNode *t) const {
    if (!t) return;
    printInOrder(t->left);
    std::cout << t->element << " ";
    printInOrder(t->right);
}

// print level-order from subtree
template <typename T>
void BST<T>::printLevelOrder(typename BST<T>::BSTNode *t) const {
    if (!t) return;
    std::queue<typename BST<T>::BSTNode *> q;
    q.push(t);
    while (!q.empty()) {
        typename BST<T>::BSTNode *cur = q.front();
        q.pop();
        std::cout << cur->element << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

// delete all nodes in subtree
template <typename T>
void BST<T>::makeEmpty(typename BST<T>::BSTNode *&t) {
    if (!t) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    t = nullptr;
}

// insert into subtree (const reference)
template <typename T>
void BST<T>::insert(const T &v, typename BST<T>::BSTNode *&t) {
    if (!t) {
        t = new BSTNode(v, nullptr, nullptr, 0);
    } else if (v < t->element) {
        insert(v, t->left);
    } else if (v > t->element) {
        insert(v, t->right);
    } else {
        // already in tree, do nothing
    }
}

// insert into subtree (rvalue reference)
template <typename T>
void BST<T>::insert(T &&v, typename BST<T>::BSTNode *&t) {
    // keep it simple: just call const-reference insert
    insert(v, t);
}

// remove from subtree
template <typename T>
void BST<T>::remove(const T &v, typename BST<T>::BSTNode *&t) {
    if (!t) return;

    if (v < t->element) {
        remove(v, t->left);
    } else if (v > t->element) {
        remove(v, t->right);
    } else {
        if (t->left && t->right) {
            typename BST<T>::BSTNode *minNode = t->right;
            while (minNode->left) {
                minNode = minNode->left;
            }
            t->element = minNode->element;
            t->searchCount = minNode->searchCount;
            remove(minNode->element, t->right);
        } else {
            typename BST<T>::BSTNode *old = t;
            if (t->left != nullptr) {
                t = t->left;
            } else {
                t = t->right;
            }
            delete old;
        }
    }
}

// search in subtree and rotate if needed
template <typename T>
bool BST<T>::contains(const T &v,
                      typename BST<T>::BSTNode *&t,
                      bool isRoot) {
    if (!t) return false;

    if (v < t->element) {
        bool found = contains(v, t->left, false);
        if (found && t->left && t->left->searchCount >= threshold) {
            rotateWithLeftChild(t);
        }
        return found;
    } else if (v > t->element) {
        bool found = contains(v, t->right, false);
        if (found && t->right && t->right->searchCount >= threshold) {
            rotateWithRightChild(t);
        }
        return found;
    } else {
        t->searchCount++;
        if (t->searchCount >= threshold && isRoot) {
            t->searchCount = 0;
        }
        return true;
    }
}

// count nodes in subtree
template <typename T>
int BST<T>::numOfNodes(typename BST<T>::BSTNode *t) const {
    if (!t) return 0;
    return 1 + numOfNodes(t->left) + numOfNodes(t->right);
}

// height in nodes from subtree
template <typename T>
int BST<T>::height(typename BST<T>::BSTNode *t) const {
    if (!t) return 0;
    int hl = height(t->left);
    int hr = height(t->right);
    if (hl > hr) {
        return 1 + hl;
    } else {
        return 1 + hr;
    }
}

// clone subtree
template <typename T>
typename BST<T>::BSTNode *BST<T>::clone(typename BST<T>::BSTNode *t) const {
    if (!t) return nullptr;
    BSTNode *newNode = new BSTNode(t->element, nullptr, nullptr, t->searchCount);
    newNode->left = clone(t->left);
    newNode->right = clone(t->right);
    return newNode;
}

// rotate with left child
template <typename T>
void BST<T>::rotateWithLeftChild(typename BST<T>::BSTNode *&k2) {
    BSTNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k1->searchCount = 0;
    k2 = k1;
}

// rotate with right child
template <typename T>
void BST<T>::rotateWithRightChild(typename BST<T>::BSTNode *&k2) {
    BSTNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k1->searchCount = 0;
    k2 = k1;
}

#endif // BST_HPP
