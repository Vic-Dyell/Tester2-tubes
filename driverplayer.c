#include "mesin_kata.h"
#include "listskill.h"
#include "boolean.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main (){
    int n = 5;
    int i;
    MAP peta;
    Portal P;
    createEmptyMap(&peta);
    P = setPortal(P, n);
    for (i=0; i<n; i++){
        printf("%d", P.contents[i]);
    }
    printf("\n");
    peta.contents[0] = '.'; 
    peta.contents[1] = '.'; 
    peta.contents[2] = '.'; 
    peta.contents[3] = '#'; 
    peta.contents[4] = '.'; 
    peta.nEffM = 5; 
    int j;
    for (j=0; j<peta.nEffM; j++){
        printf("%c ", peta.contents[j]);
    }

    ArrayP Pl;
    CreateEmptyPlayer(&Pl);
    Pl = inputPlayer(Pl, 1);
    //MovePlayer(&Pl, 2, peta, 1, P);
    displayMap(peta, Pl.contents[1].position);
}