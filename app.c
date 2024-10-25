#include <stdio.h>
#include <stdbool.h>
#include "user.c"

int main(){
    
    int menu;
    int isExitNum = 0;
    bool isExit = false;

    printf("Selamat datang di perpus hitam \n");
    do{
        printf("Silakan pilih menu : \n");
        printf("[1] : Tambah Member\n");
        printf("[2] : Tampilkan data Member\n");
        printf("[3] : Cari data Member\n");
        printf("[0] : Exit\n");

        printf("Masukkan Nomor menu : ");
        scanf("%d", &menu);
        getchar();

        switch(menu){
            case 1:
                addMember();
                break;
            case 2:
                getDataMember();
                break;
            case 3:
                findMember();
                break;
            default:
                printf("See ya!\n");
                isExit = true;
                break;
        };
    }while(!isExit);


    return 0;
}