#include <iostream>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root = NULL;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "Node " << data << " berhasil dibuat sebagai root.\n";
    } else {
        cout << "Root sudah ada.\n";
    }
}

Pohon* findNode(Pohon *node, char data) {
    if (!node) return NULL;
    if (node->data == data) return node;
    Pohon *leftResult = findNode(node->left, data);
    if (leftResult) return leftResult;
    return findNode(node->right, data);
}

Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kiri.\n";
        return NULL;
    }
    Pohon *baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "Node " << data << " berhasil ditambahkan ke anak kiri " << node->data << ".\n";
    return baru;
}

Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kanan.\n";
        return NULL;
    }
    Pohon *baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "Node " << data << " berhasil ditambahkan ke anak kanan " << node->data << ".\n";
    return baru;
}

void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan.\n";
        return;
    }
    cout << "Child dari " << node->data << ":\n";
    if (node->left) cout << "Kiri: " << node->left->data << "\n";
    else cout << "Kiri: NULL\n";
    if (node->right) cout << "Kanan: " << node->right->data << "\n";
    else cout << "Kanan: NULL\n";
}

void tampilkanDescendants(Pohon *node) {
    if (!node) return;
    if (node->left || node->right) cout << node->data << ": ";
    if (node->left) cout << node->left->data << " ";
    if (node->right) cout << node->right->data << " ";
    cout << "\n";
    tampilkanDescendants(node->left);
    tampilkanDescendants(node->right);
}

void menu() {
    int pilihan;
    char data, parent_data;
    Pohon *parent_node;

    do {
        cout << "\nMenu Binary Tree:";
        cout << "\n1. Buat Root";
        cout << "\n2. Tambahkan Anak Kiri";
        cout << "\n3. Tambahkan Anak Kanan";
        cout << "\n4. Tampilkan Child";
        cout << "\n5. Tampilkan Descendants";
        cout << "\n6. Keluar";
        cout << "\nPilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan data root: ";
                cin >> data;
                buatNode(data);
                break;

            case 2:
                cout << "Masukkan data parent: ";
                cin >> parent_data;
                cout << "Masukkan data anak kiri: ";
                cin >> data;
                parent_node = findNode(root, parent_data);
                if (parent_node) insertLeft(data, parent_node);
                else cout << "Node " << parent_data << " tidak ditemukan.\n";
                break;

            case 3:
                cout << "Masukkan data parent: ";
                cin >> parent_data;
                cout << "Masukkan data anak kanan: ";
                cin >> data;
                parent_node = findNode(root, parent_data);
                if (parent_node) insertRight(data, parent_node);
                else cout << "Node " << parent_data << " tidak ditemukan.\n";
                break;

            case 4:
                cout << "Masukkan data node: ";
                cin >> data;
                parent_node = findNode(root, data);
                tampilkanChild(parent_node);
                break;

            case 5:
                cout << "Masukkan data node: ";
                cin >> data;
                parent_node = findNode(root, data);
                tampilkanDescendants(parent_node);
                break;

            case 6:
                cout << "Keluar.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);
}

int main() {
    init();
    menu();
    return 0;
}
