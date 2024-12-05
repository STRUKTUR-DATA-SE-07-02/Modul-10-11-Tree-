#include <iostream>

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
    std::cout << "Simpul " << simpul->data << " dibuat di kiri" << '\n';

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
    std::cout << "Simpul " << simpul->data << " dibuat di kanan" << '\n';

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

Pohon *simpul_paling_kiri(Pohon *simpul) {
    if (!simpul) {
        return nullptr;
    }

    while (simpul->kiri)
    {
        simpul = simpul->kiri;
    }

    return simpul;    
}

Pohon *simpul_paling_kanan(Pohon *simpul) {
    if (!simpul) {
        return nullptr;
    }

    while (simpul->kanan)
    {
        simpul = simpul->kanan;
    }

    return simpul;    
}

int main() {
    buat_pohon();
    buat_simpul_akar('F');

    masukkan_ke_kiri('B', akar);
    masukkan_ke_kanan('G', akar);

    masukkan_ke_kiri('A', akar->kiri);
    masukkan_ke_kanan('D', akar->kiri);

    masukkan_ke_kiri('C', akar->kiri->kanan);
    masukkan_ke_kanan('E', akar->kiri->kanan);

    // Penelusuran pohon
    std::cout << "Preorder: ";
    pre_order(akar);
    std::cout << '\n';

    std::cout << "Inorder: ";
    in_order(akar);
    std::cout << '\n';

    std::cout << "Postorder: ";
    post_order(akar);
    std::cout << '\n';

    // Menampilkan simpul paling kiri dan paling kanan
    std::cout << "Paling kiri" << simpul_paling_kiri(akar)->data << '\n';
    std::cout << "Paling kana" << simpul_paling_kanan(akar)->data << '\n';

    // Menghapus simpul
    std::cout << "Menghapus simpul D" << '\n';
    akar = hapus_simpul(akar, 'D');
    std::cout << "Traversal inorder: " << '\n';
    in_order(akar);
}
