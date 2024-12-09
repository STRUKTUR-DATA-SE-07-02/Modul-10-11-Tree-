#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

Node* createRoot(int value) {
    return new Node(value);
}

void addLeft(Node* parent, int value) {
    if (parent->left == nullptr) {
        parent->left = new Node(value);
        cout << "Node " << value << " berhasil ditambahkan sebagai anak kiri." << endl;
    } else {
        cout << "Anak kiri sudah ada!" << endl;
    }
}

void addRight(Node* parent, int value) {
    if (parent->right == nullptr) {
        parent->right = new Node(value);
        cout << "Node " << value << " berhasil ditambahkan sebagai anak kanan." << endl;
    } else {
        cout << "Anak kanan sudah ada!" << endl;
    }
}

void displayChildren(Node* node) {
    if (node == nullptr) {
        cout << "Node tidak ada." << endl;
        return;
    }
    cout << "Child dari node " << node->data << ": ";
    if (node->left) cout << "Kiri: " << node->left->data << " ";
    if (node->right) cout << "Kanan: " << node->right->data << " ";
    if (!node->left && !node->right) cout << "Tidak ada child.";
    cout << endl;
}

void displayDescendants(Node* node) {
    if (node == nullptr) {
        cout << "Node tidak ada." << endl;
        return;
    }
    queue<Node*> q;
    q.push(node);
    cout << "Descendant dari node " << node->data << ": ";
    bool hasDescendant = false;
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        if (current->left) {
            cout << current->left->data << " ";
            q.push(current->left);
            hasDescendant = true;
        }
        if (current->right) {
            cout << current->right->data << " ";
            q.push(current->right);
            hasDescendant = true;
        }
    }
    if (!hasDescendant) cout << "Tidak ada descendant.";
    cout << endl;
}

bool isBST(Node* node, int min = INT_MIN, int max = INT_MAX) {
    if (node == nullptr) return true;
    if (node->data <= min || node->data >= max) return false;
    return isBST(node->left, min, node->data) && isBST(node->right, node->data, max);
}

int countLeafNodes(Node* node) {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return 1;
    return countLeafNodes(node->left) + countLeafNodes(node->right);
}

void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    Node* root = nullptr;
    int choice, value;

    do {
        cout << "\nMenu Program Binary Tree:\n";
        cout << "1. Buat Node Root\n";
        cout << "2. Tambah Anak Kiri\n";
        cout << "3. Tambah Anak Kanan\n";
        cout << "4. Tampilkan Child\n";
        cout << "5. Tampilkan Descendant\n";
        cout << "6. Cek Valid BST\n";
        cout << "7. Hitung Jumlah Simpul Daun\n";
        cout << "8. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (root != nullptr) {
                    cout << "Root sudah dibuat!" << endl;
                } else {
                    cout << "Masukkan data untuk node root: ";
                    cin >> value;
 root = createRoot(value);
                    cout << "Node " << value << " berhasil dibuat menjadi root." << endl;
                }
                break;

            case 2:
                if (root == nullptr) {
                    cout << "Buat root terlebih dahulu!" << endl;
                } else {
                    cout << "Masukkan data untuk node baru: ";
                    cin >> value;
                    addLeft(root, value);
                }
                break;

            case 3:
                if (root == nullptr) {
                    cout << "Buat root terlebih dahulu!" << endl;
                } else {
                    cout << "Masukkan data untuk node baru: ";
                    cin >> value;
                    addRight(root, value);
                }
                break;

            case 4:
                if (root == nullptr) {
                    cout << "Buat root terlebih dahulu!" << endl;
                } else {
                    displayChildren(root);
                }
                break;

            case 5:
                if (root == nullptr) {
                    cout << "Buat root terlebih dahulu!" << endl;
                } else {
                    displayDescendants(root);
                }
                break;

            case 6:
                if (isBST(root)) {
                    cout << "Pohon adalah Binary Search Tree yang valid." << endl;
                } else {
                    cout << "Pohon bukan Binary Search Tree yang valid." << endl;
                }
                break;

            case 7:
                cout << "Jumlah simpul daun: " << countLeafNodes(root) << endl;
                break;

            case 8:
                cout << "Keluar dari program." << endl;
                deleteTree(root); 
                break;

            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}