#include <iostream>
#include <limits>
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

// Variabel global
Pohon *root;

// Inisialisasi pohon
void init() {
    root = NULL;
}

// Membuat node baru
Pohon* buatNode(char data, Pohon *parent = NULL) {
    return new Pohon{data, NULL, NULL, parent};
}

// Menambahkan node kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left) {
        cout << "Node " << node->data << " sudah ada child kiri!" << endl;
        return NULL;
    }
    node->left = buatNode(data, node);
    return node->left;
}

// Menambahkan node kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right) {
        cout << "Node " << node->data << " sudah ada child kanan!" << endl;
        return NULL;
    }
    node->right = buatNode(data, node);
    return node->right;
}

// Menampilkan child dari node tertentu
void tampilChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }
    cout << "Child dari " << node->data << ": ";
    if (node->left) cout << node->left->data << " (kiri) ";
    if (node->right) cout << node->right->data << " (kanan)";
    if (!node->left && !node->right) cout << "Tidak ada";
    cout << endl;
}

// Menampilkan descendant dari node tertentu
void tampilDescendant(Pohon *node) {
    if (!node) return;
    if (node->left) {
        cout << node->left->data << " ";
        tampilDescendant(node->left);
    }
    if (node->right) {
        cout << node->right->data << " ";
        tampilDescendant(node->right);
    }
}

// Memeriksa apakah tree adalah BST
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

// Fungsi utama dengan menu
int main() {
    init();
    char pilihan, data, parent_data;
    Pohon *node;

    do {
        cout << "\nMENU TREE:";
        cout << "\n1. Buat root";
        cout << "\n2. Tambah child kiri";
        cout << "\n3. Tambah child kanan";
        cout << "\n4. Tampilkan child";
        cout << "\n5. Tampilkan descendant";
        cout << "\n6. Cek apakah BST";
        cout << "\n7. Hitung jumlah simpul daun";
        cout << "\n0. Keluar";
        cout << "\nPilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1': {
                if (!root) {
                    cout << "Masukkan data root: ";
                    cin >> data;
                    root = buatNode(data);
                    cout << "Root dengan data " << data << " berhasil dibuat." << endl;
                } else {
                    cout << "Root sudah ada!" << endl;
                }
                break;
            }
            case '2': {
                cout << "Masukkan data parent: ";
                cin >> parent_data;
                node = root;
                if (node && node->data == parent_data) {
                    cout << "Masukkan data anak kiri: ";
                    cin >> data;
                    insertLeft(data, node);
                } else {
                    cout << "Parent tidak ditemukan." << endl;
                }
                break;
            }
            case '3': {
                cout << "Masukkan data parent: ";
                cin >> parent_data;
                node = root;
                if (node && node->data == parent_data) {
                    cout << "Masukkan data anak kanan: ";
                    cin >> data;
                    insertRight(data, node);
                } else {
                    cout << "Parent tidak ditemukan." << endl;
                }
                break;
            }
            case '4': {
                cout << "Masukkan data node: ";
                cin >> data;
                node = root;
                if (node && node->data == data) {
                    tampilChild(node);
                } else {
                    cout << "Node tidak ditemukan!" << endl;
                }
                break;
            }
            case '5': {
                cout << "Masukkan data node: ";
                cin >> data;
                node = root;
                if (node && node->data == data) {
                    cout << "Descendant dari " << node->data << ": ";
                    tampilDescendant(node);
                    cout << endl;
                } else {
                    cout << "Node tidak ditemukan!" << endl;
                }
                break;
            }
            case '6': {
                if (is_valid_bst(root, numeric_limits<char>::min(), numeric_limits<char>::max())) {
                    cout << "Pohon adalah Binary Search Tree (BST)." << endl;
                } else {
                    cout << "Pohon BUKAN Binary Search Tree (BST)." << endl;
                }
                break;
            }
            case '7': {
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            }
            case '0': {
                cout << "Keluar program." << endl;
                break;
            }
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != '0');

    return 0;
}
