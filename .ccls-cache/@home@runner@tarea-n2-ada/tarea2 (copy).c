#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char id[100];
    char title[100];
    List *genres;
    List *director; 
    float rating;
    int year;
} Film;


// Menú principal
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("     Base de Datos de Películas");
    puts("========================================");

    puts("1) Cargar Películas");
    puts("2) Buscar por id");
    puts("3) Buscar por director");
    puts("4) Buscar por género");
    puts("5) Buscar por década");
    puts("6) Buscar por rango de calificaciones");
    puts("7) Buscar por década y género");
    puts("8) Salir");
}

int is_equal_str(void *key1, void *key2) {
    if (strcmp((char *)key1, (char *)key2) == 0) return 1;
    return 0;
}

void borrarComillas(char *str) {
    // Función para quitar las comillas del principio y del final de una cadena
    int len = strlen(str);
    if (str[0] == '"') {
        memmove(str, str + 1, len);
        len--;
    }
    if (len > 0 && str[len - 1] == '"') {
        str[len - 1] = '\0';
    }
}
char *espacioInicial(char *str) {
    // Función para quitar espacios iniciales de una cadena
    while (isspace((unsigned char)*str)) str++;
    return str;
}

/*void cargar_peliculas(Map *pelis_byid, Map *moviesByDirector, Map *pelis_bygen) {
    FILE *archivo = fopen("data/Top1500.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ','); 

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        Film *peli = (Film *)malloc(sizeof(Film));
        strcpy(peli->id, campos[1]);    
        strcpy(peli->title, campos[5]); 
        peli->genres = list_create();   
        peli->year = atoi(campos[10]); 
        strcpy(peli->director, campos[14]); 
        map_insert(pelis_byid, peli->id, peli);
        map_insertList(moviesByDirector, peli->director, peli);

        char *generos = strdup(campos[12]); 
        char *token = strtok(generos, ",");
        while (token != NULL) {
            Film *copy = (Film *)malloc(sizeof(Film));
            memcpy(copy, peli, sizeof(Film)); 
            list_pushBack(copy->genres, token); 
            map_insertList(pelis_bygen, token, copy); 
            token = strtok(NULL, ",");
        }
        free(generos);
    }
    fclose(archivo); 
}*/

void cargar_peliculas(Map *pelis_byid, Map *moviesByDirector, Map *pelis_bygen) {
    FILE *archivo = fopen("data/Top1500.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ','); 

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        Film *peli = (Film *)malloc(sizeof(Film));
        if (peli == NULL) {
            printf("Error: memoria insuficiente.\n");
            exit(1);
        }

        strcpy(peli->id, campos[1]);
        strcpy(peli->title, campos[5]);
        peli->rating = atof(campos[8]);
        peli->year = atoi(campos[10]);

        // Géneros
        peli->genres = list_create();
        borrarComillas(campos[11]);
        char *token = strtok(campos[11], ",");
        while (token != NULL) {
            char *clean_token = espacioInicial(token);
            list_pushBack(peli->genres, strdup(clean_token));
            token = strtok(NULL, ",");
        }

        // Directores
        peli->director = list_create();
        borrarComillas(campos[14]);
        char *token2 = strtok(campos[14], ",");
        while (token2 != NULL) {
            char *clean_token2 = espacioInicial(token2);
            list_pushBack(peli->director, strdup(clean_token2));
            token2 = strtok(NULL, ",");
        }

        // Insertar película en el mapa por ID
        map_insert(pelis_byid, strdup(peli->id), peli);

        // Insertar película en el mapa por director
        for (char *node = list_first(peli->director); node != NULL; node = list_next(peli->director)) {
            MapPair *par = map_search(moviesByDirector, node);
            if (par == NULL) {
                List* lista = list_create();
                map_insert(moviesByDirector, strdup(node), lista);
                list_pushBack(lista, peli);
            } else {
                List* lista = (List*) par->value;
                if (lista == NULL) {
                    lista = list_create();
                    par->value = lista;
                }
                list_pushBack(lista, peli);
            }
        }

        // Insertar película en el mapa por género
        for (char *node = list_first(peli->genres); node != NULL; node = list_next(peli->genres)) {
            MapPair *par = map_search(pelis_bygen, node);
            if (par == NULL) {
                List* lista = list_create();
                map_insert(pelis_bygen, strdup(node), lista);
                list_pushBack(lista, peli);
            } else {
                List* lista = (List*) par->value;
                if (lista == NULL) {
                    lista = list_create();
                    par->value = lista;
                }
                list_pushBack(lista, peli);
            }
        }
    }
    fclose(archivo); 
}

void buscarPorDecada(Map *pelis_byid) {
    int decada;
    printf("Ingrese la década (por ejemplo, 1970 para la década de 1970): ");
    scanf("%d", &decada);

    MapPair *pair = map_first(pelis_byid);
    while (pair != NULL) {
        Film *peli = pair->value;
        if (peli->year >= decada && peli->year < decada + 10) {
            printf("Películas de la década de %d:\n", decada);
            printf("ID: %s, Título: %s\n", peli->id, peli->title);
            //printf("Año: %d, Director: %s\n", peli->year, peli->director);
        }
        pair = map_next(pelis_byid);
    }
}

void buscar_por_id(Map *pelis_byid) {
    char id[10]; // Buffer para almacenar el ID de la película

    printf("Ingrese el id de la película: ");
    scanf("%s", id); // Lee el ID del teclado

    MapPair *pair = map_search(pelis_byid, id);

    if (pair != NULL) {
        Film *peli = pair->value;
        printf("Título: %s, Año: %d\n", peli->title, peli->year);
    } else {
        printf("La película con id %s no existe\n", id);
    }
}

void buscarPorDirector(Map *moviesByDirector) {
    char director[1000];
    printf("Ingrese el nombre del director: ");
    scanf(" %[^\n]", director);

    MapPair *pair = map_first(moviesByDirector);
    while (pair != NULL) {
        if (strcmp((char *)pair->key, director) == 0) {
            Film *peli = (Film *)list_first(pair->value);
            printf("Películas del director \"%s\":\n", director);
            while (peli != NULL) {
                printf("ID: %s, Título: %s\n", peli->id, peli->title);
                //printf("Año: %d, Director: %s\n", peli->year, peli->director);
                peli = (Film *)list_next(pair->value);
            }
            break;
        }
        pair = map_next(moviesByDirector);
    }
}
void buscarPorGenero(Map *pelis_byid) {
    char genero[1000];
    printf("Ingrese el género: ");
    scanf(" %[^\n]", genero);

    // Iterar sobre todas las películas en el mapa
  MapPair *pair = map_first(pelis_byid);
  while (pair != NULL) {
      if (strcmp((char *)pair->key, genero) == 0) {
          Film *peli = (Film *)list_first(pair->value);
          printf("Películas del director \"%s\":\n", genero);
          while (peli != NULL) {
              printf("ID: %s, Título: %s\n", peli->id, peli->title);
              //printf("Año: %d, Director: %s\n", peli->year, peli->director);
              peli = (Film *)list_next(pair->value);
          }
          break;
      }
      pair = map_next(pelis_byid);
  }
}
void buscarPorDecadaGenero(Map *pelis_bygen) {
    int decada;
    printf("Ingrese la década (por ejemplo, 1970 para la década de 1970): ");
    scanf("%d", &decada);

    char genero[100];
    printf("Ingrese el género: ");
    scanf(" %[^\n]", genero);

    MapPair *pair = map_first(pelis_bygen);
    while (pair != NULL) {
        if (strcmp((char *)pair->key, genero) == 0) {
            Film *peli = (Film *)list_first(pair->value);
            printf("Películas del género \"%s\" y década de %d:\n", genero, decada);
            while (peli != NULL) {
                if (peli->year >= decada && peli->year < decada + 10) {
                    printf("ID: %s, Título: %s\n", peli->id, peli->title);
                    //printf("Año: %d, Director: %s\n", peli->year, peli->director);
                }
                peli = (Film *)list_next(pair->value);
            }
            break;
        }
        pair = map_next(pelis_bygen);
    }
}

int main() {
    char opcion; 

    Map *pelis_byid = map_create(is_equal_str);
    Map *moviesByDirector = map_create(is_equal_str);
    Map *pelis_bygen = map_create(is_equal_str);

    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case '1':   
                cargar_peliculas(pelis_byid, moviesByDirector, pelis_bygen);
              presioneTeclaParaContinuar();
                break;
            case '2':
                buscar_por_id(pelis_byid);
              presioneTeclaParaContinuar();
                break;
            case '3':
              buscarPorDirector(moviesByDirector);
              presioneTeclaParaContinuar();
                break;
            case '4':
              buscarPorGenero(pelis_bygen);
              presioneTeclaParaContinuar();
                break;
            case '5':
              buscarPorDecada(pelis_byid);
              presioneTeclaParaContinuar();
                break;
            case '6':
                // buscarPorRangoCalificacion(pelis_byid);
                break;
            case '7':
              buscarPorDecadaGenero(pelis_bygen);
              presioneTeclaParaContinuar();
                break;
            default:
                presioneTeclaParaContinuar();
                break;
        }
    } while (opcion != '8');

    return 0;
}
