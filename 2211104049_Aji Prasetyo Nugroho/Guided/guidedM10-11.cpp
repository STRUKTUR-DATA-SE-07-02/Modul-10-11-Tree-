#include <iostream>
using namespace std;

// Struktur data Pohon
struct Pohon {
    char data; // data dari node
    Pohon *left, *right; // pointer ke child kiri dan kanan
    Pohon *parent; // pointer ke parent
};

// Pointer ke root pohon dan node sementara untuk operasi insert
Pohon *root, *baru;

// Fungsi untuk inisialisasi pohon
void init() {
    root = NULL;
}

// Fungsi untuk mengecek apakah pohon kosong
bool isEmpty() {
    return root == NULL;
}

// Fungsi untuk membuat root pohon
void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL}; // Membuat root baru
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah dibuat." << endl;
    }
}

// Fungsi untuk menambahkan child kiri pada node tertentu
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) { // Jika node sudah punya child kiri
        cout << "\nNode " << node->data << " sudah ada child kiri!" << endl;
        return NULL;
    }

    // Membuat node baru untuk child kiri
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru; // Menambahkan child kiri
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
    return baru;
}

// Fungsi untuk menambahkan child kanan pada node tertentu
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) { // Jika node sudah punya child kanan
        cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
        return NULL;
    }

    // Membuat node baru untuk child kanan
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru; // Menambahkan child kanan
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    return baru;
}

// Fungsi untuk mencari node berdasarkan data
void find(char data, Pohon *node) {
    if (!node) return; // Jika node NULL, hentikan pencarian

    // Jika data ditemukan
    if (node->data == data) {
        cout << "\nNode ditemukan: " << data << endl;
    }

    // Rekursif untuk mencari di child kiri dan kanan
    find(data, node->left);
    find(data, node->right);
}

// Traversal pohon secara Pre-order (Root, Left, Right)
void preOrder(Pohon *node) {
    if (!node) return; // Jika node NULL, hentikan traversal
    cout << node->data << " "; // Cetak data node
    preOrder(node->left); // Traversal child kiri
    preOrder(node->right); // Traversal child kanan
}

// Traversal pohon secara In-order (Left, Root, Right)
void inOrder(Pohon *node) {
    if (!node) return; // Jika node NULL, hentikan traversal
    inOrder(node->left); // Traversal child kiri
    cout << node->data << " "; // Cetak data node
    inOrder(node->right); // Traversal child kanan
}

// Traversal pohon secara Post-order (Left, Right, Root)
void postOrder(Pohon *node) {
    if (!node) return; // Jika node NULL, hentikan traversal
    postOrder(node->left); // Traversal child kiri
    postOrder(node->right); // Traversal child kanan
    cout << node->data << " "; // Cetak data node
}

// Fungsi untuk menghapus node tertentu dalam pohon
Pohon* deleteNode(Pohon *node, char data) {
    if (!node) return NULL; // Jika node NULL, kembalikan NULL

    // Jika data lebih kecil dari data node, cari di subtree kiri
    if (data < node->data) {
        node->left = deleteNode(node->left, data);
    }
    // Jika data lebih besar dari data node, cari di subtree kanan
    else if (data > node->data) {
        node->right = deleteNode(node->right, data);
    }
    // Jika data sama dengan data node, hapus node tersebut
    else {
        if (!node->left) { // Jika tidak ada child kiri
            Pohon *temp = node->right; // Ambil child kanan
            delete node; // Hapus node
            return temp;
        } else if (!node->right) { // Jika tidak ada child kanan
            Pohon *temp = node->left; // Ambil child kiri
            delete node; // Hapus node
            return temp;
        }

        // Jika node memiliki dua child, cari successor
        Pohon *successor = node->right;
        while (successor->left) successor = successor->left; // Cari node paling kiri di subtree kanan
        node->data = successor->data; // Ganti data node dengan successor
        node->right = deleteNode(node->right, successor->data); // Hapus successor
    }
    return node;
}

// Fungsi untuk mencari node paling kiri dalam subtree
Pohon* mostLeft(Pohon *node) {
    if (!node) return NULL; // Jika node NULL
    while (node->left) node = node->left; // Cari node paling kiri
    return node;
}

// Fungsi untuk mencari node paling kanan dalam subtree
Pohon* mostRight(Pohon *node) {
    if (!node) return NULL; // Jika node NULL
    while (node->right) node = node->right; // Cari node paling kanan
    return node;
}

int main() {
    init(); // Inisialisasi pohon

    // Membuat root dan menambah node pada pohon
    buatNode('F');
    insertLeft('B', root);
    insertRight('G', root);
    insertLeft('A', root->left);
    insertRight('D', root->left);
    insertLeft('C', root->left->right);
    insertRight('E', root->left->right);

    // Traversal pohon
    cout << "\nPre-order Traversal: ";
    preOrder(root);
    cout << "\nIn-order Traversal: ";
    inOrder(root);
    cout << "\nPost-order Traversal: ";
    postOrder(root);

    // Menghapus node D dan melakukan traversal kembali
    cout << "\nMenghapus node D.";
    root = deleteNode(root, 'D');
    cout << "\nIn-order Traversal setelah penghapusan: ";
    inOrder(root);

    return 0;
}