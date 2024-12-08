#include "bstree.h"

// Fungsi alokasi node baru
address alokasi(infotype x) {
    address newNode = new Node;
    newNode->info = x;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Fungsi untuk menyisipkan node ke dalam BST
void insertNode(address& root, infotype x) {
    if (root == nullptr) {
        root = alokasi(x);
    } else if (x < root->info) {
        insertNode(root->left, x);
    } else if (x > root->info) {
        insertNode(root->right, x);
    }
}

// Fungsi untuk mencari node berdasarkan nilai
address findNode(infotype x, address root) {
    if (root == nullptr || root->info == x) {
        return root;
    } else if (x < root->info) {
        return findNode(x, root->left);
    } else {
        return findNode(x, root->right);
    }
}

// Traversal in-order
void printInorder(address root) {
    if (root != nullptr) {
        printInorder(root->left);
        cout << root->info << " ";
        printInorder(root->right);
    }
}

// Traversal pre-order
void printPreorder(address root) {
    if (root != nullptr) {
        cout << root->info << " ";
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

// Traversal post-order
void printPostorder(address root) {
    if (root != nullptr) {
        printPostorder(root->left);
        printPostorder(root->right);
        cout << root->info << " ";
    }
}

// Fungsi untuk menghitung jumlah node
int hitungJumlahNode(address root) {
    if (root == nullptr) {
        return 0;
    } else {
        return 1 + hitungJumlahNode(root->left) + hitungJumlahNode(root->right);
    }
}

// Fungsi untuk menghitung total nilai info pada node
int hitungTotalInfo(address root) {
    if (root == nullptr) {
        return 0;
    } else {
        return root->info + hitungTotalInfo(root->left) + hitungTotalInfo(root->right);
    }
}

// Fungsi untuk menghitung kedalaman maksimal BST
int hitungKedalaman(address root) {
    if (root == nullptr) {
        return 0;
    } else {
        int leftDepth = hitungKedalaman(root->left);
        int rightDepth = hitungKedalaman(root->right);
        return 1 + max(leftDepth, rightDepth);
    }
}
