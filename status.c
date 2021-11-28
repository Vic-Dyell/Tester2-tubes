#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "player.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create status kosong */
void MakeEmpty (status *s){
/* I.S. sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
    MAP mp;
    Portal pr;
    ArrayP py;
    int ronde;
    createEmptyMap(&mp);
    createEmptyPortal(&pr);
    CreateEmptyPlayer(&py);
    (*s).ronde = 1;
    (*s).Neff = 0;
    (*s).Pl = py;
    (*s).Por = pr;
    (*s).contentsMapPlayer = mp;
}

int Nbstatus (status s){
/* Mengirimkan banyaknya elemen efektif status */
/* Mengirimkan nol jika kosong */
/* *** Daya tampung container *** */
    return (s).Neff;
}

int MaxElmt (status s){
/* Mengirimkan maksimum elemen yang dapat ditampung oleh status */
/* *** Selektor INDEKS *** */
    return IdxMax;
}

/* *** Selektor SET : Mengubah nilai status dan elemen status *** */
/* Untuk type private/limited private pada bahasa tertentu */
void Setstatus (status s, status *s_copy){
/* I.S. s terdefinisi, sembarang */
/* F.S. s_copy berisi salinan s*/
    int i;
    for(i = 1; i <= IdxMax; i++){
        (*s_copy).Pl.contents[i].position = s.Pl.contents[i].position;
        (*s_copy).Pl.contents[i].skill = s.Pl.contents[i].skill;
        (*s_copy).Pl.contents[i].playerBuff.isCerminPengganda = s.Pl.contents[i].playerBuff.isCerminPengganda;
        (*s_copy).Pl.contents[i].playerBuff.isImun = s.Pl.contents[i].playerBuff.isImun;
        (*s_copy).Pl.contents[i].playerBuff.isSenterPembesar = s.Pl.contents[i].playerBuff.isSenterPembesar;
        (*s_copy).Pl.contents[i].playerBuff.isSenterPengecil = s.Pl.contents[i].playerBuff.isSenterPengecil;
    }
    (*s_copy).ronde = s.ronde;
    (*s_copy).Por = s.Por;
    (*s_copy).Neff = s.Neff;
    (*s_copy).contentsMapPlayer = s.contentsMapPlayer;
}

void SetPlayer (status *s, IdxType i, Player P){
/* I.S. s terdefinisi, sembarang */
/* F.S. Elemen s yang ke-i bernilai P */
/* Mengeset nilai elemen status yang ke-i sehingga bernilai P */
    (*s).Pl.contents[i] = P;
}

void SetNeff (status *s, IdxType i){
/* I.S. s terdefinisi, sembarang */
/* F.S. Nilai indeks efektif s bernilai i */
/* Mengeset nilai indeks elemen efektif sehingga bernilai i */
    (*s).Neff = i;
}

void SetRonde (status *s, IdxType i){
/* I.S. s terdefinisi, sembarang */
/* F.S. Nilai berupa ronde i yang sedang berlangsung */
/* Mengeset nilai ronde sehingga bernilai i */
    (*s).ronde = i;
}

void NextRonde (status *s){
/* I.S. s terdefinisi, sembarang */
/* F.S. Permainan berlanjut ke ronde berikutnya */
    (*s).ronde += 1;

}


void UndoRonde (status *s){
/* I.S. s terdefinisi, sembarang */
/* F.S. ronde dikembalikan ke ronde sebelumnya*/
/*Jika kondisi awal berada di ronde 1 maka ronde akan bernilai IdxUndef*/
    if ((*s).ronde == 1){ //jika berada di ronde 1 maka undo akan menjadi IdxUndef
        (*s).ronde = IdxUndef;
    }
    else{
        (*s).ronde -= 1;
    }

}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */

/* ********** TEST Teleporter & Penghalang ********** */
/* Test Teleporter*/
// boolean isTeleporter(status s, int rollDadu){ 
// /* Mengirimkan true jika ada teleporter, dan false jika tidak*/
//     return (s.Por.contents[rollDadu] != -1);
// }

// /*Test Penghalang*/
// boolean isPenghalang(status s, int rollDadu, IdxType i){
// /* Mengirimkan true jika ada penghalang, dan false jika tidak*/
//     return (s.contentsMapPlayer[i].contents[rollDadu] == '#');
// }

/* Posisi pemain */
/*Mengembalikan posisi pemain ditandai dengan tanda (*) pada MAP*/
// int posisi(status s, IdxType i) { 
//     char nilai_posisi = '*';
//     int j;
//     for (j = 1; j<= Length(s); j++){
//         if(s.contentsMapPlayer[i].contents[j] == nilai_posisi){
//             return j;
//         }
//     }
// }

/* Implementasi command map & inspect*/
/*Command MAP */
// void map(status s){
// /*Melakukan pencetakan nama pemain, peta, dan posisi pemain*/
//     int i;
//     for (i = 1; i <= Length(s); i++){
//         printf("%s : %s %d", s.P.contents[i].playerName, s.contentsMapPlayer[i].contents, posisi(s,i));
//     }
// }

/*Command inspect*/
void inspect(Portal P, MAP M, int petak){
/* Melakukan pencetakan apakah petak yang di input memiliki telporter atau penghalang*/


    // petak memiliki teleporter
    if (P.contents[petak] != -1){ // -1 menunjukkan petak tidak memiliki teleporter
        printf("Petak %d memiliki teleporter menuju %d.\n", petak, P.contents[petak]);
    }

    else if (M.contents[petak] == '#'){
        printf("Petak %d merupakan petak terlarang.\n", petak);
    }
    
    else if((M.contents[petak] == '.') && (P.contents[petak] == -1)){
        printf("Petak %d merupakan petak kosong.\n", petak);
    }
}



