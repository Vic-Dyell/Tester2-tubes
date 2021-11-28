#include "boolean.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

int main (){
    int n = 5;
    int i;
    MAP peta;
    Portal P;
    createEmptyMap(&peta);
    P = setPortal(P, n);

    printf("\n");
    peta.contents[1] = '.'; 
    peta.contents[2] = '.'; 
    peta.contents[3] = '.'; 
    peta.contents[4] = '#'; 
    peta.contents[5] = '.'; 
    peta.nEffM = 5; 

    ArrayP Pl;
    CreateEmptyPlayer(&Pl);
    Pl = inputPlayer(Pl, 1);
    Pl = inputPlayer(Pl, 2);
    int posisiawal = Pl.contents[1].position;
    int posisiakhir = MovePlayer(&Pl, 2, peta, 1, P); // maju 2 langkah
    printf("%d %d\n", posisiawal, posisiakhir);
    PrintPeringkat(Pl, 2);
}