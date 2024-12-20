#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
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
    char noHp[15];
    char level[10]; // either "Anggota" or "Member"
    struct User dataMember;
};


struct Member member[100];  
struct Admin admin[1];
int totalMember = 0;


void capitalizeEachWord(char *str) {
    bool capitalize = true;
    for (int i = 0; str[i]; i++) {
        if (capitalize && isalpha((unsigned char)str[i])) {
            str[i] = toupper(str[i]);
            capitalize = false;
        } else if (str[i] == ' ') {
            capitalize = true;
        } else {
            str[i] = tolower(str[i]);
        }
    }
}


bool isDuplicateName(const char *name) {
    for (int i = 0; i < totalMember; i++) {
        if (strcasecmp(member[i].dataMember.namaLengkap, name) == 0) {
            return true;
        }
    }
    return false;
}

int getIndexByName(const char *name) {
    for (int i = 0; i < totalMember; i++) {
        if (strcasecmp(member[i].dataMember.namaLengkap, name) == 0) {
            return i; 
        }
    }
    return -1; 
}

void addMember() {
    bool isFinishAddUser = false;
    char editLagi;
    char namaLengkap[50];
    char noHp[15];
    char namaJalan[100];
    char kelurahan[40];
    char kecamatan[40];
    char kota[40];
    char level[10];
    
    srand(time(NULL));

    while (!isFinishAddUser){
        printf(CYAN "=========================================\n" RESET);
        printf(CYAN "||" RESET GREEN "       FORM INPUT DATA ANGGOTA        " RESET CYAN "||\n" RESET);
        printf(CYAN "=========================================\n" RESET);

        printf(CYAN "| %-37s |\n", "Masukkan data Anggota");
        printf(CYAN "|---------------------------------------|\n" RESET);

        printf(CYAN "| %-28s: " RESET, "Masukkan nama Anggota");
        fgets(namaLengkap, sizeof(namaLengkap), stdin);
        namaLengkap[strcspn(namaLengkap, "\n")] = '\0';

        capitalizeEachWord(namaLengkap);

        if (isDuplicateName(namaLengkap)) {
            printf(RED "Nama Anggota tersebut sudah ada!\n" RESET);
            continue; 
        }

        bool validNoHpInput = false;
        while(!validNoHpInput) {
            printf(CYAN "| %-28s: " RESET, "Masukkan nomor Anggota (tanpa spasi)");
            fgets(noHp, sizeof(noHp), stdin);
            noHp[strcspn(noHp, "\n")] = '\0';

            validNoHpInput = true;
            for (int i = 0; i < strlen(noHp); i++) {
                if (!isdigit(noHp[i])) {
                    printf(RED "Silahkan masukkan angka saja.\n" RESET);
                    validNoHpInput = false;
                    break;
                }
            }
        };

        printf(CYAN "|---------------------------------------|\n" RESET);
        printf(CYAN "| %-37s |\n", "Alamat Anggota");
        printf(CYAN "|---------------------------------------|\n" RESET);

        printf(CYAN "| %-28s: " RESET, "Nama Jalan");
        fgets(namaJalan, sizeof(namaJalan), stdin);
        namaJalan[strcspn(namaJalan, "\n")] = '\0';
        capitalizeEachWord(namaJalan);

        printf(CYAN "| %-28s: " RESET, "Nama Kelurahan");
        fgets(kelurahan, sizeof(kelurahan), stdin);
        kelurahan[strcspn(kelurahan, "\n")] = '\0';
        capitalizeEachWord(kelurahan);

        printf(CYAN "| %-28s: " RESET, "Nama Kecamatan");
        fgets(kecamatan, sizeof(kecamatan), stdin);
        kecamatan[strcspn(kecamatan, "\n")] = '\0';
        capitalizeEachWord(kecamatan);

        printf(CYAN "| %-28s: " RESET, "Nama Kota");
        fgets(kota, sizeof(kota), stdin);
        kota[strcspn(kota, "\n")] = '\0';
        capitalizeEachWord(kota);

        printf(CYAN "| %-28s: " RESET, "Level (Anggota/Member)");
        fgets(level, sizeof(level), stdin);
        level[strcspn(level, "\n")] = '\0';
        capitalizeEachWord(level);

        // Copy input data ke struct Member
        strcpy(member[totalMember].dataMember.namaLengkap, namaLengkap);
        strcpy(member[totalMember].noHp, noHp);
        strcpy(member[totalMember].dataMember.alamatUser.namaJalan, namaJalan);
        strcpy(member[totalMember].dataMember.alamatUser.kelurahan, kelurahan);
        strcpy(member[totalMember].dataMember.alamatUser.kecamatan, kecamatan);
        strcpy(member[totalMember].dataMember.alamatUser.kota, kota);
        strcpy(member[totalMember].level, level);

        printf(CYAN "---------------------------------------\n\n" RESET);

        totalMember++;

        printf("Apakah anda akan menambah data Anggota lagi? [y / t] : ");
        scanf("%c", &editLagi);
        getchar();

        if (editLagi == 't') {
            printf(RED "Anda keluar dari menu tambah Anggota!\n" RESET);
            isFinishAddUser = true;
        } else {
            printf(RED "Input tidak valid. Anda telah keluar dari menu.\n" RESET);
        }
        
        printf("\n");

    };
}

void getDataMember() {
    if (totalMember > 0) {
        
        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                                          PERPUSTAKAAN HITAM                                                    " RESET CYAN "||\n" RESET);
        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                                            DAFTAR ANGGOTA                                                       " RESET CYAN "||\n" RESET);
        printf(CYAN "====================================================================================================================================\n" RESET);
 
        printf(CYAN "| " RESET GREEN "%-5s" RESET CYAN " | " RESET GREEN "%-25s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-20s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " |\n" RESET,
               "No", "Nama Lengkap", "No HP", "Nama Jalan", "Kelurahan", "Kecamatan", "Kota");
        printf(CYAN "====================================================================================================================================\n" RESET);

        for (int i = 0; i < totalMember; i++) {
            printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " |\n" RESET, 
                   i + 1,
                   member[i].dataMember.namaLengkap,
                   member[i].noHp,
                   member[i].dataMember.alamatUser.namaJalan,
                   member[i].dataMember.alamatUser.kelurahan,
                   member[i].dataMember.alamatUser.kecamatan,
                   member[i].dataMember.alamatUser.kota);
        }

        printf(CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n" RESET);
    } else {
        printf(RED "Data anggota kosong!\n" RESET);
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
        printf("Cari data Anggota berdasarkan Nama: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = 0; 

        toLowerCase(searchName);

        int found = 0;

        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                                          PERPUSTAKAAN HITAM                                                    " RESET CYAN "||\n" RESET);
        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                                            HASIL PENCARIAN                                                     " RESET CYAN "||\n" RESET);
        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "| " RESET GREEN "%-5s" RESET CYAN " | " RESET GREEN "%-25s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-20s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " |\n" RESET,
               "No", "Nama Lengkap", "No HP", "Nama Jalan", "Kelurahan", "Kecamatan", "Kota");
        printf(CYAN "====================================================================================================================================\n" RESET);

        for (int i = 0; i < totalMember; i++) {
            char memberName[50];
            strcpy(memberName, member[i].dataMember.namaLengkap);
            toLowerCase(memberName);

            if(strlen(searchName) > 0){
                if (strstr(memberName, searchName) != NULL) {
                    printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " |\n" RESET, 
                        i + 1,
                        member[i].dataMember.namaLengkap,
                        member[i].noHp,
                        member[i].dataMember.alamatUser.namaJalan,
                        member[i].dataMember.alamatUser.kelurahan,
                        member[i].dataMember.alamatUser.kecamatan,
                        member[i].dataMember.alamatUser.kota);
                    found = 1;
                    return i+1; 
                }
            }else{
                printf("Masukkan Nama Lengkap dengan Benar \n");
            }
        }
        printf(CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n" RESET);
        
        if (!found) {
            printf("Anggota tidak ditemukan, coba periksa kembali!\n");
        }
    } else {
        printf("Tidak ada data anggota.\n");
    }
    return 0;
}

int editMember() {
    char searchName[50];
    // getDataMember();

    if (totalMember > 0) {
        int memberIndex = findMember();
        // printf("Cari data Member berdasarkan Nama: ");
        // fgets(searchName, sizeof(searchName), stdin);
        // searchName[strcspn(searchName, "\n")] = 0; 

        // toLowerCase(searchName);

        // int index = getIndexByName(searchName);

        // int found = 0;


        // printf(CYAN "====================================================================================================================================\n" RESET);
        // printf(CYAN "||" RESET YELLOW "                                            PERPUSTAKAAN HITAM                                            " RESET CYAN "||\n" RESET);
        // printf(CYAN "====================================================================================================================================\n" RESET);
        // printf(CYAN "||" RESET YELLOW "                                             HASIL PENCARIAN                                              " RESET CYAN "||\n" RESET);
        // printf(CYAN "====================================================================================================================================\n" RESET);
        // printf(CYAN "| " RESET GREEN "%-5s" RESET CYAN " | " RESET GREEN "%-25s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-20s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-15s" CYAN " | " RESET GREEN "%-15s" RESET CYAN " |\n" RESET,
        //        "No", "Nama Lengkap", "No HP", "Nama Jalan", "Kelurahan", "Kecamatan", "Kota");
        // printf(CYAN "====================================================================================================================================\n" RESET);

        // for (int i = 0; i < totalMember; i++) {
        //     char memberName[50];
        //     strcpy(memberName, member[i].dataMember.namaLengkap);
        //     toLowerCase(memberName);

        //     if (strstr(memberName, searchName) != NULL) {
        //         printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " |\n" RESET, 
        //                i + 1,
        //                member[i].dataMember.namaLengkap,
        //                member[i].noHp,
        //                member[i].dataMember.alamatUser.namaJalan,
        //                member[i].dataMember.alamatUser.kelurahan,
        //                member[i].dataMember.alamatUser.kecamatan,
        //                member[i].dataMember.alamatUser.kota);
        //         found = 1;
        //     }
        // }

        printf(CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n" RESET);

        if (memberIndex-1 < 0) {
            printf("Anggota tidak ditemukan, coba periksa kembali!\n");
            // return 0;
        } else {
            bool doneEditing = false;
            int index = memberIndex-1;
            // if (index != -1) {
                while (!doneEditing) {
                    printf("Silakan pilih data yang ingin diubah:\n");
                    printf("[1] Nama Lengkap\n");
                    printf("[2] Nomor HP\n");
                    printf("[3] Jalan\n");
                    printf("[4] Kelurahan\n");
                    printf("[5] Kecamatan\n");
                    printf("[6] Kota\n");
                    printf("[7] Level\n"); // Add this line
                    printf("[0] Selesai\n");
                    printf("Masukkan pilihan: ");

                    int choice;
                    scanf("%d", &choice);
                    getchar();

                    char namaLengkap[50];
                    char noHp[15];
                    char namaJalan[100];
                    char kota[40];
                    char kelurahan[40];
                    char kecamatan[40];
                    char level[10];  // Add this line

                    bool validInput = false;
                    switch (choice) {
                        case 1:
                            printf("Masukkan Nama Lengkap baru: ");
                            fgets(namaLengkap, sizeof(namaLengkap), stdin);
                            namaLengkap[strcspn(namaLengkap, "\n")] = '\0';
                            capitalizeEachWord(namaLengkap);
                            strcpy(member[index].dataMember.namaLengkap, namaLengkap);
                            break;
                        case 2:
                            while (!validInput) {
                                printf("Masukkan nomor baru (tanpa spasi): ");
                                fgets(noHp, sizeof(noHp), stdin);
                                noHp[strcspn(noHp, "\n")] = '\0';

                                validInput = true;
                                for (int i = 0; i < strlen(noHp); i++) {
                                    if (!isdigit(noHp[i])) {
                                        printf(RED "Silahkan masukkan angka saja.\n" RESET);
                                        validInput = false;
                                        break;
                                    }
                                }
                            }
                            strcpy(member[index].noHp, noHp);
                            break;
                        case 3:
                            printf("Masukkan Nama Jalan baru: ");
                            fgets(namaJalan, sizeof(namaJalan), stdin);
                            namaJalan[strcspn(namaJalan, "\n")] = '\0';
                            capitalizeEachWord(namaJalan);
                            strcpy(member[index].dataMember.alamatUser.namaJalan, namaJalan);
                            break;
                        case 4:
                            printf("Masukkan Kelurahan baru: ");
                            fgets(kelurahan, sizeof(kelurahan), stdin);
                            kelurahan[strcspn(kelurahan, "\n")] = '\0';
                            capitalizeEachWord(kelurahan);
                            strcpy(member[index].dataMember.alamatUser.kelurahan, kelurahan);
                            break;
                        case 5:
                            printf("Masukkan Kecamatan baru: ");
                            fgets(kecamatan, sizeof(kecamatan), stdin);
                            kecamatan[strcspn(kecamatan, "\n")] = '\0';
                            capitalizeEachWord(kecamatan);
                            strcpy(member[index].dataMember.alamatUser.kecamatan, kecamatan);
                            break;
                        case 6:
                            printf("Masukkan Kota baru: ");
                            fgets(kota, sizeof(kota), stdin);
                            kota[strcspn(kota, "\n")] = '\0';
                            capitalizeEachWord(kota);
                            strcpy(member[index].dataMember.alamatUser.kota, kota);
                            break;
                        case 7:  // Add this case
                            printf("Masukkan Level baru (Anggota/Member): ");
                            fgets(level, sizeof(level), stdin);
                            level[strcspn(level, "\n")] = '\0';
                            capitalizeEachWord(level);
                            if (strcmp(level, "Anggota") == 0 || strcmp(level, "Member") == 0) {
                                strcpy(member[index].level, level);
                            } else {
                                printf("Level tidak valid. Hanya bisa 'Anggota' atau 'Member'.\n");
                            }
                            break;
                        case 0:
                            printf("Pengeditan selesai.\n");
                            doneEditing = true;
                            break;
                        default:
                            printf("Pilihan tidak valid.\n");
                            break;
                    }
                }
            // } else {
            //     printf("Member tidak ditemukan, coba periksa kembali!\n");
            // }
        }
    } else {
        printf("Tidak ada data anggota.\n");
    }
    return 0;
}

int deleteMember() {
    char searchName[50];
    getDataMember();

    if (totalMember > 0) {
        printf("Cari data Anggota berdasarkan Nama: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = 0; 

        toLowerCase(searchName);

        int index = getIndexByName(searchName);

        int found = 0;

        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                            PERPUSTAKAAN HITAM                                            " RESET CYAN "||\n" RESET);
        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                             HASIL PENCARIAN                                              " RESET CYAN "||\n" RESET);
        printf(CYAN "====================================================================================================================================\n" RESET);
        printf(CYAN "| " RESET GREEN "%-5s" RESET CYAN " | " RESET GREEN "%-25s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-20s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " | " RESET GREEN "%-15s" RESET CYAN " |\n" RESET,
               "No", "Nama Lengkap", "No HP", "Nama Jalan", "Kelurahan", "Kecamatan", "Kota");
        printf(CYAN "====================================================================================================================================\n" RESET);

        for (int i = 0; i < totalMember; i++) {
            char memberName[50];
            strcpy(memberName, member[i].dataMember.namaLengkap);
            toLowerCase(memberName);

            if (strstr(memberName, searchName) != NULL) {
                printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " |\n" RESET, 
                       i + 1,
                       member[i].dataMember.namaLengkap,
                       member[i].noHp,
                       member[i].dataMember.alamatUser.namaJalan,
                       member[i].dataMember.alamatUser.kelurahan,
                       member[i].dataMember.alamatUser.kecamatan,
                       member[i].dataMember.alamatUser.kota);
                found = 1;
            }
        }

       printf(CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n" RESET);

        if (!found) {
            printf("Anggota tidak ditemukan, coba periksa kembali!\n");
            return 0;
        } else {
            char conf;
            if (index != -1) {
                printf("Apakah anda yakin ingin menghapus anggota ini? [y / t] : ");
                scanf("%c", &conf);
                if (conf == 'y'){
                    int length = sizeof(member) / sizeof(member[0]);
                    for (int i = index; i < length - 1; i++) {
                        member[i] = member[i + 1];
                    }
                    length--;
                    totalMember--;
                } else if(conf == 't') {
                    printf("Anda keluar dari menu.");
                } else {
                    printf("Input tidak valid. Keluar dari menu.");
                }
            } else {
                printf("Anggota tidak ditemukan, coba periksa kembali!\n");
            }
        }
    } else {
        printf("Tidak ada data anggota.\n");
    }
    return 0;
}

void menuMember() {
    printf(CYAN "||" RESET GREEN "            MENU ANGGOTA            " RESET CYAN "||\n" RESET);
    printf(CYAN "=======================================\n" RESET);
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[1]" RESET, "Tambah Anggota");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s" CYAN "|\n", BLUE "[2]" RESET, "Tampilkan Semua Anggota");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[3]" RESET, "Cari Anggota");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[4]" RESET, "Edit Anggota");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[5]" RESET, "Hapus Anggota");
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
    strcpy(member[0].noHp,"082116375827");
    strcpy(member[0].level,"Member"); // Add default level
    strcpy(member[0].dataMember.alamatUser.namaJalan,"Jl.Jalan");
    strcpy(member[0].dataMember.alamatUser.kelurahan,"Mugarsari");
    strcpy(member[0].dataMember.alamatUser.kecamatan,"Tamansari");
    strcpy(member[0].dataMember.alamatUser.kota,"Tasikmalaya");

    totalMember++;
}

void menuUser() {
    printf(CYAN "||" RESET GREEN "             MENU USER             " RESET CYAN "||\n" RESET);
    printf(CYAN "=======================================\n" RESET);
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[1]" RESET, "Ganti Password");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[2]" RESET, "Ganti Email");
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

    printf("\n Silakan Masukkan Email baru : ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strlen(newEmail) - 1] = '\0';

    do{
        printf("\n Silakan Masukkan password untuk Verfikasi: ");
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