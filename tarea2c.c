#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id[100];
  char title[100];
  List *genres;
  List *director;
  float rating;
  int year;
  int decade; // Nuevo campo para almacenar la década

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
  puts("========================================");
}

int is_equal_str(void *key1, void *key2) {
  if (strcmp((char *)key1, (char *)key2) == 0)
    return 1;
  return 0;
}

int is_equal_int(void *key1, void *key2) {
  return (*(int *)key1 == *(int *)key2);
}

//Funcion para comparar si son iguales
int are_equal_float(void *key1, void *key2) {
  float value1 = *((float *)key1);
  float value2 = *((float *)key2);
  return value1 == value2;
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
  while (isspace((unsigned char)*str))
    str++;
  return str;
}

//Funcion para Cargar los mapas 
void cargar_peliculas(Map *pelis_byid, Map *moviesByDirector, Map *pelis_bygen, Map *pelisByDecade, Map *pelis_byrating) {
  
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

    // Para Géneros
    peli->genres = list_create();
    borrarComillas(campos[11]);
    char *token = strtok(campos[11], ",");
    while (token != NULL) {
      char *clean_token = espacioInicial(token);
      list_pushBack(peli->genres, strdup(clean_token));
      token = strtok(NULL, ",");
    }

    // Para Directores
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
    
    // Insertar película en el mapa por rating
    List *rating=map_getList(pelis_byrating, &(peli->rating));
    if(rating==NULL){
      rating=list_create();
      map_insert(pelis_byrating,&(peli->rating),rating);
      //list_pushBack(rating, peli);
    }
    list_pushBack(rating, peli);
    
    // Insertar película en el mapa por director
    for (char *node = list_first(peli->director); node != NULL;
         node = list_next(peli->director)) {
      MapPair *par = map_search(moviesByDirector, node);
      if (par == NULL) {
        List *lista = list_create();
        map_insert(moviesByDirector, strdup(node), lista);
        list_pushBack(lista, peli);
      } else {
        List *lista = (List *)par->value;
        if (lista == NULL) {
          lista = list_create();
          par->value = lista;
        }
        list_pushBack(lista, peli);
      }
    }
    // Insertar película en el mapa por género
    for (char *node = list_first(peli->genres); node != NULL;
         node = list_next(peli->genres)) {
      MapPair *par = map_search(pelis_bygen, node);
      if (par == NULL) {
        List *lista = list_create();
        map_insert(pelis_bygen, strdup(node), lista);
        list_pushBack(lista, peli);
      } else {
        List *lista = (List *)par->value;
        if (lista == NULL) {
          lista = list_create();
          par->value = lista;
        }
        list_pushBack(lista, peli);
      }
    }
    // Inserta la película en el mapa por década
    peli->decade = peli->year - (peli->year % 10);
    MapPair *pair = map_search(pelisByDecade, &(peli->decade));
    if (pair == NULL) {
      List *peliculas = list_create();
      list_pushBack(peliculas, peli);
      map_insert(pelisByDecade, &(peli->decade), peliculas);
    } else {
      List *peliculas = (List *)pair->value;
      list_pushBack(peliculas, peli);
    }
  }
  fclose(archivo);
}

//Funcion para Buscar por ID
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

//Funcion para Buscar por Director
void buscarPorDirector(Map *moviesByDirector) {
  
  char director[1000];
  printf("Ingrese el nombre del director: ");
  scanf(" %[^\n]", director);
  
  // Convertir el nombre del director ingresado a minúsculas
  for (int i = 0; director[i]; i++) {
    director[i] = tolower(director[i]);
  }
  
  MapPair *pair = map_first(moviesByDirector);
  while (pair != NULL) {
    // Convertir el nombre del director en la lista a minúsculas para comparar
    char *currentDirector = (char *)pair->key;
    for (int i = 0; currentDirector[i]; i++) {
      currentDirector[i] = tolower(currentDirector[i]);
    }
    
    if (strcmp((char *)pair->key, director) == 0) {
      Film *peli = (Film *)list_first(pair->value);
      printf("Películas del director \"%s\":\n", director);
      while (peli != NULL) {
        printf("ID: %s, Título: %s\n", peli->id, peli->title);
        peli = (Film *)list_next(pair->value);
      }
      break;
    }
    pair = map_next(moviesByDirector);
  }
}

//Funcion para Buscar por Genero
void buscarPorGenero(Map *pelis_byid) {
  
  char genero[1000];
  printf("Ingrese el genero: ");
  scanf(" %[^\n]", genero);
  
  // Convertir el género ingresado a minúsculas
  for (int i = 0; genero[i]; i++) {
    genero[i] = tolower(genero[i]);
  }
  
  // Iterar sobre todas las películas en el mapa
  MapPair *pair = map_first(pelis_byid);
  
  while (pair != NULL) {
    // Convertir el género de la película en la lista a minúsculas para comparar
    char *currentGenre = (char *)pair->key;
    for (int i = 0; currentGenre[i]; i++) {
      currentGenre[i] = tolower(currentGenre[i]);
    }
    
    if (strcmp(currentGenre, genero) == 0) {
      Film *peli = (Film *)list_first(pair->value);
      printf("Películas del genero \"%s\":\n", genero);
      while (peli != NULL) {
        printf("ID: %s, Título: %s\n", peli->id, peli->title);
        // printf("Año: %d, Director: %s\n", peli->year, peli->director);
        peli = (Film *)list_next(pair->value);
      }
      break;
    }
    pair = map_next(pelis_byid);
  }
}

//Funcion para Buscar por decadas
void buscarPorDecada(Map *pelisByDecade) {
  int decada;
  
  printf("Ingrese la década (por ejemplo, 1970 para la década de 1970): ");
  scanf("%d", &decada);

  //Ajustamos la decada para que en caso que se ingrese una decada como 1975 reconozca que es de los 70
   decada = decada - (decada % 10);
  
  // Buscar la lista de películas para la década ingresada
  List *peliculas = map_getList(pelisByDecade, &decada);

  if (peliculas != NULL) {
    printf("Películas de la década de %d:\n", decada);
    Film *peli = list_first(peliculas);
    while (peli != NULL) {
      printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title,
             peli->year);
      peli = list_next(peliculas);
    }
  } else {
    printf("No se encontraron películas para la década de %d\n", decada);
  }
}

// Funcion para Buscar por Decadas y genero
void buscarPorDecadaGenero(Map *pelis_bygen) {
  int decada;
  printf("Ingrese la década (por ejemplo, 1970 para la década de 1970): ");
  scanf("%d", &decada);
  //Ajustamos la decada para que en caso que se ingrese una decada como 1975 reconozca que es de los 70
  decada = decada - (decada % 10);
  
  char genero[100];
  printf("Ingrese el género: ");
  scanf(" %[^\n]", genero);
  // Convertir el género ingresado a minúsculas
  for (int i = 0; genero[i]; i++) {
    genero[i] = tolower(genero[i]);
  }

  MapPair *pair = map_first(pelis_bygen);
  
  while (pair != NULL) {
    char *currentGenre = (char *)pair->key;
    
    for (int i = 0; currentGenre[i]; i++) {
      currentGenre[i] = tolower(currentGenre[i]);
    }
    
    if (strcmp(currentGenre, genero) == 0) {
      Film *peli = (Film *)list_first(pair->value);
      printf("Películas del género \"%s\" y década de %d:\n", genero, decada);
      while (peli != NULL) {
        if (peli->year >= decada && peli->year < decada + 10) {
          printf("ID: %s, Título: %s\n", peli->id, peli->title);
          // printf("Año: %d, Director: %s\n", peli->year, peli->director);
        }
        peli = (Film *)list_next(pair->value);
      }
      break;
    }
    pair = map_next(pelis_bygen);
  }
}

// Función para buscar películas por rating
void buscarPorRating(Map *pelis_byrating) {
  float rating_min, rating_max;
  printf("Ingrese el rango de calificación (mínimo máximo): ");
  scanf("%f %f", &rating_min, &rating_max);

  MapPair *pair = map_first(pelis_byrating);
  if (pair != NULL) {
    printf("Películas en el rango de calificación seleccionado:\n");
    while (pair != NULL) {
      float *rating = pair->key;
      if (*rating >= rating_min && *rating <= rating_max) {
        List *peliculas = map_getList(pelis_byrating, rating);
        Film *peli = list_first(peliculas);
        while (peli != NULL) {
          printf("ID: %s, Título: %s, Calificación: %.1f\n", peli->id, peli->title, peli->rating);
          peli = list_next(peliculas);
        }
      }
      pair = map_next(pelis_byrating);
    }
  } else {
      printf("No hay películas en el rango de calificación seleccionado.\n");
  }
}

int main() {
  char opcion;

  //Creacion de los mapas 
  Map *pelis_byid = map_create(is_equal_str);
  Map *moviesByDirector = map_create(is_equal_str);
  Map *pelis_bygen = map_create(is_equal_str);
  Map *pelisByDecade = map_create(is_equal_int);
  Map *pelis_byrating = map_create(are_equal_float);

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(pelis_byid, moviesByDirector, pelis_bygen,pelisByDecade,pelis_byrating);
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
      buscarPorDecada(pelisByDecade);
      presioneTeclaParaContinuar();
      break;
    case '6':
      buscarPorRating(pelis_byrating);
      presioneTeclaParaContinuar();
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
