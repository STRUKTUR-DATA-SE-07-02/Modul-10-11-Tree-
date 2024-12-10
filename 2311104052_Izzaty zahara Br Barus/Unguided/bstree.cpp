#include "bstree.h"

Node* createNode(infotype value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void insertNode(Node*& root, infotype value) {
    if (root == nullptr) {
        root = createNode(value);
    } else if (value < root->info) {
        insertNode(root->left, value);
    } else if (value > root->info) {
        insertNode(root->right, value);
    }
}

Node* findNode(Node* root, infotype value) {
    if (root == nullptr || root->info == value) {
        return root;
    }
    if (value < root->info) {
        return findNode(root->left, value);
    } else {
        return findNode(root->right, value);
    }
}

void printInOrder(Node* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->info << " ";
    printInOrder(root->right);
}

void printPreOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->info << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(Node* root) {
    if (root == nullptr) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->info << " ";
}

int hitungJumlahNode(Node* root) {
    if (root == nullptr) return 0;
    return 1 + hitungJumlahNode(root->left) + hitungJumlahNode(root->right);
}

int hitungTotalInfo(Node* root) {
    if (root == nullptr) return 0;
    return root->info + hitungTotalInfo(root->left) + hitungTotalInfo(root->right);
}

int hitungKedalaman(Node* root) {
    if (root == nullptr) return 0;
    int leftDepth = hitungKedalaman(root->left);
    int rightDepth = hitungKedalaman(root->right);
    return 1 + max(leftDepth, rightDepth);
}
