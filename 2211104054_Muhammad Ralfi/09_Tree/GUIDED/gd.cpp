#include <iostream>
using namespace std;

struct pohon {
    char data;
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

void buatNode(char data) {
    if (isEmpty()) {
    root = new pohon{data, NULL, NULL, NULL};
    cout << "Node " << data << " berhasil dibuat sebagai root" << endl;
    } else {
        cout << "Pohon sudah dibuat" << endl;
    }
}

pohon* insertKiri(char data, pohon *node) {
    if(node->kiri != NULL){
        cout << "\nNode " << data << " sudah memiliki anak kiri" << node->data << endl;
    }
    baru = new pohon{data, NULL, NULL, node};
    node->kiri = baru;
    cout << "\nNode " << data << "berhasil ditambahkan" << endl;
    return baru;
}

pohon *insertKanan(char data, pohon *node) {
    if(node->kanan != NULL){
        cout << "\nNode " << data << " sudah memiliki anak kanan" << node->data << endl;
    }
    baru = new pohon{data, NULL, NULL, node};
    node->kanan = baru;
    cout << "\nNode " << data << "berhasil ditambahkan" << endl;
    return baru;
}

void updateNode(char data, pohon *node) {
    if(!node) {
        cout << "\nNode " << data << " tidak ditemukan" << endl;
        return;
    }
    char temp = node->data;
    node->data = data;
    cout << "\nNode " << temp << " berhasil diupdate menjadi " << data << endl;
}

void find(char data, pohon *node) {
    if(!node)return;
    if(node->data == data) {
        cout << "\nNode " << data << " ditemukan" << endl;
        return;
    }
    find(data, node->kiri);
    find(data, node->kanan);
}


void preOrder(pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->kiri);
    preOrder(node->kanan);
}

void inOrder(pohon *node) {
    if (!node) return;
    inOrder(node->kiri);
    cout << node->data << " ";
    inOrder(node->kanan);
}
void postOrder(pohon *node) {
    if (!node) return;
    postOrder(node->kiri);
    postOrder(node->kanan);
    cout << node->data << " ";
}


pohon* deleteNode(pohon *node, char data) {
    if(!node) return NULL;

    if (data < node->data){
        node->kiri = deleteNode(node->kiri, data);
    } else if (data > node->data){
        node->kanan = deleteNode(node->kanan, data);
    } else {
        if (!node->kiri) {
            pohon *temp = node->kanan;
            delete node;
            return temp;
        } else if (!node->kanan) {
            pohon *temp = node->kiri;
            delete node;
            return temp;
        }

        pohon *successor = node->kanan;
        while (successor->kiri) successor = successor->kiri;
        node->data = successor->data;
        node->kanan = deleteNode(node->kanan, successor->data);
    }
    return node;
}

pohon* mostKiri(pohon *node) {
    if(!node) return NULL;
    while(node->kiri) node = node->kiri;
    return node;
}

pohon* mostKanan(pohon *node) {
    if(!node) return NULL;
    while(node->kanan) node = node->kanan;
    return node;
}

int main() {
    init();
    buatNode('F');
    insertKiri('B', root);
    insertKanan('G', root);
    insertKiri('A', root ->kiri);
    insertKanan('D', root ->kiri);
    insertKiri('C', root -> kiri ->kanan);
    insertKanan('E', root->kiri->kanan);

    cout << "\nPre-order Traversal: ";
    preOrder(root);
    cout << "\nPost-order Traversal: ";
    postOrder(root);
    cout << "\nIn-order Traversal: ";
    inOrder(root);

    cout << "\nMost Kiri Node: " << mostKiri(root)->data;
    cout << "\nMost Kanan Node: " << mostKanan(root)->data;

    cout << "\nMenghapus node 'D': ";
    root = deleteNode(root, 'D');
    cout << "\nIn-Order Traversal setelah penghapusan: ";
    inOrder(root);

    return 0;
}


/*
#include <iostream>
#include <queue>
using namespace std;

struct pohon {
    char data;
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

void buatNode(char data) {
    if (isEmpty()) {
        root = new pohon{data, NULL, NULL, NULL};
        cout << "Node " << data << " berhasil dibuat sebagai root" << endl;
    } else {
        cout << "Pohon sudah dibuat" << endl;
    }
}

pohon* insertKiri(char data, pohon *node) {
    if(node->kiri != NULL){
        cout << "\nNode " << node->data << " sudah memiliki anak kiri" << endl;
        return NULL;
    }
    baru = new pohon{data, NULL, NULL, node};
    node->kiri = baru;
    cout << "\nNode " << data << " berhasil ditambahkan sebagai anak kiri dari " << node->data << endl;
    return baru;
}

pohon* insertKanan(char data, pohon *node) {
    if(node->kanan != NULL){
        cout << "\nNode " << node->data << " sudah memiliki anak kanan" << endl;
        return NULL;
    }
    baru = new pohon{data, NULL, NULL, node};
    node->kanan = baru;
    cout << "\nNode " << data << " berhasil ditambahkan sebagai anak kanan dari " << node->data << endl;
    return baru;
}

void updateNode(char data, pohon *node) {
    if(!node) {
        cout << "\nNode tidak ditemukan" << endl;
        return;
    }
    char temp = node->data;
    node->data = data;
    cout << "\nNode " << temp << " berhasil diupdate menjadi " << data << endl;
}

void find(char data, pohon *node) {
    if(!node) return;
    if(node->data == data) {
        cout << "\nNode " << data << " ditemukan" << endl;
        return;
    }
    find(data, node->kiri);
    find(data, node->kanan);
}

void preOrder(pohon *node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->kiri);
    preOrder(node->kanan);
}

void inOrder(pohon *node) {
    if (!node) return;
    inOrder(node->kiri);
    cout << node->data << " ";
    inOrder(node->kanan);
}

void postOrder(pohon *node) {
    if (!node) return;
    postOrder(node->kiri);
    postOrder(node->kanan);
    cout << node->data << " ";
}

pohon* deleteNode(pohon *node, char data) {
    if(!node) return NULL;

    if (data < node->data){
        node->kiri = deleteNode(node->kiri, data);
    } else if (data > node->data){
        node->kanan = deleteNode(node->kanan, data);
    } else {
        if (!node->kiri) {
            pohon *temp = node->kanan;
            delete node;
            return temp;
        } else if (!node->kanan) {
            pohon *temp = node->kiri;
            delete node;
            return temp;
        }

        pohon *successor = node->kanan;
        while (successor->kiri) successor = successor->kiri;
        node->data = successor->data;
        node->kanan = deleteNode(node->kanan, successor->data);
    }
    return node;
}

pohon* mostKiri(pohon *node) {
    if(!node) return NULL;
    while(node->kiri) node = node->kiri;
    return node;
}

pohon* mostKanan(pohon *node) {
    if(!node) return NULL;
    while(node->kanan) node = node->kanan;
    return node;
}

void insertNode() {
    char data, parent_data;
    char side;

    cout << "Masukkan data untuk node baru: ";
    cin >> data;

    if (isEmpty()) {
        buatNode(data);
        return;
    }

    cout << "Masukkan data node induk: ";
    cin >> parent_data;

    cout << "Masukkan sebagai anak kiri atau kanan? (L/R): ";
    cin >> side;

    pohon* parent = root;
    queue<pohon*> q;
    q.push(parent);

    while (!q.empty()) {
        pohon* temp = q.front();
        q.pop();

        if (temp->data == parent_data) {
            if (side == 'L' || side == 'l') {
                insertKiri(data, temp);
            } else if (side == 'R' || side == 'r') {
                insertKanan(data, temp);
            }
            return;
        }

        if (temp->kiri) q.push(temp->kiri);
        if (temp->kanan) q.push(temp->kanan);
    }

    cout << "Node induk tidak ditemukan!" << endl;
}

bool is_valid_bst(pohon* node, int min_val, int max_val) {
    if (node == NULL) {
        return true;
    }

    if (node->data < min_val || node->data > max_val) {
        return false;
    }

    return is_valid_bst(node->kiri, min_val, node->data - 1) &&
           is_valid_bst(node->kanan, node->data + 1, max_val);
}

void displayTree(pohon* node, int level = 0) {
    if (node == NULL) return;

    displayTree(node->kanan, level + 1);

    for (int i = 0; i < level; i++) cout << "    ";
    cout << node->data << endl;

    displayTree(node->kiri, level + 1);
}

void displayChildren(pohon* node) {
    if (node == NULL) {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }

    cout << "Anak-anak dari node " << node->data << ": ";
    if (node->kiri) cout << node->kiri->data << " ";
    if (node->kanan) cout << node->kanan->data << " ";
    if (!node->kiri && !node->kanan) cout << "Tidak ada";
    cout << endl;
}

void displayDescendants(pohon* node) {
    if (node == NULL) return;

    if (node->kiri) {
        cout << node->kiri->data << " ";
        displayDescendants(node->kiri);
    }
    if (node->kanan) {
        cout << node->kanan->data << " ";
        displayDescendants(node->kanan);
    }
}

pohon* findNode(char data) {
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

int main() {
    init();
    int choice;
    char data;

    while (true) {
        cout << "\n--- Binary Tree Menu ---" << endl;
        cout << "1. Insert Node" << endl;
        cout << "2. Display Tree" << endl;
        cout << "3. Display Children of a Node" << endl;
        cout << "4. Display Descendants of a Node" << endl;
        cout << "5. Check if valid BST" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertNode();
                break;
            case 2:
                cout << "Tree Structure:" << endl;
                displayTree(root);
                break;
            case 3:
                cout << "Enter node data: ";
                cin >> data;
                displayChildren(findNode(data));
                break;
            case 4:
                cout << "Enter node data: ";
                cin >> data;
                cout << "Descendants of node " << data << ": ";
                displayDescendants(findNode(data));
                cout << endl;
                break;
            case 5:
                if (is_valid_bst(root, INT_MIN, INT_MAX)) {
                    cout << "The tree is a valid BST." << endl;
                } else {
                    cout << "The tree is not a valid BST." << endl;
                }
                break;
            case 6:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
*/
