#include <stdio.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include <stdlib.h>

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
    char* tanggalPinjam;
};

struct Book buku[100];
struct PinjamBuku dataPinjam[100];


int peminjam = 0;
int totalBuku = 0;


char* getCurrentDate() {
    time_t currentTime;
    struct tm* localTime;
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    char monthName[10];
    int year = localTime->tm_year + 1900;
    int date = localTime->tm_mday;

    switch (localTime->tm_mon) {
        case 0: strcpy(monthName, "Januari"); break;
        case 1: strcpy(monthName, "Februari"); break;
        case 2: strcpy(monthName, "Maret"); break;
        case 3: strcpy(monthName, "April"); break;
        case 4: strcpy(monthName, "Mei"); break;
        case 5: strcpy(monthName, "Juni"); break;
        case 6: strcpy(monthName, "Juli"); break;
        case 7: strcpy(monthName, "Agustus"); break;
        case 8: strcpy(monthName, "September"); break;
        case 9: strcpy(monthName, "Oktober"); break;
        case 10: strcpy(monthName, "November"); break;
        case 11: strcpy(monthName, "Desember"); break;
    }

    char* currentDate = (char*) malloc(30 * sizeof(char));
    sprintf(currentDate, "%02d %s %d", date, monthName, year);
    // printf("%s\n", currentDate);
    return currentDate;
    // return 0;
}

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

void tambahBuku() {
    char isFinish = 'y';

    while (isFinish == 'y' && totalBuku <= 3) {
        if (totalBuku >= 3) {
            printf(RED "Jumlah buku sudah mencapai batas!!\n" RESET);
            break;
        } else {
            printf(CYAN "=========================================\n" RESET);
            printf(CYAN "||" RESET GREEN "         FORM INPUT DATA BUKU        " RESET CYAN "||\n" RESET);
            printf(CYAN "=========================================\n" RESET);

            printf(CYAN "| %-37s |\n", "Masukkan data Buku");
            printf(CYAN "|---------------------------------------|\n" RESET);

            printf(CYAN "| %-28s: " RESET, "Masukan Judul");
            fgets(buku[totalBuku].judulBuku, sizeof(buku[totalBuku].judulBuku), stdin);
            buku[totalBuku].judulBuku[strcspn(buku[totalBuku].judulBuku, "\n")] = '\0';

            printf(CYAN "| %-28s: " RESET, "Masukan Nama Penerbit");
            fgets(buku[totalBuku].penerbit, sizeof(buku[totalBuku].penerbit), stdin);
            buku[totalBuku].penerbit[strcspn(buku[totalBuku].penerbit, "\n")] = '\0';

            printf(CYAN "| %-28s: " RESET, "Masukan Genre");
            fgets(buku[totalBuku].genre, sizeof(buku[totalBuku].genre), stdin);
            buku[totalBuku].genre[strcspn(buku[totalBuku].genre, "\n")] = '\0';

            printf(CYAN "| %-28s: " RESET, "Masukan Nama Pengarang");
            fgets(buku[totalBuku].pengarang, sizeof(buku[totalBuku].pengarang), stdin);
            buku[totalBuku].pengarang[strcspn(buku[totalBuku].pengarang, "\n")] = '\0';

            printf(CYAN "| %-28s: " RESET, "Masukan Jumlah Buku");
            scanf("%d", &buku[totalBuku].jumlah);
            getchar();

            printf(CYAN "---------------------------------------\n\n" RESET);

            printf(YELLOW "Apakah anda ingin menambahkan buku lagi?(y/t): " RESET);
            scanf("%c", &isFinish);
            getchar();

            totalBuku++;
            printf("\n"); 
        }
    }
}
void menuBuku() {
    printf(CYAN "||" RESET GREEN "             MENU BUKU             " RESET CYAN "||\n" RESET);
    printf(CYAN "=======================================\n" RESET);
    
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[1]" RESET, "Tambah Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[2]" RESET, "Edit Data Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[3]" RESET, "Tampilkan Semua Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[4]" RESET, "Pinjamkan Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[5]" RESET, "Daftar Peminjam");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[6]" RESET, "Kembalikan Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[7]" RESET, "Hapus Data Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", RED "[0]" RESET, "Keluar Ke Menu Utama");
    
    printf(CYAN "---------------------------------------\n\n" RESET);
}


int tampilkanBuku() {
    printf(CYAN "==================================================================================================================\n" RESET);
    printf(CYAN "||" RESET YELLOW "                                                   DAFTAR BUKU                                                " RESET CYAN "||\n" RESET);
    printf(CYAN "==================================================================================================================\n" RESET);

    if (totalBuku > 0) {
        printf(CYAN "| %-5s | %-20s | %-25s | %-25s | %-15s | %-5s |\n" RESET, "No", "Judul Buku", "Pengarang", "Penerbit", "Genre", "Stok");
        printf(CYAN "==================================================================================================================\n" RESET);

        for (int i = 0; i < totalBuku; i++) {
            printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-5d" CYAN " |\n" RESET,
                   i + 1,
                   buku[i].judulBuku,
                   buku[i].pengarang,
                   buku[i].penerbit,
                   buku[i].genre,
                   buku[i].jumlah);
        }
        printf(CYAN "==================================================================================================================\n" RESET);
        printf("Total Buku: %d\n", totalBuku);
        printf(CYAN "------------------------------------------------------------------------------------------------------------------\n" RESET);
        return 1;
    } else {
        printf(CYAN "||" RESET "              Data buku masih kosong               " CYAN "||\n" RESET);
        printf(CYAN "||" RESET "          Silakan tambahkan buku terlebih           " CYAN "||\n" RESET);
        printf(CYAN "||" RESET "                    dahulu                          " CYAN "||\n" RESET);
         printf(CYAN "==================================================================================================================\n" RESET);
        return 0;
    }
}

int findBook() {
    char searchTitle[50];
    tampilkanBuku();

    if (totalBuku > 0) {
        printf("Cari data Buku berdasarkan Judul: ");
        getchar(); 
        fgets(searchTitle, sizeof(searchTitle), stdin);
        searchTitle[strcspn(searchTitle, "\n")] = 0; 

        toLowerCase(searchTitle);

        int found = 0;

        printf(CYAN "================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                         HASIL PENCARIAN BUKU                                      " RESET CYAN "||\n" RESET);
        printf(CYAN "================================================================================================\n" RESET);
        printf(CYAN "| %-5s | %-20s | %-25s | %-25s | %-15s | %-5s |\n" RESET, "No", "Judul Buku", "Pengarang", "Penerbit", "Genre", "Stok");
        printf(CYAN "================================================================================================\n" RESET);

        for (int i = 0; i < totalBuku; i++) {
            char bookTitle[50];
            strcpy(bookTitle, buku[i].judulBuku);
            toLowerCase(bookTitle);

            if (strstr(bookTitle, searchTitle) != NULL) {
                printf(CYAN "| %-5d | %-20s | %-25s | %-25s | %-15s | %-5d |\n" RESET, 
                       i + 1,
                       buku[i].judulBuku,
                       buku[i].pengarang,
                       buku[i].penerbit,
                       buku[i].genre,
                       buku[i].jumlah);
                found = 1;
                return i;
            }
        }

        printf(CYAN "================================================================================================\n\n" RESET);

        if (!found) {
            printf("Buku tidak ditemukan, coba periksa kembali!\n");
        }
    } else {
        printf("Tidak ada data buku.\n");
    }
    // return 0;
}

void pinjamkanBuku() {
    int memberIndex = findMember();
    int bookIndex;
    if (memberIndex >= 0) {
        int bookNumber = 0;
        char finishPinjamChar;
        bool isFinishPinjam = false;
        bool isMemberFound = false;
        bool isCurrentDateReceived = false;

        do {
            bookIndex = findBook();
            if (bookIndex >= 0) {

                if (buku[bookIndex].jumlah > 0) {
                    for (int i = 0; i < peminjam; i++) {
                        if (dataPinjam[i].memberIndex == memberIndex) {
                            dataPinjam[i].bukuIndex[dataPinjam[i].totalPinjaman] = bookIndex;
                            dataPinjam[i].totalPinjaman++;
                            buku[bookIndex].jumlah--;
                            bookNumber++;
                            isMemberFound = true;
                            printf("Buku berhasil ditambahkan ke daftar pinjam\n");
                            break;
                        }
                    }

                    if (!isMemberFound) {
                        dataPinjam[peminjam].memberIndex = memberIndex;
                        dataPinjam[peminjam].bukuIndex[dataPinjam[peminjam].totalPinjaman] = bookIndex;
                        dataPinjam[peminjam].totalPinjaman++;
                        dataPinjam[peminjam].tanggalPinjam = getCurrentDate();
                        buku[bookIndex].jumlah--;
                        bookNumber++;
                        peminjam++;
                        printf("Buku berhasil ditambahkan ke daftar pinjam\n");
                    }
                } else {
                    printf("Maaf, stok buku tidak tersedia\n");
                }
            }

            printf("Tambahkan buku lain ? (y/t): ");
            scanf(" %c", &finishPinjamChar);
            getchar();

            if (finishPinjamChar != 'y') {
                isFinishPinjam = true;
            }
        } while (!isFinishPinjam && bookNumber < 10);

    }
        printf("\nPeminjaman berhasil dicatat!\n");
}

void daftarPeminjamAktif() {
    printf("\n=== DAFTAR PEMINJAMAN  ===\n\n");    
    
    if (peminjam > 0) {
        for(int i = 0; i < peminjam; i++) {
            printf("Peminjam ke-%d:\n", i + 1);
            printf("----------------------------------------\n");
            printf("Nama Peminjam: %s\n", 
                   member[dataPinjam[i].memberIndex].dataMember.namaLengkap);
            printf("Alamat: %s, %s, %s\n",
                   member[dataPinjam[i].memberIndex].dataMember.alamatUser.namaJalan,
                   member[dataPinjam[i].memberIndex].dataMember.alamatUser.kelurahan,
                   member[dataPinjam[i].memberIndex].dataMember.alamatUser.kecamatan,
                   member[dataPinjam[i].memberIndex].dataMember.alamatUser.kota);
            
            printf("\nBuku yang dipinjam:\n");
            for(int j = 0; j < dataPinjam[i].totalPinjaman; j++) {
                printf("%d. %s (Pengarang: %s)\n",
                       j + 1, 
                       buku[dataPinjam[i].bukuIndex[j]].judulBuku,
                       buku[dataPinjam[i].bukuIndex[j]].pengarang);
                    
            }
            printf("Tanggal Pinjam : %s \n", dataPinjam[i].tanggalPinjam);
            printf("----------------------------------------\n\n");
        }
        printf("Total Peminjam Aktif: %d\n", peminjam);
    } else {
        printf("Tidak ada peminjaman saat ini\n");
    }
    printf("===============================================\n");
}

void kembalikanBuku() {
    int bukuKembali;
    if (peminjam > 0) {
        int findIndexMember = findMember();
        for (int i = 0; i < peminjam; i++) {
            if (findIndexMember == dataPinjam[i].memberIndex) {
                printf("\nPeminjam %d. Nama : %s \n", i + 1, member[findIndexMember].dataMember.namaLengkap);
                printf("Data buku dipinjam : \n");
                for (int j = 0; j < dataPinjam[i].totalPinjaman; j++) {
                    printf("Buku %d : %s \n", j + 1, buku[dataPinjam[i].bukuIndex[j]].judulBuku);
                }

                printf("Masukan Nomor buku yang akan Dikembalikan: ");
                scanf("%d", &bukuKembali);
                getchar();

                if (bukuKembali > 0 && bukuKembali <= dataPinjam[i].totalPinjaman) {
                    buku[dataPinjam[i].bukuIndex[bukuKembali - 1]].jumlah++;

                    for (int j = bukuKembali - 1; j < dataPinjam[i].totalPinjaman - 1; j++) {
                        dataPinjam[i].bukuIndex[j] = dataPinjam[i].bukuIndex[j + 1];
                    }
                    
                    dataPinjam[i].totalPinjaman--;

                    printf("Buku berhasil dikembalikan!\n");

                    if (dataPinjam[i].totalPinjaman == 0) {

                        for (int k = i; k < peminjam - 1; k++) {
                            dataPinjam[k] = dataPinjam[k + 1];
                        }
                        peminjam--;
                        printf("Member sudah tidak memiliki pinjaman buku.\n");
                    }
                } else {
                    printf("Nomor buku tidak valid!\n");
                }
                return;
            }
        }
        printf("Member ini tidak meminjam buku\n");
    } else {
        printf("Tidak ada data peminjam\n");
    }
}

void editDataBuku(){
    int bookIndex = findBook();

    printf(CYAN "=========================================\n" RESET);
    printf(CYAN "||" RESET GREEN "         FORM EDIT DATA BUKU        " RESET CYAN "||\n" RESET);
    printf(CYAN "=========================================\n" RESET);

    printf(CYAN "| %-37s |\n", "Masukkan data Buku");
    printf(CYAN "|---------------------------------------|\n" RESET);

    printf(CYAN "| %-28s: " RESET, "Masukan Judul");
    fgets(buku[bookIndex].judulBuku, sizeof(buku[bookIndex].judulBuku), stdin);
    buku[bookIndex].judulBuku[strcspn(buku[bookIndex].judulBuku, "\n")] = '\0';

    printf(CYAN "| %-28s: " RESET, "Masukan Nama Penerbit");
    fgets(buku[bookIndex].penerbit, sizeof(buku[bookIndex].penerbit), stdin);
    buku[bookIndex].penerbit[strcspn(buku[bookIndex].penerbit, "\n")] = '\0';

    printf(CYAN "| %-28s: " RESET, "Masukan Genre");
    fgets(buku[bookIndex].genre, sizeof(buku[bookIndex].genre), stdin);
    buku[bookIndex].genre[strcspn(buku[bookIndex].genre, "\n")] = '\0';

    printf(CYAN "| %-28s: " RESET, "Masukan Nama Pengarang");
    fgets(buku[bookIndex].pengarang, sizeof(buku[bookIndex].pengarang), stdin);
    buku[bookIndex].pengarang[strcspn(buku[bookIndex].pengarang, "\n")] = '\0';

    printf(CYAN "| %-28s: " RESET, "Masukan Jumlah Buku");
    scanf("%d", &buku[bookIndex].jumlah);
    getchar();

    printf(CYAN "---------------------------------------\n\n" RESET);

    printf(YELLOW "Data Buku berhasil diubah: " RESET);
    printf("\n"); 

}

void hapusDataBuku(){
    int bookIndex = findBook();
    char isDelete;

        printf(YELLOW "Apakah anda benar - benar ingin menghapus data buku ini ? [y / t]" RESET);
        scanf("%c", &isDelete);
        getchar();
        printf("\n");
        if(isDelete == 'y'){

            for (int i = 0; i < totalBuku; i++)
            {
                if(bookIndex == i - 1){
                    for(int j = bookIndex - 1; j < totalBuku - 1 ; j++){
                        buku[i - 1] = buku[j + 1];
                    }
                }
            }
            totalBuku--;   


            printf(YELLOW "Data buku berhasil dihapus " RESET);
            printf("\n");
        }else{
            printf(YELLOW "Data buku batal dihapus " RESET);
            printf("\n");
        }

        // if (dataPinjam[i].totalPinjaman == 0) {

        //     for (int k = i; k < peminjam - 1; k++) {
        //         dataPinjam[k] = dataPinjam[k + 1];
        //     }
        //     peminjam--;
        //     printf("Member sudah tidak memiliki pinjaman buku.\n");
        // }
}