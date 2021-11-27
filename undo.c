#include "undo.h"
#include "status.h"


void CreateEmpty (Stack *S){
    Top(*S) = Nill;
}

boolean IsEmptyS (Stack S){
    return (Top(S) ==  Nill);
}
boolean IsFullS (Stack S){
    return (Top(S)== MaxEl);
}

void Push (Stack * S, infotipe X){
    status stat;
    MakeEmpty(&stat);
    Setstatus(X, &stat);
    Top(*S) += 1;
    InfoTop(*S) = stat;
}

void Pop (Stack * S, infotipe* X){
    *X = InfoTop(*S);
    Top(*S) -= 1;
}