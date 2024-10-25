#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "book.c"
#include "user.c"

void clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void header(){
    printf("=======================================\n");
    printf("||        PERPUSTAKAAN HITAM         ||\n");
    printf("=======================================\n\n");
}

void menuUtama(){
    printf("\nMenu Utama:\n");
    printf("--------------------------------\n");
    printf("[1] : Manajemen Member\n");
    printf("[2] : Manajemen Buku\n");
    printf("[0] : Keluar\n");
    printf("--------------------------------\n");
}

int main(){
    
    int menu;
    int subMenu;
    int isExitNum = 0;
    bool isExit = false;

    bukuSementara();
    do{
        clear();
        header();
        menuUtama();
    
        printf("\nPilih menu: ");
        scanf("%d", &menu);
        getchar();

        switch(menu){
            case 1:
                do
                {   
                    clear();
                    header();
                    menuMember();
                    printf("\nPilih sub-menu: ");
                    scanf("%d", &subMenu);
                    getchar();
                    
                    switch (subMenu)
                    {
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
                        break;
                    }

                    if(subMenu != 0){
                        printf("\nTekan Enter untuk melanjutkan..");
                        getchar();
                    }

                } while (subMenu != 0);
                
                break;
            case 2:
                do
                {
                    clear();
                    header();
                    menuBuku();
                    printf("\nPilih sub-menu: ");
                    scanf("%d", &subMenu);
                    getchar();

                    switch (subMenu)
                    {
                    case 1:
                        tambahBuku();
                        break;
                    case 2:
                        tampilkanBuku();
                        break;
                    
                    default:
                        break;
                    }

                    if(subMenu != 0){
                        printf("\nTekan Enter untuk melanjutkan..");
                        getchar();
                    }

                } while (subMenu != 0);
                
                break;
            default:
                printf("See ya!\n");
                isExit = true;
                break;
            
        };
    }while(!isExit);


    return 0;
}