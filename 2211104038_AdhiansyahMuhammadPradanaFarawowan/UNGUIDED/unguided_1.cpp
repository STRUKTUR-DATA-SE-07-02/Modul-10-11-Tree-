#include <iostream>
#include <vector>

struct Pohon
{
    char data;
    Pohon *kiri;
    Pohon *kanan;
    Pohon *induk;
};

Pohon *akar;
Pohon *baru;

void buat_pohon()
{
    akar = nullptr;
}

bool kosong()
{
    return akar == nullptr;
}

void buat_simpul_akar(char data)
{
    if (kosong())
    {
        akar = new Pohon;
        akar->data = data;
        akar->kanan = nullptr;
        akar->kiri = nullptr;
        akar->induk = nullptr;

        std::cout << "Simpul akar " << akar->data << " berhasil dibuat" << '\n';
    }
    else
    {
        // Kalau pohon sudah dibuat
        std::cout << "Akar sudah ada" << '\n';
    }
}

Pohon *masukkan_ke_kiri(char data, Pohon *simpul)
{
    if (simpul->kiri != nullptr)
    {
        std::cout << "Simpul " << simpul->data << " sudah ada di kiri" << '\n';
        return nullptr;
    }

    baru = new Pohon;
    baru->data = data;
    baru->kiri = nullptr;
    baru->kanan = nullptr;
    baru->induk = simpul;

    simpul->kiri = baru;
    std::cout << "Simpul " << data << " dibuat di kiri" << '\n';

    return baru;
}

Pohon *masukkan_ke_kanan(char data, Pohon *simpul)
{
    if (simpul->kanan != nullptr)
    {
        std::cout << "Simpul " << simpul->data << " sudah ada di kanan" << '\n';
        return nullptr;
    }

    baru = new Pohon;
    baru->data = data;
    baru->kiri = nullptr;
    baru->kanan = nullptr;
    baru->induk = simpul;

    simpul->kanan = baru;
    std::cout << "Simpul " << data << " dibuat di kanan" << '\n';

    return baru;
}

void perbarui_isi_simpul(char data, Pohon *simpul)
{
    if (!simpul)
    {
        std::cout << "Tidak ditemukan" << '\n';
        return;
    }

    char temp = simpul->data;
    simpul->data = data;
    std::cout << "Berhasil diubah menjadi " << data << '\n';
}

void cari_simpul(char data, Pohon *simpul)
{
    if (!simpul)
    {
        std::cout << "Simpul tidak ditemukan" << '\n';
        return;
    }

    if (simpul->data == data)
    {
        std::cout << "Ditemukan" << '\n';
        return;
    }

    cari_simpul(data, simpul->kiri);
    cari_simpul(data, simpul->kanan);
}

void pre_order(Pohon *simpul)
{
    if (!simpul)
    {
        return;
    }

    std::cout << simpul->data << " ";
    pre_order(simpul->kiri);
    pre_order(simpul->kanan);
}

void in_order(Pohon *simpul)
{
    if (!simpul)
    {
        return;
    }

    in_order(simpul->kiri);
    std::cout << simpul->data << " ";
    in_order(simpul->kanan);
}

void post_order(Pohon *simpul)
{
    if (!simpul)
    {
        return;
    }

    post_order(simpul->kiri);
    post_order(simpul->kanan);
    std::cout << simpul->data << " ";
}

Pohon *hapus_simpul(Pohon *simpul, char data)
{
    if (!simpul)
    {
        return nullptr;
    }

    if (data < simpul->data)
    {
        simpul->kiri = hapus_simpul(simpul->kiri, data);
    }
    else if (data > simpul->data)
    {
        simpul->kanan = hapus_simpul(simpul->kanan, data);
    }
    else
    {
        if (!simpul->kiri)
        {
            Pohon *temp = simpul->kanan;
            delete simpul;
            return temp;
        }
        else if (!simpul->kanan)
        {
            Pohon *temp = simpul->kiri;
            delete simpul;
            return temp;
        }

        Pohon *penerus = simpul->kanan;
        while (penerus->kiri)
        {
            penerus = penerus->kiri;
        }

        simpul->data = penerus->data;
        simpul->kanan = hapus_simpul(simpul->kanan, penerus->data);
    }

    return simpul;
}

Pohon *simpul_paling_kiri(Pohon *simpul)
{
    if (!simpul)
    {
        return nullptr;
    }

    while (simpul->kiri)
    {
        simpul = simpul->kiri;
    }

    return simpul;
}

Pohon *simpul_paling_kanan(Pohon *simpul)
{
    if (!simpul)
    {
        return nullptr;
    }

    while (simpul->kanan)
    {
        simpul = simpul->kanan;
    }

    return simpul;
}

Pohon *dapatkan_simpul(char data, Pohon *simpul)
{
    if (!simpul)
    {
        return nullptr;
    }

    if (simpul->data == data)
    {
        return simpul;
    }

    Pohon *result = dapatkan_simpul(data, simpul->kiri);
    if (result)
    {
        return result;
    }
    return dapatkan_simpul(data, simpul->kanan);
}

void tampilkan_anak(Pohon *simpul)
{
    if (!simpul)
    {
        return;
    }

    std::cout << "Simpul " << simpul->data << "\n";
    std::cout << "Kiri:" << " " << "Kanan:" << "\n";
    if (simpul->kiri)
    {
        std::cout << simpul->kiri->data << " ";
    }

    if (simpul->kanan)
    {
        std::cout << "\t\t\t";
        std::cout << simpul->kanan->data << " ";
    }

    std::cout << '\n';
}

void tampilkan_keturunan(Pohon *simpul)
{
    if (!simpul)
    {
        return;
    }

    if (simpul->kiri != nullptr)
    {
        std::cout << simpul->kiri->data << " ";
        tampilkan_keturunan(simpul->kiri);
    }
    if (simpul->kanan != nullptr)
    {
        std::cout << simpul->kanan->data << " ";
        tampilkan_keturunan(simpul->kanan);
    }

    std::cout << '\n';
}

// Edisi spesial BST
// Pohon adalah BST jika traversal dengan inorder menghasilkan deretan yang berurutan
// Waktunya pakai std::vector!
void deretan_dari_inorder(Pohon *simpul, std::vector<char> &deretan_char)
{
    if (simpul == nullptr)
    {
        return;
    }

    deretan_dari_inorder(simpul->kiri, deretan_char);
    deretan_char.push_back(simpul->data);
    deretan_dari_inorder(simpul->kanan, deretan_char);
}

bool is_valid_bst()
{
    std::vector<char> deretan_char;
    deretan_dari_inorder(akar, deretan_char);

    for (int i = 1; i < deretan_char.size(); i = i + 1)
    {
        if (deretan_char[i] <= deretan_char[i - 1])
        {
            return false;
        }
    }
    return true;
}
// Edisi spesial BST

int jumlah_daun(Pohon *simpul)
{
    if (!simpul)
    {
        return 0;
    }

    if (!simpul->kiri && !simpul->kanan)
    {
        return 1;
    };

    return jumlah_daun(simpul->kiri) + jumlah_daun(simpul->kanan);
}

void menu()
{
    std::cout << "Menu manipulasi pohon" << '\n';
    std::cout << "[1] Buat akar" << '\n';
    std::cout << "[2] Tambah simpul anak di kiri" << '\n';
    std::cout << "[3] Tambah simpul anak di kanan" << '\n';
    std::cout << "[4] Tampilkan anak" << '\n';
    std::cout << "[5] Tampilkan keturunan" << '\n';
    std::cout << "[6] Telusur secara preorder" << '\n';
    std::cout << "[7] Telusur secara inorder" << '\n';
    std::cout << "[8] Telusur secara postorder" << '\n';
    std::cout << "[9] Validasi apakah pohon adalah BST" << '\n';
    std::cout << "[10] Hitung jumlah daun" << '\n';
    std::cout << "[99] Keluar" << '\n';
    std::cout << "\n";

    std::cout << "Pilihan: ";
}

int main()
{
    int pilihan;

    std::cout << "Pohon telah dibuat" << '\n';

    while (true)
    {
        menu();
        std::cin >> pilihan;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (pilihan == 1)
        {
            if (!akar)
            {
                char _data;

                std::cout << "Masukkan data akar: ";
                std::cin >> _data;

                std::cout << "\n";

                buat_simpul_akar(_data);
                std::cout << "Akar berhasil dibuat." << '\n';
            }
            else
            {
                std::cout << "Akar sudah ada." << '\n';
            }
        }
        else if (pilihan == 2)
        {
            char _cari;
            char _data;

            std::cout << "Masukkan induk: ";
            std::cin >> _cari;

            std::cout << "Masukkan data: ";
            std::cin >> _data;

            Pohon *dicari = dapatkan_simpul(_cari, akar);
            if (dicari != nullptr)
            {
                masukkan_ke_kiri(_data, dicari);
                std::cout << "Berhasil ditambahkan ke kiri" << '\n';
            }
            else
            {
                std::cout << "Induk tidak ditemukan" << '\n';
            }
        }
        else if (pilihan == 3)
        {
            char _cari;
            char _data;

            std::cout << "Masukkan induk: ";
            std::cin >> _cari;

            std::cout << "Masukkan data: ";
            std::cin >> _data;

            Pohon *dicari = dapatkan_simpul(_cari, akar);
            if (dicari != nullptr)
            {
                masukkan_ke_kanan(_data, dicari);
                std::cout << "Berhasil ditambahkan ke kanan" << '\n';
            }
            else
            {
                std::cout << "Induk tidak ditemukan" << '\n';
            }
        }
        else if (pilihan == 4)
        {
            char _data;

            std::cout << "Masukkan simpul: ";
            std::cin >> _data;

            Pohon *dicari = dapatkan_simpul(_data, akar);

            tampilkan_anak(dicari);
        }
        else if (pilihan == 5)
        {
            char _data;

            std::cout << "Masukkan simpul: ";
            std::cin >> _data;

            Pohon *dicari = dapatkan_simpul(_data, akar);

            tampilkan_keturunan(dicari);
        }
        else if (pilihan == 6)
        {
            std::cout << "Penelurusan dengan preorder: ";
            pre_order(akar);
            std::cout << '\n';
        }
        else if (pilihan == 7)
        {
            std::cout << "Penelurusan dengan inorder: ";
            in_order(akar);
            std::cout << '\n';
        }
        else if (pilihan == 8)
        {
            std::cout << "Penelurusan dengan postorder: ";
            post_order(akar);
            std::cout << '\n';
        }
        else if (pilihan == 9)
        {
            if (is_valid_bst())
            {
                std::cout << "Pohon merupakan pohon pencarian biner." << '\n';
            }
            else
            {
                std::cout << "Pohon bukan merupakan pohon pencarian biner." << '\n';
            }
        }
        else if (pilihan == 10)
        {
            std::cout << "Jumlah simpul daun: " << jumlah_daun(akar) << '\n';
        }
        else if (pilihan == 99)
        {
            std::cout << "Keluar dari program." << '\n';
            break;
        }
        else
        {
            std::cout << "Pilihan tidak valid." << '\n';
        }
    }
    return 0;
}
