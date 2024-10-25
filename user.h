#ifndef USER_H
#define USER_H



#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    int totalPinjaman;
    int bukuPinjaman[10];
};

struct Member member[100];
struct Admin admin[1];
int totalMember = 0;

void addMember(){
    bool isFinishAddUser = false;
    int intForBool = 1;
    do{
        printf("Masukkan data Member \n");

        printf("Masukkan nama Member : ");
        fgets(member[totalMember].dataMember.namaLengkap, sizeof(member[totalMember].dataMember.namaLengkap), stdin);
        member[totalMember].dataMember.namaLengkap[strlen(member[totalMember].dataMember.namaLengkap) -  1] = '\0';

        printf("Masukkan alamat Member : \n");

        printf("Masukkan Nama Jalan : ");
        fgets(member[totalMember].dataMember.alamatUser.namaJalan, sizeof(member[totalMember].dataMember.alamatUser.namaJalan), stdin);

        printf("Masukkan Nama Kota : ");
        fgets(member[totalMember].dataMember.alamatUser.kota, sizeof(member[totalMember].dataMember.alamatUser.kota), stdin);

        printf("Masukkan Nama Provinsi : ");
        fgets(member[totalMember].dataMember.alamatUser.provinsi, sizeof(member[totalMember].dataMember.alamatUser.provinsi), stdin);

        printf("Apakah anda akan menambah data Member lagi ? [1 / 0] : ");
        scanf("%d", &intForBool);
        getchar();

        if(intForBool == 0){
            printf("Anda keluar dari menu tambah member! \n");
            isFinishAddUser = true;
        }

        totalMember++;

    }while(!isFinishAddUser);
}

void getDataMember(){
    if(totalMember > 0){
        for(int i = 0; i < totalMember; i++){
            printf("[%d]. %s, %s \n",i+1, member[i].dataMember.namaLengkap, member[i].dataMember.alamatUser.kota,  member[i].dataMember.alamatUser.provinsi);
        }
    }else{
        printf("Data member kosong ! \n");
    }
}

void findMember(){
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
        }else{
            printf("Member out of range, Please check it again ! \n");
        }
    }
}

void menuMember(){
    printf("\nMenu Member:\n");
    printf("--------------------------------\n");
    printf("[1] : Tambah Member\n");
    printf("[2] : Tampilkan Semua Member\n");
    printf("[3] : Cari Member\n");
    printf("[0] : Keluar\n");
    printf("--------------------------------\n");
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

    totalMember++;
}

void menuUser(){
    printf("\nMenu User:\n");
    printf("--------------------------------\n");
    printf("[1] : Ganti Password\n");
    // printf("[2] : Tampilkan Semua Buku\n");
    // printf("[0] : Keluar\n");
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