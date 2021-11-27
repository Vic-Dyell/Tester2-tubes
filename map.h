
#ifndef MAP_H
#define MAP_H

#include "boolean.h"
#include <time.h>

/*Ukuran panjang maksimum peta*/
#define MAX_Length 100

typedef char ElTypeMap;
typedef int ElTypePortal;
typedef struct {
    ElTypeMap contents [MAX_Length];
    int nEffM;
} MAP;
typedef struct {
    ElTypePortal contents [MAX_Length];
    int Neff;
} Portal;

/* SELEKTOR MAP */
// #define Length(M) (M).nEffM


boolean IsPortalEmpty (Portal P);
/* Mengirimkan true jika portal kosong */

/* PRIMITIF MAP */

/* *** Konstruktor membentuk MAP *** */
void createEmptyMap (MAP *M);
/* I.S. Sebuah array map M terdefinisi*/
/* F.S. Sebuah array map M dengan ukuran nEff = 0 terbentuk*/

void displayMap (MAP M, int posisi);
/* I.S. Sebuah MAP M terdefinisi*/
/* F.S. Nilai dari array Map M ditulis ke layar */

void copyMap (MAP *M1, MAP M2);
/* I.S. Sebuah MAP M1 terdefinisi*/
/* F.S. Sebuah MAP M2 akan terisi sama elemennya seperti MAP M1*/

void createEmptyPortal (Portal *P);
/* I.S. Sebuah nilai n valid untuk memori MAP*/ 
/* F.S. Sebuah array  Portal P dengan ukuran nEff = 0  terbentuk*/

Portal setPortal(Portal P, int n);
/* I.S Sebuah portal terdefinisi*/
/* F.S. Portal P dengan Neff n akan terisi dengan -1 */

int roll (time_t y, int maksdadu);
/* Untuk merandom dadu */

#endif