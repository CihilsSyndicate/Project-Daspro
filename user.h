#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "colors.h"

struct Alamat{
    char namaJalan[100];
    char kota[40];
    char kelurahan[40];
    char kecamatan[40];
};

struct User{
    char namaLengkap[50];
    struct Alamat alamatUser;
};

struct Admin{
    char email[30];
    char password[50];
    struct User dataAdmin;
};


struct Member{
    char kode[20];
    char noHp[20];
    struct User dataMember;
};


struct Member member[100];  
struct Admin admin[1];
int totalMember = 0;

void addMember() {
    bool isFinishAddUser = false;
    int intForBool = 1;
    do {
        printf(CYAN "=========================================\n" RESET);
        printf(CYAN "||" RESET GREEN "       FORM INPUT DATA MEMBER        " RESET CYAN "||\n" RESET);
        printf(CYAN "=========================================\n" RESET);

        printf(CYAN "| %-37s |\n", "Masukkan data Member");
        printf(CYAN "|---------------------------------------|\n" RESET);

        printf(CYAN "| %-28s: " RESET, "Masukkan nama Member");
        fgets(member[totalMember].dataMember.namaLengkap, sizeof(member[totalMember].dataMember.namaLengkap), stdin);
        member[totalMember].dataMember.namaLengkap[strcspn(member[totalMember].dataMember.namaLengkap, "\n")] = '\0';

        printf(CYAN "|---------------------------------------|\n" RESET);
        printf(CYAN "| %-37s |\n", "Alamat Member");
        printf(CYAN "|---------------------------------------|\n" RESET);

        printf(CYAN "| %-28s: " RESET, "Nama Jalan");
        fgets(member[totalMember].dataMember.alamatUser.namaJalan, sizeof(member[totalMember].dataMember.alamatUser.namaJalan), stdin);
        member[totalMember].dataMember.alamatUser.namaJalan[strcspn(member[totalMember].dataMember.alamatUser.namaJalan, "\n")] = '\0';

        printf(CYAN "| %-28s: " RESET, "Nama Kelurahan");
        fgets(member[totalMember].dataMember.alamatUser.kelurahan, sizeof(member[totalMember].dataMember.alamatUser.kelurahan), stdin);
        member[totalMember].dataMember.alamatUser.kelurahan[strcspn(member[totalMember].dataMember.alamatUser.kelurahan, "\n")] = '\0';

        printf(CYAN "| %-28s: " RESET, "Nama Kecamatan");
        fgets(member[totalMember].dataMember.alamatUser.kecamatan, sizeof(member[totalMember].dataMember.alamatUser.kecamatan), stdin);
        member[totalMember].dataMember.alamatUser.kecamatan[strcspn(member[totalMember].dataMember.alamatUser.kecamatan, "\n")] = '\0';

        printf(CYAN "| %-28s: " RESET, "Nama Kota");
        fgets(member[totalMember].dataMember.alamatUser.kota, sizeof(member[totalMember].dataMember.alamatUser.kota), stdin);
        member[totalMember].dataMember.alamatUser.kota[strcspn(member[totalMember].dataMember.alamatUser.kota, "\n")] = '\0';

        printf(CYAN "---------------------------------------\n\n" RESET);

        printf("Apakah anda akan menambah data Member lagi ? [1 / 0] : ");
        scanf("%d", &intForBool);
        getchar();

        if (intForBool == 0) {
            printf(RED "Anda keluar dari menu tambah member! \n" RESET);
            isFinishAddUser = true;
        }

        totalMember++;
        printf("\n"); 

    } while (!isFinishAddUser);
}

void getDataMember() {
    if (totalMember > 0) {
        
        printf(CYAN "============================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                          PERPUSTAKAAN HITAM                                            " RESET CYAN "||\n" RESET);
        printf(CYAN "============================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                             DAFTAR MEMBER                                              " RESET CYAN "||\n" RESET);
        printf(CYAN "============================================================================================================\n" RESET);
 
        printf(CYAN "| " RESET GREEN "%-5s" RESET CYAN " | " RESET GREEN "%-25s" RESET CYAN " | " RESET GREEN "%-20s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-27s" RESET CYAN " |\n" RESET,
               "No", "Nama Lengkap", "Nama Jalan", "Kota", "Provinsi");
        printf(CYAN "============================================================================================================\n" RESET);

        for (int i = 0; i < totalMember; i++) {
            printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-27s" CYAN " |\n" RESET, 
                   i + 1,
                   member[i].dataMember.namaLengkap,
                   member[i].dataMember.alamatUser.namaJalan,
                   member[i].dataMember.alamatUser.kelurahan,
                   member[i].dataMember.alamatUser.kecamatan,
                   member[i].dataMember.alamatUser.kota);
        }

        printf(CYAN "------------------------------------------------------------------------------------------------------------\n\n" RESET);
    } else {
        printf(RED "Data member kosong!\n" RESET);
    }
}


void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int findMember() {
    char searchName[50];
    getDataMember();

    if (totalMember > 0) {
        printf("Cari data Member berdasarkan Nama: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = 0; 

        toLowerCase(searchName);

        int found = 0;

        printf(CYAN "============================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                          PERPUSTAKAAN HITAM                                            " RESET CYAN "||\n" RESET);
        printf(CYAN "============================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                           HASIL PENCARIAN                                              " RESET CYAN "||\n" RESET);
        printf(CYAN "============================================================================================================\n" RESET);
        printf(CYAN "| " RESET GREEN "%-5s" RESET CYAN " | " RESET GREEN "%-25s" RESET CYAN " | " RESET GREEN "%-20s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-27s" RESET CYAN " |\n" RESET,
               "No", "Nama Lengkap", "Nama Jalan", "Kota", "Provinsi");
        printf(CYAN "============================================================================================================\n" RESET);

        for (int i = 0; i < totalMember; i++) {
            char memberName[50];
            strcpy(memberName, member[i].dataMember.namaLengkap);
            toLowerCase(memberName);

            if (strstr(memberName, searchName) != NULL) {
                printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-27s" CYAN " |\n" RESET, 
                       i + 1,
                       member[i].dataMember.namaLengkap,
                       member[i].dataMember.alamatUser.namaJalan,
                       member[i].dataMember.alamatUser.kelurahan,
                       member[i].dataMember.alamatUser.kecamatan,
                       member[i].dataMember.alamatUser.kota);
                found = 1;

                return i;
            }
        }

        printf(CYAN "------------------------------------------------------------------------------------------------------------\n\n" RESET);
        
        if (!found) {
            printf("Member tidak ditemukan, coba periksa kembali!\n");
        }
    } else {
        printf("Tidak ada data member.\n");
    }
    return 0;
}



void menuMember() {
    printf(CYAN "||" RESET GREEN "            MENU MEMBER            " RESET CYAN "||\n" RESET);
    printf(CYAN "=======================================\n" RESET);
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[1]" RESET, "Tambah Member");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[2]" RESET, "Tampilkan Semua Member");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[3]" RESET, "Cari Member");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", RED "[0]" RESET, "Kembali Ke Menu Utama");
    printf(CYAN "---------------------------------------\n\n" RESET);
}


void seedUser(){
    strcpy(admin[0].email,"admin@example.org");
    strcpy(admin[0].password, "passwordsecure");
    strcpy(admin[0].dataAdmin.namaLengkap,"Admin Perpus");
    strcpy(admin[0].dataAdmin.alamatUser.namaJalan,"Gunung Roay");
    strcpy(admin[0].dataAdmin.alamatUser.kelurahan,"Sukakarsa");
    strcpy(admin[0].dataAdmin.alamatUser.kecamatan,"Padasuka");
    strcpy(admin[0].dataAdmin.alamatUser.kota,"Tasikmalaya");
}

void seedMember(){
    strcpy(member[0].dataMember.namaLengkap,"Ricko");
    strcpy(member[0].dataMember.alamatUser.namaJalan,"Jl.Jalan");
    strcpy(member[0].dataMember.alamatUser.kelurahan,"Mugarsari");
    strcpy(member[0].dataMember.alamatUser.kecamatan,"Tamansari");
    strcpy(member[0].dataMember.alamatUser.kota,"Tasikmalaya");

    totalMember = 1;
}

void menuUser() {
    printf(CYAN "||" RESET GREEN "              MENU USER              " RESET CYAN "||\n" RESET);
    printf(CYAN "=======================================\n" RESET);
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[1]" RESET, "Ganti Password");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", RED "[0]" RESET, "Kembali ke Menu Utama");
    printf(CYAN "---------------------------------------\n\n" RESET);
}


bool verifyPasswordUser(char passwordTemp[], char newPassword[]){

    if(strcmp(passwordTemp, newPassword) == 0){
        return true;
    }else{
        return false;
    }
}


bool changeEmail(){
    char newEmail[50], passwordVerify[50];
    bool isPasswordMatch = false;

    printf("\n Silakan Masukkan password baru : ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strlen(newEmail) - 1] = '\0';

    do{
        printf("\n Silakan Masukkan password : ");
        fgets(passwordVerify, sizeof(passwordVerify), stdin);
        passwordVerify[strlen(passwordVerify) - 1] = '\0';
    
        if(verifyPasswordUser(passwordVerify, admin[0].password)){
            strcpy(admin[0].email, newEmail);
            isPasswordMatch = true;
        }else{
            printf("\n Password Salah ! ");
            isPasswordMatch = false;
        }

    }while(!isPasswordMatch);

    return true;
}

bool changePassword(){

    char passwordTemp[50], newPassword[50];
    bool isPasswordMatch = false;

    printf("\n Silakan Masukkan password baru : ");
    fgets(passwordTemp, sizeof(passwordTemp), stdin);
    passwordTemp[strlen(passwordTemp) - 1] = '\0';

    do{
        printf("\n Silakan konfirmasi password baru : ");
        fgets(newPassword, sizeof(newPassword), stdin);
        newPassword[strlen(newPassword) - 1] = '\0';

        if(verifyPasswordUser(passwordTemp, newPassword)){
            strcpy(admin[0].password, newPassword);
            isPasswordMatch = true;
        }else{
            printf("\n Password Salah ! ");
            isPasswordMatch = false;
        }
    
    }while(!isPasswordMatch);

    return true;
}

#endif