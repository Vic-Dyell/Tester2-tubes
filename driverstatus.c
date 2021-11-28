#include "status.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    status S, s_copy;

    MakeEmpty(&S);

    // Tes setNeff
    SetNeff(&S,2);
    if (S.Neff == 2){
        printf("Tes setNeff Berhasil\n");
    }

    // Tes Set Ronde
    SetRonde(&S, 1);
    if (S.ronde == 1){
        printf("Tes SetRonde Berhasil\n");
    }

    // Tes Next Ronde
    NextRonde(&S);
    if (S.ronde == 2){
        printf("Tes NextRonde Berhasil\n");
    }

    // Tes UndoRonde
    UndoRonde(&S);
    if (S.ronde == 1){
        printf("Tes UndoRonde Berhasil\n");
    }

    //Tes Nbstatus
    printf("Hasil tes Nbstatus: %d\n",Nbstatus(S));

    // Tes MaxElmt
    printf("Hasil tes MaxElmt: %d\n", MaxElmt(S));

    // Tes GetLastIdx 
    printf("Hasil tes GetLastIdx: %d\n", GetLastIdx(S));

    // Tes SetPlayer
    ArrayP Pl;
    Player P;
    P.playerName[50] = "Pemain 1";
    SetPlayer(&S, 1, P);
    if ((S).Pl.contents[1].playerName[50] == P.playerName[50]){
        printf("Tes SetPlayer Berhasil \n");

    }

    // Tes SetStatus
    Setstatus(S, &s_copy);
    if (S.Pl.contents[1].playerName[50] == s_copy.Pl.contents[1].playerName[50])
    {
        printf("Tes SetStatus Berhasil \n");
    }

    //Tes GetPlayerIdx
    printf("Hasil GetPlayerIdx: %d\n",GetPlayerIdx(S,P));
}