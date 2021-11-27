#include "mesin_kata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank()
{
  while ((CC == BLANK1)||(CC == BLANK2)) {
    ADV();
  }
}

void STARTKATA(char * C)
{
  START(C);
  IgnoreBlank();
  SalinKata();
}

void ADVKATA()
{
  IgnoreBlank();
  SalinKata();
  IgnoreBlank();
}

void SalinKata()
{
    int i = 1;
    while ((CC != BLANK1) && (CC != BLANK2) && (i <= NMax)) {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    }
    CKata.Length = i;
}

void PrintKata (Kata K)
{
  int i = 1;
  while (i<K.Length){
    printf("%c", K.TabKata[i]);
    i++;
  }
}

int KataToInt (Kata K){
  int val = 0;
  int i = 0;
  while (i<K.Length){
    val = val * 10;
    switch (K.TabKata[i]){
      case '0' : val += 0; break;
      case '1' : val += 1; break;
      case '2' : val += 2; break;
      case '3' : val += 3; break;
      case '4' : val += 4; break;
      case '5' : val += 5; break;
      case '6' : val += 6; break;
      case '7' : val += 7; break;
      case '8' : val += 8; break;
      case '9' : val += 9; break;
    };
    i++;
  }
  return val;
}
