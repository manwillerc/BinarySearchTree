#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <queue>
#include <string>
#include <utility>

template <typename T>
class BST {
public:
    // node for the tree
    struct BSTNode {
        T element;
        BSTNode *left;
        BSTNode *right;
        int searchCount;

        BSTNode(const T &e, BSTNode *l = nullptr, BSTNode *r = nullptr, int s = 0);
        BSTNode(T &&e, BSTNode *l = nullptr, BSTNode *r = nullptr, int s = 0);
    };

    static const int default_threshold_value = 1;

    BST(int th = default_threshold_value);
    BST(const std::string input, int th = default_threshold_value);
    BST(const BST &other);
    BST(BST &&other) noexcept;
    ~BST();

    void buildFromInputString(const std::string input);

    const BST &operator=(const BST &rhs);
    const BST &operator=(BST &&rhs) noexcept;

    bool empty() const;

    void printInOrder() const;
    void printLevelOrder() const;

    int numOfNodes() const;
    int height() const;

    void makeEmpty();

    void insert(const T &v);
    void insert(T &&v);

    void remove(const T &v);

    bool contains(const T &v);

private:
    BSTNode *root;
    int threshold;

    void printInOrder(BSTNode *t) const;
    void printLevelOrder(BSTNode *t) const;

    void makeEmpty(BSTNode *&t);

    void insert(const T &v, BSTNode *&t);
    void insert(T &&v, BSTNode *&t);

    void remove(const T &v, BSTNode *&t);

    bool contains(const T &v, BSTNode *&t, bool isRoot);

    int numOfNodes(BSTNode *t) const;
    int height(BSTNode *t) const;

    BSTNode *clone(BSTNode *t) const;

    void rotateWithLeftChild(BSTNode *&k2);
    void rotateWithRightChild(BSTNode *&k2);
};

#include "BST.hpp"

#endif // BST_H

