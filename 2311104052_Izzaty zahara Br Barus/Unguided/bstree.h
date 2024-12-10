#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
using namespace std;

typedef int infotype;
struct Node {
    infotype info;
    Node* left;
    Node* right;
};

Node* createNode(infotype value);
void insertNode(Node*& root, infotype value);
Node* findNode(Node* root, infotype value);
void printInOrder(Node* root);
void printPreOrder(Node* root);
void printPostOrder(Node* root);
int hitungJumlahNode(Node* root);
int hitungTotalInfo(Node* root);
int hitungKedalaman(Node* root);

#endif
