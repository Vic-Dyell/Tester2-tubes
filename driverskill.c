// r1 atau r2 == 0 --> dapet id skill 1 yaitu pintu ga kemana-mana
// r1 atau r2 == 1 --> dapet id skill 2 yaitu cermin pengganda
// r1 atau r2 == 2||3 --> dapet id skill 3 yaitu senter pembesar hoki
// r1 atau r2 == 4||5 --> dapet id skill 4 yaitu senter pengecil hoki
// r1 atau r2 == 6 --> dapet id skill 5 yaitu mesin penukar hoki
// r1 atau r2 == 7||8||9 --> dapet id skill 0 yaitu pintu ga kemana-mana, namun tidak masuk ke dalam listskill

#include "listskill.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){
    Listskill L;
    int r1, r2, r3;
    time_t t1, t2, t3;
    CreateEmptySkill(&L);
    srand((unsigned) (time(&t1)));
    srand((unsigned) (time(&t2)));
    srand((unsigned) (time(&t3)));
    r1 = rskill(t1);
    r2 = rskill(t2);
    r3 = rskill(t3);
    nambahskill(&L, r1);
    nambahskill(&L, r2);
    nambahskill(&L, r2=3);
    printf("\n");
    printskill(L);
    buangskill(&L,1);
    printskill(L);
    printf("%d\n", NbElmt(L));
    printf("%d", lihatisi(L,1)); //isi pertama seharusnya indeks skill yang dihasilkan oleh r2 karena 
}