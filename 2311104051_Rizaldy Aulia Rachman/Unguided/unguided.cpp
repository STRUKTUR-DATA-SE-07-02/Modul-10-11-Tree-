#include <iostream>
using namespace std;

// Struktur data pohon biner
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root = NULL;

// Inisialisasi pohon
void init() {
    root = NULL;
}

// Membuat node baru
void buatNode(char data) {
    if (root == NULL) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "Node " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "Root sudah ada." << endl;
    }
}

// Menambahkan node ke kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (!node) {
        cout << "Node parent tidak ditemukan." << endl;
        return NULL;
    }
    if (node->left != NULL) {
        cout << "Node " << node->data << " sudah ada anak kiri." << endl;
        return NULL;
    }
    node->left = new Pohon{data, NULL, NULL, node};
    cout << "Node " << data << " berhasil ditambahkan ke kiri " << node->data << endl;
    return node->left;
}

// Menambahkan node ke kanan
Pohon* insertRight(char data, Pohon *node) {
    if (!node) {
        cout << "Node parent tidak ditemukan." << endl;
        return NULL;
    }
    if (node->right != NULL) {
        cout << "Node " << node->data << " sudah ada anak kanan." << endl;
        return NULL;
    }
    node->right = new Pohon{data, NULL, NULL, node};
    cout << "Node " << data << " berhasil ditambahkan ke kanan " << node->data << endl;
    return node->right;
}

// Mencari node berdasarkan data
Pohon* find(char data, Pohon *node) {
    if (!node) return NULL;
    if (node->data == data) return node;
    Pohon *leftResult = find(data, node->left);
    if (leftResult) return leftResult;
    return find(data, node->right);
}

// Menampilkan anak langsung
void tampilkanChild(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }
    cout << "Node " << node->data << " memiliki:" << endl;
    if (node->left) cout << "  Anak kiri: " << node->left->data << endl;
    if (node->right) cout << "  Anak kanan: " << node->right->data << endl;
    if (!node->left && !node->right) cout << "  Tidak ada anak langsung." << endl;
}

// Menampilkan semua keturunan
void tampilkanDescendant(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    tampilkanDescendant(node->left);
    tampilkanDescendant(node->right);
}

// Memeriksa apakah pohon adalah BST
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

// Menu utama
void menu() {
    char pilihan, data, parent_data;
    Pohon *parent_node;

    do {
        cout << "\nMenu:\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambah Anak Kiri\n";
        cout << "3. Tambah Anak Kanan\n";
        cout << "4. Tampilkan Anak\n";
        cout << "5. Tampilkan Descendant\n";
        cout << "6. Periksa BST\n";
        cout << "7. Hitung Simpul Daun\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
        case '1':
            cout << "Masukkan data root: ";
            cin >> data;
            buatNode(data);
            break;
        case '2':
            cout << "Masukkan data parent: ";
            cin >> parent_data;
            cout << "Masukkan data anak kiri: ";
            cin >> data;
            parent_node = find(parent_data, root);
            if (parent_node) insertLeft(data, parent_node);
            else cout << "Node parent tidak ditemukan.\n";
            break;
        case '3':
            cout << "Masukkan data parent: ";
            cin >> parent_data;
            cout << "Masukkan data anak kanan: ";
            cin >> data;
            parent_node = find(parent_data, root);
            if (parent_node) insertRight(data, parent_node);
            else cout << "Node parent tidak ditemukan.\n";
            break;
        case '4':
            cout << "Masukkan data node: ";
            cin >> data;
            parent_node = find(data, root);
            tampilkanChild(parent_node);
            break;
        case '5':
            cout << "Masukkan data node: ";
            cin >> data;
            parent_node = find(data, root);
            if (parent_node) {
                cout << "Descendant dari " << data << ": ";
                tampilkanDescendant(parent_node);
                cout << endl;
            } else cout << "Node tidak ditemukan.\n";
            break;
        case '6':
            cout << (is_valid_bst(root, 'A', 'Z') ? "Pohon adalah BST.\n" : "Pohon bukan BST.\n");
            break;
        case '7':
            cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
            break;
        case '0':
            cout << "Keluar.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != '0');
}

// Fungsi utama
int main() {
    init();
    menu();
    return 0;
}
