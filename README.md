Tarea n°2: Correspondientes a ` Adai Illanes Gutierrez y Marcel Gutierrez Avila.`

# Buscador de Películas por distintos Criterios:

Para poder compilar se usa este comando(en la carpeta raiz) : 
`````
gcc tdas/*.c tarea2c.c -Wno-unused-result -o tarea2c
`````
para luego ejecutar el siguiente comando 
`````
./tarea2c
`````
## Funcionamiento del programa 
las 7 opciones funcionan de la manera que se piden: 

1) cargar_peliculas: funciona de buena manera, comprueba al inicio si el archivo esta vacio, en caso contrario carga todo el contenido de manera iterativa en los mapas para facilitar la busqueda para asi ir llenando cada dato necesario del archivo en la estructura propuesta llamada Film.

2) buscar_por_id: funciona correctamente y sin error. Esta funcion como lo indica el nombre se tiene un mapa llamado pelis_byid (clave: ID, valor: FILM) donde hara que se nos facilite la busqueda de una pelicula X en base a su ID.

3) buscarPorDirector: esta funcion como lo dice el nombre busca un X director y luego muestra todas las peliculas de este para lo cual se implemento un mapa para cada uno de los directores el cual es moviesByDirector (clave: director, valor: FILM), para que asi pueda mostrar las peliculas (ID, y los titulos) segun el director ingresado.

4) BuscarPorGenero: en esta funcion el usuario ingresa un X genero en donde le interesa conocer todas las peliculas que pertenecen a esta. mostrando tanto sus ID como titulos, para lo cual se creo un mapa para cada genero pelis_bygen (clave: genero, valor: FILM) que facilitara su busqueda.

5) BuscarPorDecada: en esta el usuario desea buscar peliculas que salieron en una X decada, en donde al ingresar alguna especifica muestra tanto el ID como el titulo, funciona de forma correcta, si el usuario ingresa alguna decada que no este en el csv, indicara que no hay peliculas en la decada que ingreso se uso al igual que las anteriores opciones un mapa donde almacena las decadas el cual tiene pelisByDecade(clave: decada, valor: FILM).

6) BuscarPorRating: en esta funcion el usuario desea conocer las peliculas que tengan un rating que el desee conocer, ingresando un min_rating y un max_rating, en donde mostrara las peliculas por ID y por su titulo y su rating.

7) BuscarPorDecadaGenero: en esta funcion hace que el usuario vea los generos de una decada, en cual este ingresa una X decada para luego ingresar el X genero, en donde se mostrara la X decada y las peliculas que sean del X genero ingresado.

# Ejemplos de uso:
```
 ========================================
      Base de Datos de Películas
 ========================================
1) Cargar Películas
2) Buscar por id
3) Buscar por director
4) Buscar por género
5) Buscar por década
6) Buscar por rango de calificaciones
7) Buscar por década y género
8) Salir

   ```
Aqui debes seleccionar una opcion que va desde el 1 al 8, si el usuario ingresa un digito diferente de estos saldra un error hasta que escojas una opcion valida.

## 1) cargar_peliculas: 
en esta opcion primero se pregunta si el archivo.csv es NULL, en caso contrario se leera para asi luego nosotros poder ingresar los datos correspondientes, en el cual se mostraran en la pantalla indicando sus datos: ID, titulo y año.

## 2) buscarPorID:
aca le pide al usuario que ingrese el ID para asi saber cual es titulo y el año que salio, ejemplo para poner en la consola:
```
ID: tt0068646
```
En caso que no se encuentre la pelicula relacionada al id ingresado, se mostrara lo siguiente:

`La película de X id no existe`
## 3) BuscarPorDirector:
aca el usuario debe ingresar el nombre, respetando la mayusculas del nombre y apellidos, y se mostraran las peliculas del X director, mostrando en pantalla el ID, el titulo de cada pelicula que sea de ese director, ejemplo:
```
Opcion: 3
Ingrese el nombre del director: Francis Ford Coppola
```
mostrara:

```
Películas del director "francis ford coppola":
ID: tt0068646, Título: The Godfather
ID: tt0071562, Título: The Godfather Part II
ID: tt0078788, Título: Apocalypse Now
ID: tt0099674, Título: The Godfather Part III
ID: tt0071360, Título: The Conversation
ID: tt0096316, Título: Tucker: The Man and His Dream
ID: tt0119978, Título: The Rainmaker
ID: tt0086216, Título: Rumble Fish
ID: tt0086066, Título: The Outsiders
```
En caso que no se encuentre las peliculas relacionadas al director ingresado, se mostrara lo siguiente:

`el director no se encuentra y pasara a presione una tecla para continuar`

## 4) BuscarPorGenero:
En esta opcion el usuario ingresa un genero X, en el cual se mostraran todas las peliculas asociadas a este X genero, por ejemplo:
`Drama` o `Crime`
se vera de la siguiente forma: 
```
Ingrese su opción: 4
Ingrese el genero: drama
```
y debera mostrar:

```
Películas del genero "drama":
ID: tt0068646, Título: The Godfather
ID: tt0034583, Título: Casablanca
ID: tt0061722, Título: The Graduate
ID: tt0033467, Título: Citizen Kane
ID: tt0050083, Título: 12 Angry Men
ID: tt0047478, Título: Shichinin no samurai
ID: tt0071315, Título: Chinatown
```
En caso que no se encuentre las peliculas relacionadas al director ingresado, se mostrara lo siguiente:
`el genero no se encuentra`

## 5) BuscarPorDecada:
En esta opcion el usuario ingresa una X decada para asi conocer que peliculas salieron en ese tiempo, en el cual se mostraran todas las peliculas asociadas a esta X decada, por ejemplo: `1980`
```
Ingrese su opción: 5
Ingrese la década (por ejemplo, 1970 para la década de 1970): 1980
```
debera mostrar:
```
Películas de la década de 1980:
ID: tt0080684, Título: Star Wars: Episode V - The Empire Strikes Back, Año: 1980
ID: tt0081398, Título: Raging Bull, Año: 1980
ID: tt0082971, Título: Raiders of the Lost Ark, Año: 1981
...
```
En caso que no se encuentre las peliculas relacionadas al director ingresado, se mostrara lo siguiente:
`Esa decada no se encuentra`

## 6) BuscarPorRanking:
En esta opcion habra un minimo y un maximo que el usuario debera ingresar para asi ver las peliculas con ese ranking
```
  Ingrese su opción: 6
  Ingrese el rango de calificación (mínimo máximo): 5.0 6.0
```
Debe mostrar 

```
Películas en el rango de calificación seleccionado:
ID: tt0091635, Título: Nine 1/2 Weeks, Calificación: 5.9
ID: tt0053716, Título: Cinderfella, Calificación: 5.9
ID: tt0120434, Título: Vegas Vacation, Calificación: 5.9
ID: tt2027064, Título: Blue Caprice, Calificación: 5.9
ID: tt0068835, Título: Last of the Red Hot Lovers, Calificación: 6.0
...
```
## 7) Buscar Por Decada y Genero:
En esta funcion el usuario puede ingresar una decada X para luego preguntar un X genero para asi mostrar las peliculas que salieron en esa X decada que sean del X genero que desee el usuario, por ejemplo: `1980` y el genero `Drama` o `Crime`
```
Ingrese su opción: 7
Ingrese la década (por ejemplo, 1970 para la década de 1970): 1970
Ingrese el género: Drama
```
Resultado obtenido 

```
Películas del género "drama" y década de 1970:
ID: tt0068646, Título: The Godfather
ID: tt0071315, Título: Chinatown
ID: tt0072890, Título: Dog Day Afternoon
ID: tt0074958, Título: Network
ID: tt0071562, Título: The Godfather Part II
```


## Contribuciones por integrante:
En esta parte ambos realizamos el codigo y contribuimos en el desarrollo

### Marcel Gutierrez 
- Ayudo en las ideas basicas para el codigo
- Ayudo en la implementacion de buscarPorDecada(aporto una alternativa) y rango de calificaciones
- Documentacion del README
- Auto-evaluacion: 2 (Aporte bueno).

### Adai Illanes 
- Implemento la funcion de buscar por director, genero y buscar por decada y genero
- Ayudo a implementar la base para busqueda por id
- ayudo en la parte de crear los mapas
- comentarios e identacion del codigo
- Auto-evaluacion: 3 (Aporte excelente)
``` 
1) Cargar Películas :
2) Buscar por id :
3) Buscar por director : 
4) Buscar por género :
5) Buscar por década : 
6) Buscar por rango de calificaciones :
7) Buscar por década y género :
``` 
