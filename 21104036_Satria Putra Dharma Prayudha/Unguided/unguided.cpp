#include <iostream>
#include <limits>
using namespace std;

// Struktur data pohon biner untuk menyimpan data dan pointer ke anak kiri, kanan, dan induk
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

// Variabel global untuk menyimpan root (akar) pohon dan node baru
Pohon *root, *baru;

// Inisialisasi pohon agar kosong
void init() {
    root = NULL; // Mengatur root sebagai NULL (pohon kosong)
}

// Mengecek apakah pohon kosong
bool isEmpty() {
    return root == NULL; // Mengembalikan true jika root adalah NULL
}

// Membuat node baru sebagai root pohon
void buatNode(char data) {
    if (isEmpty()) { // Jika pohon kosong
        root = new Pohon{data, NULL, NULL, NULL}; // Membuat node baru sebagai root
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah dibuat." << endl; // Root sudah ada, tidak membuat node baru
    }
}

// Menambahkan node baru sebagai anak kiri dari node tertentu
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) { // Jika anak kiri sudah ada
        cout << "\nNode " << node->data << " sudah ada child kiri!" << endl;
        return NULL; // Tidak menambahkan node baru
    }
    // Membuat node baru dan menghubungkannya ke node sebagai anak kiri
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
    return baru; // Mengembalikan pointer ke node baru
}

// Menambahkan node baru sebagai anak kanan dari node tertentu
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) { // Jika anak kanan sudah ada
        cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
        return NULL; // Tidak menambahkan node baru
    }
    // Membuat node baru dan menghubungkannya ke node sebagai anak kanan
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    return baru; // Mengembalikan pointer ke node baru
}

// Mengubah data di dalam sebuah node
void update(char data, Pohon *node) {
    if (!node) { // Jika node tidak ditemukan
        cout << "\nNode yang ingin diubah tidak ditemukan!" << endl;
        return;
    }
    char temp = node->data; // Menyimpan data lama
    node->data = data;      // Mengubah data dengan nilai baru
    cout << "\nNode " << temp << " berhasil diubah menjadi " << data << endl;
}

// Mencari node dengan data tertentu
Pohon* find(char data, Pohon *node) {
    if (!node) return NULL; // Jika node tidak ada, hentikan pencarian

    if (node->data == data) { // Jika data ditemukan
        return node;
    }
    // Melakukan pencarian secara rekursif ke anak kiri dan kanan
    Pohon* foundNode = find(data, node->left);
    if (foundNode) return foundNode;
    return find(data, node->right);
}

// Traversal Pre-order (Node -> Kiri -> Kanan)
void preOrder(Pohon *node) {
    if (!node) return; // Jika node kosong, hentikan traversal
    cout << node->data << " "; // Cetak data node saat ini
    preOrder(node->left);      // Traversal ke anak kiri
    preOrder(node->right);     // Traversal ke anak kanan
}

// Traversal In-order (Kiri -> Node -> Kanan)
void inOrder(Pohon *node) {
    if (!node) return; // Jika node kosong, hentikan traversal
    inOrder(node->left);  // Traversal ke anak kiri
    cout << node->data << " "; // Cetak data node saat ini
    inOrder(node->right); // Traversal ke anak kanan
}

// Traversal Post-order (Kiri -> Kanan -> Node)
void postOrder(Pohon *node) {
    if (!node) return; // Jika node kosong, hentikan traversal
    postOrder(node->left);  // Traversal ke anak kiri
    postOrder(node->right); // Traversal ke anak kanan
    cout << node->data << " "; // Cetak data node saat ini
}

// Menghapus node dengan data tertentu
Pohon* deleteNode(Pohon *node, char data) {
    if (!node) return NULL; // Jika node kosong, hentikan

    // Rekursif mencari node yang akan dihapus
    if (data < node->data) {
        node->left = deleteNode(node->left, data); // Cari di anak kiri
    } else if (data > node->data) {
        node->right = deleteNode(node->right, data); // Cari di anak kanan
    } else {
        // Jika node ditemukan
        if (!node->left) { // Jika tidak ada anak kiri
            Pohon *temp = node->right; // Anak kanan menggantikan posisi node
            delete node;
            return temp;
        } else if (!node->right) { // Jika tidak ada anak kanan
            Pohon *temp = node->left; // Anak kiri menggantikan posisi node
            delete node;
            return temp;
        }

        // Jika node memiliki dua anak, cari node pengganti (successor)
        Pohon *successor = node->right;
        while (successor->left) successor = successor->left; // Cari node terkecil di anak kanan
        node->data = successor->data; // Gantikan data dengan successor
        node->right = deleteNode(node->right, successor->data); // Hapus successor
    }
    return node;
}

// Menemukan node paling kiri
Pohon* mostLeft(Pohon *node) {
    if (!node) return NULL; // Jika node kosong, hentikan
    while (node->left) node = node->left; // Iterasi ke anak kiri hingga mentok
    return node;
}

// Menemukan node paling kanan
Pohon* mostRight(Pohon *node) {
    if (!node) return NULL; // Jika node kosong, hentikan
    while (node->right) node = node->right; // Iterasi ke anak kanan hingga mentok
    return node;
}

// Menampilkan child dan descendant dari node tertentu
void displayChildren(Pohon *node) {
    if (!node) return;
    cout << "\nNode " << node->data << " memiliki child: ";
    if (node->left) cout << "Kiri: " << node->left->data << " ";
    if (node->right) cout << "Kanan: " << node->right->data << " ";
    cout << "\nDescendant dari node " << node->data << ": ";
    preOrder(node);
    cout << endl;
}

// Memeriksa apakah pohon memenuhi properti Binary Search Tree
bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) && is_valid_bst(node->right, node->data, max_val);
}

// Menghitung jumlah simpul daun dalam Binary Tree
int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Fungsi untuk menampilkan menu
void menu() {
    int pilihan, subPilihan;
    char data, parentData;
    Pohon *parentNode;

    do {
        cout << "\nMenu:\n";
        cout << "1. Buat Node Root\n";
        cout << "2. Tambah Node\n";
        cout << "3. Update Node\n";
        cout << "4. Cari Node\n";
        cout << "5. Tampilkan Child dan Descendant\n";
        cout << "6. Traversal Pre-order\n";
        cout << "7. Traversal In-order\n";
        cout << "8. Traversal Post-order\n";
        cout << "9. Cek Validitas BST\n";
        cout << "10. Hitung Simpul Daun\n";
        cout << "11. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan data root: ";
                cin >> data;
                buatNode(data);
                break;
            case 2:
                cout << "Masukkan data node: ";
                cin >> data;
                cout << "Masukkan data parent: ";
                cin >> parentData;
                parentNode = find(parentData, root);
                if (parentNode) {
                    cout << "Pilih posisi (1: Kiri, 2: Kanan): ";
                    cin >> subPilihan;
                    if (subPilihan == 1) {
                        insertLeft(data, parentNode);
                    } else if (subPilihan == 2) {
                        insertRight(data, parentNode);
                    } else {
                        cout << "Pilihan tidak valid.\n";
                    }
                } else {
                    cout << "Parent tidak ditemukan.\n";
                }
                break;
            case 3:
                cout << "Masukkan data node yang ingin diupdate: ";
                cin >> parentData;
                parentNode = find(parentData, root);
                if (parentNode) {
                    cout << "Pilih aksi (1: Ubah, 2: Hapus): ";
                    cin >> subPilihan;
                    if (subPilihan == 1) {
                        cout << "Masukkan data baru: ";
                        cin >> data;
                        update(data, parentNode);
                    } else if (subPilihan == 2) {
                        root = deleteNode(root, parentData);
                    } else {
                        cout << "Pilihan tidak valid.\n";
                    }
                } else {
                    cout << "Node tidak ditemukan.\n";
                }
                break;
            case 4:
                cout << "Masukkan data node yang ingin dicari: ";
                cin >> data;
                parentNode = find(data, root);
                if (parentNode) {
                    cout << "Node ditemukan: " << parentNode->data << endl;
                    cout << "Node paling kiri: " << mostLeft(parentNode)->data << endl;
                    cout << "Node paling kanan: " << mostRight(parentNode)->data << endl;
                } else {
                    cout << "Node tidak ditemukan.\n";
                }
                break;
            case 5:
                cout << "Masukkan data node: ";
                cin >> data;
                parentNode = find(data, root);
                if (parentNode) displayChildren(parentNode);
                else cout << "Node tidak ditemukan.\n";
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
                if (is_valid_bst(root, numeric_limits<char>::min(), numeric_limits<char>::max()))
                    cout << "Pohon adalah Binary Search Tree yang valid.\n";
                else
                    cout << "Pohon bukan Binary Search Tree yang valid.\n";
                break;
            case 10:
                cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
                break;
            case 11:
                cout << "Keluar.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 11);
}

// Fungsi utama
int main() {
    init(); // Inisialisasi pohon
    menu(); // Menampilkan menu
    return 0;
}