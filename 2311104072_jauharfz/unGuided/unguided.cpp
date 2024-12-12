#include <iostream>
#include <limits>
using namespace std;

struct Pohon
{
  int data; // Changed to int for easier BST validation
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

// Function to display children of a node
void displayChildren(Pohon *node)
{
  if (!node)
  {
    cout << "Node tidak ditemukan!" << endl;
    return;
  }

  cout << "Node " << node->data << ":" << endl;
  if (node->left)
    cout << "Child kiri: " << node->left->data << endl;
  else
    cout << "Tidak ada child kiri" << endl;

  if (node->right)
    cout << "Child kanan: " << node->right->data << endl;
  else
    cout << "Tidak ada child kanan" << endl;
}

// Function to display descendants of a node
void displayDescendants(Pohon *node)
{
  if (!node)
    return;

  if (node->left)
  {
    cout << node->left->data << " ";
    displayDescendants(node->left);
  }
  if (node->right)
  {
    cout << node->right->data << " ";
    displayDescendants(node->right);
  }
}

// Function to check if tree is BST
bool is_valid_bst(Pohon *node, int min_val, int max_val)
{
  if (!node)
    return true;

  if (node->data <= min_val || node->data >= max_val)
    return false;

  return is_valid_bst(node->left, min_val, node->data) &&
         is_valid_bst(node->right, node->data, max_val);
}

// Function to count leaf nodes
int cari_simpul_daun(Pohon *node)
{
  if (!node)
    return 0;
  if (!node->left && !node->right)
    return 1;
  return cari_simpul_daun(node->left) + cari_simpul_daun(node->right);
}

// Modified insert functions to work with integers
void buatNode(int data)
{
  if (isEmpty())
  {
    root = new Pohon{data, NULL, NULL, NULL};
    cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
  }
  else
  {
    cout << "\nPohon sudah dibuat." << endl;
  }
}

Pohon *insertLeft(int data, Pohon *node)
{
  if (!node)
  {
    cout << "\nNode parent tidak ditemukan!" << endl;
    return NULL;
  }
  if (node->left)
  {
    cout << "\nNode " << node->data << " sudah ada child kiri!" << endl;
    return NULL;
  }
  baru = new Pohon{data, NULL, NULL, node};
  node->left = baru;
  cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
  return baru;
}

Pohon *insertRight(int data, Pohon *node)
{
  if (!node)
  {
    cout << "\nNode parent tidak ditemukan!" << endl;
    return NULL;
  }
  if (node->right)
  {
    cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
    return NULL;
  }
  baru = new Pohon{data, NULL, NULL, node};
  node->right = baru;
  cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
  return baru;
}

// Function to find a node with specific value
Pohon *findNode(int data, Pohon *node)
{
  if (!node)
    return NULL;
  if (node->data == data)
    return node;

  Pohon *leftResult = findNode(data, node->left);
  if (leftResult)
    return leftResult;

  return findNode(data, node->right);
}

void displayMenu()
{
  cout << "\n=== MENU BINARY TREE ===" << endl;
  cout << "1. Buat root" << endl;
  cout << "2. Insert node kiri" << endl;
  cout << "3. Insert node kanan" << endl;
  cout << "4. Tampilkan children" << endl;
  cout << "5. Tampilkan descendants" << endl;
  cout << "6. Cek BST" << endl;
  cout << "7. Hitung simpul daun" << endl;
  cout << "8. Keluar" << endl;
  cout << "Pilihan: ";
}

int main()
{
  init();
  int choice, data, parentData;
  Pohon *temp;

  do
  {
    displayMenu();
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Masukkan nilai root: ";
      cin >> data;
      buatNode(data);
      break;

    case 2:
      cout << "Masukkan nilai parent: ";
      cin >> parentData;
      cout << "Masukkan nilai node: ";
      cin >> data;
      temp = findNode(parentData, root);
      if (temp)
        insertLeft(data, temp);
      else
        cout << "Parent tidak ditemukan!" << endl;
      break;

    case 3:
      cout << "Masukkan nilai parent: ";
      cin >> parentData;
      cout << "Masukkan nilai node: ";
      cin >> data;
      temp = findNode(parentData, root);
      if (temp)
        insertRight(data, temp);
      else
        cout << "Parent tidak ditemukan!" << endl;
      break;

    case 4:
      cout << "Masukkan nilai node: ";
      cin >> data;
      temp = findNode(data, root);
      displayChildren(temp);
      break;

    case 5:
      cout << "Masukkan nilai node: ";
      cin >> data;
      temp = findNode(data, root);
      cout << "Descendants: ";
      displayDescendants(temp);
      cout << endl;
      break;

    case 6:
      if (is_valid_bst(root, INT_MIN, INT_MAX))
        cout << "Pohon adalah BST valid" << endl;
      else
        cout << "Pohon bukan BST valid" << endl;
      break;

    case 7:
      cout << "Jumlah simpul daun: " << cari_simpul_daun(root) << endl;
      break;

    case 8:
      cout << "Program selesai" << endl;
      break;

    default:
      cout << "Pilihan tidak valid!" << endl;
    }
  } while (choice != 8);

  return 0;
}
