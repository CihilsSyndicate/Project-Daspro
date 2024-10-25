#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "book.c"
#include "user.h"


void header() {
	printf("=======================================\n");
	printf("||        PERPUSTAKAAN HITAM         ||\n");
	printf("=======================================\n\n");
}

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void menuUtama() {
	printf("\nMenu Utama:\n");
	printf("--------------------------------\n");
	printf("[1] : Manajemen Member\n");
	printf("[2] : Manajemen Buku\n");
	printf("[3] : Manajemen Akun\n");
	printf("[0] : Keluar\n");
	printf("--------------------------------\n");
}

int login();

int main() {

	bukuSementara();
	seedUser();
	login();
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
				clear();
				header();
				menuUtama();

				printf("\nPilih menu: ");
				scanf("%d", &menu);
				getchar();

				switch(menu) {
				case 1:
					do
					{
						clear();
						header();
						menuMember();
						printf("\nPilih sub-menu: ");
						scanf("%d", &subMenu);
						getchar();

						switch (subMenu)
						{
						case 1:
							addMember();
							break;
						case 2:
							getDataMember();
							break;
						case 3:
							findMember();
							break;

						default:
							break;
						}

						if(subMenu != 0) {
							printf("\nTekan Enter untuk melanjutkan..");
							getchar();
						}

					} while (subMenu != 0);

					break;
				case 2:
					do
					{
						clear();
						header();
						menuBuku();
						printf("\nPilih sub-menu: ");
						scanf("%d", &subMenu);
						getchar();

						switch (subMenu)
						{
						case 1:
							tambahBuku();
							break;
						case 2:
							tampilkanBuku();
							break;

						default:
							break;
						}

						if(subMenu != 0) {
							printf("\nTekan Enter untuk melanjutkan..");
							getchar();
						}

					} while (subMenu != 0);

					break;
				case 3:
					do {
						clear();
						header();
						menuUser();
						printf("\nPilih sub-menu: ");
						scanf("%d", &subMenu);
						getchar();
						bool isRelog = false;

						do {
							switch (subMenu)
							{
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
							default:
								break;
							}
							if(isRelog) {
								clear();
								printf("Password berhasil diubah, Silakan Login Kembali ! \n");
								login();
							}
						} while(!isRelog);

					} while(subMenu != 0);
					break;
				case 0:  
					printf("See ya!\n");
					isExit = true; 
					break;
				default:
					printf("Pilihan tidak valid. Silakan coba lagi.\n");
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