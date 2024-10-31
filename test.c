#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

// int main() {
//     int *numbers;
//     numbers = (int)malloc(50 * sizeof(int));

//     numbers[0] = 1;

//     return 0;
// }

typedef struct {
    char* tanggal;
}Konz;

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

int main(){
    Konz tanggal1;
    // char* now = getCurrentDate();
    tanggal1.tanggal = getCurrentDate();
    printf("%s \n", tanggal1.tanggal);
    return 0;
}