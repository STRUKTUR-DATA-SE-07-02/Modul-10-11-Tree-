#include <iostream>
#include <queue> // Untuk traversal level-order (opsional)
using namespace std;

struct Pohon {
    char data;
    Pohon *kiri, *kanan, *parent;

    Pohon(char data, Pohon *kiri = NULL, Pohon *kanan = NULL, Pohon *parent = NULL)
        : data(data), kiri(kiri), kanan(kanan), parent(parent) {}
};

Pohon *root;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon(data, NULL, NULL, NULL);
        cout << "Node " << data << " berhasil dibuat sebagai root." << endl;
    } else {
        cout << "Root sudah ada." << endl;
    }
}

Pohon *insertLeft(char data, Pohon *node) {
    if (!node) {
        cout << "Node parent tidak ditemukan." << endl;
        return NULL;
    }
    if (node->kiri != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kiri." << endl;
        return node->kiri;
    }
    Pohon *baru = new Pohon(data, NULL, NULL, node);
    node->kiri = baru;
    cout << "Node " << data << " berhasil ditambahkan sebagai anak kiri dari " << node->data << "." << endl;
    return baru;
}

Pohon *insertRight(char data, Pohon *node) {
    if (!node) {
        cout << "Node parent tidak ditemukan." << endl;
        return NULL;
    }
    if (node->kanan != NULL) {
        cout << "Node " << node->data << " sudah memiliki anak kanan." << endl;
        return node->kanan;
    }
    Pohon *baru = new Pohon(data, NULL, NULL, node);
    node->kanan = baru;
    cout << "Node " << data << " berhasil ditambahkan sebagai anak kanan dari " << node->data << "." << endl;
    return baru;
}

void preOrder(Pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->kiri);
    preOrder(node->kanan);
}

void inOrder(Pohon *node) {
    if (!node) return;
    inOrder(node->kiri);
    cout << node->data << " ";
    inOrder(node->kanan);
}

void postOrder(Pohon *node) {
    if (!node) return;
    postOrder(node->kiri);
    postOrder(node->kanan);
    cout << node->data << " ";
}

void findNode(char data, Pohon *node, Pohon *&result) {
    if (!node) return;
    if (node->data == data) {
        result = node;
        return;
    }
    findNode(data, node->kiri, result);
    findNode(data, node->kanan, result);
}

void displayChildren(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }
    cout << "Node " << node->data << " memiliki anak: ";
    if (node->kiri) cout << "Kiri: " << node->kiri->data << " ";
    if (node->kanan) cout << "Kanan: " << node->kanan->data << " ";
    if (!node->kiri && !node->kanan) cout << "tidak ada.";
    cout << endl;
}

void displayDescendants(Pohon *node) {
    if (!node) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }
    cout << "Descendant dari node " << node->data << ": ";
    queue<Pohon *> q;
    q.push(node);
    while (!q.empty()) {
        Pohon *current = q.front();
        q.pop();
        if (current->kiri) {
            cout << current->kiri->data << " ";
            q.push(current->kiri);
        }
        if (current->kanan) {
            cout << current->kanan->data << " ";
            q.push(current->kanan);
        }
    }
    cout << endl;
}

// Fungsi memeriksa apakah pohon adalah BST
bool is_valid_bst(Pohon *node, int min_val, int max_val) {
    if (!node) return true;

    if (node->data <= min_val || node->data >= max_val) return false;

    return is_valid_bst(node->kiri, min_val, node->data) &&
           is_valid_bst(node->kanan, node->data, max_val);
}

// Fungsi menghitung jumlah simpul daun
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;

    if (!node->kiri && !node->kanan) return 1;

    return cari_simpul_daun(node->kiri) + cari_simpul_daun(node->kanan);
}

int main() {
    init();
    int choice;
    char data, parentData;
    Pohon *parent = NULL;

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

        switch (choice) {
            case 1:
                cout << "Masukkan data root: ";
                cin >> data;
                buatNode(data);
                break;
            case 2:
                cout << "Masukkan data parent: ";
                cin >> parentData;
                findNode(parentData, root, parent);
                if (parent) {
                    cout << "Masukkan data anak kiri: ";
                    cin >> data;
                    insertLeft(data, parent);
                } else {
                    cout << "Parent tidak ditemukan." << endl;
                }
                break;
            case 3:
                cout << "Masukkan data parent: ";
                cin >> parentData;
                findNode(parentData, root, parent);
                if (parent) {
                    cout << "Masukkan data anak kanan: ";
                    cin >> data;
                    insertRight(data, parent);
                } else {
                    cout << "Parent tidak ditemukan." << endl;
                }
                break;
            case 4:
                cout << "Pre-order Traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case 5:
                cout << "In-order Traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case 6:
                cout << "Post-order Traversal: ";
                postOrder(root);
                cout << endl;
                break;
            case 7:
                cout << "Masukkan data node: ";
                cin >> data;
                findNode(data, root, parent);
                displayChildren(parent);
                break;
            case 8:
                cout << "Masukkan data node: ";
                cin >> data;
                findNode(data, root, parent);
                displayDescendants(parent);
                break;
            case 9:
                cout << "Apakah pohon ini adalah BST? "
                     << (is_valid_bst(root, INT_MIN, INT_MAX) ? "Ya" : "Tidak") << endl;
                break;
            case 10:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 0);

    return 0;
}