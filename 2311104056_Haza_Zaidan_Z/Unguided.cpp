#include <iostream>
#include <limits>
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

// Deklarasi root
Pohon *root = NULL;

// Inisialisasi pohon
void init() {
    root = NULL;
}

// Fungsi membuat node baru
Pohon* buatNode(char data, Pohon *parent = NULL) {
    return new Pohon{data, NULL, NULL, parent};
}

// Menambahkan node ke pohon
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "Node " << node->data << " sudah ada child kiri!" << endl;
        return NULL;
    }
    node->left = buatNode(data, node);
    cout << "Node " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
    return node->left;
}

Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "Node " << node->data << " sudah ada child kanan!" << endl;
        return NULL;
    }
    node->right = buatNode(data, node);
    cout << "Node " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    return node->right;
}

// Fungsi traversal pre-order
void preOrder(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

// Fungsi untuk menampilkan child dan descendant dari node tertentu
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }
    cout << "Node: " << node->data << endl;
    if (node->left)
        cout << "Child Kiri: " << node->left->data << endl;
    else
        cout << "Child Kiri: NULL" << endl;

    if (node->right)
        cout << "Child Kanan: " << node->right->data << endl;
    else
        cout << "Child Kanan: NULL" << endl;

    cout << "Descendants (Pre-order): ";
    preOrder(node);
    cout << endl;
}

// Fungsi memeriksa apakah pohon adalah Binary Search Tree
bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// Fungsi menghitung jumlah simpul daun
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Menu utama
void menu() {
    char data, parentData;
    int pilihan;
    Pohon *parentNode = NULL;

    do {
        cout << "\nMENU:\n"
             << "1. Tambah Root\n"
             << "2. Tambah Child Kiri\n"
             << "3. Tambah Child Kanan\n"
             << "4. Tampilkan Child dan Descendants\n"
             << "5. Periksa Validitas BST\n"
             << "6. Hitung Simpul Daun\n"
             << "7. Traversal Pre-order\n"
             << "0. Keluar\n"
             << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                if (!root) {
                    cout << "Masukkan data root: ";
                    cin >> data;
                    root = buatNode(data);
                    cout << "Root berhasil dibuat dengan data: " << data << endl;
                } else {
                    cout << "Root sudah ada!" << endl;
                }
                break;

            case 2:
                cout << "Masukkan data parent: ";
                cin >> parentData;
                cout << "Masukkan data anak kiri: ";
                cin >> data;
                parentNode = root; // cari parent node (untuk sederhana, diasumsikan valid)
                if (parentNode)
                    insertLeft(data, parentNode);
                else
                    cout << "Parent tidak ditemukan!" << endl;
                break;

            case 3:
                cout << "Masukkan data parent: ";
                cin >> parentData;
                cout << "Masukkan data anak kanan: ";
                cin >> data;
                parentNode = root; // cari parent node (untuk sederhana, diasumsikan valid)
                if (parentNode)
                    insertRight(data, parentNode);
                else
                    cout << "Parent tidak ditemukan!" << endl;
                break;

            case 4:
                cout << "Masukkan data node: ";
                cin >> data;
                tampilkanChild(root); // langsung tampilkan semua untuk contoh sederhana
                break;

            case 5:
                if (is_valid_bst(root, numeric_limits<char>::min(), numeric_limits<char>::max()))
                    cout << "Pohon adalah Binary Search Tree (BST)" << endl;
                else
                    cout << "Pohon BUKAN Binary Search Tree (BST)" << endl;
                break;

            case 6:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;

            case 7:
                cout << "Pre-order Traversal: ";
                preOrder(root);
                cout << endl;
                break;

            case 0:
                cout << "Keluar dari program." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// Fungsi utama
int main() {
    init();
    menu();
    return 0;
}
