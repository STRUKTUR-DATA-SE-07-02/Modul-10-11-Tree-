#include <iostream>
#include <limits>
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

bool is_valid_bst(Pohon* node, char min_val, char max_val) {
    if (!node) return true;

    if (node->data <= min_val || node->data >= max_val) {
        return false;
    }

    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

bool checkBST(Pohon* root) {
    return is_valid_bst(root, numeric_limits<char>::min(), numeric_limits<char>::max());
}

void inOrder(Pohon* node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

int main() {
    cout << "Membuat pohon BST yang valid:" << endl;
    buatNode('F');
    Pohon* nodeB = insertLeft(root, 'B');
    Pohon* nodeG = insertRight(root, 'G');
    insertLeft(nodeB, 'A');
    insertRight(nodeB, 'D');
    insertLeft(nodeG, 'I');
    insertRight(nodeG, 'H');

    cout << "In-order Traversal: ";
    inOrder(root);
    cout << endl;

    if (checkBST(root)) {
        cout << "Pohon ini adalah BST yang valid." << endl;
    } else {
        cout << "Pohon ini BUKAN BST yang valid." << endl;
    }

    cout << "\nMembuat pohon yang TIDAK valid sebagai BST:" << endl;
    buatNode('F');
    nodeB = insertLeft(root, 'G');
    nodeG = insertRight(root, 'B');

    cout << "In-order Traversal: ";
    inOrder(root);
    cout << endl;

    if (checkBST(root)) {
        cout << "Pohon ini adalah BST yang valid." << endl;
    } else {
        cout << "Pohon ini BUKAN BST yang valid." << endl;
    }

    return 0;
}
