#include <iostream>
#include <climits> // Untuk INT_MIN dan INT_MAX
using namespace std;

/// PROGRAM BINARY TREE

// Struktur data pohon biner
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
void tampilkanChild(Pohon *node) {
    if (!node) return;
    cout << "Child dari node " << node->data << ": ";
    if (node->left) cout << node->left->data << " (kiri) ";
    if (node->right) cout << node->right->data << " (kanan) ";
    if (!node->left && !node->right) cout << "Tidak ada child.";
    cout << endl;
}
void tampilkanDescendant(Pohon *node) {
    if (!node) return;
    if (node->left || node->right) {
        if (node->left) {
            cout << node->left->data << " ";
            tampilkanDescendant(node->left);
        }
        if (node->right) {
            cout << node->right->data << " ";
            tampilkanDescendant(node->right);
        }
    }
}
bool is_valid_bst(Pohon *node, int min_val, int max_val) {
    if (!node) return true; // Pohon kosong adalah BST
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}
void preOrder(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}
void menuInput() {
    char pilihan, data, parentData;
    Pohon *parentNode = NULL;
    while (true) {
        cout << "\nMenu Pohon Biner:\n";
        cout << "1. Tambah Node Root\n";
        cout << "2. Tambah Child Kiri\n";
        cout << "3. Tambah Child Kanan\n";
        cout << "4. Tampilkan Child\n";
        cout << "5. Tampilkan Descendant\n";
        cout << "6. Periksa BST\n";
        cout << "7. Hitung Simpul Daun\n";
        cout << "8. Traversal Pre-order\n";
        cout << "9. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                cout << "Masukkan data root: ";
                cin >> data;
                buatNode(data);
                break;
            case '2':
                cout << "Masukkan parent: ";
                cin >> parentData;
                cout << "Cari parent...\n";
                parentNode = root; // Untuk mencari node parent
                if (parentNode) {
                    cout << "Masukkan data untuk child kiri: ";
                    cin >> data;
                    insertLeft(data, parentNode);
                } else cout << "Parent tidak ditemukan!\n";
                break;
            case '3':
                cout << "Masukkan parent: ";
                cin >> parentData;
                parentNode = root;
                if (parentNode) {
                    cout << "Masukkan data untuk child kanan: ";
                    cin >> data;
                    insertRight(data, parentNode);
                } else cout << "Parent tidak ditemukan!\n";
                break;
            case '4':
                cout << "Masukkan node: ";
                cin >> data;
                tampilkanChild(root);
                break;
            case '5':
                cout << "Masukkan node: ";
                                cin >> data;
                parentNode = root;
                if (parentNode) {
                    cout << "Descendant dari " << data << ": ";
                    tampilkanDescendant(parentNode);
                    cout << endl;
                } else {
                    cout << "Node tidak ditemukan!\n";
                }
                break;
            case '6':
                cout << "Memeriksa apakah pohon adalah BST... ";
                cout << (is_valid_bst(root, INT_MIN, INT_MAX) ? "Ya, pohon adalah BST.\n" : "Tidak, pohon bukan BST.\n");
                break;
            case '7':
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            case '8':
                cout << "Pre-order Traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case '9':
                cout << "Keluar dari program.\n";
                return;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    }
}

// Fungsi utama
int main() {
    init(); // Inisialisasi pohon
    menuInput(); // Menjalankan menu interaktif
    return 0;
}

