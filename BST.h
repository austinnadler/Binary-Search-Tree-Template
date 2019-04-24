// File: BST.h

#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>
using namespace std;

template <typename K>
class BST {
private:
    using Function = void(const K& key);
    class Node {
        public:
            Node* left;
            K key;
            Node* right;

            Node(Node* const left, const K& key, Node* const right) 
            : left(left), key(key), right(right) 
            {}

            bool isLeaf()               { return !this->left && !this->right; }
            bool hasLeftChildOnly()     { return this->left && !this->right;  }
            bool hasRightChildOnly()    { return !this->left && this->right;  }
    };

    /* ------------------ Utlity methods ------------------ */

    Node* createNode(Node* const left, const K& key, Node* const right) {
        try {
            return new Node(left, key, right); // This returns the address of the node so this method can be used:
        }
        catch (std::bad_alloc e) { // before->next = after->prev = createNode(before, element, after);
            std::cerr << "Memory error adding to tree";
            exit(1);
        }
    }

    void releaseTree(Node*& node) {
        if(node != nullptr) {
            releaseTree(node->left);
            releaseTree(node->right);
            node->left = node->right = nullptr;
            delete node;
            node = nullptr;
        }
    }

    void copyTree(Node*& node, Node* const copyNode) {
        if(copyNode != nullptr) {
            node = createNode(nullptr, copyNode->key, nullptr);
            copyTree(node->left, copyNode->left);
            copyTree(node->right, copyNode->right);
        }
    }

    void releaseNode(Node*& node) {
        delete node;
        node = nullptr;
    }

    void deleteNode(Node*& node) {
        Node* del = nullptr;
        if(node->isLeaf()) {
            releaseNode(node);
        } else if(node->hasLeftChildOnly()) {
            del = node;
            node = node->left;
            releaseNode(del);
        } else if(node->hasRightChildOnly()) {
            del = node;
            node = node->right;
            releaseNode(del);
        } else {
            node->key = immediateSuccessor(node->right);
        }
    }

    K immediateSuccessor(Node*& node) {
        // Node* del = nullptr;
        K successor = K();
        if(node->left == nullptr) {
            successor = node->key;
            releaseNode(node);
            return successor;
        } else {
            immediateSuccessor(node->left);
        }
        return successor;
    }

    /* --------------- End Utility Methods ---------------- */

    /* ------------------ Action methods ------------------ */
   
    bool m_contains(const K& key, Node* const node) {
        if(node == nullptr) {
            return false;
        } else if(key == node->key) {
            return true;
        } else if(key < node->key) {
            m_contains(key, node->left);
        } else {
            m_contains(key, node->right);
        }
        return false;
    }

    void m_deleteK(const K& key, Node*& node) {
        if(node == nullptr) {
            throw logic_error("Key not found");
        } else if(key == node->key) {
            deleteNode(node);
        } else if(key < node->key) {
            m_deleteK(key, node->left);
        } else {
            m_deleteK(key, node->right);
        }
    }

    void m_insert(Node*& node, const K& key) {
        if(node == nullptr) {
            node = createNode(nullptr, key, nullptr);
        } else if(key < node->key) {
            m_insert(node->left, key);
        } else {
            m_insert(node->right, key);
        }
    }

    /* ---------------- End Action Methods ---------------- */

    /* ------------------ Traversals ---------------------- */

    void preorder(Node* const node, Function visit) {
        if(node != nullptr) {
            visit(node->key);
            preorder(node->left, visit);
            preorder(node->right, visit);
        }
    }

    void inorder(Node* const node, Function visit) const {
        if (node != nullptr) {
            inorder(node->left, visit);
            visit(node->key);
            inorder(node->right, visit);
        }
    }

    void postorder(Node* const node, Function visit) {
        if(node != nullptr) {
            postorder(node->left, visit);
            postorder(node->right, visit);
            visit(node->key);
        }
    } 

    /* ---------------- End Traversals ---------------- */
    
    /* ----------------- Visit Methods ---------------- */

    static void print(const K& key) {
        cout << key << " ";
    }

    /* -------------- End Visit Methods --------------- */

    /* ------------------ BST fields -------------------*/

    Node* root;
    int numNodes = 0;

    /* ---------------- End BST fields ---------------- */
public:
    BST() : root(nullptr) {}

    virtual ~BST() {
        releaseTree(root);
    }

    bool contains(const K& key) {
        return m_contains(key, root);
    }

    void insert(const K& key) {
        m_insert(root, key);
        numNodes += 1;
    }

    void deleteK(const K& key) {
        m_deleteK(key, root);
        numNodes -= 1;
    }
    
    int size() {
        return numNodes;
    }

    bool isEmpty() {
        return numNodes == 0;
    }

    void printInOrder() {
        inorder(root, print);
    }

    void printPreOrder() {
        preorder(root, print);
    }

    void printPostOrder() {
        postorder(root, print);
    }

};


#endif