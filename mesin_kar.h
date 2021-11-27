#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#include "boolean.h"
#include "string.h"
/* State Mesin */
extern char CC;

void START(char * C);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC, CC != EOF
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = EOF
          Jika  CC = EOF maka config akan menutup */

#endif