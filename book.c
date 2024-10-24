#include <stdio.h>
#include <string.h>

struct Book
{
    char judulBuku[100];
    char penerbit[50];
    char genre[50];
    char pengarang[50];
    int jumlah;
};

struct Book buku[100];
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
        scanf("%d", &buku[totalBuku].judulBuku);

        totalBuku++;

        printf("Apakah anda ingin menambahkan buku lagi?(y/t): ");
        scanf("%c", &isFinish);
    }while (isFinish == 't');
    

}