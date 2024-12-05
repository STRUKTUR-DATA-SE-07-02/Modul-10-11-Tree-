#include <iostream>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

// Root pohon
Pohon *root = NULL, *baru;

// Fungsi untuk menginisialisasi pohon
void init() {
    root = NULL;
}

// Fungsi untuk memeriksa apakah pohon kosong
bool isEmpty() {
    return root == NULL;
}

// Fungsi untuk membuat node root
void buatNode(char data) {
    if (isEmpty()) {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah dibuat." << endl;
    }
}

// Fungsi untuk menambahkan anak kiri
Pohon* insertLeft(char data, Pohon *node) {
    if (node->left != NULL) {
        cout << "\nNode " << node->data << " sudah ada child kiri!" << endl;
        return NULL;
    }

    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
    return baru;
}

// Fungsi untuk menambahkan anak kanan
Pohon* insertRight(char data, Pohon *node) {
    if (node->right != NULL) {
        cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
        return NULL;
    }
    
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
    return baru;
}

// Fungsi untuk menampilkan anak dari node
void displayChildren(Pohon *node) {
    if (node == NULL) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }

    cout << "Children dari node " << node->data << ": ";

    // Cek jika anak kiri ada
    if (node->left != NULL) {
        cout << node->left->data << " ";
    }

    // Cek jika anak kanan ada
    if (node->right != NULL) {
        cout << node->right->data << " ";
    }

    // Jika tidak ada anak kiri dan kanan
    if (node->left == NULL && node->right == NULL) {
        cout << "Tidak ada anak." << endl;
    } else {
        cout << endl;
    }
}

// Fungsi untuk menampilkan keturunan dari node
void displayDescendants(Pohon *node) {
    if (node == NULL) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }

    cout << "Descendants dari node " << node->data << ": ";
    if (node->left != NULL) {
        cout << node->left->data << " ";
        displayDescendants(node->left);
    }
    if (node->right != NULL) {
        cout << node->right->data << " ";
        displayDescendants(node->right);
    }

    cout << endl;
}

// Fungsi rekursif untuk mencari node
Pohon* findNode(char data, Pohon* node) {
    if (node == NULL) return NULL;
    if (node->data == data) return node;
    Pohon* leftSearch = findNode(data, node->left);
    if (leftSearch) return leftSearch;
    return findNode(data, node->right);
}

// Fungsi untuk memeriksa apakah pohon adalah BST
bool is_valid_bst(Pohon* node, char min_val, char max_val) {
    if (node == NULL) return true;

    if (node->data < min_val || node->data > max_val)
        return false;

    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// Fungsi untuk menghitung jumlah simpul daun
int countLeafNodes(Pohon* node) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return countLeafNodes(node->left) + countLeafNodes(node->right);
}

int main() {
    init();

    // Deklarasi variabel yang dipakai untuk menyimpan node
    Pohon* parentLeft;
    Pohon* parentRight;
    Pohon* node;
    Pohon* nodeDescendants;
    Pohon* foundNode;
    
    // Menu untuk memasukkan data pohon dan memilih operasi
    int choice;
    char data, parentData;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Buat Root\n";
        cout << "2. Tambah Anak Kiri\n";
        cout << "3. Tambah Anak Kanan\n";
        cout << "4. Tampilkan Anak dari Node\n";
        cout << "5. Tampilkan Keturunan dari Node\n";
        cout << "6. Cari Node\n";
        cout << "7. Cek apakah Pohon Valid sebagai BST\n";
        cout << "8. Hitung Jumlah Simpul Daun\n";
        cout << "9. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan data root: ";
                cin >> data;
                buatNode(data);
                break;

            case 2:
                cout << "Masukkan data node yang akan diberi anak kiri: ";
                cin >> parentData;
                cout << "Masukkan data anak kiri: ";
                cin >> data;
                parentLeft = findNode(parentData, root);
                if (parentLeft != NULL) {
                    insertLeft(data, parentLeft);
                } else {
                    cout << "Node " << parentData << " tidak ditemukan.\n";
                }
                break;

            case 3:
                cout << "Masukkan data node yang akan diberi anak kanan: ";
                cin >> parentData;
                cout << "Masukkan data anak kanan: ";
                cin >> data;
                parentRight = findNode(parentData, root);
                if (parentRight != NULL) {
                    insertRight(data, parentRight);
                } else {
                    cout << "Node " << parentData << " tidak ditemukan.\n";
                }
                break;

            case 4:
                cout << "Masukkan data node untuk melihat anak-anaknya: ";
                cin >> data;
                node = findNode(data, root);
                displayChildren(node);
                break;

            case 5:
                cout << "Masukkan data node untuk melihat keturunannya: ";
                cin >> data;
                nodeDescendants = findNode(data, root);
                displayDescendants(nodeDescendants);
                break;

            case 6:
                cout << "Masukkan data node yang akan dicari: ";
                cin >> data;
                foundNode = findNode(data, root);
                if (foundNode != NULL) {
                    cout << "Node " << data << " ditemukan.\n";
                } else {
                    cout << "Node " << data << " tidak ditemukan.\n";
                }
                break;

            case 7:
                if (is_valid_bst(root, 'A', 'Z')) {
                    cout << "Pohon ini adalah Binary Search Tree.\n";
                } else {
                    cout << "Pohon ini bukan Binary Search Tree.\n";
                }
                break;

            case 8:
                cout << "Jumlah simpul daun: " << countLeafNodes(root) << endl;
                break;

            case 9:
                cout << "Keluar dari program.\n";
                return 0;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
