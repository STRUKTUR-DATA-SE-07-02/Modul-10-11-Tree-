#include <iostream>
#include <limits>
using namespace std;

struct Pohon {
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root, *baru;

void init() {
    root = NULL; 
}

bool isEmpty() {
    return root == NULL; 
}

void buatNode(char data) {
    if (isEmpty()) { 
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah dibuat." << endl; 
    }
}

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


void update(char data, Pohon *node) {
    if (!node) { 
        cout << "\nNode yang ingin diubah tidak ditemukan!" << endl;
        return;
    }
    char temp = node->data; 
    node->data = data;      
    cout << "\nNode " << temp << " berhasil diubah menjadi " << data << endl;
}


Pohon* find(char data, Pohon *node) {
    if (!node) return NULL; 

    if (node->data == data) { 
        return node;
    }
    
    Pohon* foundNode = find(data, node->left);
    if (foundNode) return foundNode;
    return find(data, node->right);
}


void preOrder(Pohon *node) {
    if (!node) return; 
    cout << node->data << " "; 
    preOrder(node->left);      
    preOrder(node->right);     
}


void inOrder(Pohon *node) {
    if (!node) return; 
    inOrder(node->left);  
    cout << node->data << " "; 
    inOrder(node->right); 
}


void postOrder(Pohon *node) {
    if (!node) return; 
    postOrder(node->left);  
    postOrder(node->right); 
    cout << node->data << " "; 
}


Pohon* deleteNode(Pohon *node, char data) {
    if (!node) return NULL; 

    
    if (data < node->data) {
        node->left = deleteNode(node->left, data); 
    } else if (data > node->data) {
        node->right = deleteNode(node->right, data); 
    } else {
        
        if (!node->left) { 
            Pohon *temp = node->right; 
            delete node;
            return temp;
        } else if (!node->right) { 
            Pohon *temp = node->left; 
            delete node;
            return temp;
        }

        
        Pohon *successor = node->right;
        while (successor->left) successor = successor->left; 
        node->data = successor->data; 
        node->right = deleteNode(node->right, successor->data); 
    }
    return node;
}


Pohon* mostLeft(Pohon *node) {
    if (!node) return NULL; 
    while (node->left) node = node->left; 
    return node;
}


Pohon* mostRight(Pohon *node) {
    if (!node) return NULL; 
    while (node->right) node = node->right; 
    return node;
}


void displayChildren(Pohon *node) {
    if (!node) return;
    cout << "\nNode " << node->data << " memiliki child: ";
    if (node->left) cout << "Kiri: " << node->left->data << " ";
    if (node->right) cout << "Kanan: " << node->right->data << " ";
    cout << "\nDescendant dari node " << node->data << ": ";
    preOrder(node);
    cout << endl;
}


bool is_valid_bst(Pohon *node, char min_val, char max_val) {
    if (!node) return true;
    if (node->data <= min_val || node->data >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->data) && is_valid_bst(node->right, node->data, max_val);
}


int cari_simpul_daun(Pohon *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}


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


int main() {
    init(); 
    menu(); 
    return 0;
}