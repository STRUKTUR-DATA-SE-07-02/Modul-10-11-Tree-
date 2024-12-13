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

// Fungsi untuk mencari node di BST
address findNode(address root, infotype x) {
    if (root == nullptr || root->info == x) {
        return root;
    }
    if (x < root->info) {
        return findNode(root->left, x);
    } else {
        return findNode(root->right, x);
    }
}

// Prosedur untuk mencetak tree secara InOrder
void printInOrder(address root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->info << " ";
        printInOrder(root->right);
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

// Fungsi untuk menghitung jumlah node
int hitungJumlahNode(address root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + hitungJumlahNode(root->left) + hitungJumlahNode(root->right);
}

// Fungsi untuk menghitung total info node
int hitungTotalInfo(address root) {
    if (root == nullptr) {
        return 0;
    }
    return root->info + hitungTotalInfo(root->left) + hitungTotalInfo(root->right);
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
    cout<< "Hello World!" << endl;

    // Menambahkan node ke BST
    insertNode(root, 1);
    insertNode(root, 2);
    insertNode(root, 6);
    insertNode(root, 4);
    insertNode(root, 5);
    insertNode(root, 3);
    insertNode(root, 6);
    insertNode(root, 7);

  // Cetak tree secara InOrder
    cout << "Tree in InOrder: ";
    printInOrder(root);
    cout << endl;

     // Hitung kedalaman tree
    cout << "Kedalaman Tree: " << hitungKedalaman(root) << endl;

    // Hitung jumlah node
    cout << "Jumlah Node: " << hitungJumlahNode(root) << endl;
   
    // Hitung total info node
    cout << "Total Node: " << hitungTotalInfo(root) << endl;

    return 0;
}