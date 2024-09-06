#include "caricaSaldo.h"
#include "utility.h"
#include <iostream>

void caricaSaldo(float& saldo) {
    float saldoCaricato;

    pulisci();

    std::cout << "\n BLACKJACK" << std::endl;
    std::cout << "\n Saldo attuale: " << saldo << "$" << std::endl;
    std::cout << "\n Quanti soldi vuoi caricare nel saldo? (Max 1M): ";
    std::cin >> saldoCaricato;
    
    if (saldoCaricato > 0 && saldoCaricato < 1000000) {
        saldo += saldoCaricato;
        std::cout << "\n Il suo saldo è stato aggiornato con successo a " << saldo << "$.";
    } else {
        std::cout << "\n Il saldo inserito non è valido, il suo saldo è rimasto invariato.";
    }
    aspetta(3);
    pulisci();
}
