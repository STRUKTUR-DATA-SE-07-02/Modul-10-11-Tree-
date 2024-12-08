#include <iostream>
using namespace std;

/// PROGRAM BINARY TREE

// Struktur data pohon biner
struct Pohon {
    char data;                 // Data pada node
    Pohon *left, *right;       // Pointer ke anak kiri dan kanan
    Pohon *parent;             // Pointer ke induk node
};
// Variabel global
Pohon *root, *baru;
// Inisialisasi pohon kosong
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
        cout << "\nNode " << data << " berhasil dibuat sebagai root.\n";
    } else {
        cout << "\nPohon sudah ada.\n";
    }
}
// Menambahkan node anak kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "\nNode " << node->data << " sudah memiliki anak kiri!\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke kiri node " << node->data << ".\n";
    return baru;
}
// Menambahkan node anak kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "\nNode " << node->data << " sudah memiliki anak kanan!\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke kanan node " << node->data << ".\n";
    return baru;
}
void update(char data, Pohon *node) {
    if (!node) { // Jika node tidak ditemukan
        cout << "\nNode yang ingin diubah tidak ditemukan!" << endl;
        return;
    }
    char temp = node->data; // Menyimpan data lama
    node->data = data;      // Mengubah data dengan nilai baru
    cout << "\nNode " << temp << " berhasil diubah menjadi " << data << endl;
}

// Mencari node dengan data tertentu
void find(char data, Pohon *node) {
    if (!node) return; // Jika node tidak ada, hentikan pencarian

    if (node->data == data) { // Jika data ditemukan
        cout << "\nNode ditemukan: " << data << endl;
        return;
    }
    // Melakukan pencarian secara rekursif ke anak kiri dan kanan
    find(data, node->left);
    find(data, node->right);
}
// Menampilkan child dari node tertentu
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "\nNode tidak ditemukan!\n";
        return;
    }
    cout << "\nChild dari node " << node->data << ":\n";
    if (node->left)
        cout << "Anak Kiri: " << node->left->data << endl;
    else
        cout << "Anak Kiri: NULL\n";

    if (node->right)
        cout << "Anak Kanan: " << node->right->data << endl;
    else
        cout << "Anak Kanan: NULL\n";
}
// Menampilkan semua descendant (keturunan) dari node tertentu
void tampilkanDescendant(Pohon *node) {
    if (!node) return;

    if (node->left || node->right) {
        cout << node->data << " -> ";
        if (node->left) cout << node->left->data << " ";
        if (node->right) cout << node->right->data << " ";
        cout << endl;
    }
    tampilkanDescendant(node->left);
    tampilkanDescendant(node->right);
}
// Traversal Pre-order
void preOrder(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}
// Traversal In-order
void inOrder(Pohon *node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}
// Traversal Post-order
void postOrder(Pohon *node) {
    if (!node) return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}
bool is_valid_bst(Pohon* node, char min_val, char max_val) {
    if (node == NULL) return true; 
    if (node->data <= min_val || node->data >= max_val)
        return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}
bool isValidBST(Pohon* root) {
    return is_valid_bst(root, CHAR_MIN, CHAR_MAX);
}
int cari_simpul_daun(Pohon* node) {
    if (node == NULL) return 0; 
    if (node->left == NULL && node->right == NULL)
        return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Menu
void menu() {
    int pilihan;
    char data, parentData;
    Pohon *parentNode;

    do {
        cout << "\n\n=== MENU POHON BINARY TREE ===\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambahkan Anak Kiri\n";
        cout << "3. Tambahkan Anak Kanan\n";
        cout << "4. Tampilkan Child dari Node\n";
        cout << "5. Tampilkan Descendant dari Node\n";
        cout << "6. Traversal Pre-order\n";
        cout << "7. Traversal In-order\n";
        cout << "8. Traversal Post-order\n";
        cout << "9. Keluar\n";
        cout << "10. Periksa Validitas BST\n";
        cout << "11. Hitung Jumlah Simpul Daun\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "\nMasukkan data root: ";
                cin >> data;
                buatNode(data);
                break;
            }
            case 2: {
                cout << "\nMasukkan data parent: ";
                cin >> parentData;
                cout << "Masukkan data anak kiri: ";
                cin >> data;

                parentNode = root; // Mulai pencarian dari root
                find(parentData, root);
                if (parentNode)
                    insertLeft(data, parentNode);
                break;
            }
            case 3: {
                cout << "\nMasukkan data parent: ";
                cin >> parentData;
                cout << "Masukkan data anak kanan: ";
                cin >> data;

                parentNode = root; // Mulai pencarian dari root
                find(parentData, root);
                if (parentNode)
                    insertRight(data, parentNode);
                break;
            }
            case 4: {
                cout << "\nMasukkan data node: ";
                cin >> data;

                parentNode = root;
                find(data, root);
                tampilkanChild(parentNode);
                break;
            }
            case 5: {
                cout << "\nMasukkan data node: ";
                cin >> data;

                parentNode = root;
                find(data, root);
                cout << "\nDescendant dari node " << data << ":\n";
                tampilkanDescendant(parentNode);
                break;
            }
            case 6: {
                cout << "\nTraversal Pre-order: ";
                preOrder(root);
                break;
            }
            case 7: {
                cout << "\nTraversal In-order: ";
                inOrder(root);
                break;
            }
            case 8: {
                cout << "\nTraversal Post-order: ";
                postOrder(root);
                break;
            }
            case 9: {
                cout << "\nKeluar dari program.\n";
                break;
            }
            case 10: {
                // Cek apakah pohon valid sebagai BST
                cout << "\nMemeriksa apakah pohon valid sebagai BST...\n";
                if (isValidBST(root))
                    cout << "Pohon ini adalah Binary Search Tree (BST).\n";
                else
                    cout << "Pohon ini BUKAN Binary Search Tree (BST).\n";
                break;
            }
            case 11: {
                // Hitung jumlah simpul daun
                int jumlahDaun = cari_simpul_daun(root);
                cout << "\nJumlah simpul daun dalam pohon: " << jumlahDaun << endl;
                break;
            }

            default:
                cout << "\nPilihan tidak valid.\n";
        }
    } while (pilihan != 9);
}
int main() {
    init();
    menu();
    return 0;
}