#include <iostream>
using namespace std;

struct Pohon {
    char data;
    Pohon *kiri, *kanan;
    Pohon *parent;

    Pohon(char data, Pohon *kiri = NULL, Pohon *kanan = NULL, Pohon *parent = NULL) 
        : data(data), kiri(kiri), kanan(kanan), parent(parent) {}
};

Pohon *root, *baru;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

void buatNode (char data){
    if (isEmpty()) {
        root = new Pohon(data, NULL, NULL, NULL); // membuat node baru menggunakan konstruktor
        cout << "Node " << data << " berhasil dibuat menjadi root" << endl;
    } else {
        cout << "Pohon sudah ada" << endl;
    }   
}

Pohon *insertLeft(char data, Pohon *node) {
    if (node->kiri != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kiri " << endl;
        return node->kiri;
    }
    baru = new Pohon(data, NULL, NULL, node);
    node->kiri = baru;
    cout << "Node " << data << " berhasil ditambahkan sebagai anak kiri dari node " << node->data << endl;
    return baru;
}

Pohon *insertRight(char data, Pohon *node) {
    if (node->kanan != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kanan" << endl;
        return node->kanan;
    }
    baru = new Pohon(data, NULL, NULL, node);
    node->kanan = baru;
    cout << "Node " << data << " berhasil ditambahkan sebagai anak kanan dari node " << node->data << endl;
    return baru;
}

void update (char data, Pohon *node) {
    if(!node) {
        cout << "\nNode tidak ditemukan" << endl;
        return;
    };
    char temp = node->data;
    node->data = data;
    cout << "\nData node " << temp << " berhasil diubah menjadi" << data << endl;
}

void find(char data, Pohon *node) {
    if(!node) return;

    if (node->data == data) {
        cout << "\nNode ditemukan : "<< data << endl;
    }
    find(data, node->kiri);
    find(data, node->kanan);
}

void preOrder(Pohon *node) {
    if(!node) return;
    cout << node->data << " ";
    preOrder(node->kiri);
    preOrder(node->kanan);
}

void inOrder(Pohon *node) {
    if(!node) return;
    inOrder(node->kiri);
    cout << node->data << " ";
    inOrder(node->kanan);
}

void postOrder(Pohon *node) {
    if(!node) return;
    postOrder(node->kiri);
    postOrder(node->kanan);
    cout << node->data << " ";
}

Pohon* deleteNode(Pohon *node, char data) {
    if (!node) return NULL;

    if (data < node->data) {
        node->kiri = deleteNode(node->kiri, data);
    }
    else if (data > node->data) {
        node->kanan = deleteNode(node->kanan, data);
    }
    else {
        if (!node->kiri) {
            Pohon *temp = node->kiri;
            delete node;
            return temp;
        } else if (!node->kanan) {
            Pohon *temp = node->kiri;
            delete node;
            return temp;
        }

        Pohon *successor = node->kanan;
        while (successor->kiri) successor = successor->kiri;
        node->data = successor->data;
        node->kanan = deleteNode(node->kanan, successor->data);
    }
    return node;
}

Pohon* mostLeft(Pohon *node) {
    if(!node) return NULL;
    while(node->kiri) node = node->kiri;
    return node;
}

Pohon* mostRight(Pohon *node) {
    if(!node) return NULL;
    while(node->kanan) node = node->kanan;
    return node;
}

int main() {
    init();
    buatNode('F');
    insertLeft('B', root);
    insertRight('G', root);
    insertLeft('A', root->kiri);
    insertRight('D', root->kiri);
    insertLeft('C', root->kanan);
    insertRight('E', root->kanan);
    cout << "\nPre-order Traversal: ";
    preOrder(root);
    cout << "\nIn-order Traversal: ";
    inOrder(root);
    cout << "\nPost-order Traversal: ";
    postOrder(root);

    // Menampilkan node paling kiri dan kanan
    cout << "\nMost Left Node: " << mostLeft(root)->data;
    cout << "\nMost Right Node: " << mostRight(root)->data;

    // Menghapus node
    cout << "\nMenghapus node D.";
    root = deleteNode(root, 'D');
    cout << "\nIn-order Traversal setelah penghapusan: ";
    inOrder(root);

    return 0;
}
    