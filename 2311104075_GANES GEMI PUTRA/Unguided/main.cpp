#include <iostream>
#include <climits> // Untuk CHAR_MIN dan CHAR_MAX
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root;

// Inisialisasi pohon
void init() {
    root = NULL;
}

// Membuat node baru sebagai root pohon
void buatNode(char data) {
    if (!root) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "Node " << data << " berhasil dibuat sebagai root.\n";
    } else {
        cout << "Pohon sudah memiliki root.\n";
    }
}

// Menambahkan node baru ke kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left) {
        cout << "Node " << node->data << " sudah memiliki child kiri.\n";
        return NULL;
    }
    Pohon *baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "Node " << data << " berhasil ditambahkan ke kiri " << node->data << ".\n";
    return baru;
}

// Menambahkan node baru ke kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right) {
        cout << "Node " << node->data << " sudah memiliki child kanan.\n";
        return NULL;
    }
    Pohon *baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "Node " << data << " berhasil ditambahkan ke kanan " << node->data << ".\n";
    return baru;
}

// Menampilkan child dari node
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan.\n";
        return;
    }
    cout << "Node " << node->data << " memiliki:\n";
    cout << "- Anak kiri: " << (node->left ? node->left->data : '-') << "\n";
    cout << "- Anak kanan: " << (node->right ? node->right->data : '-') << "\n";
}

// Menampilkan semua descendant dari node
void tampilkanDescendant(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    tampilkanDescendant(node->left);
    tampilkanDescendant(node->right);
}

// Fungsi untuk memeriksa apakah pohon adalah BST yang valid
bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;

    if (node->data <= min_val || node->data >= max_val)
        return false;

    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// Fungsi untuk menghitung jumlah simpul daun
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0; // Jika node kosong, tidak ada simpul
    if (!node->left && !node->right) return 1; // Jika node adalah daun
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right); // Rekursi ke kiri dan kanan
}

// Menu interaktif
void menu() {
    int pilihan;
    char data, parent;
    Pohon *node;

    do {
        cout << "\n--- Menu Pohon Biner ---\n";
        cout << "1. Tambahkan root\n";
        cout << "2. Tambahkan node kiri\n";
        cout << "3. Tambahkan node kanan\n";
        cout << "4. Tampilkan child\n";
        cout << "5. Tampilkan descendant\n";
        cout << "6. Periksa validitas BST\n";
        cout << "7. Hitung jumlah simpul daun\n";
        cout << "8. Keluar\n";
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
                cin >> parent;
                cout << "Masukkan data node kiri: ";
                cin >> data;
                node = root;
                while (node && node->data != parent) {
                    if (parent < node->data) node = node->left;
                    else node = node->right;
                }
                if (node) {
                    insertLeft(data, node);
                } else {
                    cout << "Parent tidak ditemukan.\n";
                }
                break;
            case 3:
                cout << "Masukkan data parent: ";
                cin >> parent;
                cout << "Masukkan data node kanan: ";
                cin >> data;
                node = root;
                while (node && node->data != parent) {
                    if (parent < node->data) node = node->left;
                    else node = node->right;
                }
                if (node) {
                    insertRight(data, node);
                } else {
                    cout << "Parent tidak ditemukan.\n";
                }
                break;
            case 4:
                cout << "Masukkan data node: ";
                cin >> data;
                node = root;
                while (node && node->data != data) {
                    if (data < node->data) node = node->left;
                    else node = node->right;
                }
                tampilkanChild(node);
                break;
            case 5:
                cout << "Masukkan data node: ";
                cin >> data;
                node = root;
                while (node && node->data != data) {
                    if (data < node->data) node = node->left;
                    else node = node->right;
                }
                if (node) {
                    cout << "Descendant dari " << node->data << ": ";
                    tampilkanDescendant(node);
                    cout << "\n";
                } else {
                    cout << "Node tidak ditemukan.\n";
                }
                break;
            case 6:
                cout << "Apakah pohon merupakan BST yang valid? ";
                if (is_valid_bst(root, CHAR_MIN, CHAR_MAX))
                    cout << "Ya.\n";
                else
                    cout << "Tidak.\n";
                break;
            case 7:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << "\n";
                break;
            case 8:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);
}

// Fungsi utama
int main() {
    init();
    menu();
    return 0;
}
