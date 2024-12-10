#include <iostream>
#include <climits> 
using namespace std;

/// Struktur pohon biner
struct Pohon {
    int data;         // Data node
    Pohon *left;      // Anak kiri
    Pohon *right;     // Anak kanan
};

// Deklarasi root pohon
Pohon *root = NULL;

// Fungsi untuk membuat node baru
Pohon* buatNode(int data) {
    Pohon* nodeBaru = new Pohon();
    nodeBaru->data = data;
    nodeBaru->left = NULL;
    nodeBaru->right = NULL;
    return nodeBaru;
}

// Menambahkan node baru ke kiri
Pohon* insertLeft(Pohon *node, int data) {
    if (!node) return NULL; // Jika node kosong, hentikan
    if (!node->left) {
        node->left = buatNode(data); // Tambahkan anak kiri
        cout << "Node " << data << " berhasil ditambahkan ke kiri " << node->data << endl;
    }
    return node->left;
}

// Menambahkan node baru ke kanan
Pohon* insertRight(Pohon *node, int data) {
    if (!node) return NULL; // Jika node kosong, hentikan
    if (!node->right) {
        node->right = buatNode(data); // Tambahkan anak kanan
        cout << "Node " << data << " berhasil ditambahkan ke kanan " << node->data << endl;
    }
    return node->right;
}

// Fungsi rekursif untuk memeriksa apakah pohon adalah BST
bool is_valid_bst(Pohon *node, int min_val, int max_val) {
    if (!node) return true; // Pohon kosong dianggap valid
    // Jika data node melanggar batas, kembalikan false
    if (node->data <= min_val || node->data >= max_val) return false;
    // Periksa anak kiri dan kanan dengan batas nilai diperbarui
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// Fungsi utama
int main() {
    // Membuat pohon valid sebagai BST
    root = buatNode(10);
    Pohon *node5 = insertLeft(root, 5);
    Pohon *node20 = insertRight(root, 20);
    insertLeft(node5, 1);
    insertRight(node5, 8);
    insertLeft(node20, 15);
    insertRight(node20, 25);

    // Uji pohon valid sebagai BST
    cout << "\nApakah pohon valid sebagai BST? "
         << (is_valid_bst(root, INT_MIN, INT_MAX) ? "Ya" : "Tidak") << endl;

    // Membuat pohon tidak valid sebagai BST
    root = buatNode(10);
    insertLeft(root, 20); // Nilai salah untuk BST
    insertRight(root, 5);

    // Uji pohon tidak valid sebagai BST
    cout << "\nApakah pohon valid sebagai BST? "
         << (is_valid_bst(root, INT_MIN, INT_MAX) ? "Ya" : "Tidak") << endl;

    return 0;
}