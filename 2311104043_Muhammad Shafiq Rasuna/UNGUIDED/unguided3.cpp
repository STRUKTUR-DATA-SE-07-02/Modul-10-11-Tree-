#include <iostream>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right;
};

Pohon* root = NULL;

void buatNode(char data) {
    root = new Pohon{data, NULL, NULL};
}

Pohon* insertLeft(Pohon* node, char data) {
    node->left = new Pohon{data, NULL, NULL};
    return node->left;
}

Pohon* insertRight(Pohon* node, char data) {
    node->right = new Pohon{data, NULL, NULL};
    return node->right;
}

int cari_simpul_daun(Pohon* node) {
    if (!node) {
        return 0;
    }

    if (!node->left && !node->right) {
        return 1;
    }

    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

void inOrder(Pohon* node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

int main() {
    buatNode('A');
    Pohon* nodeB = insertLeft(root, 'B');
    Pohon* nodeC = insertRight(root, 'C');
    insertLeft(nodeB, 'D');
    insertRight(nodeB, 'E');
    insertRight(nodeC, 'F');

    cout << "In-order Traversal: ";
    inOrder(root);
    cout << endl;

    int jumlahDaun = cari_simpul_daun(root);
    cout << "Jumlah simpul daun dalam pohon: " << jumlahDaun << endl;

    return 0;
}
