#include <iostream>
#include <queue>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
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
        cout << "\nNode " << data << " berhasil dibuat menjadi root.\n";
    } else {
        cout << "\nPohon sudah memiliki root.\n";
    }
}

Pohon* insertLeft(char data, Pohon *node) {
    if (!node) {
        cout << "\nNode induk tidak ditemukan!\n";
        return NULL;
    }
    if (node->left) {
        cout << "\nNode " << node->data << " sudah ada child kiri.\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << ".\n";
    return baru;
}

Pohon* insertRight(char data, Pohon *node) {
    if (!node) {
        cout << "\nNode induk tidak ditemukan!\n";
        return NULL;
    }
    if (node->right) {
        cout << "\nNode " << node->data << " sudah ada child kanan.\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << ".\n";
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

// Fungsi untuk menampilkan child dari suatu node
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "\nNode tidak ditemukan!\n";
        return;
    }
    cout << "\nChild dari node " << node->data << ": ";
    if (node->left) cout << "Left: " << node->left->data << " ";
    if (node->right) cout << "Right: " << node->right->data << " ";
    if (!node->left && !node->right) cout << "Tidak ada child.";
    cout << endl;
}

// Fungsi untuk menampilkan semua descendant dari suatu node
void tampilkanDescendant(Pohon *node) {
    if (!node) {
        cout << "\nNode tidak ditemukan!\n";
        return;
    }
    cout << "\nDescendant dari node " << node->data << ": ";
    queue<Pohon*> q;
    q.push(node);
    while (!q.empty()) {
        Pohon *current = q.front();
        q.pop();
        if (current != node) cout << current->data << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << endl;
}

Pohon* cariNode(Pohon *node, char data) {
    if (!node) return NULL;
    if (node->data == data) return node;
    Pohon *left = cariNode(node->left, data);
    if (left) return left;
    return cariNode(node->right, data);
}

int main() {
    init();
    int pilihan;
    char data, parentData;
    Pohon *parentNode = NULL;

    do {
        cout << "\n--- Menu Pohon Biner ---";
        cout << "\n1. Buat Root";
        cout << "\n2. Tambah Anak Kiri";
        cout << "\n3. Tambah Anak Kanan";
        cout << "\n4. Tampilkan Pre-order";
        cout << "\n5. Tampilkan In-order";
        cout << "\n6. Tampilkan Post-order";
        cout << "\n7. Tampilkan Child Node";
        cout << "\n8. Tampilkan Descendant Node";
        cout << "\n9. Keluar";
        cout << "\nPilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\nMasukkan data root: ";
                cin >> data;
                buatNode(data);
                break;
            case 2:
                cout << "\nMasukkan data parent: ";
                cin >> parentData;
                parentNode = cariNode(root, parentData);
                if (parentNode) {
                    cout << "Masukkan data anak kiri: ";
                    cin >> data;
                    insertLeft(data, parentNode);
                } else {
                    cout << "\nParent tidak ditemukan!\n";
                }
                break;
            case 3:
                cout << "\nMasukkan data parent: ";
                cin >> parentData;
                parentNode = cariNode(root, parentData);
                if (parentNode) {
                    cout << "Masukkan data anak kanan: ";
                    cin >> data;
                    insertRight(data, parentNode);
                } else {
                    cout << "\nParent tidak ditemukan!\n";
                }
                break;
            case 4:
                cout << "\nPre-order Traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case 5:
                cout << "\nIn-order Traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case 6:
                cout << "\nPost-order Traversal: ";
                postOrder(root);
                cout << endl;
                break;
            case 7:
                cout << "\nMasukkan data node: ";
                cin >> data;
                parentNode = cariNode(root, data);
                tampilkanChild(parentNode);
                break;
            case 8:
                cout << "\nMasukkan data node: ";
                cin >> data;
                parentNode = cariNode(root, data);
                tampilkanDescendant(parentNode);
                break;
            case 9:
                cout << "\nKeluar dari program.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }
    } while (pilihan != 9);

    return 0;
}