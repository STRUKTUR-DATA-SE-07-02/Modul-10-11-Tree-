#include <iostream>
using namespace std;

struct Pohon
{
    char data;
    Pohon *left, *right;
    Pohon *parent;
};

Pohon *root, *baru;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root. " << endl;
    } else {
        cout << "\nPohon sudah dibuat. " << endl;
    }
}

Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "\nNode " << node->data << "sudah ada child kiri" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri" << node->data << endl;
    return baru;
}

Pohon* insertRight(char data, Pohon*node) {
    if (node->right != NULL) {
        cout << "\nNode" << node->data << " sudah ada child kanan!" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    return baru; 
}

void update(char data, Pohon *node) {
    if (!node) {
        cout << "\nNode yang ingin diubah tidak ditemukan!" << endl;
        return;
    }
    char temp = node->data;
    node->data = data;
    cout << "\nNode " << temp << " berhasil diubah menjadi " << data << endl;
}

void find(char data, Pohon *node) {
    if (!node) return;

    if(node->data == data) {
        cout << "\nNode ditemukan: " << data << endl;
        return;
    }
    find(data, node->left);
    find(data, node->right);
}

void preOrder(Pohon *node) {
    if (node == NULL) return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Pohon *node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

void postOrder(Pohon *node) {
    if (!node) return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}

Pohon* deleteNode(Pohon *node, char data) {
    if (!node) return NULL;

    if (data < node->data) {
        node->left = deleteNode(node->left, data);
    }
    else if (data > node->data) {
        node->right = deleteNode(node->right, data);
    }
    else {
        if (!node->left) {
            Pohon *temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            Pohon *temp = node->left;
            delete node;
            return temp;
        }

        Pohon *successor = node->right;
        while (successor->left) successor = successor->left;
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data);
    }
    return node;
}

Pohon* mostLeft(Pohon *node) {
    if (!node) return NULL;
    while (node->left) node = node->left;
    return node;
}

Pohon* mostRight(Pohon *node) {
    if (!node) return NULL;
    while (node->right) node = node->right;
    return node;
}

int main() {
    init(); 
    buatNode('F'); 
    insertLeft('B', root); 
    insertRight('G', root); 
    insertLeft('A', root->left); 
    insertRight('D', root->left); 
    insertLeft('C', root->left->right);
    insertRight('E', root->left->right); 

    cout << "\nPre-order Traversal: ";
    preOrder(root);
    cout << "\nIn-order Traversal: ";
    inOrder(root);
    cout << "\nPost-order Traversal: ";
    postOrder(root);

    cout << "\nMost Left Node: " << mostLeft(root)->data;
    cout << "\nMost Right Node: " << mostRight(root)->data;

    cout << "\nMenghapus node D.";
    root = deleteNode(root, 'D');
    cout << "\nIn-order Traversal setelah penghapusan: ";
    inOrder(root);

    return 0;
}