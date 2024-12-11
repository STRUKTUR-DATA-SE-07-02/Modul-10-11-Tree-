#include <iostream>
#include <climits>
using namespace std;

struct Pohon {
    char data; // Untuk pohon biner
    int intData; // Untuk pohon BST
    Pohon *left, *right, *parent;
};

// Variabel global untuk pohon biner
Pohon *root = NULL;

// Fungsi untuk inisialisasi pohon biner
void init() {
    root = NULL;
}

// Fungsi untuk memeriksa apakah pohon biner kosong
bool isEmpty() {
    return root == NULL;
}

// Fungsi untuk membuat node baru sebagai root
void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, 0, NULL, NULL, NULL};
        cout << "Node " << data << " berhasil dibuat sebagai root.\n";
    } else {
        cout << "Root sudah ada.\n";
    }
}

// Fungsi untuk mencari node dalam pohon biner
Pohon* findNode(Pohon *node, char data) {
    if (!node) return NULL;
    if (node->data == data) return node;
    Pohon *leftResult = findNode(node->left, data);
    if (leftResult) return leftResult;
    return findNode(node->right, data);
}

// Fungsi untuk menambahkan anak kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kiri.\n";
        return NULL;
    }
    Pohon *baru = new Pohon{data, 0, NULL, NULL, node};
    node->left = baru;
    cout << "Node " << data << " berhasil ditambahkan ke anak kiri " << node->data << ".\n";
    return baru;
}

// Fungsi untuk menambahkan anak kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kanan.\n";
        return NULL;
    }
    Pohon *baru = new Pohon{data, 0, NULL, NULL, node};
    node->right = baru;
    cout << "Node " << data << " berhasil ditambahkan ke anak kanan " << node->data << ".\n";
    return baru;
}

// Fungsi untuk menampilkan anak dari node tertentu
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

// Fungsi untuk menampilkan keturunan dari node tertentu
void tampilkanDescendants(Pohon *node) {
    if (!node) return;
    if (node->left || node->right) cout << node->data << ": ";
    if (node->left) cout << node->left->data << " ";
    if (node->right) cout << node->right->data << " ";
    cout << "\n";
    tampilkanDescendants(node->left);
    tampilkanDescendants(node->right);
}

// Fungsi untuk memeriksa validitas BST
bool is_valid_bst(Pohon* node, int min_val, int max_val) {
    if (!node) return true; 
    if (node->intData <= min_val || node->intData >= max_val)
        return false;
    return is_valid_bst(node->left, min_val, node->intData) &&
           is_valid_bst(node->right, node->intData, max_val);
}

// Fungsi untuk menghitung jumlah simpul daun
int cari_simpul_daun(Pohon* node) {
    if (!node) return 0; 
    if (!node->left && !node->right) return 1; 
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Menu untuk interaksi pengguna
void menu() {
    int pilihan;
    char data, parent_data;
    Pohon *parent_node;

    do {
        cout << "\nMenu Binary Tree:";
        cout << "\n1. Add Root";
        cout << "\n2. Tambahkan Anak Kiri";
        cout << "\n3. Tambahkan Anak Kanan";
        cout << "\n4. Tampilkan Child";
        cout << "\n5. Tampilkan Descendants";
        cout << "\n6. Cek Validitas BST";
        cout << "\n7. Hitung Jumlah Simpul Daun";
        cout << "\n8. Keluar";
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
                cout << "Masukkan data node: ";
                cin >> data;
                parent_node = findNode(root, data);
                cout << "Pohon valid BST: " << (is_valid_bst(parent_node, INT_MIN, INT_MAX) ? "Ya" : "Tidak") << endl;
                break;

            case 7:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;

            case 8:
                cout << "Keluar.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);
}

int main() {
    init();
    menu();
    return 0;
}