#include <iostream>
#include <queue>
#include <limits>
#include <climits> // Untuk nilai INT_MIN dan INT_MAX
using namespace std;

struct TreeNode {
    char value;
    TreeNode *left, *right, *parent;

    TreeNode(char value, TreeNode *left = NULL, TreeNode *right = NULL, TreeNode *parent = NULL)
        : value(value), left(left), right(right), parent(parent) {}
};

TreeNode *root;

void initialize() {
    root = NULL;
}

bool isTreeEmpty() {
    return root == NULL;
}

void createRootNode(char value) {
    if (isTreeEmpty()) {
        root = new TreeNode(value);
        cout << "Node " << value << " berhasil dibuat sebagai root." << endl;
    } else {
        cout << "Root sudah ada." << endl;
    }
}

TreeNode *insertLeftNode(char value, TreeNode *node) {
    if (!node) {
        cout << "Node parent tidak ditemukan." << endl;
        return NULL;
    }
    if (node->left != NULL) {
        cout << "Node " << node->value << " sudah memiliki anak kiri." << endl;
        return node->left;
    }
    TreeNode *newNode = new TreeNode(value, NULL, NULL, node);
    node->left = newNode;
    cout << "Node " << value << " berhasil ditambahkan sebagai anak kiri dari " << node->value << "." << endl;
    return newNode;
}

TreeNode *insertRightNode(char value, TreeNode *node) {
    if (!node) {
        cout << "Node parent tidak ditemukan." << endl;
        return NULL;
    }
    if (node->right != NULL) {
        cout << "Node " << node->value << " sudah memiliki anak kanan." << endl;
        return node->right;
    }
    TreeNode *newNode = new TreeNode(value, NULL, NULL, node);
    node->right = newNode;
    cout << "Node " << value << " berhasil ditambahkan sebagai anak kanan dari " << node->value << "." << endl;
    return newNode;
}

void preOrderTraversal(TreeNode *node) {
    if (!node) return;
    cout << node->value << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void inOrderTraversal(TreeNode *node) {
    if (!node) return;
    inOrderTraversal(node->left);
    cout << node->value << " ";
    inOrderTraversal(node->right);
}

void postOrderTraversal(TreeNode *node) {
    if (!node) return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->value << " ";
}

void findNode(char value, TreeNode *node, TreeNode *&result) {
    if (!node) return;
    if (node->value == value) {
        result = node;
        return;
    }
    findNode(value, node->left, result);
    findNode(value, node->right, result);
}

void displayChildren(TreeNode *node) {
    if (!node) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }
    cout << "Node " << node->value << " memiliki anak: ";
    if (node->left) cout << "Kiri: " << node->left->value << " ";
    if (node->right) cout << "Kanan: " << node->right->value << " ";
    if (!node->left && !node->right) cout << "tidak ada.";
    cout << endl;
}

void displayDescendants(TreeNode *node) {
    if (!node) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }
    cout << "Descendant dari node " << node->value << ": ";
    queue<TreeNode *> q;
    q.push(node);
    while (!q.empty()) {
        TreeNode *current = q.front();
        q.pop();
        if (current->left) {
            cout << current->left->value << " ";
            q.push(current->left);
        }
        if (current->right) {
            cout << current->right->value << " ";
            q.push(current->right);
        }
    }
    cout << endl;
}

bool is_valid_bst(TreeNode *node, int min_val, int max_val) {
    if (!node) return true;

    if (node->value <= min_val || node->value >= max_val) return false;

    return is_valid_bst(node->left, min_val, node->value) &&
           is_valid_bst(node->right, node->value, max_val);
}

int countLeafNodes(TreeNode *node) {
    if (!node) return 0;

    if (!node->left && !node->right) return 1;

    return countLeafNodes(node->left) + countLeafNodes(node->right);
}

int main() {
    initialize();
    int choice;
    char value, parentValue;
    TreeNode *parent = NULL;

    do {
        cout << "\n=== Menu Pohon Biner ===";
        cout << "\n1. Tambah Root";
        cout << "\n2. Tambah Anak Kiri";
        cout << "\n3. Tambah Anak Kanan";
        cout << "\n4. Tampilkan Pre-order Traversal";
        cout << "\n5. Tampilkan In-order Traversal";
        cout << "\n6. Tampilkan Post-order Traversal";
        cout << "\n7. Tampilkan Anak Node";
        cout << "\n8. Tampilkan Descendant Node";
        cout << "\n9. Periksa Apakah BST";
        cout << "\n10. Hitung Jumlah Simpul Daun";
        cout << "\n0. Keluar";
        cout << "\nPilihan Anda: ";
        cin >> choice;

        if (cin.fail()) { // Jika terjadi kesalahan input
            cin.clear();  // Bersihkan kesalahan pada cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Hapus sisa input
            cout << "Input tidak valid. Silakan masukkan angka.\n";
            continue; // Ulangi loop tanpa keluar
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer input setelah membaca

        switch (choice) {
            case 1:
                cout << "Masukkan data root: ";
                cin >> value;
                cin.ignore(); // Bersihkan buffer input
                createRootNode(value);
                break;
            case 2:
                cout << "Masukkan data parent: ";
                cin >> parentValue;
                cin.ignore();
                findNode(parentValue, root, parent);
                if (parent) {
                    cout << "Masukkan data anak kiri: ";
                    cin >> value;
                    cin.ignore();
                    insertLeftNode(value, parent);
                } else {
                    cout << "Parent tidak ditemukan." << endl;
                }
                break;
            case 3:
                cout << "Masukkan data parent: ";
                cin >> parentValue;
                cin.ignore();
                findNode(parentValue, root, parent);
                if (parent) {
                    cout << "Masukkan data anak kanan: ";
                    cin >> value;
                    cin.ignore();
                    insertRightNode(value, parent);
                } else {
                    cout << "Parent tidak ditemukan." << endl;
                }
                break;
            case 4:
                cout << "Pre-order Traversal: ";
                preOrderTraversal(root);
                cout << endl;
                break;
            case 5:
                cout << "In-order Traversal: ";
                inOrderTraversal(root);
                cout << endl;
                break;
            case 6:
                cout << "Post-order Traversal: ";
                postOrderTraversal(root);
                cout << endl;
                break;
            case 7:
                cout << "Masukkan data node: ";
                cin >> value;
                cin.ignore();
                findNode(value, root, parent);
                displayChildren(parent);
                break;
            case 8:
                cout << "Masukkan data node: ";
                cin >> value;
                cin.ignore();
                findNode(value, root, parent);
                displayDescendants(parent);
                break;
            case 9:
                cout << "Apakah pohon ini adalah BST? "
                     << (is_valid_bst(root, INT_MIN, INT_MAX) ? "Ya" : "Tidak") << endl;
                break;
            case 10:
                cout << "Jumlah simpul daun: " << countLeafNodes(root) << endl;
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

    } while (choice != 0);

    return 0;
}
