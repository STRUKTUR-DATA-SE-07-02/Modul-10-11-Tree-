#include <iostream>
#include <climits>
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

// Variabel global
Pohon *root = NULL, *baru;

// Inisialisasi pohon
void init() {
    root = NULL;
}

// Mengecek apakah pohon kosong
bool isEmpty() {
    return root == NULL;
}

// Membuat node baru
void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nRoot sudah dibuat." << endl;
    }
}

// Menambahkan node sebagai anak kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "\nNode " << node->data << " sudah memiliki anak kiri!" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke anak kiri " << node->data << endl;
    return baru;
}

// Menambahkan node sebagai anak kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "\nNode " << node->data << " sudah memiliki anak kanan!" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke anak kanan " << node->data << endl;
    return baru;
}

// Menampilkan anak langsung dari node
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "\nNode tidak ditemukan." << endl;
        return;
    }
    cout << "\nAnak langsung dari " << node->data << ": ";
    if (node->left) cout << "Kiri: " << node->left->data << " ";
    if (node->right) cout << "Kanan: " << node->right->data << " ";
    if (!node->left && !node->right) cout << "Tidak memiliki anak.";
    cout << endl;
}

// Menampilkan semua keturunan dari node
void tampilkanDescendant(Pohon *node) {
    if (!node) return;
    if (node->left || node->right) cout << node->data << " -> ";
    if (node->left) {
        cout << node->left->data << " ";
        tampilkanDescendant(node->left);
    }
    if (node->right) {
        cout << node->right->data << " ";
        tampilkanDescendant(node->right);
    }
}

// Memeriksa apakah pohon valid BST
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

// Menu program
void menu() {
    char pilihan, data, parent;
    Pohon *current;
    do {
        cout << "\nMenu Program Binary Tree:"
             << "\n1. Buat Node Root"
             << "\n2. Tambah Anak Kiri"
             << "\n3. Tambah Anak Kanan"
             << "\n4. Tampilkan Child"
             << "\n5. Tampilkan Descendant"
             << "\n6. Cek Valid BST"
             << "\n7. Hitung Jumlah Simpul Daun"
             << "\n8. Keluar"
             << "\nPilih: ";
        cin >> pilihan;
        switch (pilihan) {
            case '1':
                cout << "Masukkan data root: ";
                cin >> data;
                buatNode(data);
                break;
            case '2':
                cout << "Masukkan parent: ";
                cin >> parent;
                current = root; // Cari node parent
                while (current && current->data != parent) {
                    if (parent < current->data)
                        current = current->left;
                    else
                        current = current->right;
                }
                if (current) {
                    cout << "Masukkan data anak kiri: ";
                    cin >> data;
                    insertLeft(data, current);
                } else {
                    cout << "Node parent tidak ditemukan.\n";
                }
                break;
            case '3':
                cout << "Masukkan parent: ";
                cin >> parent;
                current = root; // Cari node parent
                while (current && current->data != parent) {
                    if (parent < current->data)
                        current = current->left;
                    else
                        current = current->right;
                }
                if (current) {
                    cout << "Masukkan data anak kanan: ";
                    cin >> data;
                    insertRight(data, current);
                } else {
                    cout << "Node parent tidak ditemukan.\n";
                }
                break;
            case '4':
                cout << "Masukkan node untuk menampilkan child: ";
                cin >> parent;
                current = root;
                while (current && current->data != parent) {
                    if (parent < current->data)
                        current = current->left;
                    else
                        current = current->right;
                }
                tampilkanChild(current);
                break;
            case '5':
                cout << "Masukkan node untuk menampilkan descendant: ";
                cin >> data;
                current = root;
                while (current && current->data != data) {
                    if (data < current->data)
                        current = current->left;
                    else
                        current = current->right;
                }
                if (current) {
                    cout << "Descendant dari " << data << ": ";
                    tampilkanDescendant(current);
                } else {
                    cout << "Node tidak ditemukan.\n";
                }
                break;
            case '6':
                if (is_valid_bst(root, CHAR_MIN, CHAR_MAX))
                    cout << "\nPohon adalah Binary Search Tree.\n";
                else
                    cout << "\nPohon BUKAN Binary Search Tree.\n";
                break;
            case '7':
                cout << "\nJumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            case '8':
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != '8');
}

// Fungsi utama
int main() {
    init();
    menu();
    return 0;
}
