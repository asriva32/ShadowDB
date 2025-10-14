#ifndef RBTREE_H
#define RBTREE_H
#include <functional>

enum Color {RED, BLACK};

template<typename T>
struct Node{
    int height;
    Color color;
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;
    T key;
    Node(const T &k): key(k), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T, std::strict_weak_order<T, T> Comparator>
class RBTree {
public:
    RBTree(Comparator comparator): root(nullptr), comp(comparator), node_count(0) {}
    ~RBTree() { deleteTree(root); }

    void insert(const T &key);
    bool contains(const T &key);
    int size();


private:
    Node<T>* root;
    Comparator comp;
    int node_count;

    void leftRotate(Node<T>* &node);
    void rightRotate(Node<T>* &node);
    void fixInsert(Node<T>* &node);
    void deleteTree(Node<T>* &node);
};

template<typename T, std::strict_weak_order<T, T> Comparator>
void RBTree<T, Comparator>::leftRotate(Node<T>* &node) {
    Node<T>* child = node->right;
    node->right = child->left;
    if (node->right != nullptr) {
        node->right->parent = node;
    }
    child->parent = node->parent;
    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }
    child->left = node;
    node->parent = child;
}

template<typename T, std::strict_weak_order<T, T> Comparator>
void RBTree<T, Comparator>::rightRotate(Node<T>* &node) {
    Node<T>* child = node->left;
    node->left = child->right;
    if (node->left != nullptr){
        node->left->parent = node;
    }
    child->parent = node->parent;
    if (node->parent == nullptr){
        root = child;
    }else if (node == node->parent->left){
        node->parent->left = child;
    }else{
        node->parent->right = child;
    }
    child->right = node;
    node->parent = child;
}

template<typename T, std::strict_weak_order<T, T> Comparator>
void RBTree<T, Comparator>::fixInsert(Node<T>* &node) {
    Node<T>* parent = nullptr;
    Node<T>* grandparent = nullptr;
    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node<T>* uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    leftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                rightRotate(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        else {
            Node<T>* uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rightRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                leftRotate(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

template<typename T, std::strict_weak_order<T, T> Comparator>
void RBTree<T, Comparator>::insert(const T &key) {
    Node<T>* node = new Node(key);
        Node<T>* parent = nullptr;
        Node<T>* current = root;
        while (current != nullptr) {
            parent = current;
            if (comp(node->key, current->key)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        node->parent = parent;
        if (parent == nullptr) {
            root = node;
        } else if (comp(node->key, parent->key)) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        fixInsert(node);
        ++node_count;
}

template<typename T, std::strict_weak_order<T, T> Comparator>
bool RBTree<T, Comparator>::contains(const T &key) {
    Node<T>* cur = root;
    while (cur) {
        if (cur->key == key) {
            return true;
        }
        if (comp(key, cur->key)) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return false;
}

template<typename T, std::strict_weak_order<T, T> Comparator>
int RBTree<T, Comparator>::size(){
    return node_count;
}

template<typename T, std::strict_weak_order<T, T> Comparator>
void RBTree<T, Comparator>::deleteTree(Node<T>* &node){
    if(node){
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

#endif //RBTREE_H