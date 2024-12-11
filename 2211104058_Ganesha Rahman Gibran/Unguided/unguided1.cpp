#include <iostream>
#include <limits>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root = NULL;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

Pohon* buatNode(char data) {
    return new Pohon{data, NULL, NULL, NULL};
}

void insertNode(char data, Pohon* parent, bool isLeft) {
    if (isLeft) {
        if (parent->left == NULL) {
            parent->left = buatNode(data);
            parent->left->parent = parent;
            cout << "Node " << data << " berhasil ditambahkan ke anak kiri dari " << parent->data << endl;
        } else {
            cout << "Anak kiri dari " << parent->data << " sudah ada!" << endl;
        }
    } else {
        if (parent->right == NULL) {
            parent->right = buatNode(data);
            parent->right->parent = parent;
            cout << "Node " << data << " berhasil ditambahkan ke anak kanan dari " << parent->data << endl;
        } else {
            cout << "Anak kanan dari " << parent->data << " sudah ada!" << endl;
        }
    }
}

void displayChild(Pohon* node) {
    if (!node) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }
    cout << "Node: " << node->data << endl;
    cout << "Anak kiri: " << (node->left ? node->left->data : '-') << endl;
    cout << "Anak kanan: " << (node->right ? node->right->data : '-') << endl;
}

void displayDescendants(Pohon* node) {
    if (!node) return;
    if (node->left) cout << node->left->data << " ";
    if (node->right) cout << node->right->data << " ";
    displayDescendants(node->left);
    displayDescendants(node->right);
}

bool is_valid_bst(Pohon* node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) && is_valid_bst(node->right, node->data, max_val);
}

int cari_simpul_daun(Pohon* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

void menu() {
    int pilihan;
    char data, parentData;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambahkan Node\n";
        cout << "3. Tampilkan Child\n";
        cout << "4. Tampilkan Descendant\n";
        cout << "5. Periksa BST Valid\n";
        cout << "6. Hitung Simpul Daun\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                if (isEmpty()) {
                    cout << "Masukkan data root: ";
                    cin >> data;
                    root = buatNode(data);
                    cout << "Root " << data << " berhasil dibuat.\n";
                } else {
                    cout << "Root sudah ada.\n";
                }
                break;
            case 2:
                if (isEmpty()) {
                    cout << "Buat root terlebih dahulu.\n";
                } else {
                    cout << "Masukkan data parent: ";
                    cin >> parentData;
                    cout << "Masukkan data node baru: ";
                    cin >> data;
                    cout << "Tambahkan ke (1) kiri atau (2) kanan? ";
                    int pos;
                    cin >> pos;

                    Pohon* current = root;
                    // Pencarian parent
                    while (current && current->data != parentData) {
                        current = (current->left && parentData < current->data) ? current->left : current->right;
                    }
                    if (!current) {
                        cout << "Parent tidak ditemukan.\n";
                    } else {
                        insertNode(data, current, pos == 1);
                    }
                }
                break;
            case 3:
                if (isEmpty()) {
                    cout << "Pohon kosong.\n";
                } else {
                    cout << "Masukkan data node: ";
                    cin >> data;
                    Pohon* current = root;
                    // Pencarian node
                    while (current && current->data != data) {
                        current = (current->left && data < current->data) ? current->left : current->right;
                    }
                    displayChild(current);
                }
                break;
            case 4:
                if (isEmpty()) {
                    cout << "Pohon kosong.\n";
                } else {
                    cout << "Masukkan data node: ";
                    cin >> data;
                    Pohon* current = root;
                    // Pencarian node
                    while (current && current->data != data) {
                        current = (current->left && data < current->data) ? current->left : current->right;
                    }
                    if (!current) {
                        cout << "Node tidak ditemukan.\n";
                    } else {
                        cout << "Descendant dari " << data << ": ";
                        displayDescendants(current);
                        cout << endl;
                    }
                }
                break;
            case 5:
                if (is_valid_bst(root, numeric_limits<char>::min(), numeric_limits<char>::max())) {
                    cout << "Pohon adalah Binary Search Tree yang valid.\n";
                } else {
                    cout << "Pohon bukan Binary Search Tree yang valid.\n";
                }
                break;
            case 6:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

int main() {
    menu();
    return 0;
}
