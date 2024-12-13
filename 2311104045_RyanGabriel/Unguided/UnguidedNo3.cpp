#include <iostream>
using namespace std;

// Definisi Node dan tipe data
typedef int infotype;
struct Node {
    infotype info;
    Node* left;
    Node* right;
};

typedef Node* address;

// Fungsi alokasi node baru
address alokasi(infotype x) {
    address newNode = new Node;
    newNode->info = x;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Prosedur untuk menyisipkan node ke BST
void insertNode(address& root, infotype x) {
    if (root == nullptr) {
        root = alokasi(x);
    } else if (x < root->info) {
        insertNode(root->left, x);
    } else if (x > root->info) {
        insertNode(root->right, x);
    }
}

// Prosedur untuk mencetak tree secara PreOrder
void printPreOrder(address root) {
    if (root != nullptr) {
        cout << root->info << " ";
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

// Prosedur untuk mencetak tree secara PostOrder
void printPostOrder(address root) {
    if (root != nullptr) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        cout << root->info << " ";
    }
}

// Fungsi untuk menghitung kedalaman tree
int hitungKedalaman(address root) {
    if (root == nullptr) {
        return 0;
    }
    int leftDepth = hitungKedalaman(root->left);
    int rightDepth = hitungKedalaman(root->right);
    return 1 + max(leftDepth, rightDepth);
}

// Program utama
int main() {
    address root = nullptr;

    // Menambahkan node sesuai ilustrasi tree pada Gambar 10-14
    insertNode(root, 6); // Root
    insertNode(root, 4); // Level 2
    insertNode(root, 7); // Level 2
    insertNode(root, 2); // Level 3
    insertNode(root, 5); // Level 3
    insertNode(root, 1); // Level 4
    insertNode(root, 3); // Level 4

    // Cetak tree secara PreOrder
    cout << "Tree in PreOrder: ";
    printPreOrder(root);
    cout << endl;

    // Cetak tree secara PostOrder
    cout << "Tree in PostOrder: ";
    printPostOrder(root);
    cout << endl;

    // Hitung kedalaman tree
    cout << "Kedalaman Tree: " << hitungKedalaman(root) << endl;

    return 0;
}