/*#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id[100];
  char title[100];
  List *genres;
  char director[1000];
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
}*/
/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
/*int is_equal_str(void *key1, void *key2) {
  if (strcmp((char *)key1, (char *)key2) == 0) return 1;
  return 0;
}*/
/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
/*int is_equal_int(void *key1, void *key2) {
  if (*(int *)key1 == *(int *)key2) return 1;
  return 0;

  // return *(int *)key1 == *(int *)key2;
  //  Compara valores enteros directamente
}*/
/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */
/*void cargar_peliculas(Map *pelis_byid, Map *moviesByDirector) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/Top1500.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Film y almacena los datos de cada película
    Film *peli = (Film *)malloc(sizeof(Film));
    strcpy(peli->id, campos[1]);    // Asigna ID
    strcpy(peli->title, campos[5]); // Asigna título
    peli->genres = list_create();   // Inicializa la lista de géneros
    peli->year = atoi(campos[10]); // Asigna año, convirtiendo de cadena a entero
    strcpy(peli->director, campos[14]); // Asigna director


    // Inserta la película en el mapa usando el ID como clave
    map_insert(pelis_byid, peli->id, peli);
    map_insert(moviesByDirector, peli->director, peli);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas

  // Itera sobre el mapa para mostrar las películas cargadas
  MapPair *pair = map_first(moviesByDirector);
  while (pair != NULL) {
    Film *peli = pair->value;
    printf("ID: %s, Título: %s, Año: %d, Director: %s\n", peli->id, peli->title, peli->year, peli->director);
    pair = map_next(moviesByDirector); // Avanza al siguiente par en el mapa
  }
}*/

/**
 * Busca y muestra la información de una película por su ID en un mapa.
 */
/*void buscar_por_id(Map *pelis_byid) {
  char id[10]; // Buffer para almacenar el ID de la película

  // Solicita al usuario el ID de la película
  printf("Ingrese el id de la película: ");
  scanf("%s", id); // Lee el ID del teclado

  // Busca el par clave-valor en el mapa usando el ID proporcionado
  MapPair *pair = map_search(pelis_byid, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la
  // película
  if (pair != NULL) {
    Film *peli =
        pair->value; // Obtiene el puntero a la estructura de la película
    // Muestra el título y el año de la película
    printf("Título: %s, Año: %d, Director: %s\n", peli->title, peli->year,peli->director);
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con id %s no existe\n", id);
  }
}
// Buacar por director
void buscarPorDirector(Map *pelis_bydir) {
  char director[1000];
  printf("Ingrese el nombre del director: ");
  scanf(" %[^\n]", director);

  MapPair *pair = map_search(pelis_bydir, director);
  if (pair != NULL) {
    Film *peli = pair->value; // Obtiene la película
    while(peli != NULL){
      
      printf("Película encontrada:\n");
      printf("ID: %s, Título: %s\n", peli->id, peli->title);
      printf("Año: %d, Director: %s\n", peli->year, peli->director);
      
      
    }
    

  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con el director %s no existe\n", director);
  }
}*/
/*void buscarPorGenero(Map *pelis_bygen){
char genero[100];
printf("Ingrese el género: ");
scanf(" %[^\n]", genero);

}*/

/*int main() {
  char opcion; 
  // Crea un mapa para almacenar películas, utilizando una función de
  // comparación que trabaja con claves de tipo string.
  Map *pelis_byid = map_create(is_equal_str);
  Map *pelis_bydir = map_create(is_equal_str);

  Map *pelis_bygen = map_create(is_equal_str);

  // Recuerda usar un mapa por criterio de búsqueda

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(pelis_byid,pelis_bydir);
      break;
    case '2':
      buscar_por_id(pelis_byid);
      break;
    case '3':
      buscarPorDirector(pelis_bydir);
      break;
    case '4':
      // buscarPorGenero(pelis_byid);
      break;
    case '5':
      // buscarPorDecada(pelis_byid);
      break;
    case '6':
      // buscarPorRangoCalificacion(pelis_byid);
      break;
    case '7':
      // buscarPorDecadaGenero(pelis_byid);
      break;
    default:
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}
*/
/*#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id[100];
  char title[100];
  List *genres;
  char director[1000];
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
}*/
/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
/*int is_equal_str(void *key1, void *key2) {
  if (strcmp((char *)key1, (char *)key2) == 0) return 1;
  return 0;
}*/
/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
/*int is_equal_int(void *key1, void *key2) {
  if (*(int *)key1 == *(int *)key2) return 1;
  return 0;

  // return *(int *)key1 == *(int *)key2;
  //  Compara valores enteros directamente
}*/
/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */
/*void cargar_peliculas(Map *pelis_byid, Map *moviesByDirector) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/Top1500.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Film y almacena los datos de cada película
    Film *peli = (Film *)malloc(sizeof(Film));
    strcpy(peli->id, campos[1]);    // Asigna ID
    strcpy(peli->title, campos[5]); // Asigna título
    peli->genres = list_create();   // Inicializa la lista de géneros
    peli->year = atoi(campos[10]); // Asigna año, convirtiendo de cadena a entero
    strcpy(peli->director, campos[14]); // Asigna director


    // Inserta la película en el mapa usando el ID como clave
    map_insert(pelis_byid, peli->id, peli);
    map_insert(moviesByDirector, peli->director, peli);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas

  // Itera sobre el mapa para mostrar las películas cargadas
  MapPair *pair = map_first(moviesByDirector);
  while (pair != NULL) {
    Film *peli = pair->value;
    printf("ID: %s, Título: %s, Año: %d, Director: %s\n", peli->id, peli->title, peli->year, peli->director);
    pair = map_next(moviesByDirector); // Avanza al siguiente par en el mapa
  }
}
*/
/**
 * Busca y muestra la información de una película por su ID en un mapa.
 */
/*void buscar_por_id(Map *pelis_byid) {
  char id[10]; // Buffer para almacenar el ID de la película

  // Solicita al usuario el ID de la película
  printf("Ingrese el id de la película: ");
  scanf("%s", id); // Lee el ID del teclado

  // Busca el par clave-valor en el mapa usando el ID proporcionado
  MapPair *pair = map_search(pelis_byid, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la
  // película
  if (pair != NULL) {
    Film *peli =
        pair->value; // Obtiene el puntero a la estructura de la película
    // Muestra el título y el año de la película
    printf("Título: %s, Año: %d, Director: %s\n", peli->title, peli->year,peli->director);
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con id %s no existe\n", id);
  }
}*/
// Buacar por director
/*void buscarPorDirector(Map *pelis_bydir) {
  char director[1000];
  printf("Ingrese el nombre del director: ");
  scanf(" %[^\n]", director);

  MapPair *pair = map_search(pelis_bydir, director);
  if (pair != NULL) {
    Film *peli = pair->value; // Obtiene la película

    printf("Película encontrada:\n");
    printf("ID: %s, Título: %s\n", peli->id, peli->title);
    printf("Año: %d, Director: %s\n", peli->year, peli->director);

  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con el director %s no existe\n", director);
  }
}*/
/*void buscarPorGenero(Map *pelis_bygen){
char genero[100];
printf("Ingrese el género: ");
scanf(" %[^\n]", genero);

}*/

/*int main() {
  char opcion; 
  // Crea un mapa para almacenar películas, utilizando una función de
  // comparación que trabaja con claves de tipo string.
  Map *pelis_byid = map_create(is_equal_str);
  Map *pelis_bydir = map_create(is_equal_str);

  Map *pelis_bygen = map_create(is_equal_str);

  // Recuerda usar un mapa por criterio de búsqueda

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(pelis_byid,pelis_bydir);
      break;
    case '2':
      buscar_por_id(pelis_byid);
      break;
    case '3':
      buscarPorDirector(pelis_bydir);
      break;
    case '4':
      // buscarPorGenero(pelis_byid);
      break;
    case '5':
      // buscarPorDecada(pelis_byid);
      break;
    case '6':
      // buscarPorRangoCalificacion(pelis_byid);
      break;
    case '7':
      // buscarPorDecadaGenero(pelis_byid);
      break;
    default:
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}*/

#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id[100];
  char title[100];
  List *genres;
  char director[1000];
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

int is_equal_int(void *key1, void *key2) {
  if (*(int *)key1 == *(int *)key2) return 1;
  return 0;

  // return *(int *)key1 == *(int *)key2;
  //  Compara valores enteros directamente
}

void cargar_peliculas(Map *pelis_byid, Map *moviesByDirector, Map *pelis_bygen) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/Top1500.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Film y almacena los datos de cada película
    Film *peli = (Film *)malloc(sizeof(Film));
    strcpy(peli->id, campos[1]);    // Asigna ID
    strcpy(peli->title, campos[5]); // Asigna título
    peli->genres = list_create();   // Inicializa la lista de géneros
    peli->year = atoi(campos[10]); // Asigna año, convirtiendo de cadena a entero
    strcpy(peli->director, campos[14]); // Asigna director

//insertar para los generos 
    char *token =strtok(campos[12], ",");
    while  (token != NULL ){
      list_pushBack(peli->genres, token);
      token = strtok(NULL,",");
      //map_insertList(pelis_bygen, peli->genres, peli);
    }
    // Inserta la película en el mapa usando el ID como clave
    map_insert(pelis_byid, peli->id, peli);
    map_insertList(moviesByDirector, peli->director, peli);
    map_insertList(pelis_bygen, peli->genres, peli);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas

  // Itera sobre el mapa para mostrar las películas cargadas
  MapPair *pair = map_first(pelis_byid);
  while (pair != NULL) {
    Film *peli = pair->value;
    printf("ID: %s, Título: %s, Año: %d, Director: %s\n", peli->id, peli->title, peli->year, peli->director);
    pair = map_next(pelis_byid); // Avanza al siguiente par en el mapa
  }
}

void buscar_por_id(Map *pelis_byid) {
  char id[10]; // Buffer para almacenar el ID de la película

  // Solicita al usuario el ID de la película
  printf("Ingrese el id de la película: ");
  scanf("%s", id); // Lee el ID del teclado

  // Busca el par clave-valor en el mapa usando el ID proporcionado
  MapPair *pair = map_search(pelis_byid, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la
  // película
  if (pair != NULL) {
    Film *peli =
        pair->value; // Obtiene el puntero a la estructura de la película
    // Muestra el título y el año de la película
    printf("Título: %s, Año: %d, Director: %s\n", peli->title, peli->year,peli->director);
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con id %s no existe\n", id);
  }
}

// Buacar por director
void buscarPorDirector(Map *pelis_bydir) {
  char director[1000];
  printf("Ingrese el nombre del director: ");
  scanf(" %[^\n]", director);

  List *films = map_getList(pelis_bydir, director);
  //MapPair *pair = map_search(pelis_bydir, director);

  if (films != NULL) {
    void *current =list_first(films);
    while (current !=NULL ){
      Film *peli = (Film *)current;
      printf("Película encontrada:\n");
      printf("ID: %s, Título: %s\n", peli->id, peli->title);
      printf("Año: %d, Director: %s\n", peli->year, peli->director);
      current = list_next(films); 
      
    }
  //Film *peli = pair->value; // Obtiene la película
  //map_next(pelis_bydir);
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con el director %s no se encuentra\n", director);
  }
}

void buscarPorGenero(Map *pelis_bygen){
char genero[100];
printf("Ingrese el género: ");
scanf(" %[^\n]", genero);
List *films = map_getList(pelis_bygen, genero);
if(films != NULL){
  void *current = list_first(films);
  while (current != NULL){
    Film *peli = (Film *)current;
    printf("Peliculas segun el Genero:\n");
    printf("ID: %s, Título: %s\n", peli->id, peli->title);
    printf("Año: %d, Director: %s\n", peli->year, peli->director);
    current = list_next(films);
  }
}
  else{
    printf("No se encontraron peliculas con ese genero\n");
  }

  
}


int main() {
  char opcion; 
  // Crea un mapa para almacenar películas, utilizando una función de
  // comparación que trabaja con claves de tipo string.
  Map *pelis_byid = map_create(is_equal_str);
  Map *pelis_bydir = map_create(is_equal_str);

  Map *pelis_bygen = map_create(is_equal_str);

  // Recuerda usar un mapa por criterio de búsqueda

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':   cargar_peliculas(pelis_byid,pelis_bydir,pelis_bygen);
      break;
    case '2':
      buscar_por_id(pelis_byid);
      break;
    case '3':
      buscarPorDirector(pelis_bydir);
      break;
    case '4':
       buscarPorGenero(pelis_bygen);
      break;
    case '5':
      // buscarPorDecada(pelis_byid);
      break;
    case '6':
      // buscarPorRangoCalificacion(pelis_byid);
      break;
    case '7':
      // buscarPorDecadaGenero(pelis_byid);
      break;
    default:
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}
