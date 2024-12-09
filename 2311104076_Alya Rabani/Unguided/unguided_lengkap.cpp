#include <iostream>
#include <limits> // Untuk nilai batas min dan max
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right;
    Pohon *parent;
};

Pohon *root, *baru;

// Inisialisasi pohon
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
        cout << "Node " << data << " berhasil dibuat sebagai root.\n";
    } else {
        cout << "Pohon sudah ada!\n";
    }
}

// Menambahkan node ke kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "Child kiri dari " << node->data << " sudah ada!\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "Node " << data << " ditambahkan ke kiri dari " << node->data << "\n";
    return baru;
}

// Menambahkan node ke kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "Child kanan dari " << node->data << " sudah ada!\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "Node " << data << " ditambahkan ke kanan dari " << node->data << "\n";
    return baru;
}

// 2 Modifikasi mencari node berdasarkan data secara rekrusif
Pohon* findNode(char data, Pohon *node) {
    if (!node) return NULL; // Basis rekursif: jika node NULL, kembalikan NULL
    
    if (node->data == data) // Jika data cocok, kembalikan node
        return node;

    // Cari ke anak kiri dan kanan secara rekursif
    Pohon *leftResult = findNode(data, node->left);
    if (leftResult) return leftResult; // Jika ditemukan di anak kiri, kembalikan hasil

    Pohon *rightResult = findNode(data, node->right);
    return rightResult; // Jika ditemukan di anak kanan, kembalikan hasil
}

// 1 Modifikasi menampilkan child dari node tertentu
void tampilChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan.\n";
        return;
    }
    cout << "Node: " << node->data << "\n";
    if (node->left) cout << "Child Kiri: " << node->left->data << "\n";
    else cout << "Child Kiri: NULL\n";
    if (node->right) cout << "Child Kanan: " << node->right->data << "\n";
    else cout << "Child Kanan: NULL\n";
}

// 1 Modifikasi menampilkan descendant dari node tertentu (rekursif)
void tampilDescendant(Pohon *node) {
    if (!node) return;
    if (node->left || node->right)
        cout << node->data << " memiliki descendant: ";
    if (node->left) cout << node->left->data << " ";
    if (node->right) cout << node->right->data << " ";
    cout << "\n";
    tampilDescendant(node->left);
    tampilDescendant(node->right);
}

// 2 Modifikasi menambahkan fungsi validasi apakah pohon adalah BST
bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// 3 Modifikasi menghitung jumlah simpul daun
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0; // Basis rekursi
    if (!node->left && !node->right) return 1; // Node daun
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Fungsi utama dengan menu
int main() 
{
    int pilihan;
    char data, parent;
    Pohon *temp = NULL;
    init();

    // 1 Modifikasi membuat menu program agar user dapat menginputkan sendiri
    do {
        cout << "\n=== MENU POHON BINARY TREE ===\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambah Child Kiri\n";
        cout << "3. Tambah Child Kanan\n";
        cout << "4. Tampilkan Child Node\n";
        cout << "5. Tampilkan Descendant Node\n";
        cout << "6. Cek Apakah Pohon adalah BST\n";
        cout << "7. Hitung Jumlah Simpul Daun\n";
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
                cin >> parent;
                cout << "Masukkan data anak kiri: ";
                cin >> data;
                temp = findNode(parent, root); // Cari node berdasarkan data
                if (temp) {
                    insertLeft(data, temp);
                    } else {
                        cout << "Node dengan data " << parent << " tidak ditemukan!\n";
                    }
                break;
            case 3:
                cout << "Masukkan data parent: ";
                cin >> parent;
                cout << "Masukkan data anak kanan: ";
                cin >> data;
                temp = findNode(parent, root); // Cari node berdasarkan data
                if (temp) {
                    insertRight(data, temp);
                } else {
                    cout << "Node dengan data " << parent << " tidak ditemukan!\n";
                }
                break;
            case 4:
                cout << "Masukkan node yang ingin ditampilkan child-nya: ";
                cin >> data;
                temp = findNode(data, root); // Cari node berdasarkan data
                if (temp) {
                    tampilChild(temp);
                } else {
                    cout << "Node dengan data " << data << " tidak ditemukan!\n";
                }
                break;
            case 5:
                cout << "Masukkan node yang ingin ditampilkan descendant-nya: ";
                cin >> data;
                tampilDescendant(findNode(data, root));
                break;
            case 6:
                if (is_valid_bst(root, numeric_limits<char>::min(), numeric_limits<char>::max()))
                    cout << "Pohon adalah BST yang valid.\n";
                else
                    cout << "Pohon bukan BST yang valid.\n";
                break;
            case 7:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << "\n";
                break;
            case 0:
                cout << "Keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
