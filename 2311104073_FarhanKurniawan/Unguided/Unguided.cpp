#include <iostream>
#include <limits.h>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root;

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
    Pohon *baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
    return baru;
}

Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
        return NULL;
    }
    Pohon *baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    return baru;
}

void tampilChild(Pohon *node) {
    if (!node) {
        cout << "\nNode tidak ditemukan!" << endl;
        return;
    }
    cout << "\nNode " << node->data << " memiliki:\n";
    if (node->left) cout << "Child kiri: " << node->left->data << endl;
    else cout << "Tidak ada child kiri.\n";
    if (node->right) cout << "Child kanan: " << node->right->data << endl;
    else cout << "Tidak ada child kanan.\n";
}

void tampilDescendant(Pohon *node) {
    if (!node) return;
    if (node->left) cout << node->left->data << " ";
    if (node->right) cout << node->right->data << " ";
    tampilDescendant(node->left);
    tampilDescendant(node->right);
}

bool is_valid_bst(Pohon *node, int min_val, int max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

void menu() {
    int pilihan;
    char data, parent_data;
    Pohon *parent_node = NULL;

    do {
        cout << "\n\n=== MENU ===";
        cout << "\n1. Buat Root";
        cout << "\n2. Tambah Node Kiri";
        cout << "\n3. Tambah Node Kanan";
        cout << "\n4. Tampilkan Child";
        cout << "\n5. Tampilkan Descendant";
        cout << "\n6. Cek Valid BST";
        cout << "\n7. Hitung Jumlah Simpul Daun";
        cout << "\n8. Keluar";
        cout << "\nPilihan: ";
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
            cout << "Masukkan data node baru: ";
            cin >> data;
            parent_node = root; // Implement pencarian node parent jika perlu
            insertLeft(data, parent_node);
            break;

        case 3:
            cout << "Masukkan data parent: ";
            cin >> parent_data;
            cout << "Masukkan data node baru: ";
            cin >> data;
            parent_node = root; // Implement pencarian node parent jika perlu
            insertRight(data, parent_node);
            break;

        case 4:
            cout << "Masukkan data node: ";
            cin >> data;
            tampilChild(root); // Implement pencarian node jika perlu
            break;

        case 5:
            cout << "Masukkan data node: ";
            cin >> data;
            cout << "Descendant: ";
            tampilDescendant(root); // Implement pencarian node jika perlu
            break;

        case 6:
            cout << (is_valid_bst(root, INT_MIN, INT_MAX) ? "Valid BST" : "Bukan BST") << endl;
            break;

        case 7:
            cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
            break;

        case 8:
            cout << "Keluar program." << endl;
            break;

        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 8);
}

int main() {
    init();
    menu();
    return 0;
}