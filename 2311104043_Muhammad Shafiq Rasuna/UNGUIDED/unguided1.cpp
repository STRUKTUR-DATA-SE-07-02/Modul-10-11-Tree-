#include <iostream>
using namespace std;

struct Pohon {
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
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah dibuat." << endl;
    }
}

Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "\nNode " << node->data << " sudah ada child kiri!" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
    return baru;
}

Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    return baru;
}

void preOrder(Pohon *node) {
    if (!node) return;
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

void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }
    cout << "\nNode " << node->data << " memiliki child: ";
    if (node->left) cout << "Kiri: " << node->left->data << " ";
    else cout << "Kiri: NULL ";
    if (node->right) cout << "Kanan: " << node->right->data << endl;
    else cout << "Kanan: NULL" << endl;
}

void tampilkanDescendant(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    tampilkanDescendant(node->left);
    tampilkanDescendant(node->right);
}

Pohon* cariNode(Pohon *node, char data) {
    if (!node) return NULL;
    if (node->data == data) return node;
    Pohon *leftSearch = cariNode(node->left, data);
    if (leftSearch) return leftSearch;
    return cariNode(node->right, data);
}

int main() {
    init();
    char pilihan, data, parentData;
    Pohon *node;

    do {
        cout << "\nMenu:\n";
        cout << "1. Buat Node Root\n";
        cout << "2. Tambah Child Kiri\n";
        cout << "3. Tambah Child Kanan\n";
        cout << "4. Tampilkan Pre-order\n";
        cout << "5. Tampilkan In-order\n";
        cout << "6. Tampilkan Post-order\n";
        cout << "7. Tampilkan Child dari Node\n";
        cout << "8. Tampilkan Descendant dari Node\n";
        cout << "9. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                cout << "Masukkan data untuk root: ";
                cin >> data;
                buatNode(data);
                break;
            case '2':
                cout << "Masukkan data untuk node parent: ";
                cin >> parentData;
                node = cariNode(root, parentData);
                if (node) {
                    cout << "Masukkan data untuk child kiri: ";
                    cin >> data;
                    insertLeft(data, node);
                } else {
                    cout << "Node parent tidak ditemukan!" << endl;
                }
                break;
            case '3':
                cout << "Masukkan data untuk node parent: ";
                cin >> parentData;
                node = cariNode(root, parentData);
                if (node) {
                    cout << "Masukkan data untuk child kanan: ";
                    cin >> data;
                    insertRight(data, node);
                } else {
                    cout << "Node parent tidak ditemukan!" << endl;
                }
                break;
            case '4':
                cout << "\nPre-order Traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case '5':
                cout << "\nIn-order Traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case '6':
                cout << "\nPost-order Traversal: ";
                postOrder(root);
                cout << endl;
                break;
            case '7':
                cout << "Masukkan data node untuk melihat child: ";
                cin >> data;
                node = cariNode(root, data);
                tampilkanChild(node);
                break;
            case '8':
                cout << "Masukkan data node untuk melihat descendant: ";
                cin >> data;
                node = cariNode(root, data);
                if (node) {
                    cout << "\nDescendant dari node " << node->data << ": ";
                    tampilkanDescendant(node);
                    cout << endl;
                } else {
                    cout << "Node tidak ditemukan!" << endl;
                }
                break;
            case '9':
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != '9');

    return 0;
}
