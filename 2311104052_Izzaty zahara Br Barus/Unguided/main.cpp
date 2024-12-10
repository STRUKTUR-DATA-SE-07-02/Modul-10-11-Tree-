#include "bstree.h"
#include "bstree.cpp"
int main() {
    Node* root = nullptr;

    insertNode(root, 4);
    insertNode(root, 2);
    insertNode(root, 6);
    insertNode(root, 1);
    insertNode(root, 3);
    insertNode(root, 5);
    insertNode(root, 7);

    cout << "In-Order Traversal: ";
    printInOrder(root);
    cout << endl;

    cout << "Pre-Order Traversal: ";
    printPreOrder(root);
    cout << endl;

    cout << "Post-Order Traversal: ";
    printPostOrder(root);
    cout << endl;

    cout << "Jumlah Node: " << hitungJumlahNode(root) << endl;
    cout << "Total Info: " << hitungTotalInfo(root) << endl;
    cout << "Kedalaman Tree: " << hitungKedalaman(root) << endl;

    return 0;
}
