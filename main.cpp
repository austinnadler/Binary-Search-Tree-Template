// File: main.cpp
#include "BST.h"
#include <iostream>
using namespace std;

int main() {
    BST<int> tree;
    tree.insert(50);
    tree.insert(4);
    tree.insert(9);
    tree.insert(100);
    tree.insert(-12);
    tree.insert(20);
    tree.insert(30);

    cout << "numNodes : " << tree.size() << endl;
    // tree.deleteK(4);
    cout << "Tree contains 1? (Expect: 1) : " << tree.contains(1) << endl;
    cout << "Tree contains 3? (Expect: 0) : " << tree.contains(3) << endl;

    cout << "Traversals: " << endl;
    cout << "In-order traversal : "; tree.printInOrder(); cout << endl;
    cout << "Pre-order traversal : "; tree.printPreOrder(); cout << endl;
    cout << "Post-order traversal : "; tree.printPostOrder(); cout << endl;
    cout << "Empty? (Expect: 0) : " << tree.isEmpty() << endl;
    return 0;
}// end main()
