#include "listskill.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (Listskill L){
    return (First(L)==Nil && Last(L)==Nil);
}
/* Mengirim true jika list kosong. Lihat definisi di atas. */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptySkill (Listskill *L){
    First(*L)=Nil;
    Last(*L)=Nil;
}
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
address Alokasi (infotype X){
    address P;
    P = (ElmtList *) malloc(sizeof(ElmtList));
    if (P != Nil) {
        Info (P) = X;
        Next (P) = Nil;
        Prev(P) = Nil;
        return P;    
    }
    else {
        return Nil;
    }
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
void Dealokasi (address P){
    free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (Listskill *L, infotype X){
    address P;
    P = Alokasi(X);
    if (P != Nil) {
        InsertFirst(L, P);
    }
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (Listskill *L, infotype X){
    address P = Alokasi(X);
    if (P != Nil){
        InsertLast(L, P);
    }    
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (Listskill *L, infotype *X){
    address P;
    DelFirst(L, &P);
    *X = Info(P);
    Dealokasi(P);
}
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast (Listskill *L, infotype *X){
    address P;
    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(P);
}
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (Listskill *L, address P){
    if (IsEmpty(*L)) {
        First(*L) = P;
        Last(*L) = P;
        Prev(P) = Nil;
        Next(P) = Nil;
    }
    else {
        Prev(P) = Nil;
        Prev(First(*L)) = P;
        Next(P) = First(*L);
        First(*L) = P;
    }    
}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsertLast (Listskill *L, address P){
    if (IsEmpty(*L)) {
        InsertFirst(L, P);
    }
    else {
        Next(P) = Nil;
        Next(Last(*L)) = P;
        Prev(P) = Last(*L);
        Last(*L) = P;
    }

}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertAfter (Listskill *L, address P, address Prec){
    if (Prec == Last(*L)) {
        InsertLast(L, P) ;
    }
    else {
        Next(P) = Next(Prec) ;
        Next(Prec) = P ;
        Prev(P) = Prec ;
        Prev(Next(P)) = P ;
    }    
}
/* I.S. Prec pastilah elemen list; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (Listskill *L, address *P){
    *P = First(*L);
    First(*L) = Next(First(*L));
    if (First(*L)==Nil){
        Last(*L)=Nil;
    }
    else {
        Next(*P) = Nil;
        Prev(First(*L))=Nil;
    }
}
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelLast (Listskill *L, address *P){
    if (Prev(Last(*L)) == Nil) {
        DelFirst(L,P);
    }
    else {
        DelAfter(L,P, Prev(Last(*L)));
    }    
}
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */
void DelAfter (Listskill *L, address *Pdel, address Prec){
    *Pdel = Next(Prec);
    Next(Prec) = Next(*Pdel);
    if (Next(*Pdel)!=Nil){
        Prev(Next(*Pdel)) = Prec;
    }
    else {
        Last(*L)=Prec;
    }
    Next(*Pdel) = Nil;
    Prev(*Pdel) = Nil;
}
/* I.S. List tidak kosong. Prec adalah anggota list. */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */


int rskill (time_t t){ // 0-9
    return rand() % 10;
}

int NbElmt (Listskill L){
    address P;
    P = First(L);
    int count;
    count = 0;
    while (P!=Nil){
        count = count + 1;
        P = Next(P);
    }
    return count;
}

void DelI (Listskill *L, int n){
    address P;
    P = First(*L);
    int i;
    i = 0;
    if (n==1){
        DelFirst(L, &P);
    }
    else if (n==NbElmt(*L)){
        DelLast(L, &Last(*L));
    }
    else {
        while (i<n){
            i = i + 1;
            P = Next(P);
        }
        P = Prev(P);
        DelAfter(L, &P, Prev(P));
    }    
}

void nambahskill (Listskill *L, int r){ // r di sini diambil dari randomize
    int skill1;
    if (r==0){
        skill1 = 1; // id skill 1 : Pintu Ga Ke Mana-Mana
        printf ("Selamat Anda mendapatkan Pintu Ga Ke Mana-Mana \n");
    }
    else if (r==1){ 
        skill1 = 2; // id skill 2 : Cermin Pengganda
        printf ("Selamat Anda mendapatkan Cermin Pengganda \n");
    }
    else if (r==2 || r==3){ 
        skill1 = 3; // id skill 3 : Senter Pembesar Hoki
        printf ("Selamat Anda mendapatkan Senter Pembesar Hoki \n");
    }
    else if (r==4 || r==5){ 
        skill1 = 4; // id skill 4 : Senter Pengecil Hoki
        printf ("Selamat Anda mendapatkan Senter Pengecil Hoki \n");
    }
    else if (r==6){ 
        skill1 = 5; // id skill 5 : Mesin Penukar Hoki
        printf ("Selamat Anda mendapatkan Mesin Penukar Posisi \n");
    }  
    else if (r==7 || r==8 || r==9){ 
        skill1 = 0; // skill 6 ga masuk ke list
        printf("Sayang sekali... Anda mendapatkan Teknologi Gagal \n");
    }    

    // harusnya udah dapet id skillnya
    if (skill1!=0 && NbElmt(*L)<10){
        InsVLast(L, skill1);
    } 
    else if (NbElmt(*L)>=10){
        printf("Jumlah skill yang dimiliki sudah mencapai maksimum\n");
    }
}

void buangskill (Listskill *L, int x){
    if (IsEmpty(*L)) {
        printf("Anda tidak mempunyai skill \n");    
    }
    else {
        x = abs(x);
        DelI(L, x);
    }
}    

void printskill (Listskill L){
    address CP;
    if (IsEmpty(L)){
        printf("Kamu belum memiliki skill apapun \n");
    }    
    else {    
        int i = 1;
        CP = First(L);
        printf("Kamu memiliki skill: \n");
        while (CP!=Nil) {
            printf("%d. ", i);
            if (Info(CP)==1){
                printf("Pintu Ga Kemana-Mana\n");
            }
            else if (Info(CP)==2){
                printf("Cermin Pengganda\n");
            }   
            else if (Info(CP)==3){
                printf("Senter Pembesar Hoki\n");
            }
            else if (Info(CP)==4){
                printf("Senter Pengecil Hoki\n");
            }
            else if (Info(CP)==5){
                printf("Mesin Penukar Hoki\n");
            }
            CP = Next(CP);
            i = i+1;
        }
        printf("Tekan 0 untuk keluar. Masukkan bilangan negatif untuk membuang skill.\n"); 
    }
}

int lihatisi (Listskill L, infotype X){
    address P;
    if (X==1){
        return (Info(First(L)));
    }
    else{
        int i = 1;
        P = First(L);
        while (i<X){
            P = Next(P);
            i = i+1;
        }
        return Info(P);
    }
}