#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "colors.h"

struct Alamat{
    char namaJalan[100];
    char kota[40];
    char provinsi[30];  
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
    struct User dataMember;
};


struct Member member[100];  
struct Admin admin[1];
int totalMember = 0;

void addMember(){
    bool isFinishAddUser = false;
    int intForBool = 1;
    do{
        printf(CYAN "=========================================\n" RESET);
        printf(CYAN "||" RESET GREEN "       FORM INPUT DATA MEMBER        " RESET CYAN "||\n" RESET);
        printf(CYAN "=========================================\n" RESET);

        printf(CYAN "| %-37s |\n", "Masukkan data Member");
        printf(CYAN "|---------------------------------------|\n" RESET);

        printf(CYAN "| %-28s: " RESET, "Masukkan nama Member");
        fgets(member[totalMember].dataMember.namaLengkap, sizeof(member[totalMember].dataMember.namaLengkap), stdin);
        
        member[totalMember].dataMember.namaLengkap[strlen(member[totalMember].dataMember.namaLengkap) - 1] = '\0';
        printf(CYAN "|---------------------------------------|\n" RESET);
        printf(CYAN "| %-37s |\n", "Alamat Member");
        printf(CYAN "|---------------------------------------|\n" RESET);

        printf(CYAN "| %-28s: " RESET, "Nama Jalan");
        fgets(member[totalMember].dataMember.alamatUser.namaJalan, sizeof(member[totalMember].dataMember.alamatUser.namaJalan), stdin);

        printf(CYAN "| %-28s: " RESET, "Nama Kota");
        fgets(member[totalMember].dataMember.alamatUser.kota, sizeof(member[totalMember].dataMember.alamatUser.kota), stdin);

        printf(CYAN "| %-28s: " RESET, "Nama Provinsi");
        fgets(member[totalMember].dataMember.alamatUser.provinsi, sizeof(member[totalMember].dataMember.alamatUser.provinsi), stdin);

        printf(CYAN "---------------------------------------\n\n" RESET);

        printf("Apakah anda akan menambah data Member lagi ? [1 / 0] : ");
        scanf("%d", &intForBool);
        getchar();

        if(intForBool == 0){
            printf(RED "Anda keluar dari menu tambah member! \n" RESET);
            isFinishAddUser = true;
        }

        totalMember++;

    }while(!isFinishAddUser);
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
                   member[i].dataMember.alamatUser.kota,
                   member[i].dataMember.alamatUser.provinsi);
        }

        printf(CYAN "------------------------------------------------------------------------------------------------------------\n\n" RESET);
    } else {
        printf(RED "Data member kosong!\n" RESET);
    }
}




int findMember(){
    int arrMemberIndex;
    getDataMember();

    if(totalMember > 0){
        printf("Cari data Member berdasarkan Nomor : ");
        scanf("%d", &arrMemberIndex);
        getchar();

        if(arrMemberIndex <= totalMember && arrMemberIndex > 0){
            printf("Member yang anda cari Nomor : %d \n", arrMemberIndex);
            printf("Nama Member : %s \n", member[arrMemberIndex - 1].dataMember.namaLengkap);
            printf("Alamat Member : %s, %s, %s \n", member[arrMemberIndex - 1].dataMember.alamatUser.namaJalan, member[arrMemberIndex - 1].dataMember.alamatUser.kota,  member[arrMemberIndex - 1].dataMember.alamatUser.provinsi);
            return arrMemberIndex;
        }else{
            printf("Member out of range, Please check it again ! \n");
        }
    }else{
        return 0;
    }


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
    strcpy(admin[0].dataAdmin.alamatUser.kota,"Tasikmalaya");
    strcpy(admin[0].dataAdmin.alamatUser.provinsi,"Jawa Barat");
}

void seedMember(){
    strcpy(member[0].dataMember.namaLengkap,"Ricko");
    strcpy(member[0].dataMember.alamatUser.namaJalan,"Jl.Jalan");
    strcpy(member[0].dataMember.alamatUser.kota,"Tasikmalaya");
    strcpy(member[0].dataMember.alamatUser.provinsi,"Jawa Barat");

    totalMember = 1;
}

void menuUser(){
    printf("\nMenu User:\n");
    printf("--------------------------------\n");
    printf("[1] : Ganti Password\n");
    // printf("[2] : Tampilkan Semua Buku\n");
    printf("[0] : Kembali ke Menu Utama\n");
    printf("--------------------------------\n");
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