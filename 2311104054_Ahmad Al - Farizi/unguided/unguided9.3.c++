#include <iostream>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right;
};

Pohon* createNode(char data) {
    Pohon* node = new Pohon;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int cari_simpul_daun(Pohon* node) {
    if (!node) return 0; 
    if (!node->left && !node->right) return 1; 

    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

int main() {
    Pohon* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    root->right->right = createNode('F');

    /*
       Pohon:
           A
          / \
         B   C
        / \    \
       D   E    F
    */

    cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;

    return 0;
}
