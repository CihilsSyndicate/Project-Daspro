#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "book.c"
#include "user.h"
#include "colors.h"
#include <windows.h>
#include <mmsystem.h>




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


		for(int i = 0; i < sizeof(admin) / sizeof(admin[0]); i++){

			if(strcmp(email, admin[i].email) == 0 && strcmp(password, admin[i].password) == 0) {
				do {
					int exitSubMenu = 0;         
					clear();
					header();
					menuUtama();

					printf("\nPilih menu: ");
					char menuInput[10];
					fgets(menuInput, sizeof(menuInput), stdin);

					if (sscanf(menuInput, "%d", &menu) != 1) {
						printf("Input tidak valid. Harap masukkan angka.\n");
						printf("\nTekan Enter untuk melanjutkan...");
						getchar();
						continue; 
					}
					switch(menu) {
					case 1:
						// Menu Member
						exitSubMenu = 0;
						int subMenu = 0;  
						do {
							clear();
							header();
							menuMember();
							printf("\nPilih sub-menu: ");
							fgets(menuInput, sizeof(menuInput), stdin);

							if (sscanf(menuInput, "%d", &subMenu) != 1) {
								printf("Input tidak valid. Harap masukkan angka.\n");
								printf("\nTekan Enter untuk melanjutkan...");
								getchar();
								continue;
							}

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
							fgets(menuInput, sizeof(menuInput), stdin);

							if (sscanf(menuInput, "%d", &subMenu) != 1) {
								printf("Input tidak valid. Harap masukkan angka.\n");
								printf("\nTekan Enter untuk melanjutkan...");
								getchar();
								continue;
							}

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
							fgets(menuInput, sizeof(menuInput), stdin);

							if (sscanf(menuInput, "%d", &subMenu) != 1) {
								printf("Input tidak valid. Harap masukkan angka.\n");
								printf("\nTekan Enter untuk melanjutkan...");
								getchar();
								continue;
							}

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
									printf("Password berhasil diubah, Silakan Login Kembali!\n");
									login();
								}
							} while(!isRelog && subMenu != 0);

						} while (!exitSubMenu);
						break;

					case 0:
						printf(RED " _____        _                           _     _____  _                              _  _ \n" RESET);
						printf(RED "/  ___|      | |                         | |   |_   _|(_)                            | || | \n" RESET);
						printf(RED "\\ `--.   ___ | |  __ _  _ __ ___    __ _ | |_    | |   _  _ __    __ _   __ _   __ _ | || | \n" RESET);
						printf(RED " `--. \\ / _ \\| | / _` || '_ ` _ \\  / _` || __|   | |  | || '_ \\  / _` | / _` | / _` || || |\n" RESET);
						printf(RED "/\\__/ /|  __/| || (_| || | | | | || (_| || |_    | |  | || | | || (_| || (_| || (_| || ||_|\n" RESET);
						printf(RED "\\____/  \\___||_| \\__,_||_| |_| |_| \\__,_| \\__|   \\_/  |_||_| |_| \\__, | \\__, | \\__,_||_|(_)\n" RESET);
						printf(RED "                                                                  __/ |  __/ |             \n" RESET);
						printf(RED "                                                                 |___/  |___/      \n\n" RESET);

						isExit = true;
						break;

					default:
						printf("Pilihan anda tidak valid\n");
						printf("\nTekan Enter untuk melanjutkan...");
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
				
		}
	} while(loginAttempt < 3);

	if (loginAttempt >= 3) {
		printf("Akun anda telah diblokir \n");
	}
	return 0;
}

// void playBackgroundMusic() {
  
//     PlaySound("bgm.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
// }

int main() {

 	// playBackgroundMusic();
	bukuSementara();
	seedUser();
	seedMember();
	login();
	// PlaySound(NULL, 0, 0);
}
