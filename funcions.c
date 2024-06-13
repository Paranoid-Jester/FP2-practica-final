#include "funcions.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Carrega les dades de la matriu de proximitat des d'un fitxer.
 * @param filename Nom del fitxer des del qual carregar les dades.
 * @param amistat Punter a l'estructura amist_propers_t on s'emmagatzemaran les dades.
 * @return 1 si la càrrega ha estat exitosa, 0 en cas d'error.
 */
int carregar_dades_matriu(char filename[], amist_propers_t *amistat) {
    int funciona = 1; // VARIABLE PER DETERMINAR SI FUNCIONA 1 = OK, 0 = NO OK
    FILE *fitxer;

    // Obre el fitxer en mode de lectura
    fitxer = fopen(filename, "r");

    if (fitxer == NULL) {
        // Mostra un missatge d'error si el fitxer no es pot obrir
        printf("ERROR EN OBRIR EL FITXER \n");
        funciona = 0;
    }

    // Llegeix el nombre d'usuaris des del fitxer
    fscanf(fitxer, "%d", &(amistat->num_usuaris));

    // Allibera memòria per emmagatzemar la matriu de proximitat
    amistat->propers = malloc(amistat->num_usuaris * amistat->num_usuaris * sizeof(propers_t));
    if (amistat->propers == NULL) {
        // Mostra un missatge d'error si no es pot reservar memòria
        printf("ERROR EN MEMORIA \n");
        funciona = 0;
    } else {
        // Llegeix les dades de la matriu de proximitat des del fitxer
        for (int i = 0; i < amistat->num_usuaris; i++) {
            for (int j = 0; j < amistat->num_usuaris; j++) {
                fscanf(fitxer, "%d", &(amistat->propers[i * amistat->num_usuaris + j]));
            }
        }
    }

    // Tanca el fitxer després de llegir les dades
    fclose(fitxer);

    return funciona; // Retorna l'estat de la càrrega de dades
}

/**
 * @brief Guarda les dades de la matriu de proximitat en un fitxer.
 * @param filename Nom del fitxer on es guardaran les dades.
 * @param amistat Punter a l'estructura amist_propers_t que conté les dades a guardar.
 */
void guardar_dades_matriu(char filename[], amist_propers_t *amistat) {
    FILE *fitxer = fopen(filename, "w"); // Obre el fitxer en mode escriptura

    if (fitxer == NULL) {
        // Mostra un missatge d'error si el fitxer no es pot obrir
        printf("ERROR EN OBRIR EL FITXER PER ESCRIURE \n");
    } else {
        // Escriu el nombre d'usuaris a la primera línia del fitxer
        fprintf(fitxer, "%d\n", amistat->num_usuaris);

        // Recorre la matriu per guardar les dades de proximitat
        for (int i = 0; i < amistat->num_usuaris; i++) {
            for (int j = 0; j < amistat->num_usuaris; j++) {
                // Escriu el valor de proximitat entre l'usuari i i l'usuari j
                fprintf(fitxer, "%d ", amistat->propers[i * amistat->num_usuaris + j]);
            }
            // Escriu una nova línia després de cada fila de la matriu
            fprintf(fitxer, "\n");
        }

        fclose(fitxer); // Tanca el fitxer després de guardar les dades
    }
}

/**
 * @brief Carrega les dades dels usuaris des d'un fitxer.
 * @param filename Nom del fitxer des del qual carregar les dades.
 * @param usuaris Doble punter a l'estructura Usuari_t on s'emmagatzemaran les dades.
 * @return Nombre d'usuaris carregats.
 */
int carregar_dades(char filename[], Usuari_t **usuaris) {
    int nombre_usuaris;
    FILE *fitxer;

     // Obre el fitxer en mode de lectura
    fitxer = fopen(filename, "r");

    if (fitxer == NULL) {
        printf("ERROR EN OBRIR EL FITXER \n");
    }

    fscanf(fitxer, "%d", &nombre_usuaris); // Llegeix el nombre d'usuaris des del fitxer

    *usuaris = malloc(nombre_usuaris * sizeof(Usuari_t));// Allibera memòria per emmagatzemar les dades dels usuaris
    if (*usuaris ==  NULL) {
        printf("error");
        fclose(fitxer);
    }
    // Llegeix les dades de cada usuari des del fitxer
    for (int i = 0; i < nombre_usuaris; i++) {
        fscanf(fitxer, "%d %s %s %s %s", &(*usuaris)[i].id, (*usuaris)[i].nom, &(*usuaris)[i].genere, (*usuaris)[i].procedencia, (*usuaris)[i].data);
    }

    fclose(fitxer);
    return nombre_usuaris;// Retorna el nombre d'usuaris carregats
}

/**
 * @brief Mostra el perfil d'un usuari específic.
 * @param usuaris Punter a la llista d'usuaris.
 * @param amistat Punter a l'estructura amist_propers_t.
 * @param user_id Identificador de l'usuari a mostrar.
 */
void mostrar_perfil(Usuari_t *usuaris, amist_propers_t *amistat, int user_id) {
    // Comprova si l'ID de l'usuari és vàlid
    if (user_id >= 0 && user_id < amistat->num_usuaris) {
        // Obté l'usuari corresponent a l'ID
        Usuari_t usuari = usuaris[user_id];

        // Mostra les dades de l'usuari
        printf("Nom: %s\n", usuari.nom);
        printf("Genere: %c\n", usuari.genere);
        printf("Procedencia: %s\n", usuari.procedencia);
        printf("Data de Naixement: %s\n", usuari.data);
    } else {
        // Mostra un missatge d'error si l'ID no és vàlid
        printf("ERROR: ID d'usuari no valid\n");
    }
}

/**
 * @brief Mostra les dades de tots els usuaris.
 * @param usuaris Punter a la llista d'usuaris.
 * @param num_usuaris Nombre total d'usuaris.
 */
void mostrar_dades(Usuari_t *usuaris, int num_usuaris) {
    printf("Dades dels usuaris:\n");

    // Recorrem la llista d'usuaris per mostrar les seves dades
    for (int i = 0; i < num_usuaris; i++) {
        printf("Usuari %d:\n", usuaris[i].id); // Mostra l'ID de l'usuari
        printf("Nom: %s\n", usuaris[i].nom); // Mostra el nom de l'usuari
        printf("Genere: %c\n", usuaris[i].genere); // Mostra el genere de l'usuari
        printf("Procedencia: %s\n", usuaris[i].procedencia); // Mostra la procedència de l'usuari
        printf("Data de naixement: %s\n", usuaris[i].data); // Mostra la data de naixement de l'usuari
        printf("\n"); // Línia en blanc per separar els usuaris
    }
}

/**
 * @brief Mostra les amistats d'un usuari específic.
 * @param usuaris Punter a la llista d'usuaris.
 * @param amistat Punter a l'estructura amist_propers_t.
 * @param user_id Identificador de l'usuari del qual mostrar les amistats.
 */
void mostrar_les_meves_amistats(Usuari_t *usuaris, amist_propers_t *amistat, int user_id) {
    int amistats_trobades = 0; // Variable per determinar si es troben amistats

    if (user_id >= 0 && user_id < amistat->num_usuaris) {
        printf("Amistats de l'usuari %d:\n", user_id);
        printf("--------------------------------\n");

        // Recorrem la fila corresponent a l'usuari user_id
        for (int i = 0; i < amistat->num_usuaris; i++) {
            // Comprovem si hi ha una amistat (-1) amb l'usuari i
            if (amistat->propers[user_id * amistat->num_usuaris + i] == -1) {
                printf("Usuari %d %s\n", i, usuaris[i].nom);
                amistats_trobades = 1;
            }
        }

        // Si no es troben amistats, es mostra un missatge
        if (!amistats_trobades) {
            printf("L'usuari %d no te amistats\n", user_id);
        }
    } else {
        // Es mostra un missatge d'error si l'ID de l'usuari no és vàlid
        printf("ERROR: ID d'usuari no valid\n");
    }
}

/**
 * @brief Mostra possibles amistats per a un usuari específic.
 * @param usuaris Punter a la llista d'usuaris.
 * @param amistat Punter a l'estructura amist_propers_t.
 * @param user_id Identificador de l'usuari del qual mostrar possibles amistats.
 * @return 1 si el ID d'usuari és vàlid, 0 si no ho és.
 */
int possibles_amistats(Usuari_t *usuaris, amist_propers_t *amistat, int user_id) {
    int resultat = 1; // Variable per determinar si el ID és vàlid
    if (user_id >= 0 && user_id < amistat->num_usuaris) {
        int proximitat = 0; // Contador de possibles amistats

        printf("Possibles amistats de l'usuari %d:\n", user_id);
        printf("--------------------------------\n");

        // Recorre tots els usuaris per trobar possibles amistats
        for (int i = 0; i < amistat->num_usuaris; i++) {
            // Comprova si la proximitat és menor o igual a 3 i major que 0
            if (amistat->propers[user_id * amistat->num_usuaris + i] <= 3 && amistat->propers[user_id * amistat->num_usuaris + i] > 0) {
                proximitat++;
                printf("     - ID: %d Nom: %s\n", i, usuaris[i].nom);
            }
        }

        // Si no es troben possibles amistats
        if (!proximitat) {
            printf("L'usuari %d no te amistats properes \n", user_id);
        }
    } else {
        // Mostra un missatge d'error si l'ID no és vàlid
        printf("ERROR: ID d'usuari no valid\n");
        resultat = 0; // ID no vàlid
    }
    return resultat; // Retorna el resultat final
}

/**
 * @brief Afegeix una amistat entre dos usuaris.
 * @param usuaris Punter a la llista d'usuaris.
 * @param amistat Punter a l'estructura amist_propers_t.
 * @param user_id Identificador del primer usuari.
 * @param user_id2 Identificador del segon usuari.
 */
void afegir_amistat(Usuari_t *usuaris, amist_propers_t *amistat, int user_id, int user_id2) {
    if (user_id >= 0 && user_id < amistat->num_usuaris && user_id2 >= 0 && user_id2 < amistat->num_usuaris) {
        // Estableix la proximitat entre els dos usuaris a -1 (amistat confirmada)
        amistat->propers[user_id * amistat->num_usuaris + user_id2] = -1;
        amistat->propers[user_id2 * amistat->num_usuaris + user_id] = -1;

        // Guarda les dades actualitzades a l'arxiu
        guardar_dades_matriu("propers.txt", amistat);
    } else {
        // Mostra un missatge d'error si algun dels ID dels usuaris no és vàlid
        printf("ERROR: ID d'usuari no valid\n");
    }
}

/**
 * @brief Verifica si un ID de usuario ya existe en la lista de usuarios.
 * @param usuaris Punter a l'estructura Usuari_t que conté la llista d'usuaris.
 * @param num_usuaris Nombre total d'usuaris en la llista.
 * @param id ID de l'usuari que es vol verificar.
 * @return true si l'ID ja existeix, false en cas contrari.
 */
bool id_existe(Usuari_t *usuaris, int num_usuaris, int id) {
    bool res = false; // Variable per emmagatzemar el resultat de la cerca
    for (int i = 0; i < num_usuaris; i++) {
        if (usuaris[i].id == id) {
            res = true; // Canvia el resultat a true si es troba l'ID
        }
    }
    return res; // Retorna el resultat de la cerca
}

/**
 * @brief Afegeix un usuari nou al fitxer d'usuaris.
 * @param new_user Punter a l'estructura Usuari_t que conté les dades del nou usuari.
 */
void afegir_usuari_al_arxiu(Usuari_t *new_user) {
    FILE *file = fopen("usuaris.txt", "a"); // Obre el fitxer en mode append
    

    if (file == NULL) {
        // Mostra un missatge d'error si el fitxer no es pot obrir
        printf("No se pudo abrir el archivo para escribir.\n");
    } else {
        // Escriu les dades del nou usuari al fitxer
        fprintf(file, "\n%d\n%s\n%c\n%s\n%s\n", new_user->id, new_user->nom, new_user->genere, new_user->procedencia, new_user->data);
        fclose(file); // Tanca el fitxer després d'escriure les dades
    }
}

/**
 * @brief Afegeix un nou usuari a la llista d'usuaris i actualitza la matriu de proximitat.
 * @param usuaris Doble punter a l'estructura Usuari_t que conté la llista d'usuaris.
 * @param num_usuaris Punter al nombre total d'usuaris.
 * @param amistat Punter a l'estructura amist_propers_t que conté la matriu de proximitat.
 * @return 1 si l'usuari s'ha afegit correctament, 0 en cas contrari.
 */
int afegir_usuari(Usuari_t **usuaris, int *num_usuaris, amist_propers_t *amistat) {
    int resultat = 1; // Variable per determinar el resultat final
    int tamany = *num_usuaris + 1; // Incrementa el nombre d'usuaris en 1

    // Reassigna memòria per emmagatzemar el nou usuari
    *usuaris = realloc(*usuaris, tamany * sizeof(Usuari_t));
    if (*usuaris == NULL) {
        // Mostra un missatge d'error si no es pot reservar memòria
        printf("Error en reservar memoria para un nuevo usuario.\n");
        resultat = 0;
    } else {
        Usuari_t *new_user = &((*usuaris)[*num_usuaris]); // Obté el punter al nou usuari

        // Solicita un ID únic per al nou usuari
        do {
            printf("Introduce el ID del nuevo usuario: ");
            scanf("%d", &new_user->id);
            if (id_existe(*usuaris, *num_usuaris, new_user->id)) {
                printf("Este ID ya existe, por favor introduce un ID diferente.\n");
            }
        } while (id_existe(*usuaris, *num_usuaris, new_user->id));

        // Solicita les dades del nou usuari
        printf("Introduce el nombre del nuevo usuario: ");
        scanf("%s", new_user->nom);
        printf("Introduce el genero del nuevo usuario (H o D): ");
        scanf(" %c", &new_user->genere);
        printf("Introduce la procedencia del nuevo usuario: ");
        scanf("%s", new_user->procedencia);
        printf("Introduce la fecha de nacimiento del nuevo usuario: ");
        scanf("%s", new_user->data);

        *num_usuaris = tamany; // Actualitza el nombre total d'usuaris
        afegir_usuari_al_arxiu(new_user); // Afegeix el nou usuari al fitxer

        // Actualitza la matriu de proximitat
        propers_t *new_propers = malloc(tamany * tamany * sizeof(propers_t));
        if (new_propers == NULL) {
            // Mostra un missatge d'error si no es pot expandir la matriu de proximitat
            printf("Error al expandir la matriz de proximidad.\n");
            resultat = 0;
        } else {
            // Copia les dades antigues a la nova matriu i afegeix nous valors
            for (int i = 0; i < tamany; i++) {
                for (int j = 0; j < tamany; j++) {
                    if (i < tamany - 1 && j < tamany - 1) {
                        new_propers[i * tamany + j] = amistat->propers[i * (tamany - 1) + j];
                    } else if (i == j) {
                        new_propers[i * tamany + j] = 0;
                    } else if (i == tamany - 1 || j == tamany - 1) {
                        int random_value = (rand() % 5) + 1;
                        new_propers[i * tamany + j] = random_value;
                        new_propers[j * tamany + i] = random_value;
                    }
                }
            }

            free(amistat->propers); // Allibera la memòria antiga
            amistat->propers = new_propers; // Assigna la nova matriu de proximitat
            amistat->num_usuaris = tamany; // Actualitza el nombre d'usuaris 
            guardar_dades_matriu("propers.txt", amistat); // Guarda les dades de la matriu de proximitat
        }
    }

    return resultat; // Retorna el resultat final
}

/**
 * @brief Elimina una amistat d'un usuari específic.
 * @param usuaris Punter a la llista d'usuaris.
 * @param amistat Punter a l'estructura amist_propers_t.
 * @param user_id Identificador de l'usuari del qual eliminar una amistat.
 */
void eliminar_amistat(Usuari_t *usuaris, amist_propers_t *amistat, int user_id) {
    int amistats_trobades = 0; // Variable per determinar si es troben amistats
    int num_amistats = 0; // Variable per emmagatzemar el nombre d'amistats
    int amistats[amistat->num_usuaris]; // Array per emmagatzemar els IDs d'amistats

    // Comprova si l'ID de l'usuari és vàlid
    if (user_id >= 0 && user_id < amistat->num_usuaris) {
        printf("Amistats de l'usuari %d:\n", user_id);
        printf("--------------------------------\n");

        // Recorre la matriu per trobar les amistats
        for (int i = 0; i < amistat->num_usuaris; i++) {
            if (amistat->propers[user_id * amistat->num_usuaris + i] == -1) {
                printf("%d: Usuari %d %s\n", num_amistats, i, usuaris[i].nom);
                amistats[num_amistats] = i; // Emmagatzema l'ID de l'usuari amic
                num_amistats++;
                amistats_trobades = 1;
            }
        }

        // Mostra un missatge si no es troben amistats
        if (!amistats_trobades) {
            printf("L'usuari %d no te amistats\n", user_id);
        } else {
            // Selecciona l'amistat a eliminar
            int seleccio;
            printf("Selecciona l'index del número de la amistat a eliminar: ");
            scanf("%d", &seleccio);

            // Comprova si la selecció és vàlida
            if (seleccio >= 0 && seleccio < num_amistats) {
                int amistat_id = amistats[seleccio];
                int random_value = (rand() % 5) + 1; // Genera un valor aleatori entre 1 i 5
                amistat->propers[user_id * amistat->num_usuaris + amistat_id] = random_value;
                amistat->propers[amistat_id * amistat->num_usuaris + user_id] = random_value;
                printf("Amistat amb l'usuari %d (%s) eliminada.\n", amistat_id, usuaris[amistat_id].nom);
                guardar_dades_matriu("propers.txt", amistat); // Guarda les dades actualitzades
            } else {
                printf("Selecció invàlida.\n");
            }
        }
    } else {
        printf("ERROR: ID d'usuari no valid\n");
    }
}


