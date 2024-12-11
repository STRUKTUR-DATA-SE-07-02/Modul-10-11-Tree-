#include <iostream>
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right;
    Pohon *parent;
};

Pohon *root;

// Inisialisasi pohon kosong
void init() {
    root = NULL;
}

// Membuat node baru
Pohon* buatNode(char data) {
    return new Pohon{data, NULL, NULL, NULL};
}

// Menambahkan node ke tree
Pohon* insertNode(char data, Pohon *node, bool isLeft) {
    Pohon *baru = buatNode(data);
    if (isLeft) {
        node->left = baru;
        cout << "\nNode " << data << " berhasil ditambahkan ke anak kiri " << node->data << endl;
    } else {
        node->right = baru;
        cout << "\nNode " << data << " berhasil ditambahkan ke anak kanan " << node->data << endl;
    }
    baru->parent = node;
    return baru;
}

// Menampilkan child dari suatu node
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "\nNode tidak ditemukan." << endl;
        return;
    }
    cout << "\nNode " << node->data << " memiliki:";
    if (node->left) cout << "\n  Anak kiri: " << node->left->data;
    else cout << "\n  Anak kiri: (tidak ada)";
    if (node->right) cout << "\n  Anak kanan: " << node->right->data;
    else cout << "\n  Anak kanan: (tidak ada)";
    cout << endl;
}

// Menampilkan semua descendant dari suatu node
void tampilkanDescendant(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    tampilkanDescendant(node->left);
    tampilkanDescendant(node->right);
}

// Fungsi untuk validasi BST
bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// Menghitung jumlah simpul daun
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Menu utama
void menu() {
    int pilihan;
    char data, parent_data;
    do {
        cout << "\nMenu Binary Tree:";
        cout << "\n1. Tambah Node";
        cout << "\n2. Tampilkan Child";
        cout << "\n3. Tampilkan Descendant";
        cout << "\n4. Periksa Validitas BST";
        cout << "\n5. Hitung Jumlah Simpul Daun";
        cout << "\n6. Keluar";
        cout << "\nPilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                if (!root) {
                    cout << "\nMasukkan data root: ";
                    cin >> data;
                    root = buatNode(data);
                    cout << "\nRoot " << data << " berhasil dibuat." << endl;
                } else {
                    cout << "\nMasukkan data node: ";
                    cin >> data;
                    cout << "\nMasukkan data parent: ";
                    cin >> parent_data;
                    Pohon *parent = root;
                    bool found = false;
                    while (parent && !found) {
                        if (parent->data == parent_data) {
                            found = true;
                        } else {
                            if (parent->left) parent = parent->left;
                            else parent = parent->right;
                        }
                    }
                    if (!found) {
                        cout << "\nParent tidak ditemukan.";
                        break;
                    }
                    cout << "\nTambahkan ke (1) kiri atau (2) kanan? ";
                    int posisi;
                    cin >> posisi;
                    insertNode(data, parent, posisi == 1);
                }
                break;

            case 2:
                cout << "\nMasukkan data node: ";
                cin >> data;
                tampilkanChild(root);
                break;

            case 3:
                cout << "\nMasukkan data node: ";
                cin >> data;
                cout << "\nDescendant dari node " << data << ": ";
                tampilkanDescendant(root);
                cout << endl;
                break;

            case 4:
                if (is_valid_bst(root, CHAR_MIN, CHAR_MAX))
                    cout << "\nPohon adalah Binary Search Tree yang valid.";
                else
                    cout << "\nPohon bukan Binary Search Tree yang valid.";
                break;

            case 5:
                cout << "\nJumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;

            case 6:
                cout << "\nKeluar dari program." << endl;
                break;

            default:
                cout << "\nPilihan tidak valid." << endl;
        }
    } while (pilihan != 6);
}

int main() {
    init();
    menu();
    return 0;
}
