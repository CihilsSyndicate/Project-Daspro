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
    char* tanggalKembali;  // New field
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

char* getDueDate(char* borrowDate) {
    time_t currentTime;
    struct tm loanDate = {0};
    char day[3], year[5], monthStr[20];
    
    sscanf(borrowDate, "%s %s %s", day, monthStr, year);
    
    loanDate.tm_mday = atoi(day);
    loanDate.tm_year = atoi(year) - 1900;
    
    // Convert month name to number
    const char *months[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", 
                           "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    for(int i = 0; i < 12; i++) {
        if(strcmp(monthStr, months[i]) == 0) {
            loanDate.tm_mon = i;
            break;
        }
    }

    currentTime = mktime(&loanDate);
    currentTime += (7 * 24 * 60 * 60); // Add 7 days
    
    struct tm* dueDate = localtime(&currentTime);
    char* dueDateStr = (char*) malloc(30 * sizeof(char));
    sprintf(dueDateStr, "%02d %s %d", dueDate->tm_mday, months[dueDate->tm_mon], dueDate->tm_year + 1900);
    
    return dueDateStr;
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
        if (totalBuku >= 100) {
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
    
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[1]" RESET, "Cari Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[2]" RESET, "Tambah Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[3]" RESET, "Edit Data Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[4]" RESET, "Tampilkan Semua Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[5]" RESET, "Pinjamkan Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[6]" RESET, "Daftar Peminjam");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[7]" RESET, "Kembalikan Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n", BLUE "[8]" RESET, "Hapus Data Buku");
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

        printf(CYAN "==================================================================================================================\n" RESET);
        printf(CYAN "||" RESET YELLOW "                                                   DAFTAR BUKU                                                " RESET CYAN "||\n" RESET);
        printf(CYAN "==================================================================================================================\n" RESET);
        printf(CYAN "| %-5s | %-20s | %-25s | %-25s | %-15s | %-5s |\n" RESET, "No", "Judul Buku", "Pengarang", "Penerbit", "Genre", "Stok");
        printf(CYAN "==================================================================================================================\n" RESET);

        for (int i = 0; i < totalBuku; i++) {
            char bookTitle[50];
            strcpy(bookTitle, buku[i].judulBuku);
            toLowerCase(bookTitle);

            if (strstr(bookTitle, searchTitle) != NULL) {
                printf(CYAN "| " RESET "%-5d" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-25s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-5d" CYAN " |\n" RESET,
                    i + 1,
                    buku[i].judulBuku,
                    buku[i].pengarang,
                    buku[i].penerbit,
                    buku[i].genre,
                    buku[i].jumlah);
                found = 1;
                return i+1;
            }
        }

        printf(CYAN "==================================================================================================================\n" RESET);
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
    if (memberIndex > 0) {
        memberIndex -= 1;
        int bookNumber = 0;
        char finishPinjamChar;
        bool isFinishPinjam = false;

        do {
            bookIndex = findBook();
            if (bookIndex) {
                bookIndex -= 1;
                if (buku[bookIndex].jumlah > 0) {
                    bool isMemberFound = false;
                    bool alreadyBorrowed = false;

                    for (int i = 0; i < peminjam; i++) {
                        if (dataPinjam[i].memberIndex == memberIndex) {
                            isMemberFound = true;
                            
                            for (int j = 0; j < dataPinjam[i].totalPinjaman; j++) {
                                if (dataPinjam[i].bukuIndex[j] == bookIndex) {
                                    alreadyBorrowed = true;
                                    if (strcmp(member[memberIndex].level, "Anggota") == 0) {
                                        printf("Maaf, Anggota tidak dapat meminjam buku yang sama disaat bersamaan!\n");
                                        break;
                                    }
                                }
                            }

                            if (!alreadyBorrowed || strcmp(member[memberIndex].level, "Member") == 0) {
                                if (dataPinjam[i].totalPinjaman < 10) {
                                    dataPinjam[i].bukuIndex[dataPinjam[i].totalPinjaman] = bookIndex;
                                    dataPinjam[i].totalPinjaman++;
                                    dataPinjam[i].tanggalPinjam = getCurrentDate();
                                    dataPinjam[i].tanggalKembali = getDueDate(dataPinjam[i].tanggalPinjam);
                                    buku[bookIndex].jumlah--;
                                    bookNumber++;
                                    printf("\nBuku berhasil ditambahkan ke daftar pinjam\n\n");
                                } else {
                                    printf("Maaf, batas maksimum peminjaman buku adalah 10\n");
                                }
                            }
                            break;
                        }
                    }

                    // If member doesn't have any active borrowings yet
                    if (!isMemberFound) {
                        dataPinjam[peminjam].memberIndex = memberIndex;
                        dataPinjam[peminjam].bukuIndex[0] = bookIndex;
                        dataPinjam[peminjam].totalPinjaman = 1;
                        dataPinjam[peminjam].tanggalPinjam = getCurrentDate();
                        dataPinjam[peminjam].tanggalKembali = getDueDate(dataPinjam[peminjam].tanggalPinjam);
                        buku[bookIndex].jumlah--;
                        bookNumber++;
                        peminjam++;
                        printf("\nBuku berhasil ditambahkan ke daftar pinjam\n\n");
                    }
                } else {
                    printf("Maaf, stok buku tidak tersedia\n");
                }

                printf("Tambahkan buku lain ? (y/t): ");
                scanf(" %c", &finishPinjamChar);
                getchar();

                if (finishPinjamChar != 'y') {
                    isFinishPinjam = true;
                }
            } else {
                printf("Buku tidak ada \n");
            }

        } while (!isFinishPinjam && bookNumber < 10);

        printf("\nPeminjaman berhasil dicatat!\n");
    } else {
        printf("Peminjaman buku gagal ! \n");
    }
}

void daftarPeminjamAktif() {
    printf(CYAN "===========================================================================================================================\n" RESET);
    printf(CYAN "||" RESET YELLOW "                                              DAFTAR PEMINJAMAN AKTIF                                             " RESET CYAN "||\n" RESET);
    printf(CYAN "===========================================================================================================================\n" RESET);

    if (peminjam > 0) {
        printf(CYAN "| %-4s | %-20s | %-20s | %-20s | %-15s | %-15s |\n" RESET,
               "No", "Nama Peminjam", "Alamat", "Buku Dipinjam", "Tanggal Pinjam", "Batas Kembali");
        printf(CYAN "---------------------------------------------------------------------------------------------------------------------------\n" RESET);

        int no = 1;
        for (int i = 0; i < peminjam; i++) {
            for (int j = 0; j < dataPinjam[i].totalPinjaman; j++) {
                printf(CYAN "| " RESET "%3d" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-20s" CYAN " | " RESET "%-15s" CYAN " | " RESET "%-15s" CYAN " |\n" RESET,
                       no,
                       member[dataPinjam[i].memberIndex].dataMember.namaLengkap,
                       member[dataPinjam[i].memberIndex].dataMember.alamatUser.namaJalan,
                       buku[dataPinjam[i].bukuIndex[j]].judulBuku,
                       dataPinjam[i].tanggalPinjam,
                       dataPinjam[i].tanggalKembali);
                no++;
            }
            printf(CYAN "---------------------------------------------------------------------------------------------------------------------------\n" RESET);
        }

        printf(CYAN "|" RESET GREEN " Total Peminjam Aktif: %-3d" RESET CYAN "|\n" RESET, peminjam);
    } else {
        printf(RED "                                              Tidak ada peminjaman saat ini                                              \n" RESET);
    }

    printf(CYAN "===========================================================================================================================\n\n" RESET);
}

void kembalikanBuku() {
    int bukuKembali;
    if (peminjam > 0) {
        int findIndexMember = findMember();
        if (findIndexMember > 0) {
            findIndexMember -= 1;
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
            printf("Member tidak ditemukan\n");
        }
    } else {
        printf("Tidak ada data peminjam\n");
    }
}

void editDataBuku(){
    int bookIndex = findBook();

    if(bookIndex-1 > -1){
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

    }else{
        printf("Buku tidak ada.\n");
    }

}

void hapusDataBuku() {
    int bookIndex = findBook();
    char isDelete;

    if (bookIndex > 0) {
        printf(YELLOW "Apakah anda benar - benar ingin menghapus data buku ini ? [y / t]" RESET);
        scanf("%c", &isDelete);
        getchar();
        printf("\n");

        if (isDelete == 'y') {
            // Shift all books after the deleted index one position up
            for (int i = bookIndex - 1; i < totalBuku - 1; i++) {
                buku[i] = buku[i + 1];
            }
            totalBuku--;
            printf(YELLOW "Data buku berhasil dihapus\n" RESET);
        } else {
            printf(YELLOW "Data buku batal dihapus\n" RESET);
        }
    } else {
        printf("Buku tidak ditemukan\n");
    }
}