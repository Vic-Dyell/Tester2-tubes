#include "mesin_kata.h"
#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main () {
    /*Deklarasi Variable*/
    int o, j, k, z;
    char arr [100];
    char input[100] = "map.txt";
    MAP M;
    Portal Pt;
    /*ALGORITMA*/
    createEmptyMap(&M);
    STARTKATA(input);
    M.nEffM = KataToInt(CKata);
    printf("%d\n", M.nEffM); 
    ADVKATA();
    PrintKata(CKata);
    for (o=1; o<M.nEffM+1;o++){
        M.contents[o] = CKata.TabKata[o];
        printf("%c",M.contents[o]); 
    }
    printf("\n");
    ADVKATA();
    int maksdadu;
    maksdadu = KataToInt(CKata);
    printf("%d\n", maksdadu);
    ADVKATA();
    int toto = KataToInt(CKata);
    Pt = setPortal(Pt, M.nEffM);
    for(j=1;j<M.nEffM;j++){
        printf("%d",Pt.contents[j]); 
    }
    printf("\n");
    for(k=0;k<toto;k++){
        ADVKATA();
        int temp = KataToInt(CKata);
        ADVKATA();
        int nportal = KataToInt(CKata);
        Pt.contents[temp] = nportal;
    }
    for(z=1;z<Pt.Neff;z++){
        printf("%d ",Pt.contents[z]);
    }
    printf("\n");
    printf("%d", Pt.contents[1]);
    printf("%d", Pt.contents[2]);
    printf("%d", Pt.contents[3]);
}