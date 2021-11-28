#include "mesin_kata.h"
#include "listskill.h"
#include "boolean.h"
#include "player.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <time.h>
#include <math.h>
#include "undo.h"

int main() {
    /*Baca map*/
    int o, k;
    char arr [100];
    char input[100] = "map.txt";
    MAP M;
    Portal Pt;
    status S;
    Stack st;
    
    MakeEmpty(&S);
    createEmptyMap(&M);
    CreateEmpty(&st);
    STARTKATA(input);
    M.nEffM = KataToInt(CKata);
    ADVKATA();
    for (o=1; o<M.nEffM+1;o++){
        M.contents[o] = CKata.TabKata[o];
    }
    ADVKATA();
    int maksdadu;
    maksdadu = KataToInt(CKata);
    ADVKATA();
    int toto = KataToInt(CKata);
    Pt = setPortal(Pt, M.nEffM);
    for(k=0;k<toto;k++){
        ADVKATA();
        int temp = KataToInt(CKata);
        ADVKATA();
        int nportal = KataToInt(CKata);
        Pt.contents[temp] = nportal;
    }
    /*Set Status*/
    S.Por.Neff = M.nEffM;
    S.contentsMapPlayer.nEffM = M.nEffM;
    int v;
    for (v=1; v<=M.nEffM;v++){
        S.Por.contents[v] = Pt.contents[v];
        S.contentsMapPlayer.contents[v] = M.contents[v];
    }

    SetRonde(&S, S.ronde);
    int npemain;
    int i;
    int mainmenu;
    int l;
    // MENU
    boolean endgame;
    endgame = false;
    printf("SELAMAT DATANG DIPERMAINAN MOBITANGGA\n");
    printf("MAIN MENU\n");
    printf("1. Let's play the game!\n");
    printf("2. Ah males dah.. exit aja lah\n");
    printf("Masukkan menu yang anda inginkan: ");
    scanf("%d", &mainmenu);
    if(mainmenu==2){
        endgame = true;
        printf("DADAAHHHHH\n");
    }
    else{
        printf("PERMAINAN DIMULAI\n");    
        printf("Silahkan masukkan jumlah pemain: ");
        scanf("%d", &npemain);
         // MASUKIN KE LIST OF PLAYER
        ArrayP P;
        CreateEmptyPlayer(&P);
        P.Neff = npemain;
        for(i=1;i<=npemain;i++){
            P = inputPlayer(P, i);
            for (int nomorp = 0; nomorp < 50; nomorp++){
                S.Pl.contents[i].playerName[nomorp] = P.contents[i].playerName[nomorp];
            }    
        }
        int urutan = 1;
        while (endgame == false){
            int r;
            boolean udahroll = false;
            boolean endturn = false;
            P.contents[urutan].playerBuff.isCerminPengganda = false;
            P.contents[urutan].playerBuff.isImun = false;
            P.contents[urutan].playerBuff.isSenterPembesar = false;
            P.contents[urutan].playerBuff.isSenterPengecil = false;
            printf("Peta Anda: ");
            displayMap(M, P.contents[urutan].position);
            time_t t;
            srand((unsigned) (time(&t)));
            r = rskill(t);
            printf("RONDE: %d\n", S.ronde);
            printf("PEMAIN KE-%d\n", urutan);
            nambahskill(&P.contents[urutan].skill, r); 
            while (endturn == false) {
                char cmd[10]; 
                int dadu;
                printf("Masukkan command (dengan huruf kapital) ketik HELP untuk melihat apa saja command yang bisa digunakan: ");
                scanf("%s", cmd);

                // COMMAND
                if (strcmp(cmd, "ROLL")==0 && udahroll==false){
                    time_t tdadu;
                    srand((unsigned) (time(&tdadu)));
                    dadu = roll(tdadu, maksdadu); 
                    if (P.contents[urutan].playerBuff.isSenterPembesar==true){
                        if (dadu < floor(maksdadu/2)){ 
                            dadu = maksdadu - dadu;
                        }
                    }
                    else if (P.contents[urutan].playerBuff.isSenterPengecil==true){
                        if (dadu > floor(maksdadu/2)){
                            dadu = abs(dadu - maksdadu);
                        }
                    }
                    printf("Anda mendapatkan dadu bernilai : %d\n", dadu);
                    udahroll = true;
                    P.contents[urutan].position = MovePlayer(&P, dadu, M, urutan, Pt);
                    if (P.contents[urutan].position == M.nEffM){
                        endgame = true;
                        endturn = true;
                        printf("SELAMAT %s TELAH MEMENANGKAN PERMAINAN MOBITANGGA\n", P.contents[urutan].playerName);
                        PrintPeringkat(P, npemain);
                    }
                    else{
                        printf("Posisi saat ini: %d\n",  P.contents[urutan].position);
                    }
                }
                else if (strcmp(cmd, "ROLL")==0 && udahroll==true){
                    printf("Maaf Anda telah pernah melakukan roll pada turn ini.\n");
                    printf("Mohon untuk tidak melakukan roll lagi\n");
                }    
                else if (strcmp(cmd, "BUFF")==0){
                    if (P.contents[urutan].playerBuff.isCerminPengganda==true){
                        printf("Anda memiliki buff Cermin Pengganda\n");
                    }
                    if (P.contents[urutan].playerBuff.isImun==true){
                        printf("Anda memiliki buff Imunitas Teleport\n");
                    }
                    if (P.contents[urutan].playerBuff.isSenterPembesar==true){
                        printf("Anda memiliki buff Senter Pembesar Hoki\n");
                    }
                    if (P.contents[urutan].playerBuff.isSenterPengecil==true){
                        printf("Anda memiliki buff Senter Pengecil Hoki\n");
                    }
                    if(P.contents[urutan].playerBuff.isCerminPengganda==false && P.contents[urutan].playerBuff.isImun==false && P.contents[urutan].playerBuff.isSenterPembesar==false && P.contents[urutan].playerBuff.isSenterPengecil==false){
                        printf("Yaahh Anda belum memiliki buff apapun saat ini\n");
                    }
                }
                else if (strcmp(cmd, "INSPECT")==0){
                    int selection;
                    printf("Masukkan petak yang ingin diketahui: ");
                    scanf(" %d", &selection);
                    inspect(Pt, M, selection);
                }
                else if (strcmp(cmd, "MAP")==0){
                    int penunjukorang;
                    for (penunjukorang=1; penunjukorang<=npemain; penunjukorang++){
                        printf("%s    : ", P.contents[penunjukorang].playerName);
                        displayMap(M, P.contents[penunjukorang].position);
                    }
                }
                else if (strcmp(cmd, "UNDO")==0){
                    status A;
                    
                    int a;
                    if (S.ronde == 1 ) {
                        S.ronde = 1;
                        urutan = 1;
                        int t;
                        for(t =1; t<=npemain;t++){
                            P.contents[t].position = 1;
                            /*SKILLNYA DIBUAT EMPTY*/
                        }
                        endturn = true;
                    }
                    else {
                        Pop(&st, &A);
                        for(a=1;a<=npemain;a++){
                            P.contents[a].position = A.Pl.contents[a].position;
                            P.contents[a].skill = A.Pl.contents[a].skill;
                            P.contents[a].playerBuff.isCerminPengganda = A.Pl.contents[a].playerBuff.isCerminPengganda;
                            P.contents[a].playerBuff.isImun = A.Pl.contents[a].playerBuff.isImun;
                            P.contents[a].playerBuff.isSenterPembesar = A.Pl.contents[a].playerBuff.isSenterPembesar;
                            P.contents[a].playerBuff.isSenterPengecil = A.Pl.contents[a].playerBuff.isSenterPengecil;
                        }
                        // S.ronde = S.ronde - 1;
                        UndoRonde(&S); 
                        urutan = 1;
                        endturn = true;
                    }
                }
                else if (strcmp(cmd, "SKILL")==0 && udahroll == true){
                    printf("Anda sudah melakukan roll, tidak dapat melakukan skill lagi\n");
                }
                else if (strcmp(cmd, "SKILL")==0 && udahroll == false){
                    int x; 
                    int tukar;
                    printskill(P.contents[urutan].skill); // L di sini listskill per player
                    if(!IsEmpty(P.contents[urutan].skill)){
                        printf("Masukkan skill: ");
                        scanf("%d", &x);
                        if (x<0){
                            buangskill(&P.contents[urutan].skill, x);
                            printf("Skill Anda telah berhasil dibuang\n");
                        }
                        else if (x>0){ // pakai skill
                            if (lihatisi(P.contents[urutan].skill, x)==1 && P.contents[urutan].playerBuff.isImun==false){
                                P.contents[urutan].playerBuff.isImun = true; // P di sini list player
                                printf("%s ", P.contents[urutan].playerName);
                                printf("memakai skill Pintu Ga Kemana-Mana.\n");
                                buangskill(&P.contents[urutan].skill, x);
                                // efek bisa menolak teleport
                            }
                            else if (lihatisi(P.contents[urutan].skill, x)==1 && P.contents[urutan].playerBuff.isImun==true){
                                printf("Anda telah memiliki buff imunitas teleport\n");
                            }
                            else if (lihatisi(P.contents[urutan].skill,x)==2 && P.contents[urutan].playerBuff.isCerminPengganda==false){
                                int r1, r2;
                                P.contents[urutan].playerBuff.isCerminPengganda = true;
                                printf("%s ", P.contents[urutan].playerName);
                                printf("memakai skill Cermin Pengganda.\n");
                                buangskill(&P.contents[urutan].skill, x);
                                time_t t1, t2;
                                srand((unsigned) (time(&t1)));
                                srand((unsigned) (time(&t2)));
                                r1 = rskill(t1);
                                r2 = rskill(t2);
                                nambahskill(&P.contents[urutan].skill, r1);
                                nambahskill(&P.contents[urutan].skill, r2);
                            }
                            else if (lihatisi(P.contents[urutan].skill,x)==2 && P.contents[urutan].playerBuff.isCerminPengganda==true){
                                printf("Anda telah memiliki buff cermin pengganda\n");
                            }
                            else if (lihatisi(P.contents[urutan].skill,x)==3 && P.contents[urutan].playerBuff.isSenterPembesar==false && P.contents[urutan].playerBuff.isSenterPengecil==false){
                                P.contents[urutan].playerBuff.isSenterPembesar = true;
                                printf("%s ", P.contents[urutan].playerName);
                                printf("memakai skill Senter Pembesar Hoki.\n");
                                buangskill(&P.contents[urutan].skill, x);
                                // efek nya ke dadu
                            }
                            else if (lihatisi(P.contents[urutan].skill,x)==3 && (P.contents[urutan].playerBuff.isSenterPembesar==true || P.contents[urutan].playerBuff.isSenterPengecil==true)){
                                if (P.contents[urutan].playerBuff.isSenterPembesar==true){
                                    printf("Anda telah memiliki buff senter pembesar hoki\n");
                                }
                                else if (P.contents[urutan].playerBuff.isSenterPengecil==true){
                                    printf("Anda telah memiliki buff senter pengecil hoki\n");
                                }
                            }
                            else if (lihatisi(P.contents[urutan].skill,x)==4 && P.contents[urutan].playerBuff.isSenterPembesar==false && P.contents[urutan].playerBuff.isSenterPengecil==false){
                                P.contents[urutan].playerBuff.isSenterPengecil = true;
                                printf("%s ", P.contents[urutan].playerName);
                                printf("memakai skill Senter Pengecil Hoki\n");
                                buangskill(&P.contents[urutan].skill, x);
                                P.contents[urutan].playerBuff.isSenterPengecil = true;
                                // efek nya ke dadu
                            }
                            else if (lihatisi(P.contents[urutan].skill,x)==4 && (P.contents[urutan].playerBuff.isSenterPembesar==true || P.contents[urutan].playerBuff.isSenterPengecil==true)){
                                if (P.contents[urutan].playerBuff.isSenterPembesar==true){
                                    printf("Anda telah memiliki buff senter pembesar hoki\n");
                                }
                                else if (P.contents[urutan].playerBuff.isSenterPengecil==true){
                                    printf("Anda telah memiliki buff senter pengecil hoki\n");
                                }
                            }
                            else if (lihatisi(P.contents[urutan].skill,x)==5){
                                ArrayP simpannama;
                                CreateEmptyPlayer(&simpannama);
                                int tukar, indeks, indeks1;
                                indeks1=1;
                                printf("memakai skill Penukar Posisi\n");
                                buangskill(&P.contents[urutan].skill, x);
                                // buat fungsi print nama ada siapa aja
                                for (indeks=1; indeks<=npemain; indeks++){
                                    if (indeks != urutan){
                                        printf("%d. %s\n", indeks1, P.contents[indeks].playerName);
                                        for (int no = 0; no < 50; no++){
                                            simpannama.contents[indeks1].playerName[no] = P.contents[indeks].playerName[no];
                                        }
                                        indeks1 = indeks1 + 1;
                                    }
                                }
                                printf("Masukkan nomor berapa yang ingin Anda tukar: ");
                                scanf("%d", &tukar);
                                // buat fungsi penukar posisi yaitu dengan menukar nama dari list player
                                int dummy;
                                for (int pencacah = 1; pencacah<=npemain; pencacah++){
                                    if (strcmp(P.contents[pencacah].playerName, simpannama.contents[tukar].playerName)==0){
                                        dummy = P.contents[urutan].position;
                                        P.contents[urutan].position = P.contents[pencacah].position;
                                        P.contents[pencacah].position = dummy;
                                    }
                                }
                                printf("Anda berhasil melakukan tukar posisi.\n");
                                printf("Silahkan ketik command MAP jika ingin melihat kondisi peta saat ini!\n");
                            }
                            // kalo 0 langsung skip
                        }
                    }
                } 
                else if (strcmp(cmd, "ENDTURN")==0 && udahroll==true){
                    endturn = true;
                    if (npemain > 1) {
                        urutan = urutan + 1;
                        if (urutan>npemain){ // SUDAH HABIS 1 RONDE
                            int z;
                            for (z=1;z<=npemain;z++){
                                S.Pl.contents[z].skill = P.contents[z].skill;
                                S.Pl.contents[z].position = P.contents[z].position;
                                S.Pl.contents[z].playerBuff.isCerminPengganda = P.contents[z].playerBuff.isCerminPengganda;
                                S.Pl.contents[z].playerBuff.isImun = P.contents[z].playerBuff.isImun;
                                S.Pl.contents[z].playerBuff.isSenterPembesar = P.contents[z].playerBuff.isSenterPembesar;
                                S.Pl.contents[z].playerBuff.isSenterPengecil = P.contents[z].playerBuff.isSenterPengecil;
                            }
                            // push stack buat undo
                            Push(&st, S);
                            NextRonde(&S);
                            urutan = (urutan % npemain);
                        }
                    } 
                    else /*npemain == 1*/{
                        endturn = true;
                        urutan = 1;
                        int w;
                            for (w=1;w<=npemain;w++){
                                S.Pl.contents[w].skill = P.contents[w].skill;
                                S.Pl.contents[w].position = P.contents[w].position;
                                S.Pl.contents[w].playerBuff = P.contents[w].playerBuff;
                            }
                            
                            // push stack buat undo
                            Push(&st, S);
                            NextRonde(&S);
                            urutan = 1;
                    }       
                } 
                else if (strcmp(cmd, "ENDTURN")==0 && udahroll==false){
                    printf("Anda hanya bisa ENDTURN setelah melakukan roll\n");
                    printf("Silakan melakukan ROLL terlebih dahulu\n");
                }
                else if (strcmp(cmd, "HELP")==0){
                    printf("Berikut adalah panduan dalam mengisi command:\n");
                    printf("1. Masukkan command dengan menggunakan huruf kapital (CAPSLOCK)\n");
                    printf("2. Daftar command yang dapat digunakan:\n");
                    printf("   ~ SKILL untuk melihat dan memakai skill yang telah didapatkan\n");
                    printf("   ~ ROLL untuk merandom dadu dan bergerak. Note: setelah ROLL tidak bisa menggunakan SKILL lagi\n");
                    printf("   ~ BUFF untuk mengecek buff apa saja yang sedang aktif\n");
                    printf("   ~ INSPECT untuk melihat kotak ke berapa berisikan apa\n");
                    printf("   ~ MAP untuk melihat posisi semua player di peta\n");
                    printf("   ~ ENDTURN untuk mengakhiri giliran. Note: ENDTURN hanya bisa dilakukan setelah player melakukan ROLL\n");
                    printf("   ~ UNDO untuk kembali ke awal ronde\n");
                }
                else{
                    printf("Masukkan command yang sesuai!\n"); 
                }
            }
        } 
    }    
}