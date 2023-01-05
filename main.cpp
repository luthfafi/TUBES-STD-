#include <iostream>

#include "oplib.h"


using namespace std;
int main()
{
    List_p siswa;
    List_c buku;
    List_Relasi relasi;
    createListMhs(siswa);
    createListBuku(buku);
    createListRelasi(relasi);

    // a. Menambahkan data mahasiswa//

    data_mahasiswa s1;
    s1.nama = "Dimas";
    s1.nim = "13094";
    s1.kelas = "IF-11";
    address_p p1 = createElementMhs(s1);
    insertFirstMhs(siswa, p1);

    data_mahasiswa s2;
    s2.nama = "Tiara";
    s2.nim = "13031";
    s2.kelas = "IF-06";
    address_p p2 = createElementMhs(s2);
    insertFirstMhs(siswa, p2);

    data_mahasiswa s3;
    s3.nama = "Toni";
    s3.nim = "13016";
    s3.kelas = "IF-12";
    address_p p3 = createElementMhs(s3);
    insertFirstMhs(siswa, p3);

    data_mahasiswa s4;
    s4.nama = "Dian";
    s4.nim = "13076";
    s4.kelas = "IF-11";
    address_p p4 = createElementMhs(s4);
    insertFirstMhs(siswa, p4);

    // b. Menambahkan data buku

    data_buku b1;
    b1.judul = "Pulang";
    b1.kode = "3A07";
    address_c bk1 = createElementBuku(b1);
    insertFirstBuku(buku, bk1);

    data_buku b2;
    b2.judul = "Mariposa";
    b2.kode = "A30B";
    address_c bk2 = createElementBuku(b2);
    insertFirstBuku(buku, bk2);

    data_buku b3;
    b3.judul = "Dikta dan Hukum";
    b3.kode = "20A3";
    address_c bk3 = createElementBuku(b3);
    insertFirstBuku(buku, bk3);

    data_buku b4;
    b4.judul = "Hujan";
    b4.kode = "1A34";
    address_c bk4 = createElementBuku(b4);
    insertFirstBuku(buku, bk4);

    // c. Mencari data mahasiswa tertentu

    address_p v;

    v = findElementMhs(siswa, "13076");
    cout<<infoMhs(v).nama<<" "<<infoMhs(v).nim<<" "<<infoMhs(v).kelas<<endl;

    // d. Menambahkan relasi data buku yang dipinjam oleh mahasiswa dan sebaliknya


    makeRelasi(relasi, p2, bk1);
    makeRelasi(relasi, p2, bk2);
    makeRelasi(relasi, p2, bk3);
    makeRelasi(relasi, p3, bk3);
    makeRelasi(relasi, p4, bk2);
    makeRelasi(relasi, p4, bk3);
    makeRelasi(relasi, p1, bk4);
    showSemuaBukuDanMhs(relasi);
    cout<<endl;

    // e. Mencari data buku yang dipinjam oleh mahasiswa tertentu

    List_c Lc = findElementBuku(relasi, "Toni");
    address_c C = firstBuku(Lc);
    if (C == nil) {
        cout << "Buku tidak ditemukan" << endl;
    } else {
        do {
            cout << "Judul: " << infoBuku(C).judul << " - Kode: " << infoBuku(C).kode << endl;
        } while (C != firstBuku(Lc));
    }
    cout<<endl;

    // f. Menghapus buku beserta relasinya

    if (deleteBuku(relasi,buku, "Mariposa")){
        cout << "Data Buku berhasil dihapus" << endl;
    } else {
        cout << "Data Buku tidak ditemukan" << endl;
    }

    showSemuaBukuDanMhs(relasi);
    cout<<endl;

    // g. Menghapus data mahasiswa yang meminjam buku tertentu

    deleteRelasi_MHS_BK(relasi, buku, "Hujan");


    // h. Menampilkan seluruh data mahasiswa beserta semua data buku yang dipinjam

    showSemuaBukuDanMhs(relasi);


    // i. Menampilkan data buku yang paling favorite dikalangan mahasiswa

    showBukuTerfavorite(relasi);

    // j. Menampilkan data mahasiswa yang paling rajin membaca
    showMhsRajinMembaca(relasi);


    return 0;
}
