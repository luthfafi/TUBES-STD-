#include "oplib.h"

void createListMhs(List_p &L){
    firstMhs(L) = nil;
}

void createListBuku(List_c &L){
    firstBuku(L) = nil;
}

void createListRelasi(List_Relasi &L){
    firstRelasi(L) = nil;
}

address_p createElementMhs(infotype_p x){
    address_p P = new elm_p;
    infoMhs(P) = x;
    nextMhs(P) = nil;
    return P;
}

address_c createElementBuku(infotype_c x){
    address_c P = new elm_c;
    infoBuku(P) = x;
    nextBuku(P) = nil;
    return P;
}

address_r createElementRelasi(address_p P, address_c C){
    address_r R = new elm_r;
    nextMhs(R) = P;
    nextBuku(R) = C;
    nextRelasi(R) = nil;

    return R;
}

void insertFirstMhs(List_p &L, address_p P){
    nextMhs(P) = firstMhs(L);
    firstMhs(L) = P;
}

void insertFirstBuku(List_c &L, address_c P){
    nextBuku(P) = firstBuku(L);
    firstBuku(L) = P;
}

void insertFirstRelasi(List_Relasi &L, address_r R){
    nextRelasi(R) = firstRelasi(L);
    firstRelasi(L) = R;
}

void printInfoMhs(List_p L){
    address_p P = firstMhs(L);
    cout<<"List Parent"<<endl;
    while (P != nil){
        cout<<infoMhs(P).nama<<" "<<infoMhs(P).nim<<" "<<infoMhs(P).kelas<<endl;
        P = nextMhs(P);
    }
    cout<<endl<<endl;
}

void printInfoBuku(List_c L){
    address_c P = firstBuku(L);
    cout<<"List Child"<<endl;
    while (P != nil){
        cout<<infoBuku(P).judul<<" "<<infoBuku(P).kode<<endl;
        P = nextBuku(P);
    }
    cout<<endl<<endl;
}

address_p findElementMhs(List_p L, string nim){
    address_p S = firstMhs(L);
    while (S != nil){
        if(infoMhs(S).nim == nim){
            return S;
        }
    }
    return nil;
}

List_c findElementBuku(List_Relasi L, string nama){
    List_c cariBuku;
    createListBuku(cariBuku);

    if (firstRelasi(L) == nil){
        return cariBuku;
    }

    address_r R = firstRelasi(L);
    while (R != nil) {
        if (infoMhs(nextMhs(R)).nama == nama){
            address_c Q = createElementBuku(infoBuku(nextBuku(R)));
            insertFirstBuku(cariBuku, Q);
        }
        R = nextRelasi(R);
    }

    return cariBuku;
}

address_p findMhs(List_p P, string nama){
    address_p Q = firstMhs(P);
    while (nextMhs(Q) != nil) {
        if (infoMhs(Q).nama == nama) {
            return Q;
        }
        Q = nextMhs(Q);
    }

    if (infoMhs(Q).nama == nama) {
        return Q;
    }

    return nil;
}


void makeRelasi(List_Relasi &L, address_p P, address_c C){
    address_r R = createElementRelasi(P, C);
    if (firstRelasi(L) == nil) {
        insertFirstRelasi(L, R);
    } else {
        address_r Q = firstRelasi(L);
        while (nextRelasi(Q) != nil) {
            Q = nextRelasi(Q);
        }
        nextRelasi(Q) = R;
    }
}

bool deleteBuku(List_Relasi &L, List_c &C, string judul){
    address_c curr = firstBuku(C);
    address_c prev = nil;
    while (curr != nil && infoBuku(curr).judul != judul) {
        prev = curr;
        curr = nextBuku(curr);
    }
    if (curr == nil) {
        return false;
    }
    if (prev == nil) {
        firstBuku(C) = nextBuku(curr);
    } else {
        nextBuku(prev) = nextBuku(curr);
    }
    nextBuku(curr) = nil;
    address_r curr_rel = firstRelasi(L);
    address_r prev_rel = nil;
    while (curr_rel != nil) {
        if (nextBuku(curr_rel) == curr) {
            if (prev_rel == nil) {
                firstRelasi(L) = nextRelasi(curr_rel);
                prev_rel = firstRelasi(L);
            } else {
                nextRelasi(prev_rel) = nextRelasi(curr_rel);
                prev_rel = nextRelasi(curr_rel);
            }
        } else {
            prev_rel = curr_rel;
        }
        curr_rel = nextRelasi(curr_rel);
    }

    return true;
}



bool deleteMhs(List_Relasi &L, List_p &P, string nama){
    address_p curr = firstMhs(P);
    while (curr != nil && infoMhs(curr).nama != nama) {
            curr = nextMhs(curr);
    }
    if (curr == nil) {
        return false;
    }
    if (curr == firstMhs(P)) {
        firstMhs(P) = nextMhs(curr);
    } else {
        address_p temp = firstMhs(P);
        while (nextMhs(temp) != curr) {
            temp = nextMhs(temp);
        }
        nextMhs(temp) = nextMhs(curr);
        }

        address_r curr_rel = firstRelasi(L);
        while (curr_rel != nil) {
            if (nextMhs(curr_rel) == curr) {
                if (nextRelasi(curr_rel) == firstRelasi(L)) {
                    firstRelasi(L) = nextRelasi(curr_rel);
                } else {
                    address_r temp_rel = firstRelasi(L);
                    while (nextRelasi(temp_rel) != curr_rel) {
                        temp_rel = nextRelasi(temp_rel);
                    }
                    nextRelasi(temp_rel) = nextRelasi(curr_rel);
                    }
                }
                curr_rel = nextRelasi(curr_rel);
        }
        return true;
}


void deleteMhs_BK(List_Relasi &L, List_p &P, List_c &C,  string nama) {
    address_p SW = findMhs(P, nama);
    if (SW != nil && firstRelasi(L) != nil) {
        address_r Q, prec;
        Q = firstRelasi(L);
        prec = nil;
        while (Q != nil) {
            prec = Q;
            Q = next(Q);
            if (nextMhs(prec) == SW) {
                deleteMhs(L, P, infoMhs(nextMhs(prec)).nama);
                Q = firstRelasi(L);
            }
        }
    } else {
        cout << "Mahasiswa tidak ditemukan" << endl;
    }
}

void deleteRelasi(List_Relasi &L, address_r R){
    if (firstRelasi(L) == nil){
        return;
    }

    address_r curr = firstRelasi(L);
    while (curr != nil && curr != R) {
        curr = nextRelasi(curr);
    }
    if (curr == nil) {
        return;
    }
    if (curr == firstRelasi(L)) {
        firstRelasi(L) = nextRelasi(curr);
    } else {
        address_r prev = firstRelasi(L);
        while (nextRelasi(prev) != curr) {
            prev = nextRelasi(prev);
        }
        nextRelasi(prev) = nextRelasi(curr);
    }
    nextRelasi(curr) = nil;
}



void deleteRelasi_MHS_BK(List_Relasi &L, List_c C, string judul){
    address_r curr = firstRelasi(L), x;
    while (true){
        x = nextRelasi(curr);
        if (infoBuku(nextBuku(curr)).judul == judul){
            if (curr == firstRelasi(L)) {
                firstRelasi(L) = nextRelasi(curr);
            } else {
                address_r prev = firstRelasi(L);
                while (nextRelasi(prev) != curr) {
                    prev = nextRelasi(prev);
                }
                nextRelasi(prev) = nextRelasi(curr);
            }
            deleteRelasi(L, curr);
            return;
        }
        curr = x;
        if (curr == firstRelasi(L)){
            break;
        }
    }
}


void showSemuaBukuDanMhs(List_Relasi L){
     if (firstRelasi(L) != nil) {
        address_r X = firstRelasi(L);
        while (nextRelasi(X) != nil) {
            cout << infoBuku(nextBuku(X)).judul << " - " << infoMhs(nextMhs(X)).nama<< endl;
            X = nextRelasi(X);
        }
        cout << infoBuku(nextBuku(X)).judul<< " - " << infoMhs(nextMhs(X)).nama << endl;
    }
}


void showBukuTerfavorite(List_Relasi L){
    if (firstRelasi(L) == nil) {
        cout << "Tidak ada buku favorite" << endl;
        return;
    }

    address_r X = firstRelasi(L);
    address_r maxRelasi = X;
    int maxY = 0;

    while (nextRelasi(X) != nil) {
        int count = 0;
        address_r Z = X;
        while (Z != nil && nextBuku(Z) == nextBuku(X)) {
            count++;
            Z = nextRelasi(Z);
        }

        if (count > maxY) {
            maxY = count;
            maxRelasi = X;
        }
        X = nextRelasi(X);
       }
        cout << "Buku Terfavorite di kalangan mahasiswa : " << infoBuku(nextBuku(maxRelasi)).judul << endl;
        cout << "Kode: " << infoBuku(nextBuku(maxRelasi)).kode << endl;
}

void showMhsRajinMembaca(List_Relasi L){
    if (firstRelasi(L) == nil) {
        cout << "Tidak ada Mahasiswa yang rajin membaca" << endl;
        return;
    }

    address_r current = firstRelasi(L);
    address_r maxRelasi = current;
    int maxCount = 0;

    while (nextRelasi(current) != nil) {
        int count = 0;
        address_r temp = current;
        while (temp != nil && nextMhs(temp) == nextMhs(current)) {
            count++;
            temp = nextRelasi(temp);
        }

        if (count > maxCount) {
            maxCount = count;
            maxRelasi = current;
        }
        current = nextRelasi(current);
    }
    cout << "Mahasiswa yang Rajin Membaca : "<< infoMhs(nextMhs(maxRelasi)).nama << endl;
}
