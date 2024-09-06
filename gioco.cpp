#include "gioco.h"
#include "utility.h"

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using std::vector;
using std::string;

struct Carta {
    string nome;
    int valore;
};

void mescolaMazzo(vector<Carta>& mazzo);
Carta distribuisciCarta(vector<Carta>& mazzo);
int calcolaPunteggio(const vector<Carta>& mano);
void mostraMano(const vector<Carta>& mano, const string& giocatore);
void mostraScelte();
bool continuaGiocare();

void gioco(float& saldo) {
    while (true) {
        float puntata = 0;

        pulisci();
        std::cout << "\n BLACKJACK" << std::endl;
        std::cout << "\n Saldo attuale: " << saldo << "$" << std::endl;
        std::cout << "\n Quanto vuoi puntare? (Max 50000): ";
        std::cin >> puntata;

        while (puntata <= 0 || puntata > saldo || puntata > 50000) {
            std::cout << "\n Puntata non valida. Inserisci un importo valido (Max 50000): ";
            std::cin >> puntata;
        }

        saldo -= puntata; 

        vector<string> semi = {"Cuori", "Quadri", "Fiori", "Picche"};
        vector<string> valori = {"Asso", "Due", "Tre", "Quattro", "Cinque", "Sei", 
                                    "Sette", "Otto", "Nove", "Dieci", "Jack", "Regina", "Re"};
        vector<Carta> mazzo;

        for (const auto& seme : semi) {
            for (int i = 0; i < valori.size(); i++) {
                Carta carta;
                carta.nome = valori[i] + " di " + seme;
                if (i >= 9) {
                    carta.valore = 10; 
                } else if (i == 0) {
                    carta.valore = 11; 
                } else {
                    carta.valore = i + 1; 
                }
                mazzo.push_back(carta);
            }
        }

        mescolaMazzo(mazzo);

        vector<Carta> manoGiocatore;
        vector<Carta> manoBanco;

        manoGiocatore.push_back(distribuisciCarta(mazzo));
        manoGiocatore.push_back(distribuisciCarta(mazzo));
        manoBanco.push_back(distribuisciCarta(mazzo));
        manoBanco.push_back(distribuisciCarta(mazzo));

        pulisci();
        std::cout << "\n BLACKJACK" << std::endl;
        std::cout << "\n Saldo attuale: " << saldo << "$" << std::endl;
        std::cout << " Puntata attuale: " << puntata << "$" << std::endl;

        mostraMano(manoGiocatore, "Giocatore");
        mostraMano(manoBanco, "Banco");

        int punteggioGiocatore = calcolaPunteggio(manoGiocatore);
        int punteggioBanco = calcolaPunteggio(manoBanco);

        std::cout << "\n Il tuo punteggio è: " << punteggioGiocatore << std::endl;
        std::cout << " Punteggio del banco: " << punteggioBanco << std::endl;

        while (true) {
            mostraScelte();
            int scelta;
            std::cout << " Scelta: ";
            std::cin >> scelta;

            if (scelta == 1) {  
                manoGiocatore.push_back(distribuisciCarta(mazzo));
                punteggioGiocatore = calcolaPunteggio(manoGiocatore);

                pulisci();
                std::cout << "\n BLACKJACK" << std::endl;
                std::cout << "\n Saldo attuale: " << saldo << "$" << std::endl;
                std::cout << " Puntata attuale: " << puntata << "$" << std::endl;
                mostraMano(manoGiocatore, "Giocatore");
                mostraMano(manoBanco, "Banco");

                std::cout << "\n Il tuo punteggio è: " << punteggioGiocatore << std::endl;
                std::cout << " Punteggio del banco: " << punteggioBanco << std::endl;

                if (punteggioGiocatore > 21) {
                    std::cout << "\n Hai sballato! Hai perso " << puntata << "$." << std::endl;
                    break; 
                }
            } else if (scelta == 2) { 
                while (punteggioBanco < 17) {
                    manoBanco.push_back(distribuisciCarta(mazzo));
                    punteggioBanco = calcolaPunteggio(manoBanco);
                }

                pulisci();
                std::cout << "\n BLACKJACK" << std::endl;
                std::cout << "\n Saldo attuale: " << saldo << "$" << std::endl;
                std::cout << " Puntata attuale: " << puntata << "$" << std::endl;
                mostraMano(manoGiocatore, "Giocatore");
                mostraMano(manoBanco, "Banco");

                std::cout << "\n Il tuo punteggio è: " << punteggioGiocatore << std::endl;
                std::cout << " Punteggio del banco: " << punteggioBanco << std::endl;

                if (punteggioBanco > 21) {
                    std::cout << "\n Il banco ha sballato! Hai vinto " << puntata << "$." << std::endl;
                    saldo += 2 * puntata; 
                } else if (punteggioGiocatore > punteggioBanco) {
                    std::cout << "\n Hai vinto " << puntata << "$!" << std::endl;
                    saldo += 2 * puntata; 
                } else if (punteggioGiocatore < punteggioBanco) {
                    std::cout << "\n Hai perso " << puntata << "$." << std::endl;
                } else {
                    std::cout << "\n Pareggio! La tua puntata è stata restituita." << std::endl;
                    saldo += puntata; 
                }
                break;
            }
        }

        if (!continuaGiocare()) {
            std::cout << "\n Torniamo al menu principale..." << std::endl;
            aspetta(2);
            pulisci();
            break; 
        }
    }
}

void mescolaMazzo(vector<Carta>& mazzo) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(mazzo.begin(), mazzo.end(), g);
}

Carta distribuisciCarta(vector<Carta>& mazzo) {
    Carta carta = mazzo.back(); 
    mazzo.pop_back();            
    return carta;
}

int calcolaPunteggio(const vector<Carta>& mano) {
    int punteggio = 0;
    int numeroAssi = 0;

    for (const auto& carta : mano) {
        punteggio += carta.valore;
        if (carta.valore == 11) { 
            numeroAssi++;
        }
    }

    while (punteggio > 21 && numeroAssi > 0) {
        punteggio -= 10;
        numeroAssi--;
    }

    return punteggio;
}

void mostraMano(const vector<Carta>& mano, const string& giocatore) {
    std::cout << "\n Carte in mano " << giocatore << ":\n";
    for (const auto& carta : mano) {
        std::cout << " - " << carta.nome << " (Valore: " << carta.valore << ")\n";
    }
}

void mostraScelte() {
    std::cout << "\n 1) Chiedi carta";
    std::cout << "\n 2) Stai" << std::endl;
}

bool continuaGiocare() {
    char risposta;
    std::cout << "\n Vuoi continuare a giocare? (s/N): ";
    std::cin >> risposta;
    return (risposta == 's' || risposta == 'S');
}
