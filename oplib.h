#ifndef OPLIB_H_INCLUDED
#define OPLIB_H_INCLUDED

#include <iostream>
using namespace std;

#define nil NULL
#define firstMhs(L) ((L).firstMhs)
#define firstBuku(L) ((L).firstBuku)
#define firstRelasi(L) ((L).firstRelasi)

#define infoMhs(P) (P)->infoMhs
#define nextMhs(P) (P)->nextMhs
#define infoBuku(P) (P)->infoBuku
#define nextBuku(P) (P)->nextBuku
#define nextRelasi(P) (P)->nextRelasi

//List Mahasiswa

struct data_mahasiswa{
    string nama;
    string nim;
    string kelas;
};
typedef struct data_mahasiswa infotype_p;
typedef struct elm_p *address_p;

struct elm_p{
    infotype_p infoMhs;
    address_p nextMhs;
};

struct List_p{
    address_p firstMhs;
};


//List Buku

struct data_buku{
    string judul;
    string kode;
};

typedef struct data_buku infotype_c;
typedef struct elm_c *address_c;


struct elm_c{
    infotype_c infoBuku;
    address_c nextBuku;
};

struct List_c{
    address_c firstBuku;
};

//List Relasi

typedef struct elm_r *address_r;

struct elm_r {
    address_c nextBuku;
    address_p nextMhs;
    address_r nextRelasi;
};

struct List_Relasi {
    address_r firstRelasi;
};

void createListMhs(List_p &L);
void createListBuku(List_c &L);
void createListRelasi(List_Relasi &L);

address_p createElementMhs(infotype_p x);
address_c createElementBuku(infotype_c x);
address_r createElementRelasi(address_p P, address_c C);

void insertFirstMhs(List_p &L, address_p P);
void insertFirstBuku(List_c &L, address_c P);
void insertFirstRelasi(List_Relasi &L, address_r R);

void printInfoMhs(List_p L);
void printInfoBuku(List_c L);

address_p findElementMhs(List_p L, string nim);
void makeRelasi(List_Relasi &L, address_p P, address_c C);
List_c findElementBuku(List_Relasi L, string judul);
address_p findMhs(List_p P, string nama);

bool deleteBuku(List_Relasi &L, List_c &C, string judul);
bool deleteMhs(List_Relasi &L, List_p &P, string nama);
void deleteMhs_BK(List_Relasi &L, List_p &P, List_c &C,  string nama);
void deleteRelasi_MHS_BK(List_Relasi &L, List_c C, string judul);
void deleteRelasi(List_Relasi &L, address_r R);

void showSemuaBukuDanMhs(List_Relasi L);
void showBukuTerfavorite(List_Relasi L);
void showMhsRajinMembaca(List_Relasi L);

#endif // OPLIB_H_INCLUDED
