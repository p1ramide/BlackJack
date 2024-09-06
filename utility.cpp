#include "utility.h"
#include <cstdlib>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

void pulisci() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void aspetta(int secondi) {
    #ifdef _WIN32
        Sleep(secondi * 1000); 
    #else
        sleep(secondi); 
    #endif
}