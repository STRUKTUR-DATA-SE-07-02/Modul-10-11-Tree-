#include <iostream>
#include <queue>
using namespace std;

// Struktur data tree seperti pada guided
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

// Variabel global
Pohon *root = NULL, *baru = NULL;

// Inisialisasi pohon
void init() {
    root = NULL;
}

// Membuat node baru sebagai root
void buatNode(char data) {
    if (!root) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "Node " << data << " berhasil dibuat sebagai root.\n";
    } else {
        cout << "Root sudah ada.\n";
    }
}

// Menambahkan node ke anak kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "Node " << node->data << " sudah memiliki child kiri!\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    return baru;
}

// Menambahkan node ke anak kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "Node " << node->data << " sudah memiliki child kanan!\n";
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    return baru;
}

// Fungsi untuk mencari node
Pohon* findNode(char data, Pohon *node) {
    if (!node) return NULL;
    if (node->data == data) return node;
    Pohon *leftResult = findNode(data, node->left);
    if (leftResult) return leftResult;
    return findNode(data, node->right);
}

// Menampilkan child dari node tertentu
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan.\n";
        return;
    }
    cout << "Node " << node->data << ":\n";
    if (node->left) cout << " - Child kiri: " << node->left->data << endl;
    else cout << " - Tidak ada child kiri.\n";
    if (node->right) cout << " - Child kanan: " << node->right->data << endl;
    else cout << " - Tidak ada child kanan.\n";
}

// Menampilkan descendant dari node tertentu
void tampilkanDescendant(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan.\n";
        return;
    }
    queue<Pohon*> q;
    q.push(node);
    cout << "Descendant dari node " << node->data << ": ";
    while (!q.empty()) {
        Pohon *current = q.front();
        q.pop();
        if (current != node) cout << current->data << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << endl;
}

// Fungsi rekursif untuk memeriksa apakah tree valid BST
bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// Fungsi rekursif untuk menghitung jumlah simpul daun
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Fungsi menu utama
void menu() {
    char pilihan, data, parent;
    while (true) {
        cout << "\n=== Menu Binary Tree ===\n";
        cout << "1. Tambah Root\n2. Tambah Child\n3. Tampilkan Child\n4. Tampilkan Descendant\n";
        cout << "5. Periksa Validitas BST\n6. Hitung Simpul Daun\n7. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                cout << "Masukkan data root: ";
                cin >> data;
                buatNode(data);
                break;
            case '2':
                cout << "Masukkan data parent: ";
                cin >> parent;
                cout << "Masukkan data child: ";
                cin >> data;
                cout << "Kiri (L) atau Kanan (R)? ";
                char arah;
                cin >> arah;
                if (arah == 'L' || arah == 'l') {
                    insertLeft(data, findNode(parent, root));
                } else {
                    insertRight(data, findNode(parent, root));
                }
                break;
            case '3':
                cout << "Masukkan data node: ";
                cin >> data;
                tampilkanChild(findNode(data, root));
                break;
            case '4':
                cout << "Masukkan data node: ";
                cin >> data;
                tampilkanDescendant(findNode(data, root));
                break;
            case '5':
                if (is_valid_bst(root, CHAR_MIN, CHAR_MAX))
                    cout << "Tree adalah Binary Search Tree yang valid.\n";
                else
                    cout << "Tree bukan Binary Search Tree yang valid.\n";
                break;
            case '6':
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            case '7':
                return;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
}

int main() {
    init();
    menu();
    return 0;
}
