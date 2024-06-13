#ifndef FUNCIONS_H
#define FUNCIONS_H

#define MAX_LLARG_NOM 50
#define MAX_USUARIS 10000

#include <stdbool.h>

typedef struct {
    int id;                        // Identificador únic de l'usuari
    char nom[MAX_LLARG_NOM];       // Nom de l'usuari
    char genere;                   // Gènere de l'usuari (H per home, D per dona)
    char procedencia[MAX_LLARG_NOM]; // Procedència de l'usuari
    char data[MAX_LLARG_NOM];      // Data de naixement de l'usuari
} Usuari_t;

typedef int propers_t; // Definició del tipus per als valors de proximitat

typedef struct {
    int files;         // Nombre de files de la matriu (no s'utilitza actualment)
    int columnes;      // Nombre de columnes de la matriu (no s'utilitza actualment)
    int num_usuaris;   // Nombre total d'usuaris
    propers_t *propers; // Punter a la matriu de proximitat emmagatzemada com una taula 1D
} amist_propers_t;

int carregar_dades_matriu(char filename[], amist_propers_t *amistat);
void guardar_dades_matriu(char filename[], amist_propers_t *amistat);
int carregar_dades(char filename[], Usuari_t **usuaris);
void mostrar_perfil(Usuari_t *usuaris, amist_propers_t *amistat, int user_id);
void mostrar_dades(Usuari_t *usuaris, int num_usuaris);
void mostrar_les_meves_amistats(Usuari_t *usuaris, amist_propers_t *amistat, int user_id);
int possibles_amistats(Usuari_t *usuaris, amist_propers_t *amistat, int user_id);
void afegir_amistat(Usuari_t *usuaris, amist_propers_t *amistat, int user_id, int user_id2);
bool id_existe(Usuari_t *usuaris, int num_usuaris, int id);
void afegir_usuari_al_arxiu(Usuari_t *new_user);
int afegir_usuari(Usuari_t **usuaris, int *num_usuaris, amist_propers_t *amistat);
void eliminar_amistat(Usuari_t *usuaris, amist_propers_t *amistat, int user_id);

#endif // FUNCIONS_H

