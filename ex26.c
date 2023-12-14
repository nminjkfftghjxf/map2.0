#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura pentru a reprezenta o țară
struct Tara {
    char nume[50];
    int culoare;
    int nrVecini;
    struct Tara** vecini;
};

// Functie pentru colorarea țărilor
void coloreazaTari(struct Tara* tari, int numarTari, char** culori) {
    // Sortare descrescătoare a țărilor în funcție de numărul de vecini
    for (int i = 0; i < numarTari - 1; i++) {
        for (int j = 0; j < numarTari - i - 1; j++) {
            if (tari[j].nrVecini < tari[j + 1].nrVecini) {
                struct Tara temp = tari[j];
                tari[j] = tari[j + 1];
                tari[j + 1] = temp;
            }
        }
    }

    // Parcurgere și colorare
    for (int i = 0; i < numarTari; i++) {
        struct Tara* tara = &tari[i];
        int culoareDisponibila = 1;

        // Verificăm culorile vecinilor și alegem o culoare disponibilă
        for (int j = 0; j < tara->nrVecini; j++) {
            struct Tara* vecin = tara->vecini[j];
            if (vecin->culoare != 0) {
                culori[vecin->culoare] = NULL;
            }
        }

        // Alegem prima culoare disponibilă
        for (int j = 1; j <= numarTari; j++) {
            if (culori[j] != NULL) {
                culoareDisponibila = j;
                break;
            }
        }

        // Colorăm țara
        tara->culoare = culoareDisponibila;
    }
}

int main() {
    int numarTari;

    printf("Introduceti numarul de tari: ");
    scanf("%d", &numarTari);

    // Alocare dinamica pentru vectorul de tari
    struct Tara* tari = (struct Tara*)malloc(numarTari * sizeof(struct Tara));

    // Citirea datelor pentru fiecare tara
    for (int i = 0; i < numarTari; i++) {
        printf("Introduceti numele tarii %d: ", i + 1);
        scanf("%s", tari[i].nume);

        printf("Introduceti numarul de vecini pentru tara %s: ", tari[i].nume);
        scanf("%d", &tari[i].nrVecini);

        // Alocare dinamica pentru vectorul de vecini
        tari[i].vecini = (struct Tara**)malloc(tari[i].nrVecini * sizeof(struct Tara*));

        printf("Introduceti numele vecinilor pentru tara %s:\n", tari[i].nume);
        for (int j = 0; j < tari[i].nrVecini; j++) {
            tari[i].vecini[j] = NULL;

            // Alocare dinamica pentru numele vecinilor
            char numeVecin[50];
            scanf("%s", numeVecin);

            // Gasirea tarii corespunzatoare si adaugarea vecinului
            for (int k = 0; k < numarTari; k++) {
                if (strcmp(tari[k].nume, numeVecin) == 0) {
                    tari[i].vecini[j] = &tari[k];
                    break;
                }
            }
        }
    }

    // Vector de culori disponibile
    char* culori[numarTari + 1];
    for (int i = 1; i <= numarTari; i++) {
        culori[i] = (char*)malloc(10 * sizeof(char));
        snprintf(culori[i], 10, "Culoare%d", i);
    }

    // Apelul functiei de colorare
    coloreazaTari(tari, numarTari, culori);

    // Afișarea rezultatelor
    printf("\nRezultatele colorarii:\n");
    for (int i = 0; i < numarTari; i++) {
        printf("Tara: %s, Culoare: %s\n", tari[i].nume, culori[tari[i].culoare]);
    }

    // Eliberarea memoriei alocate dinamic
    for (int i = 0; i < numarTari; i++) {
        free(tari[i].vecini);
    }
    free(tari);

    for (int i = 1; i <= numarTari; i++) {
        free(culori[i]);
    }

    return 0;
}

