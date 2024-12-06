#include <iostream>
#include <queue>
using namespace std;

struct Pohon
{
    char data;
    Pohon *left, *right;
    Pohon *parent;
};

Pohon *root, *baru;

void init()
{
    root = NULL;
}

bool isEmpty()
{
    return root == NULL;
}

void buatNode(char data)
{
    if (isEmpty())
    {
        root = new Pohon{data, NULL, NULL, NULL};
        cout << "\nNode " << data << " berhasil dibuat menjadi root" << endl;
    }
    else
    {
        cout << "\nPohon sudah dibuat" << endl;
    }
}

Pohon *insertLeft(char data, Pohon *node)
{
    if (node->left != NULL)
    {
        cout << "\nNode " << node->data << " sudah ada child kiri" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->left = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kiri dari "
         << node->data << endl;
    return baru;
}

Pohon *insertRight(char data, Pohon *node)
{
    if (node->right != NULL)
    {
        cout << "\nNode " << node->data << " sudah ada child kanan" << endl;
        return NULL;
    }
    baru = new Pohon{data, NULL, NULL, node};
    node->right = baru;
    cout << "\nNode " << data << " berhasil ditambahkan ke child kanan dari "
         << node->data << endl;
    return baru;
}

void update(char data, Pohon *node)
{
    if (!node)
    {
        cout << "\nNode yang ingin diubah tidak ditemukan" << endl;
        return;
    }
    char temp = node->data;
    node->data = data;
    cout << "\nNode " << temp << " berhasil diubah menjadi " << data << endl;
}

void find(char data, Pohon *node, Pohon *&result)
{
    if (!node)
        return;

    if (node->data == data)
    {
        result = node;
        return;
    }

    find(data, node->left, result);
    find(data, node->right, result);
}

void preOrder(Pohon *node)
{
    if (!node)
        return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Pohon *node)
{
    if (!node)
        return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

void postOrder(Pohon *node)
{
    if (!node)
        return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}

Pohon *deleteNode(Pohon *node, char data)
{
    if (!node)
        return NULL;

    if (data < node->data)
    {
        node->left = deleteNode(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = deleteNode(node->right, data);
    }
    else
    {
        if (!node->left)
        {
            Pohon *temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right)
        {
            Pohon *temp = node->left;
            delete node;
            return temp;
        }

        Pohon *successor = node->right;
        while (successor->left)
            successor = successor->left;
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data);
    }
    return node;
}

Pohon *mostLeft(Pohon *node)
{
    if (!node)
        return NULL;
    while (node->left)
        node = node->left;
    return node;
}

Pohon *mostRight(Pohon *node)
{
    if (!node)
        return NULL;
    while (node->right)
        node = node->right;
    return node;
}

void showChild(Pohon *node)
{
    if (!node)
    {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }
    cout << "Child kiri dari node " << node->data << ": ";
    if (node->left)
        cout << node->left->data;
    else
        cout << "Tidak ada";
    cout << "\nChild kanan dari node " << node->data << ": ";
    if (node->right)
        cout << node->right->data;
    else
        cout << "Tidak ada";
    cout << endl;
}

int cari_simpul_daun(Pohon *node)
{
    if (node == NULL)
        return 0;

    if (node->left == NULL && node->right == NULL)
        return 1;

    return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

void showDescendants(Pohon *node)
{
    if (!node)
    {
        cout << "Node tidak ditemukan!" << endl;
        return;
    }

    cout << "Descendants dari node " << node->data << ": ";
    queue<Pohon *> q;
    if (node->left)
        q.push(node->left);
    if (node->right)
        q.push(node->right);

    while (!q.empty())
    {
        Pohon *current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
    cout << endl;
}

bool is_valid_bst(Pohon *node, char min_val, char max_val)
{
    if (node == NULL)
        return true;

    if (node->data <= min_val || node->data >= max_val)
        return false;

    return is_valid_bst(node->left, min_val, node->data) &&
           is_valid_bst(node->right, node->data, max_val);
}

bool check_bst()
{
    return is_valid_bst(root, CHAR_MIN, CHAR_MAX);
}

int main()
{
    init();
    int choice;
    char data, parentData;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Buat root\n";
        cout << "2. Tambahkan child kiri\n";
        cout << "3. Tambahkan child kanan\n";
        cout << "4. Tampilkan pre-order traversal\n";
        cout << "5. Tampilkan in-order traversal\n";
        cout << "6. Tampilkan post-order traversal\n";
        cout << "7. Tampilkan child dari node\n";
        cout << "8. Tampilkan descendant dari node\n";
        cout << "9. Hapus node\n";
        cout << "10. Periksa apakah BST valid\n";
        cout << "11. Tampilkan jumlah simpul daun\n";
        cout << "12. Keluar\n";
        cout << "Masukkan pilihan (1-12): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Masukkan data root: ";
            cin >> data;
            buatNode(data);
            break;
        case 2:
            cout << "Masukkan data node parent dan child kiri: ";
            cin >> parentData >> data;
            Pohon *parentNode = NULL;
            find(parentData, root, parentNode);
            if (parentNode)
            {
                insertLeft(data, parentNode);
            }
            else
            {
                cout << "Node parent tidak ditemukan!" << endl;
            }
            break;
        case 3:
            cout << "Masukkan data node parent dan child kanan: ";
            cin >> parentData >> data;
            find(parentData, root, parentNode);
            if (parentNode)
            {
                insertRight(data, parentNode);
            }
            else
            {
                cout << "Node parent tidak ditemukan!" << endl;
            }
            break;
        case 4:
            cout << "Pre-order traversal: ";
            preOrder(root);
            cout << endl;
            break;
        case 5:
            cout << "In-order traversal: ";
            inOrder(root);
            cout << endl;
            break;
        case 6:
            cout << "Post-order traversal: ";
            postOrder(root);
            cout << endl;
            break;
        case 7:
            cout << "Masukkan data node untuk tampilkan child: ";
            cin >> data;
            find(data, root, parentNode);
            showChild(parentNode);
            break;
        case 8:
            cout << "Masukkan data node untuk tampilkan descendant: ";
            cin >> data;
            find(data, root, parentNode);
            showDescendants(parentNode);
            break;
        case 9:
            cout << "Masukkan data node yang akan dihapus: ";
            cin >> data;
            deleteNode(root, data);
            break;
        case 10:
            if (check_bst())
                cout << "Pohon adalah BST valid." << endl;
            else
                cout << "Pohon bukan BST valid." << endl;
            break;
        case 11:
            cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
            break;
        case 12:
            return 0;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    }

    return 0;
}
