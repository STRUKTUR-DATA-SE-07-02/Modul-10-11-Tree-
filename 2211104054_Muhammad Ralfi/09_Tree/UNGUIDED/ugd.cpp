#include <iostream>
#include <queue>
#include <climits>
using namespace std;

struct pohon {
    int data; // Ganti char menjadi int
    pohon *kiri;
    pohon *kanan;
    pohon *parent;
};

pohon *root, *baru;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

void buatNode(int data) {
    if (isEmpty()) {
        root = new pohon{data, NULL, NULL, NULL};
        cout << "Node " << data << " berhasil dibuat sebagai root" << endl;
    } else {
        cout << "Pohon sudah dibuat" << endl;
    }
}

pohon* insertKiri(int data, pohon *node) {
    if(node->kiri != NULL){
        cout << "\nNode " << node->data << " sudah memiliki anak kiri" << endl;
        return NULL;
    }
    baru = new pohon{data, NULL, NULL, node};
    node->kiri = baru;
    cout << "\nNode " << data << " berhasil ditambahkan sebagai anak kiri dari " << node->data << endl;
    return baru;
}

pohon* insertKanan(int data, pohon *node) {
    if(node->kanan != NULL){
        cout << "\nNode " << node->data << " sudah memiliki anak kanan" << endl;
        return NULL;
    }
    baru = new pohon{data, NULL, NULL, node};
    node->kanan = baru;
    cout << "\nNode " << data << " berhasil ditambahkan sebagai anak kanan dari " << node->data << endl;
    return baru;
}

void displayTree(pohon* node, int level = 0) {
    if (node == NULL) return;

    displayTree(node->kanan, level + 1);

    for (int i = 0; i < level; i++) cout << "    ";
    cout << node->data << endl;

    displayTree(node->kiri, level + 1);
}

pohon* findNode(int data) {
    if (isEmpty()) return NULL;

    queue<pohon*> q;
    q.push(root);

    while (!q.empty()) {
        pohon* temp = q.front();
        q.pop();

        if (temp->data == data) return temp;

        if (temp->kiri) q.push(temp->kiri);
        if (temp->kanan) q.push(temp->kanan);
    }

    return NULL;
}

// Fungsi rekursif untuk memeriksa properti Binary Search Tree
bool is_valid_bst(pohon* node, int min_val, int max_val) {
    if (!node) return true;

    int nilai = node->data; // Anggap data sudah berupa int
    if (nilai <= min_val || nilai >= max_val) return false;

    return is_valid_bst(node->kiri, min_val, nilai) &&
           is_valid_bst(node->kanan, nilai, max_val);
}

void periksaBST() {
    if (is_valid_bst(root, INT_MIN, INT_MAX)) {
        cout << "Pohon ini adalah Binary Search Tree yang valid.\n";
    } else {
        cout << "Pohon ini BUKAN Binary Search Tree yang valid.\n";
    }
}

// Fungsi rekursif untuk menghitung jumlah simpul daun
int cari_simpul_daun(pohon* node) {
    if (!node) return 0; // Jika node kosong, kembalikan 0

    // Jika node tidak memiliki anak kiri dan kanan, maka itu adalah simpul daun
    if (!node->kiri && !node->kanan) return 1;

    // Traversal ke kiri dan kanan
    return cari_simpul_daun(node->kiri) + cari_simpul_daun(node->kanan);
}

void hitungSimpulDaun() {
    int jumlah_daun = cari_simpul_daun(root);
    cout << "Jumlah simpul daun: " << jumlah_daun << endl;
}

int main() {
    init();
    int pilihan;
    int data, parent_data;

    while (true) {
        cout << "--- Menu Pohon Biner ---" << endl;
        cout << "1. Tambah Root Node" << endl;
        cout << "2. Tambah Child Kiri" << endl;
        cout << "3. Tambah Child Kanan" << endl;
        cout << "4. Tampilkan Struktur Pohon" << endl;
        cout << "5. Periksa apakah pohon adalah BST" << endl;
        cout << "6. Hitung Jumlah Simpul Daun" << endl;
        cout << "7. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                if (isEmpty()) {
                    cout << "Masukkan data root: ";
                    cin >> data;
                    buatNode(data);
                } else {
                    cout << "Root sudah ada!" << endl;
                }
                break;

            case 2: // Tambah Child Kiri
                cout << "Masukkan data node induk: ";
                cin >> parent_data;
                cout << "Masukkan data anak kiri: ";
                cin >> data;
                if (pohon* parent = findNode(parent_data)) {
                    insertKiri(data, parent);
                } else {
                    cout << "Node induk tidak ditemukan!" << endl;
                }
                break;

            case 3: // Tambah Child Kanan
                cout << "Masukkan data node induk: ";
                cin >> parent_data;
                cout << "Masukkan data anak kanan: ";
                cin >> data;
                if (pohon* parent = findNode(parent_data)) {
                    insertKanan(data, parent);
                } else {
                    cout << "Node induk tidak ditemukan!" << endl;
                }
                break;

            case 4:
                cout << "Struktur Pohon:" << endl;
                displayTree(root);
                break;

            case 5:
                periksaBST();
                break;

            case 6:
                hitungSimpulDaun();
                break;

            case 7:
                cout << "Keluar dari program." << endl;
                return 0;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}
