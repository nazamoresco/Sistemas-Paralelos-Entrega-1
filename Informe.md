## Ejercicio Numero 2

Empezaremos lo mas explicito y simple posible sin esforzarnos demasiado en encontrar ninguna optimizacion, de esta forma podriamos documentar las optimizaciones y sus cambios en el tiempo de ejecucion.

Como excepcion a esto, comenzamos con una extraccion de una multiplicacion `(RA + RB) -> R(A + B)`,  sencillamente porque nos resulto mas sencillo contruirlo directamente de esta forma.

A continuacion los specs de la PC hogareña:
* Procesador: Intel Core i7-10700 2.90 GHz
* Ram: 16,0 GB

Escribimos un pequeño test bash para asegurar la correctitud del programa a medida que vamos agregando optimizaciones.

```
Resultados del algoritmo base en PC:
  Tiempo en segundos 0.5465590954 para 512
  Tiempo en segundos 5.0782840252 para 1024
  Tiempo en segundos 114.8600111008 para 2048
```

###  Almacenamiento de valores sobre su recalculamiento - Optimizacion V2

La primera optimizacion que implementamos fue la de almacenar valores en variables auxiliares en vez de realizar el mismo calculo varias veces.

Esto lo realizamos con el calculo del indice y con el acceso a elementos de las matrices, pero no vimos mejora y hasta en ciertos casos empeoraba por lo que descatamos esta optimizacion.

```
Resultados del algoritmo V2 en PC:
  Tiempo en segundos 0.5131499767 para 512
  Tiempo en segundos 9.0782840252 para 1024
```

## Mejora a la Optimizacion V2 - Optimizacion V2.2
Eliminamos el almacenamiento del calculo de los indices de las matrices pero mantuvimos el almacenamiento de los accesos a la matrices durante el calculo de R donde si vimos una mejora significativa.

```
Resultados del algoritmo V2.2 en PC:
  Tiempo en segundos 0.4950668812 para 512
  Tiempo en segundos 4.0553719997 para 1024
  Tiempo en segundos 62.7206149101 para 2048
```

## Matriz resultado en vez de reutilizar R - Optimizacion V3.
  Probamos usar una matriz para almacenar el resultado en vez de usar R mismo.
  No presento mejoras, y hasta cierta desmejora.

```
Resultados del algoritmo V3 en PC:
  Tiempo en segundos 0.5233290195  para 512
  Tiempo en segundos 4.0354280472  para 1024
  Tiempo en segundos 66.0288639069 para 2048
```
## Decremento del indice como condicion en el for - Optimizacion V4

Para realizar esta optimizacion tomamos ventaja de que en C el 0 se considera falso para combinar el decremento y la condicion del for en una sola expresion.
Para esto tuvimos que invertir todos los for, se observo una mejora.

```
Resultados del algoritmo V4 en PC:
  Tiempo en segundos 0.4419710636 para 512
  Tiempo en segundos 3.7746620178 para 1024
  Tiempo en segundos 52.0080058575 para 2048
```

## Acceso por columnas del operando derecho en la multiplicacion de matrices - Optimizacion V5

Finalmente, accedimos por columna en los operandos derechos de las multiplicacion de matrices para asi realizarlas mas eficientemente.
Esto se debe a que para el calculo de un elemento del resultado de una multiplicaion se debe recorrer la fila de la matriz izquierda y la columna de la matriz derecha, por lo que acceder a la matriz derecha por filas es extremadamente ineficiente.
La mejora fue tan significativa que nos dejo satisfechos y dimos por finalizado el proceso de optimizacion.

Para esto debimos incluir una nueva matriz resultado pero aun asi se mantuvo la mejora.

```
Resultados del algoritmo V5 en PC:
  Tiempo en segundos 0.2881238461 512
  Tiempo en segundos 2.2192440033 1024
  Tiempo en segundos 18.6206161976 2048
```

```
Resultados del algoritmo V5 optimizado con O3 en PC:
  Tiempo en segundos 0.1262190342 en 512
  Tiempo en segundos 1.0131981373 en 1024
  Tiempo en segundos 8.9814372063 en 2048
  Tiempo en segundos 71.7591030598 en 4096
```

```
Resultados del algoritmo V5 en CLUSTER:
  Tiempo en segundos 0.9209411144 para 512
  Tiempo en segundos 7.8719360828 para 1024
  Tiempo en segundos 66.6019508839 para 1024
```

```
Resultados del algoritmo V5 optimizado con O3 en CLUSTER:
  Tiempo en segundos 0.2335169315 para 512
  Tiempo en segundos 3.9887001514 para 1024
  Tiempo en segundos 33.6858358383 para 2048
  Tiempo en segundos 289.3322269917 para 4096
```
