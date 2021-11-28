#ifndef status_H
#define status_H

#include "boolean.h"
#include "listskill.h"
#include "player.h"
#include "map.h"

#define IdxMax 4
#define IdxUndef -999 /* indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int IdxType;

typedef struct
{
    ArrayP Pl;
    MAP contentsMapPlayer; // menyimpan MAP dari setiap pemain yang bermain
    Portal Por; // Portal yang terdapat pada peta
    int Neff; // banyaknya elemen aktif 
    int ronde; // ronde dalam permainan
} status;

/* SELEKTOR MAP */
#define Length(s) (s).Neff

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create status kosong */
void MakeEmpty (status *s);
/* I.S. sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int Nbstatus (status s);
/* Mengirimkan banyaknya elemen efektif status*/
/* Mengirimkan nol jika kosong */
/* *** Daya tampung container *** */
int MaxElmt (status s);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh status */

/* *** Selektor SET : Mengubah nilai status dan elemen status *** */
/* Untuk type private/limited private pada bahasa tertentu */
void Setstatus (status s, status *s_copy);
/* I.S. s terdefinisi, sembarang */
/* F.S. s_copy berisi salinan s*/
void SetPlayer (status *s, IdxType i, Player P);
/* I.S. s terdefinisi, sembarang */
/* F.S. Elemen s yang ke-i bernilai P */
/* Mengeset nilai elemen status yang ke-i sehingga bernilai P */

void SetNeff (status *s, IdxType i);
/* I.S. s terdefinisi, sembarang */
/* F.S. Nilai indeks efektif s bernilai i */
/* Mengeset nilai indeks elemen efektif sehingga bernilai i */

void SetRonde (status *s, IdxType i);
/* I.S. s terdefinisi, sembarang */
/* F.S. Nilai berupa ronde i yang sedang berlangsung */
/* Mengeset nilai ronde sehingga bernilai i */

void NextRonde (status *s);
/* I.S. s terdefinisi, sembarang */
/* F.S. Permainan berlanjut ke ronde berikutnya */

void UndoRonde (status *s);
/* I.S. s terdefinisi, sembarang */
/* F.S. ronde dikembalikan ke ronde sebelumnya*/
/*Jika kondisi awal berada di ronde 1 maka ronde akan bernilai IdxUndef*/

/*Command inspect*/
void inspect(Portal P, MAP M, int petak);
/* Melakukan pencetakan apakah petak yang di input memiliki telporter atau penghalang*/

#endif
