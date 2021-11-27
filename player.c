/* File : pemain.c */

#include "player.h"
#include "listskill.h"
#include <stdio.h>
#include <stdlib.h>

/*** Konstruktor Player ***/
void CreateEmptyPlayer (ArrayP *P)
{
    /* ALGORITMA */
    (*P).Neff = 0;
}

ArrayP inputPlayer (ArrayP P, int i) 
{
    Listskill S;
    CreateEmptySkill(&S);
    printf("Masukkan nama: ");
    scanf("%s", P.contents[i].playerName);
    P.contents[i].playerBuff.isCerminPengganda = false;
    P.contents[i].playerBuff.isImun = false;
    P.contents[i].playerBuff.isSenterPembesar = false;
    P.contents[i].playerBuff.isSenterPengecil = false;
    P.contents[i].skill = S;
    P.contents[i].position = 1;

    return P;
}

void PrintSkill (Listskill S)
{   
    printskill(S);
}

int MovePlayer (ArrayP *P, int ndadu, MAP M, int i, Portal ptl) 
{
    int currPosition;
    int x;
    char pakaiImun;

    currPosition = P->contents[i].position;

    if ((currPosition + ndadu) <= M.nEffM) {
        if (M.contents[currPosition + ndadu] == '#' && (M.contents[currPosition - ndadu] == '#' || currPosition - ndadu <= 0)) {
            printf("Anda tidak bisa kemana-mana\n");
            return currPosition;
        } 
        else if (M.contents[currPosition + ndadu] == '#' && M.contents[currPosition - ndadu] != '#' && currPosition - ndadu > 0) { // hanya bisa mundur
            printf("Anda hanya bisa melangkah mundur\n");
            currPosition = currPosition - ndadu;
            if (ptl.contents[currPosition] != -1){
                if (P->contents[i].playerBuff.isImun == true) {
                    printf("Apakah Anda ingin menggunakana buff Imunitas Teleport? (Y/N): \n");
                    scanf(" %c", &pakaiImun);
                    if (pakaiImun == 'Y') {
                        return currPosition;
                    } 
                }    
                else { //pakaiImun = N
                    currPosition = ptl.contents[currPosition];
                    printf("Anda memasuki portal menuju ke posisi %d\n", currPosition);
                    return currPosition;
                }
            } 
            return currPosition;   
        }
        else if (M.contents[currPosition + ndadu] != '#' && (M.contents[currPosition - ndadu] == '#' || currPosition - ndadu <= 0)){  // hanya bisa maju
            printf("Anda hanya bisa melangkah maju\n");
            currPosition = currPosition + ndadu;
            if (ptl.contents[currPosition] != -1){
                if (P->contents[i].playerBuff.isImun == true) {
                    printf("Apakah Anda ingin menggunakana buff Imunitas Teleport? (Y/N): \n");
                    scanf(" %c", &pakaiImun);
                    if (pakaiImun == 'Y') {
                        return currPosition;
                    } 
                }    
                else { //pakaiImun = N
                    currPosition = ptl.contents[currPosition];
                    printf("Anda memasuki portal menuju ke posisi %d\n", currPosition);
                    return currPosition;
                }    
            } 
            return currPosition; 
        }    
        else if (M.contents[currPosition + ndadu] != '#' && M.contents[currPosition - ndadu] != '#' && currPosition - ndadu > 0){ //bisa maju dan mundur
            printf("1. Maju\n");
            printf("2. Mundur\n");
            printf("Pilih perintah yang Anda inginkan : ");
            scanf("%d", &x);
            while (x != 1 && x != 2){
                printf("Masukkan salah!\n");
                printf("1. Maju\n");
                printf("2. Mundur\n");
                printf("Pilih perintah yang Anda inginkan : ");
                scanf("%d", &x);
            }

            if (x == 1) {
                printf("Anda memilih untuk maju!\n");
                currPosition = currPosition + ndadu;
                if (ptl.contents[currPosition] != -1){
                    if (P->contents[i].playerBuff.isImun == true) {
                        printf("Apakah Anda ingin menggunakana buff Imunitas Teleport? (Y/N): \n");
                        scanf(" %c", &pakaiImun);
                        if (pakaiImun == 'Y') {
                            return currPosition;
                        } 
                    }    
                    else { //pakaiImun = N
                        currPosition = ptl.contents[currPosition];
                        printf("Anda memasuki portal menuju ke posisi %d\n", currPosition);
                        return currPosition;
                    }    
                } 
                return currPosition;
            } 
           
            else if (x == 2) {
                printf("Anda memilih untuk mundur\n");
                currPosition = currPosition - ndadu;
                if (ptl.contents[currPosition] != -1){
                    if (P->contents[i].playerBuff.isImun == true) {
                        printf("Apakah Anda ingin menggunakana buff Imunitas Teleport? (Y/N): ");
                        scanf("%c", &pakaiImun);
                        if (pakaiImun == 'Y') {
                            return currPosition;
                        } 
                    }    
                    else { //pakaiImun = N
                        currPosition = ptl.contents[currPosition];
                        printf("Anda memasuki portal menuju ke posisi %d\n", currPosition);
                        return currPosition;
                    }
                } 
                return currPosition;
            }
        } 
    } 
    else {
        printf("Anda tidak bisa kemana-mana.\n");
        return currPosition; 
    }     
}


void swapint(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapplay(Player *xp, Player *yp){
    Player temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void PrintPeringkat(ArrayP P, int i){
    int posisi[i];
    
    for (int c = 1; c <= i; c++){
        posisi[c] = P.contents[c].position;
    }
    
    // sorting
    int a, b, max_idx;
 
    // One by one move boundary of unsorted subarray
    for (a = 1; a <= i-1; a++)
    {
        // Find the minimum element in unsorted array
        max_idx = a;
        for (b = a+1; b <= i; b++)
          if (posisi[b] > posisi[max_idx])
            max_idx = b;
 
        // Swap the found minimum element with the first element
        swapint(&posisi[max_idx], &posisi[a]);
        swapplay(&P.contents[max_idx], &P.contents[a]);
    }

    printf("Peringkat Akhir Pemainan\n");
    for (int f = 1; f <= i; f++){
         printf("%d. %s\n", f, P.contents[f].playerName);
    }
}
