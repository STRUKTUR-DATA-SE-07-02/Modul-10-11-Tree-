#include <iostream>
#include <limits>
using namespace std;

// Struktur data pohon biner
struct Pohon
{
    char data;
    Pohon *left, *right, *parent;
};

Pohon *root, *baru;

// Fungsi inisialisasi dan dasar (sama seperti sebelumnya)
void init() { root = NULL; }
bool isEmpty() { return root == NULL; }

// Fungsi untuk membuat node baru
Pohon *createNode(char data)
{
    Pohon *newNode = new Pohon{data, NULL, NULL, NULL};
    return newNode;
}

// Fungsi untuk menambahkan node
Pohon *insertNode(Pohon *node, char data, char parentData, bool isLeft)
{
    if (!node)
        return NULL;

    // Jika node yang dicari ditemukan
    if (node->data == parentData)
    {
        Pohon *newNode = createNode(data);

        if (isLeft)
        {
            if (node->left)
            {
                cout << "Node kiri sudah terisi!" << endl;
                return NULL;
            }
            node->left = newNode;
            newNode->parent = node;
        }
        else
        {
            if (node->right)
            {
                cout << "Node kanan sudah terisi!" << endl;
                return NULL;
            }
            node->right = newNode;
            newNode->parent = node;
        }
        return newNode;
    }

    // Rekursif pencarian
    Pohon *leftResult = insertNode(node->left, data, parentData, isLeft);
    if (leftResult)
        return leftResult;

    Pohon *rightResult = insertNode(node->right, data, parentData, isLeft);
    return rightResult;
}

// Fungsi untuk mencari node
Pohon *findNode(Pohon *node, char data)
{
    if (!node)
        return NULL;

    if (node->data == data)
        return node;

    Pohon *leftResult = findNode(node->left, data);
    if (leftResult)
        return leftResult;

    Pohon *rightResult = findNode(node->right, data);
    return rightResult;
}

// Fungsi untuk menampilkan child dari suatu node
void tampilkanChild(Pohon *node)
{
    if (!node)
    {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }

    cout << "Node: " << node->data << endl;
    if (node->left)
        cout << "Child Kiri: " << node->left->data << endl;
    else
        cout << "Tidak memiliki child kiri" << endl;

    if (node->right)
        cout << "Child Kanan: " << node->right->data << endl;
    else
        cout << "Tidak memiliki child kanan" << endl;
}

// Fungsi untuk menampilkan descendants
void tampilkanDescendant(Pohon *node)
{
    if (!node)
    {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }

    cout << "Descendants dari " << node->data << ": ";

    // Fungsi rekursif untuk mencetak descendants
    if (!node->left && !node->right)
    {
        cout << "Tidak memiliki descendants" << endl;
        return;
    }

    // Pre-order traversal untuk descendants
    if (node->left)
    {
        cout << node->left->data << " ";
        tampilkanDescendant(node->left);
    }

    if (node->right)
    {
        cout << node->right->data << " ";
        tampilkanDescendant(node->right);
    }

    cout << endl;
}

// Fungsi untuk memeriksa apakah suatu pohon adalah BST (Rekursif)
bool is_valid_bst(Pohon *node, char min_val = numeric_limits<char>::min(),
                  char max_val = numeric_limits<char>::max())
{
    // Base case: pohon kosong dianggap valid
    if (!node)
        return true;

    // Cek apakah node saat ini memenuhi batasan
    if (node->data <= min_val || node->data >= max_val)
        return false;

    // Rekursif ke anak kiri dan kanan
    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

// Fungsi untuk menghitung simpul daun (Rekursif)
int cari_simpul_daun(Pohon *node)
{
    // Base case
    if (!node)
        return 0;

    // Jika node adalah daun (tidak memiliki anak)
    if (!node->left && !node->right)
        return 1;

    // Rekursif ke anak kiri dan kanan
    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Menu interaktif
void menu()
{
    int pilihan;
    char data, parentData;

    do
    {
        cout << "\n--- MENU POHON BINER ---" << endl;
        cout << "1. Buat Root" << endl;
        cout << "2. Tambah Node Kiri" << endl;
        cout << "3. Tambah Node Kanan" << endl;
        cout << "4. Tampilkan Child" << endl;
        cout << "5. Tampilkan Descendants" << endl;
        cout << "6. Cek BST" << endl;
        cout << "7. Hitung Simpul Daun" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            if (isEmpty())
            {
                cout << "Masukkan data root: ";
                cin >> data;
                root = createNode(data);
            }
            else
            {
                cout << "Root sudah ada!" << endl;
            }
            break;

        case 2:
        case 3:
            if (isEmpty())
            {
                cout << "Buat root terlebih dahulu!" << endl;
                break;
            }

            cout << "Masukkan data node baru: ";
            cin >> data;
            cout << "Masukkan data parent: ";
            cin >> parentData;

            insertNode(root, data, parentData, pilihan == 2);
            break;

        case 4:
            cout << "Masukkan node yang ingin dilihat child-nya: ";
            cin >> data;
            tampilkanChild(findNode(root, data));
            break;

        case 5:
            cout << "Masukkan node yang ingin dilihat descendants-nya: ";
            cin >> data;
            tampilkanDescendant(findNode(root, data));
            break;

        case 6:
            cout << "Pohon " << (is_valid_bst(root) ? "valid" : "tidak valid")
                 << " sebagai BST" << endl;
            break;

        case 7:
            cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
            break;

        case 0:
            cout << "Keluar dari program." << endl;
            break;

        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

int main()
{
    init();
    menu();
    return 0;
}
