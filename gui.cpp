#include <iostream>
#include <clocale>
#include "caricaSaldo.h"
#include "utility.h"
#include "gioco.h"

int main(int argc, char** argv) {
    std::setlocale(LC_ALL, "it_IT.utf8");

    float saldo = 5000;
    int scelta = 0;

    pulisci();

    do {
        std::cout << "\n BLACKJACK" << std::endl;
        std::cout << "\n Saldo attuale: " << saldo << "$" << std::endl;
        std::cout << "\n 1) Gioca";
        std::cout << "\n 2) Carica saldo";
        std::cout << "\n 3) Esci" << std::endl;
        std::cout << "\n Scelta: ";
        std::cin >> scelta;

        switch (scelta) {
            case 1:
                gioco(saldo);
                break;
            case 2:
                caricaSaldo(saldo);
                break;
        }

        if (scelta <= 0 || scelta > 3) {
            pulisci();
            std::cout << "\n La scelta inserita non è valida." << std::endl;
        }

    } while (scelta != 3);
    return 0;
}