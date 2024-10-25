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

struct Member{
    struct User dataMember;
};

struct Member member[100];
int totalMember = 0;

void addMember(){
    bool isFinishAddUser = false;
    int countUser = 1;
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
            // printf("[%d]. %s \n",i+1, member[i].dataMember.alamatUser.kota);
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