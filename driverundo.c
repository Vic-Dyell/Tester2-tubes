#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "undo.h"
#include "status.h"

int main(){
    status stat, stat1;
    Stack stak;
    MakeEmpty(&stat);
    CreateEmpty(&stak);
    Push(&stak, stat);
    printf("%d\n", InfoTop(stak).Pl.contents[1].position);
    Pop(&stak,&stat1);
    printf("Akan keluar angka 1 setelah stack di pop\n");
    if (IsEmptyS(stak)){
        printf("%d\n", 1);
    }

}
