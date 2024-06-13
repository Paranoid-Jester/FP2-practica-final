#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcions.h"

/**
 * @brief Funció principal del programa.
 * @param argc Nombre d'arguments passats a la línia de comandes.
 * @param argv Vector d'arguments passats a la línia de comandes.
 * @return Retorna 0 si el programa acaba correctament, 1 en cas d'error.
 */
int main(int argc, char *argv[]) {
    int res = 0; // Variable per emmagatzemar el resultat final de la funció main

    if (argc != 2) {
        printf("Ús: %s id_user\n", argv[0]);
        res = 1; // Estableix el resultat a 1 si hi ha un error en els arguments
    } else {
        int user_id = atoi (argv[1]);

        if (user_id > MAX_USUARIS)
        {
            printf ("ID molt gran\n");
            res = 1;
        }

        else
        {

        srand(time(NULL)); // Inicialitza el generador de números aleatoris

        int num_usuaris; // Variable per emmagatzemar el nombre d'usuaris
        int usuaris_matriu; // Variable per emmagatzemar l'estat de càrrega de la matriu d'usuaris
        Usuari_t *usuaris; // Punter a l'estructura d'usuaris

        // Carrega dades dels usuaris des del fitxer
        num_usuaris = carregar_dades("usuaris.txt", &usuaris);

        amist_propers_t amistat; // Estructura per a la matriu de proximitat

        // Carrega dades de la matriu de proximitat des del fitxer
        usuaris_matriu = carregar_dades_matriu("propers.txt", &amistat);

       
        int user_id2; // Variable per emmagatzemar l'ID del segon usuari

        // Comprova si s'han carregat usuaris correctament
        if (num_usuaris != 0) {
            printf("S'han carregat %d usuaris\n", num_usuaris);

            int opcio; // Variable per emmagatzemar l'opció del menú

            // Bucle per mostrar el menú i executar les opcions seleccionades
            do {
                printf("Tria una opcio:\n");
                printf("0-El meu perfil:\n");
                printf("1-Les meves amistats:\n");
                printf("2-Afegir amistats:\n");
                printf("3-Afegir usuari:\n");
                printf("4-Eliminar amistat:\n");
                printf("5-Sortir:\n");

                scanf("%d", &opcio); // Llegeix l'opció seleccionada per l'usuari

                switch (opcio) {
                    case 0:
                        printf("El meu perfil:\n");
                        mostrar_perfil(usuaris, &amistat, user_id); // Mostra el perfil de l'usuari
                        break;

                    case 1:
                        printf("Les meves amistats:\n");
                        mostrar_les_meves_amistats(usuaris, &amistat, user_id); // Mostra les amistats de l'usuari
                        break;

                    case 2:
                        printf("Afegir amistats:\n");
                        if (possibles_amistats(usuaris, &amistat, user_id)) {
                            printf("Introdueix l'ID de l'usuari a afegir:\n");
                            scanf("%d", &user_id2);
                            afegir_amistat(usuaris, &amistat, user_id, user_id2); // Afegeix amistat
                        }
                        break;

                    case 3:
                        printf("\n");
                        if (afegir_usuari(&usuaris, &num_usuaris, &amistat)) {
                            printf("Usuari afegit correctament.\n"); // Usuari afegit correctament
                        } else {
                            printf("Error en afegir l'usuari.\n"); // Error en afegir l'usuari
                        }
                        break;

                    case 4:
                        printf("Eliminar amistat:\n");
                        eliminar_amistat(usuaris, &amistat, user_id); // Elimina amistat
                        break;

                    case 5:
                        printf("Sortint de l'aplicacio...\n"); // Surt de l'aplicació
                        break;

                    default:
                        printf("Has d'introduir una opcio correcta del menu\n"); // Opció incorrecta
                        break;
                }
            } while (opcio != 5); // Repeteix el menú fins que es seleccioni l'opció de sortir
        } else {
            printf("No s'ha pogut carregar cap usuari\n"); // No s'han pogut carregar usuaris
        }

        free(usuaris); // Allibera memòria dels usuaris
        free(amistat.propers); // Allibera memòria de la matriu de proximitat
    }
    }

    return res; // Retorna el resultat final de la funció main
}
