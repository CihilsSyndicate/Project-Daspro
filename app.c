#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "book.c"
#include "user.h"
#include "colors.h"


void printCentered(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    printf("%*s%s%*s\n", padding, "", text, padding, "");
}


void header() {
    printf(CYAN "=======================================\n" RESET);
    printf(CYAN "||" RESET YELLOW "        PERPUSTAKAAN HITAM         " RESET CYAN "||\n" RESET);
    printf(CYAN "=======================================\n" RESET);
}

void menuUtama() {
    printf(CYAN "||" RESET GREEN "            MENU UTAMA             " RESET CYAN "||\n" RESET);
    printf(CYAN "=======================================\n" RESET);
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n" RESET, BLUE "[1]" RESET, "Manajemen Member");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n" RESET, BLUE "[2]" RESET, "Manajemen Buku");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n" RESET, BLUE "[3]" RESET, "Manajemen Akun");
    printf(CYAN "| %s " CYAN "|" RESET " %-29s " CYAN "|\n" RESET, RED "[0]" RESET, "Keluar");
    printf(CYAN "---------------------------------------\n\n" RESET);
}

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}



int login() {
	int menu;
	int subMenu;
	int isExitNum = 0;
	bool isExit = false;
	int loginAttempt = 0;
	do {
		char email[50], password[50];
		header();

		printf("Masukkan Email anda : ");
		fgets(email, sizeof(email), stdin);
		email[strlen(email) - 1] = '\0';

		printf("Masukkan Password anda : ");
		fgets(password, sizeof(password), stdin);
		password[strlen(password) - 1] = '\0';

		if(strcmp(email, admin[0].email) == 0 && strcmp(password, admin[0].password) == 0) {
			do {
				int exitSubMenu = 0;         
				clear();
				header();
				menuUtama();

				printf("\nPilih menu: ");
				scanf("%d", &menu);
				getchar();


				switch(menu) {
				case 1:
					
					exitSubMenu = 0;
					int subMenu = 0;  
					do {
						clear();
						header();
						menuMember();
						printf("\nPilih sub-menu: ");
						scanf("%d", &subMenu);
						getchar();

						switch (subMenu) {
						case 1:
							addMember();
							break;
						case 2:
							getDataMember();
							break;
						case 3:
							findMember();
							break;
						case 0:
							exitSubMenu = 1;
							break;
						default:
							printf("Pilihan anda tidak valid\n");
							break;
						}

						if(subMenu != 0 && !exitSubMenu) {
							printf("\nTekan Enter untuk melanjutkan..");
							getchar();
						}

					} while (!exitSubMenu);

					break;
				case 2:
					// Menu Buku
					exitSubMenu = 0;
					subMenu = 0;
					do {
						clear();
						header();
						menuBuku();
						printf("\nPilih sub-menu: ");
						scanf("%d", &subMenu);
						getchar();

						switch (subMenu) {
						case 1:
							tambahBuku();
							break;
						case 2:
							tampilkanBuku();
							break;
						case 3:
							pinjamkanBuku();
							break;
						case 4:
							daftarPeminjamAktif();
							break;
						case 5:
							kembalikanBuku();
							break;
						case 0:
							exitSubMenu = 1;
							break;
						default:
							printf("Pilihan anda tidak valid\n");
							break;
						}

						if(subMenu != 0 && !exitSubMenu) {
							printf("\nTekan Enter untuk melanjutkan..");
							getchar();
						}

					} while (!exitSubMenu);

					break;
				case 3:
					// Menu User
					exitSubMenu = 0;
					subMenu = 0;
					do {
						clear();
						header();
						menuUser();
						printf("\nPilih sub-menu: ");
						scanf("%d", &subMenu);
						getchar();
						bool isRelog = false;

						do {
							switch (subMenu) {
							case 1:
								clear();
								header();
								isRelog = changePassword();
								break;
							case 2:
								clear();
								header();
								isRelog = changeEmail();
								break;
							case 0:
								exitSubMenu = 1;
								break;
							default:
								printf("Pilihan anda tidak valid\n");
								break;
							}

							if(isRelog && subMenu != 0) {
								clear();
								printf("Password berhasil diubah, Silakan Login Kembali ! \n");
								login();
							}
						} while(!isRelog && subMenu != 0);

					} while (!exitSubMenu);

					break;
				case 0:
						printf("See ya!\n");
						isExit = true;
						break;
				default:
					printf("Pilihan anda tidak valid\n");
					printf("\nTekan Enter untuk melanjutkan..");
					getchar();
					break;
				}

			} while(!isExit);
			break;
		} else {
			clear();
			printf("Data yang anda masukkan salah, coba lagi \n");
			loginAttempt++;
		}
	} while(loginAttempt < 3);

	if (loginAttempt >= 3) {
		printf("Akun anda telah diblokir \n");
	}
	return 0;
}

int main() {

	bukuSementara();
	seedUser();
	seedMember();
	login();
}
