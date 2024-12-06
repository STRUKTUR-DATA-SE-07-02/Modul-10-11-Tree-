#include <iostream>
#include <limits>
using namespace std;

//Struktur data pohon biner yang dimodifikasi
struct Pohon {
    int data;  //Diubah ke int untuk mendukung BST validation
    Pohon *left, *right;
    Pohon *parent;
};

Pohon *root, *baru;

//Nomor 1: Implementasi Menu dan Fungsi Tambahan
void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

//Membuat node baru dengan input user
void buatNode() {
    int data;
    cout << "Masukkan nilai node: ";
    cin >> data;

    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah memiliki root." << endl;
    }
}

//Menampilkan child dari sebuah node
void tampilkanChild(Pohon* node) {
    if (!node) {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }

    cout << "Node " << node->data << ":" << endl;
    if (node->left)
        cout << "Child kiri: " << node->left->data << endl;
    else
        cout << "Tidak ada child kiri" << endl;

    if (node->right)
        cout << "Child kanan: " << node->right->data << endl;
    else
        cout << "Tidak ada child kanan" << endl;
}

//Menampilkan semua descendant dari sebuah node
void tampilkanDescendant(Pohon* node) {
    if (!node) return;

    if (node->left) {
        cout << node->left->data << " ";
        tampilkanDescendant(node->left);
    }
    if (node->right) {
        cout << node->right->data << " ";
        tampilkanDescendant(node->right);
    }
}

//Nomor 2: Validasi BST
bool is_valid_bst(Pohon* node, int min_val, int max_val) {
    if (!node) return true;

    // Cek apakah nilai node berada dalam range yang valid
    if (node->data <= min_val || node->data >= max_val)
        return false;

    // Rekursif cek subtree kiri dan kanan
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

//Nomor 3: Menghitung Simpul Daun
int cari_simpul_daun(Pohon* node) {
    if (!node) return 0;

    // Jika node adalah daun (tidak punya anak)
    if (!node->left && !node->right)
        return 1;

    // Rekursif hitung daun di subtree kiri dan kanan
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Fungsi helper untuk mencari node berdasarkan nilai
Pohon* cariNode(Pohon* node, int nilai) {
    if (!node || node->data == nilai) return node;

    Pohon* kiri = cariNode(node->left, nilai);
    if (kiri) return kiri;

    return cariNode(node->right, nilai);
}

// Menu utama program
void menu() {
    int pilihan, nilai;
    do {
        cout << "\n=== MENU BINARY TREE ===" << endl;
        cout << "1. Buat Root" << endl;
        cout << "2. Tambah Node Kiri" << endl;
        cout << "3. Tambah Node Kanan" << endl;
        cout << "4. Tampilkan Child" << endl;
        cout << "5. Tampilkan Descendant" << endl;
        cout << "6. Cek Valid BST" << endl;
        cout << "7. Hitung Simpul Daun" << endl;
        cout << "8. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                buatNode();
                break;
            case 2: {
                cout << "Masukkan nilai parent: ";
                cin >> nilai;
                Pohon* parent = cariNode(root, nilai);
                if (!parent) {
                    cout << "Node parent tidak ditemukan!" << endl;
                    break;
                }
                cout << "Masukkan nilai node baru: ";
                cin >> nilai;
                baru = new Pohon{nilai, NULL, NULL, parent};
                parent->left = baru;
                cout << "Node berhasil ditambahkan sebagai child kiri" << endl;
                break;
            }
            case 3: {
                cout << "Masukkan nilai parent: ";
                cin >> nilai;
                Pohon* parent = cariNode(root, nilai);
                if (!parent) {
                    cout << "Node parent tidak ditemukan!" << endl;
                    break;
                }
                cout << "Masukkan nilai node baru: ";
                cin >> nilai;
                baru = new Pohon{nilai, NULL, NULL, parent};
                parent->right = baru;
                cout << "Node berhasil ditambahkan sebagai child kanan" << endl;
                break;
            }
            case 4: {
                cout << "Masukkan nilai node: ";
                cin >> nilai;
                Pohon* node = cariNode(root, nilai);
                tampilkanChild(node);
                break;
            }
            case 5: {
                cout << "Masukkan nilai node: ";
                cin >> nilai;
                Pohon* node = cariNode(root, nilai);
                if (node) {
                    cout << "Descendant dari node " << nilai << ": ";
                    tampilkanDescendant(node);
                    cout << endl;
                } else {
                    cout << "Node tidak ditemukan!" << endl;
                }
                break;
            }
            case 6: {
                if (is_valid_bst(root, INT_MIN, INT_MAX))
                    cout << "Pohon adalah BST valid" << endl;
                else
                    cout << "Pohon bukan BST valid" << endl;
                break;
            }
            case 7: {
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            }
        }
    } while (pilihan != 8);
}

int main() {
    init();
    menu();
    return 0;
}
