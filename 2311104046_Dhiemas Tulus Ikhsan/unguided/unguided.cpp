#include <iostream>
#include <limits>
#include <climits> // Untuk batas minimum dan maksimum karakter
using namespace std;

// Struktur pohon
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root, *baru;

// Fungsi inisialisasi
void init() {
    root = NULL;
}

// Mengecek apakah pohon kosong
bool isEmpty() {
    return root == NULL;
}

// Membuat node baru sebagai root
void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root.\n";
    } else {
        cout << "\nPohon sudah dibuat.\n";
    }
}

// Menambahkan node ke anak kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (!node) return NULL;
    if (node->left != NULL) {
        cout << "\nNode " << node->data << " sudah memiliki child kiri.\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << ".\n";
    return baru;
}

// Menambahkan node ke anak kanan
Pohon* insertRight(char data, Pohon *node) {
    if (!node) return NULL;
    if (node->right != NULL) {
        cout << "\nNode " << node->data << " sudah memiliki child kanan.\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << ".\n";
    return baru;
}

// Menemukan node berdasarkan data
Pohon* findNode(Pohon *node, char data) {
    if (!node) return NULL;
    if (node->data == data) return node;
    Pohon *leftResult = findNode(node->left, data);
    if (leftResult) return leftResult;
    return findNode(node->right, data);
}

// Menampilkan child dari node
void tampilChild(Pohon *node) {
    if (!node) {
        cout << "\nNode tidak ditemukan.\n";
        return;
    }
    cout << "\nChild dari node " << node->data << ":\n";
    if (node->left) cout << "Kiri: " << node->left->data << "\n";
    else cout << "Kiri: NULL\n";
    if (node->right) cout << "Kanan: " << node->right->data << "\n";
    else cout << "Kanan: NULL\n";
}

// Menampilkan descendant dari node
void tampilDescendant(Pohon *node) {
    if (!node) return;
    if (node->left) cout << node->left->data << " ";
    if (node->right) cout << node->right->data << " ";
    tampilDescendant(node->left);
    tampilDescendant(node->right);
}

// Traversal In-order
void inOrder(Pohon *node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

// Validasi apakah pohon merupakan BST
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

// Fungsi Menu
void menu() {
    int pilihan;
    char data, parentData;
    Pohon *node;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambah Anak Kiri\n";
        cout << "3. Tambah Anak Kanan\n";
        cout << "4. Tampilkan Child\n";
        cout << "5. Tampilkan Descendant\n";
        cout << "6. In-Order Traversal\n";
        cout << "7. Validasi BST\n";
        cout << "8. Hitung Simpul Daun\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cout << "Masukkan data root: ";
            cin >> data;
            buatNode(data);
            break;
        case 2:
            cout << "Masukkan data parent: ";
            cin >> parentData;
            cout << "Masukkan data anak kiri: ";
            cin >> data;
            node = findNode(root, parentData);
            insertLeft(data, node);
            break;
        case 3:
            cout << "Masukkan data parent: ";
            cin >> parentData;
            cout << "Masukkan data anak kanan: ";
            cin >> data;
            node = findNode(root, parentData);
            insertRight(data, node);
            break;
        case 4:
            cout << "Masukkan data node: ";
            cin >> data;
            node = findNode(root, data);
            tampilChild(node);
            break;
        case 5:
            cout << "Masukkan data node: ";
            cin >> data;
            node = findNode(root, data);
            cout << "\nDescendant dari node " << data << ": ";
            tampilDescendant(node);
            cout << "\n";
            break;
        case 6:
            cout << "\nIn-Order Traversal: ";
            inOrder(root);
            cout << "\n";
            break;
        case 7:
            cout << "Apakah pohon valid BST? "
                 << (is_valid_bst(root, CHAR_MIN, CHAR_MAX) ? "Ya" : "Tidak") << "\n";
            break;
        case 8:
            cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << "\n";
            break;
        case 0:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

// Fungsi utama
int main() {
    init();
    menu();
    return 0;
}
