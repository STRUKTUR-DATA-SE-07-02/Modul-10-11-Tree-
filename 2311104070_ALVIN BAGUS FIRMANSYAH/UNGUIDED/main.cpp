#include <iostream>
#include <climits>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root = nullptr;

void init() {
    root = nullptr;
}

bool isEmpty() {
    return root == nullptr;
}

Pohon* buatNode(char data, Pohon* parent = nullptr) {
    Pohon* baru = new Pohon;
    baru->data = data;
    baru->left = baru->right = nullptr;
    baru->parent = parent;
    return baru;
}

void insertLeft(char data, Pohon* node) {
    if (node->left != nullptr) {
        cout << "Node " << node->data << " sudah memiliki child kiri!" << endl;
    } else {
        node->left = buatNode(data, node);
        cout << "Node " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
    }
}

void insertRight(char data, Pohon* node) {
    if (node->right != nullptr) {
        cout << "Node " << node->data << " sudah memiliki child kanan!" << endl;
    } else {
        node->right = buatNode(data, node);
        cout << "Node " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    }
}

void displayChild(Pohon* node) {
    if (node == nullptr) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }
    cout << "Node: " << node->data << endl;
    cout << "Left Child: " << (node->left ? node->left->data : '-') << endl;
    cout << "Right Child: " << (node->right ? node->right->data : '-') << endl;
}

void displayDescendants(Pohon* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    displayDescendants(node->left);
    displayDescendants(node->right);
}

bool is_valid_bst(Pohon* node, char min_val, char max_val) {
    if (node == nullptr) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

int cari_simpul_daun(Pohon* node) {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

void inOrder(Pohon* node) {
    if (node == nullptr) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

void menu() {
    int choice;
    char data, parentData;
    Pohon* parentNode;

    do {
        cout << "\n--- MENU BINARY TREE ---\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambah Anak Kiri\n";
        cout << "3. Tambah Anak Kanan\n";
        cout << "4. Tampilkan Child\n";
        cout << "5. Tampilkan Descendants\n";
        cout << "6. Periksa Valid BST\n";
        cout << "7. Hitung Simpul Daun\n";
        cout << "8. Traversal In-order\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!isEmpty()) {
                    cout << "Root sudah dibuat!" << endl;
                } else {
                    cout << "Masukkan data root: ";
                    cin >> data;
                    root = buatNode(data);
                    cout << "Root " << data << " berhasil dibuat." << endl;
                }
                break;

            case 2:
                if (isEmpty()) {
                    cout << "Pohon belum dibuat. Buat root terlebih dahulu!" << endl;
                } else {
                    cout << "Masukkan parent: ";
                    cin >> parentData;
                    cout << "Masukkan data anak kiri: ";
                    cin >> data;
                    parentNode = root;
                    insertLeft(data, parentNode);
                }
                break;

            case 3:
                if (isEmpty()) {
                    cout << "Pohon belum dibuat. Buat root terlebih dahulu!" << endl;
                } else {
                    cout << "Masukkan parent: ";
                    cin >> parentData;
                    cout << "Masukkan data anak kanan: ";
                    cin >> data;
                    parentNode = root;
                    insertRight(data, parentNode);
                }
                break;

            case 4:
                if (isEmpty()) {
                    cout << "Pohon kosong." << endl;
                } else {
                    cout << "Masukkan node untuk melihat child: ";
                    cin >> data;
                    displayChild(root);
                }
                break;

            case 5:
                if (isEmpty()) {
                    cout << "Pohon kosong." << endl;
                } else {
                    cout << "Masukkan node untuk melihat descendants: ";
                    cin >> data;
                    displayDescendants(root);
                    cout << endl;
                }
                break;

            case 6:
                cout << (is_valid_bst(root, CHAR_MIN, CHAR_MAX) ? "Pohon adalah BST" : "Pohon bukan BST") << endl;
                break;

            case 7:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;

            case 8:
                cout << "Traversal In-order: ";
                inOrder(root);
                cout << endl;
                break;

            case 0:
                cout << "Keluar dari program." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (choice != 0);
}

int main() {
    init();
    menu();
    return 0;
}
