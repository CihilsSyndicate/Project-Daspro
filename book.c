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
    int totalPinjaman;
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
    printf("[4] : Daftar Peminjam\n");
    printf("[0] : Keluar\n");
    printf("--------------------------------\n");
}

int tampilkanBuku() {
    printf("\n===============================================\n");
    printf("||              DAFTAR BUKU                  ||\n");
    printf("===============================================\n");
    
    if (totalBuku > 0) {
        for (int i = 0; i < totalBuku; i++) {
            printf("\nBuku ke-%d:\n", i + 1);
            printf("----------------------------------------\n");
            printf("Judul Buku    : %s\n", buku[i].judulBuku);
            printf("Pengarang     : %s\n", buku[i].pengarang);
            printf("Penerbit      : %s\n", buku[i].penerbit);
            printf("Genre         : %s\n", buku[i].genre);
            printf("Stok          : %d\n", buku[i].jumlah);
            printf("----------------------------------------\n");
        }
        printf("\nTotal Buku: %d\n", totalBuku);
        printf("===============================================\n");
        return 1;
    } else {
        printf("||          Data buku masih kosong          ||\n");
        printf("||      Silakan tambahkan buku terlebih     ||\n");
        printf("||               dahulu                     ||\n");
        printf("===============================================\n");
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
        dataPinjam[peminjam].totalPinjaman = 0;
        
        do{
            bookIndex = findBook();
            if(bookIndex > 0) {
                bookIndex -= 1;  

                if(buku[bookIndex].jumlah > 0) {
                    dataPinjam[peminjam].bukuIndex[bookNumber] = bookIndex;
                    dataPinjam[peminjam].totalPinjaman++;
                    buku[bookIndex].jumlah--;
                    bookNumber++;
                    
                    printf("Buku berhasil ditambahkan ke daftar pinjam \n");
                } else {
                    printf("Maaf, stok buku tidak tersedia\n");
                }
            }

            printf("Tambahkan buku lain ? (y/t): ");
            scanf(" %c", &finishPinjamChar);
            getchar();

            if(finishPinjamChar != 'y'){
                isFinishPinjam = true;
            }

        } while(!isFinishPinjam && bookNumber < 10);
        
        if(dataPinjam[peminjam].totalPinjaman > 0) {
            peminjam++;
            printf("\nPeminjaman berhasil dicatat!\n");
        }
    }
}

void daftarPeminjamAktif() {
    printf("\n=== DAFTAR PEMINJAMAN  ===\n\n");    
    
    if (peminjam > 0) {
        for(int i = 0; i < peminjam; i++) {
            printf("Peminjam ke-%d:\n", i + 1);
            printf("----------------------------------------\n");
            printf("Nama Peminjam: %s\n", 
                   member[dataPinjam[i].memberIndex - 1].dataMember.namaLengkap);
            printf("Alamat: %s, %s, %s\n",
                   member[dataPinjam[i].memberIndex - 1].dataMember.alamatUser.namaJalan,
                   member[dataPinjam[i].memberIndex - 1].dataMember.alamatUser.kota,
                   member[dataPinjam[i].memberIndex - 1].dataMember.alamatUser.provinsi);
            
            printf("\nBuku yang dipinjam:\n");
            for(int j = 0; j < dataPinjam[i].totalPinjaman; j++) {
                printf("%d. %s (Pengarang: %s)\n", //bae barengkeun, maneh asup ka 
                       j + 1, 
                       buku[dataPinjam[i].bukuIndex[j]].judulBuku,
                       buku[dataPinjam[i].bukuIndex[j]].pengarang);
            }
            printf("----------------------------------------\n\n");
        }
        printf("Total Peminjam Aktif: %d\n", peminjam);
    } else {
        printf("Tidak ada peminjaman saat ini\n");
    }
    printf("===============================================\n");
}

void kembalikanBuku(){
    if(peminjam > 0){
        int findIndexMember = findMember();
        for(int i = 0; i < peminjam; i++){
            if(findIndexMember-1 == dataPinjam[i].memberIndex){
                printf("\nPeminjam %d. Nama : %s \n", i+1, member[dataPinjam[i].memberIndex].dataMember.namaLengkap);
                printf("Data buku dipinjam : \n");
                for(int j = 0; j < dataPinjam[i].totalPinjaman; j++){
                    printf("Buku 1 : %s \n", buku[dataPinjam[i].bukuIndex[j]].judulBuku);
                }
            }else{
                printf("Member ini tidak meminjam buku \n");
            }
        }
    }else{
        printf("Tidak ada data peminjam \n");
    }
}
