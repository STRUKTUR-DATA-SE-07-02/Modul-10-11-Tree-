#include "bstree.h"

int main() {
    address root = nullptr;

    // Menambahkan node ke dalam BST
    insertNode(root, 1);
    insertNode(root, 2);
    insertNode(root, 6);
    insertNode(root, 4);
    insertNode(root, 5);
    insertNode(root, 3);
    insertNode(root, 7);

    // Traversal
    cout << "In-order Traversal: ";
    printInorder(root);
    cout << "\nPre-order Traversal: ";
    printPreorder(root);
    cout << "\nPost-order Traversal: ";
    printPostorder(root);

    // Informasi tambahan
    cout << "\nJumlah Node: " << hitungJumlahNode(root);
    cout << "\nTotal Info: " << hitungTotalInfo(root);
    cout << "\nKedalaman Maksimal: " << hitungKedalaman(root);

    return 0;
}
