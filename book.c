#include <stdio.h>
#include <string.h>
#include "user.h"

struct Book
{
    char judulBuku[100];
    char penerbit[50];
    char genre[50];
    char pengarang[50];
    int jumlah;
};


struct PinjamBuku{
    int memberIndex;
    int bukuIndex[10];
};

struct Book buku[100];
struct PinjamBuku dataPinjam[100];


int peminjam = 0;
int totalBuku = 0;


void bukuSementara(){
    strcpy(buku[0].judulBuku, "Laskar Pelangi");
    strcpy(buku[0].penerbit, "Bentang Pustaka");
    strcpy(buku[0].genre, "Novel");
    strcpy(buku[0].pengarang, "Andrea Hirata");
    buku[0].jumlah = 5;

    strcpy(buku[1].judulBuku, "Bumi Manusia");
    strcpy(buku[1].penerbit, "Hasta Mitra");
    strcpy(buku[1].genre, "Novel Sejarah");
    strcpy(buku[1].pengarang, "Pramoedya Ananta Toer");
    buku[1].jumlah = 3;

    totalBuku = 2; 
}

void tambahBuku(){
    char isFinish = 'y';
    if(totalBuku >= 100){
        printf("Jumlah buku sudah mencapai batas!!");
    }

    do{
        printf("\n====== Tambah Buku ======\n");

        printf("Masukan Judul: ");
        fgets(buku[totalBuku].judulBuku, sizeof(buku[totalBuku].judulBuku), stdin);
        buku[totalBuku].judulBuku[strlen(buku[totalBuku].judulBuku) - 1] = '\0';

        printf("Masukan Nama Penerbit: ");
        fgets(buku[totalBuku].penerbit, sizeof(buku[totalBuku].penerbit), stdin);
        buku[totalBuku].penerbit[strlen(buku[totalBuku].penerbit) - 1] = '\0';

        printf("Masukan Genre: ");
        fgets(buku[totalBuku].genre, sizeof(buku[totalBuku].genre), stdin);
        buku[totalBuku].genre[strlen(buku[totalBuku].genre) - 1] = '\0';

        printf("Masukan Nama Pengarang: ");
        fgets(buku[totalBuku].pengarang, sizeof(buku[totalBuku].pengarang), stdin);
        buku[totalBuku].pengarang[strlen(buku[totalBuku].pengarang) - 1] = '\0';

        printf("Masukan Jumlah Buku: ");
        scanf("%d", &buku[totalBuku].jumlah);
        getchar();

        totalBuku++;

        printf("Apakah anda ingin menambahkan buku lagi?(y/t): ");
        scanf("%c", &isFinish);
        getchar();
    }while (isFinish == 'y');

}

void menuBuku(){
    printf("\nMenu Buku:\n");
    printf("--------------------------------\n");
    printf("[1] : Tambah Buku\n");
    printf("[2] : Tampilkan Semua Buku\n");
    printf("[3] : Pinjamkan Buku\n");
    printf("[0] : Keluar\n");
    printf("--------------------------------\n");
}

int tampilkanBuku(){
    printf("\n========== Buku ==========\n");
    if(totalBuku > 0){
        for (int i = 0; i < totalBuku; i++)
        {
            printf("%d. %s\n", i + 1, buku[i].judulBuku);
        }
    }else{
        printf("Data buku kosong, silakan diisi terlebih dahulu \n");
        return 0;
    }
    
}

int findBook(){
    int bookIndex;
    tampilkanBuku();

    if(totalBuku > 0){
        printf("Pilih buku berdasarkan Nomor : ");
        scanf("%d", &bookIndex);

        printf("Data Buku \n");
        printf("No Urut Buku : %d \n", bookIndex);

        bookIndex -= 1;

        printf("Judul Buku : %s \n", buku[bookIndex].judulBuku);
        printf("Genre Buku : %s \n", buku[bookIndex].genre);
        printf("Pengarang Buku : %s \n", buku[bookIndex].pengarang);
        printf("Penerbit Buku : %s \n", buku[bookIndex].penerbit);
        printf("Jumlah Buku : %d \n", buku[bookIndex].jumlah);

        return bookIndex += 1;

    }

}

void pinjamkanBuku(){
    int memberIndex = findMember();
    int bookIndex;
    if(memberIndex > 0){
        int bookNumber = 0;
        char finishPinjamChar;
        bool isFinishPinjam = false;
        memberIndex -= 1;
        dataPinjam[peminjam].memberIndex = memberIndex;

        do{
            bookIndex = findBook();
            dataPinjam[peminjam].bukuIndex[bookNumber] = bookIndex-1;
            
            bookNumber++;
            printf("Buku berhasil ditambahkan ke daftar pinjam \n");

            printf("Tambahkan buku lain ? (y/t)");
            scanf("%c", &finishPinjamChar);
            getchar();

            if(finishPinjamChar != 'y'){
                isFinishPinjam = true;
            }


        }while(!isFinishPinjam);
        peminjam++;

    }
}

