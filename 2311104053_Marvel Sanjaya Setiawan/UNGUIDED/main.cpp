#include <iostream>
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right;
    Pohon *parent;
};

// Variabel global untuk menyimpan root dan node baru
Pohon *root, *baru;

// Inisialisasi pohon agar kosong
void init() {
    root = NULL;
}

// Mengecek apakah pohon kosong
bool isEmpty() {
    return root == NULL;
}

// Membuat node baru sebagai root pohon
void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah dibuat." << endl;
    }
}

// Menambahkan node baru sebagai anak kiri dari node tertentu
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

// Menambahkan node baru sebagai anak kanan dari node tertentu
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

// Mengubah data di dalam sebuah node
void update(char data, Pohon *node) {
    if (!node) {
        cout << "\nNode yang ingin diubah tidak ditemukan!" << endl;
        return;
    }
    char temp = node->data;
    node->data = data;
    cout << "\nNode " << temp << " berhasil diubah menjadi " << data << endl;
}

// Mencari node dengan data tertentu
Pohon* find(char data, Pohon *node) {
    if (!node) return NULL;

    if (node->data == data) {
        cout << "\nNode ditemukan: " << data << endl;
        return node;
    }
    Pohon* foundNode = find(data, node->left);
    if (foundNode == NULL) foundNode = find(data, node->right);
    return foundNode;
}

// Traversal Pre-order (Node -> Kiri -> Kanan)
void preOrder(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

// Traversal In-order (Kiri -> Node -> Kanan)
void inOrder(Pohon *node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

// Traversal Post-order (Kiri -> Kanan -> Node)
void postOrder(Pohon *node) {
    if (!node) return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}

// Menampilkan child dan descendant dari node tertentu
void showChildDescendant(Pohon *node) {
    if (!node) return;
    cout << "Child dari node " << node->data << ": ";
    if (node->left) cout << node->left->data << " ";
    if (node->right) cout << node->right->data << " ";
    cout << endl << "Descendant dari node " << node->data << ": ";
    preOrder(node);
    cout << endl;
}

// Fungsi untuk memeriksa apakah pohon memenuhi properti Binary Search Tree (BST)
bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) && is_valid_bst(node->right, node->data, max_val);
}

// Fungsi rekursif untuk menghitung jumlah simpul daun
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Fungsi utama dengan menu
int main() {
    init();
    char pilihan;
    char data, parentData;
    Pohon *parentNode;

    do {
        cout << "\nMenu Program Binary Tree:";
        cout << "\n1. Buat Node Root";
        cout << "\n2. Tambah Anak Kiri";
        cout << "\n3. Tambah Anak Kanan";
        cout << "\n4. Tampilkan Child";
        cout << "\n5. Tampilkan Descendant";
        cout << "\n6. Cek Valid BST";
        cout << "\n7. Hitung Jumlah Simpul Daun";
        cout << "\n8. Keluar";
        cout << "\nPilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                cout << "Masukkan data untuk node root: ";
                cin >> data;
                buatNode(data);
                break;
            case '2':
                cout << "Masukkan data untuk node baru: ";
                cin >> data;
                cout << "Masukkan data node induk: ";
                cin >> parentData;
                parentNode = find(parentData, root);
                if (parentNode) insertLeft(data, parentNode);
                break;
            case '3':
                cout << "Masukkan data untuk node baru: ";
                cin >> data;
                cout << "Masukkan data node induk: ";
                cin >> parentData;
                parentNode = find(parentData, root);
                if (parentNode) insertRight(data, parentNode);
                break;
            case '4':
                cout << "Masukkan data node: ";
                cin >> data;
                parentNode = find(data, root);
                if (parentNode) {
                    showChildDescendant(parentNode);
                } else {
                    cout << "Node tidak ditemukan." << endl;
                }
                break;
            case '5':
                cout << "Masukkan data node: ";
                cin >> data;
                parentNode = find(data, root);
                if (parentNode) {
                    showChildDescendant(parentNode);
                } else {
                    cout << "Node tidak ditemukan." << endl;
                }
                break;
            case '6':
                if (is_valid_bst(root, '0', 'z')) {
                    cout << "Pohon adalah Binary Search Tree yang valid." << endl;
                } else {
                    cout << "Pohon bukan Binary Search Tree yang valid." << endl;
                }
                break;
            case '7':
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            case '8':
                cout << "Keluar." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != '8');

    return 0;
}
