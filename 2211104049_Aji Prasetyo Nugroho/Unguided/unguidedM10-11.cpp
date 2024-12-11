#include <iostream>
#include <climits>
using namespace std;

// Struktur node pohon
struct Pohon {
    char data;
    Pohon *left, *right, *parent;
    
    // Konstruktor
    Pohon(char x) : data(x), left(NULL), right(NULL), parent(NULL) {}
};

class BinaryTree {
private:
    Pohon *root;

    // Fungsi rekursif untuk mencari node
    Pohon* findNode(Pohon* node, char data) {
        if (!node) return NULL;
        
        if (node->data == data) return node;
        
        Pohon* leftResult = findNode(node->left, data);
        if (leftResult) return leftResult;
        
        Pohon* rightResult = findNode(node->right, data);
        if (rightResult) return rightResult;
        
        return NULL;
    }

public:
    BinaryTree() : root(NULL) {}

    // Fungsi untuk memeriksa apakah pohon kosong
    bool isEmpty() {
        return root == NULL;
    }

    // Membuat node root
    void buatNode(char data) {
        if (isEmpty()) {
            root = new Pohon(data);
            cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
        } else {
            cout << "\nPohon sudah dibuat. Gunakan menu insert." << endl;
        }
    }

    // Menambahkan node kiri
    Pohon* insertLeft(char data, Pohon *node) {
        if (!node) {
            cout << "\nNode induk tidak ditemukan!" << endl;
            return NULL;
        }
        
        if (node->left != NULL) {
            cout << "\nNode " << node->data << " sudah ada child kiri!" << endl;
            return NULL;
        }
        
        Pohon* baru = new Pohon(data);
        baru->parent = node;
        node->left = baru;
        cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
        return baru;
    }

    // Menambahkan node kanan
    Pohon* insertRight(char data, Pohon *node) {
        if (!node) {
            cout << "\nNode induk tidak ditemukan!" << endl;
            return NULL;
        }
        
        if (node->right != NULL) {
            cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
            return NULL;
        }
        
        Pohon* baru = new Pohon(data);
        baru->parent = node;
        node->right = baru;
        cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
        return baru;
    }

    // Menampilkan child dari suatu node
    void tampilkanChild(Pohon* node) {
        if (!node) {
            cout << "Node tidak ditemukan!" << endl;
            return;
        }
        
        cout << "Node: " << node->data << endl;
        cout << "Child Kiri: " << (node->left ? node->left->data : '-') << endl;
        cout << "Child Kanan: " << (node->right ? node->right->data : '-') << endl;
    }

    // Menampilkan descendant dari suatu node
    void tampilkanDescendant(Pohon* node) {
        if (!node) {
            cout << "Node tidak ditemukan!" << endl;
            return;
        }
        
        cout << "Descendant dari " << node->data << ": ";
        
        if (node->left || node->right) {
            if (node->left) {
                cout << "Kiri: ";
                Pohon* current = node->left;
                while (current) {
                    cout << current->data << " ";
                    current = current->left;
                }
            }
            
            if (node->right) {
                cout << "Kanan: ";
                Pohon* current = node->right;
                while (current) {
                    cout << current->data << " ";
                    current = current->right;
                }
            }
            cout << endl;
        } else {
            cout << "Tidak memiliki descendant." << endl;
        }
    }

    // Fungsi untuk mendapatkan root
    Pohon* getRoot() {
        return root;
    }

    // Fungsi untuk mencari node
    Pohon* findNodeWrapper(char data) {
        return findNode(root, data);
    }

    // Fungsi untuk memeriksa validitas BST
    bool is_valid_bst(Pohon* node, long min_val = LONG_MIN, long max_val = LONG_MAX) {
        if (node == NULL) return true;
        
        if (node->data <= min_val || node->data >= max_val) 
            return false;
        
        return is_valid_bst(node->left, min_val, node->data) && 
               is_valid_bst(node->right, node->data, max_val);
    }

    // Fungsi untuk menghitung simpul daun
    int cari_simpul_daun(Pohon* node) {
        if (node == NULL) return 0;
        
        if (node->left == NULL && node->right == NULL) 
            return 1;
        
        return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
    }
};

// Fungsi menu utama
void menu(BinaryTree& pohon) {
    int pilihan;
    char data, induk;
    Pohon* node;
    
    do {
        cout << "\n--- MENU POHON BINER ---" << endl;
        cout << "1. Buat Root" << endl;
        cout << "2. Tambah Node Kiri" << endl;
        cout << "3. Tambah Node Kanan" << endl;
        cout << "4. Tampilkan Child" << endl;
        cout << "5. Tampilkan Descendant" << endl;
        cout << "6. Periksa Validitas BST" << endl;
        cout << "7. Hitung Simpul Daun" << endl;
        cout << "8. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                if (!pohon.isEmpty()) {
                    cout << "Pohon sudah memiliki root!" << endl;
                    break;
                }
                cout << "Masukkan data root: ";
                cin >> data;
                pohon.buatNode(data);
                break;
            
            case 2:
                if (pohon.isEmpty()) {
                    cout << "Buat root terlebih dahulu!" << endl;
                    break;
                }
                cout << "Masukkan data node induk: ";
                cin >> induk;
                cout << "Masukkan data node kiri: ";
                cin >> data;
                node = pohon.findNodeWrapper(induk);
                pohon.insertLeft(data, node);
                break;
            
            case 3:
                if (pohon.isEmpty()) {
                    cout << "Buat root terlebih dahulu!" << endl;
                    break;
                }
                cout << "Masukkan data node induk: ";
                cin >> induk;
                cout << "Masukkan data node kanan: ";
                cin >> data;
                node = pohon.findNodeWrapper(induk);
                pohon.insertRight(data, node);
                break;
            
            case 4:
                if (pohon.isEmpty()) {
                    cout << "Pohon kosong!" << endl;
                    break;
                }
                cout << "Masukkan data node: ";
                cin >> data;
                node = pohon.findNodeWrapper(data);
                pohon.tampilkanChild(node);
                break;
            
            case 5:
                if (pohon.isEmpty()) {
                    cout << "Pohon kosong!" << endl;
                    break;
                }
                cout << "Masukkan data node: ";
                cin >> data;
                node = pohon.findNodeWrapper(data);
                pohon.tampilkanDescendant(node);
                break;
            
            case 6:
                if (pohon.isEmpty()) {
                    cout << "Pohon kosong!" << endl;
                    break;
                }
                cout << "Validitas BST: " << (pohon.is_valid_bst(pohon.getRoot()) ? "Ya" : "Tidak") << endl;
                break;
            
            case 7:
                if (pohon.isEmpty()) {
                    cout << "Pohon kosong!" << endl;
                    break;
                }
                cout << "Jumlah Simpul Daun: " << pohon.cari_simpul_daun(pohon.getRoot()) << endl;
                break;
            
            case 8:
                cout << "Keluar dari program." << endl;
                break;
            
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 8);
}

int main() {
    BinaryTree pohon;
    menu(pohon);
    return 0;
}