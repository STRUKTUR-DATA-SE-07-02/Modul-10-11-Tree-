#include <iostream>
#include <limits>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

Pohon* buatNode(char data, Pohon* parent = NULL) {
    return new Pohon{data, NULL, NULL, parent};
}

Pohon* insertLeft(char data, Pohon* node) {
    if (!node) return NULL;
    if (node->left) {
        cout << "Child kiri sudah ada!\n";
        return NULL;
    }
    node->left = buatNode(data, node);
    return node->left;
}

Pohon* insertRight(char data, Pohon* node) {
    if (!node) return NULL;
    if (node->right) {
        cout << "Child kanan sudah ada!\n";
        return NULL;
    }
    node->right = buatNode(data, node);
    return node->right;
}

void preOrder(Pohon* node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Pohon* node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

void postOrder(Pohon* node) {
    if (!node) return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}

void tampilkanChild(Pohon* node) {
    if (!node) return;
    cout << "Node " << node->data << " memiliki:\n";
    if (node->left) cout << "- Child kiri: " << node->left->data << endl;
    else cout << "- Tidak ada child kiri.\n";
    if (node->right) cout << "- Child kanan: " << node->right->data << endl;
    else cout << "- Tidak ada child kanan.\n";
}

void tampilkanDescendant(Pohon* node) {
    if (!node) return;
    cout << "Descendant dari " << node->data << ": ";
    preOrder(node);
    cout << endl;
}

bool is_valid_bst(Pohon* node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

int cari_simpul_daun(Pohon* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

void menu() {
    int pilihan;
    char data, parent;
    Pohon* currentNode = NULL;

    do {
        cout << "\n=== MENU POHON ===\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambah Child Kiri\n";
        cout << "3. Tambah Child Kanan\n";
        cout << "4. Tampilkan Child\n";
        cout << "5. Tampilkan Descendant\n";
        cout << "6. Traversal Pre-order\n";
        cout << "7. Traversal In-order\n";
        cout << "8. Traversal Post-order\n";
        cout << "9. Cek Valid BST\n";
        cout << "10. Hitung Jumlah Simpul Daun\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                if (!root) {
                    cout << "Masukkan data root: ";
                    cin >> data;
                    root = buatNode(data);
                    cout << "Root berhasil dibuat.\n";
                } else {
                    cout << "Root sudah ada.\n";
                }
                break;
            case 2:
                cout << "Masukkan parent node: ";
                cin >> parent;
                cout << "Masukkan data: ";
                cin >> data;
                currentNode = insertLeft(data, root);
                if (currentNode) cout << "Child kiri berhasil ditambahkan.\n";
                break;
            case 3:
                cout << "Masukkan parent node: ";
                cin >> parent;
                cout << "Masukkan data: ";
                cin >> data;
                currentNode = insertRight(data, root);
                if (currentNode) cout << "Child kanan berhasil ditambahkan.\n";
                break;
            case 4:
                cout << "Masukkan node: ";
                cin >> data;
                tampilkanChild(root);
                break;
            case 5:
                cout << "Masukkan node: ";
                cin >> data;
                tampilkanDescendant(root);
                break;
            case 6:
                cout << "Pre-order Traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case 7:
                cout << "In-order Traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case 8:
                cout << "Post-order Traversal: ";
                postOrder(root);
                cout << endl;
                break;
            case 9:
                if (is_valid_bst(root, numeric_limits<char>::min(), numeric_limits<char>::max())) {
                    cout << "Pohon adalah Binary Search Tree.\n";
                } else {
                    cout << "Pohon bukan Binary Search Tree.\n";
                }
                break;
            case 10:
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
    init();
    menu();
    return 0;
}
