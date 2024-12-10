#include <iostream>
#include <climits>
using namespace std;

struct Pohon {
    int data;
    Pohon *left, *right;
};

Pohon* createNode(int data) {
    Pohon* node = new Pohon;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

bool is_valid_bst(Pohon* node, int min_val, int max_val) {
    if (!node) return true; 

    if (node->data <= min_val || node->data >= max_val)
        return false;

    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

int main() {
    Pohon* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(2);
    root->left->right = createNode(8);

    Pohon* root_invalid = createNode(10);
    root_invalid->left = createNode(5);
    root_invalid->right = createNode(20);
    root_invalid->left->left = createNode(12); 

    cout << "Pohon valid BST: " << (is_valid_bst(root, INT_MIN, INT_MAX) ? "Ya" : "Tidak") << endl;
    cout << "Pohon tidak valid BST: " << (is_valid_bst(root_invalid, INT_MIN, INT_MAX) ? "Ya" : "Tidak") << endl;

    return 0;
}
