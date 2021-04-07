#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PI 3.14159265358979323846



//Para calcular tiempo
double dwalltime(){
        double sec;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}

double randFP(double min, double max) {
    double range = (max -min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main(int argc, char* argv[]){
    time_t t;
    double *A,*B,*C,*T,*R,*M;
    double timetick, timeend;
    int N;

    srand((unsigned) time(&t));
    //...
    if ((N = atoi(argv[1])) <= 0)
    {
        printf("\nUsar: %s n\n  n: Dimension de las matrices NxN \n", argv[0]);
        exit(1);
    }


    //Aloca memoria para las matrices
    A=(double*)malloc(N*N*sizeof(double));
    B=(double*)malloc(N*N*sizeof(double));
    C=(double*)malloc(N*N*sizeof(double));
    M=(double*)malloc(N*N*sizeof(double));
    T=(double*)malloc(N*N*sizeof(double));
    R=(double*)malloc(N*N*sizeof(double));

    //Inicializar las matrices
    if(argc > 2) {
        char input[256];

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            A[indice] = strtod(input, NULL);
            printf("A %s \n",input);
        }

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            B[indice] = strtod(input, NULL);
            printf("B %s \n",input);
        }

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            T[indice] = strtod(input, NULL);
            printf("T %s \n",input);
        }

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            M[indice] = strtod(input, NULL);
            printf("M %s \n",input);
        }

    } else {
        for (int fila = 0; fila < N; fila++) {
            for (int columna = 0; columna < N; columna++) {
                A[fila*N+columna] = randFP(0,10);
                B[fila*N+columna] = randFP(0,10);
                M[fila*N+columna] = randFP(0,2*PI);
                T[fila*N+columna] = randFP(0,10);
            }
        }
    }

    // DEBUG
    // printf("INCIALIZADO\n");
    // for (int fila = 0; fila < N; fila++) {
    //     for (int columna = 0; columna < N; columna++) {
    //         printf("A FILA %d, Columna %d = %f\n", fila + 1, columna + 1, A[fila*N+columna]);
    //         // printf("B FILA %d, Columna %d = %f\n", fila + 1, columna + 1, B[fila*N+columna]);
    //         // printf("T FILA %d, Columna %d = %f\n", fila + 1, columna + 1, T[fila*N+columna]);
    //         printf("M FILA %d, Columna %d = %lf\n", fila + 1, columna + 1, M[fila*N+columna]);
    //     }
    // }


    timetick = dwalltime();
    printf("----------------------------------\n");
    // Suma A + B, almacenamos el resultado en A
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            A[fila*N+columna] = A[fila*N+columna] + B[fila*N+columna];
        }
    }

    /*R
        𝑅𝑖,𝑗=(1−𝑇𝑖,𝑗)(1−𝑐𝑜𝑠𝜃𝑖,𝑗)+𝑇𝑖,𝑗 𝑠𝑖𝑛𝜃𝑖,𝑗

        Ti,jes el elemento en la posición (i,j)de la matriz T.
        El angulo θi,j, en radianes, se obtiene de la posición (i,j) de una matriz M de NxN.
        Los valores de los elementos de la matriz Mestán comprendidos en un rango entre 0 y 2π.
        */


    // Calculo de R
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            // printf("Con T: %f\n", T[fila*N+columna]);
            // printf("Con M: %f\n",  M[fila*N+columna]);
            // printf("Datos: COS M -> %f \n  SIN M -> %f \n", cos(M[fila*N+columna]), sin(M[fila*N+columna]));

            R[fila*N+columna] = (1 - T[fila*N+columna]) * (1 - cos(M[fila*N+columna])) +  T[fila*N+columna] * sin(M[fila*N+columna]);
            // printf("R -> %f\n", R[fila*N+columna]);
        }
    }
    // printf("----------------------------------\n");
    // printf("RESULTADO R\n");
    // for (int fila = 0; fila < N; fila++) {
    //     for (int columna = 0; columna < N; columna++) {
    //         printf("RES FILA %d, Columna %d = %f\n", fila + 1, columna + 1, R[fila*N+columna]);
    //     }
    // }

    //Promedio de R
    double suma = 0.0;
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            suma += R[fila*N+columna];
        }
    }

    double promedio = suma / (N*N);
    double *RES=(double*)malloc(N*1*sizeof(double));
    // R * (A + B) -> R * A
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            suma = 0;
            for (int indiceFila = 0; indiceFila < N; indiceFila++) {
                // printf("Multiplico %f * %f\n",R[fila*N+indiceFila], A[indiceFila*N+columna]);
                suma += R[fila*N+indiceFila] * A[indiceFila*N+columna];
            }
            RES[0*N+columna] = suma;
        }
        for (int ind = 0; ind < N; ind++) {
            R[fila*N+ind] = RES[0*N+ind];
            // printf("RES FILA 0, Columna %d = %f\n",  + ind, RES[0*N+ind]);
        } // COMERTAR EN LA DOCU
    }
    // printf("----------------------------------\n");
    // for (int fila = 0; fila < N; fila++) {
    //     for (int columna = 0; columna < N; columna++) {
    //         printf("R tiene en Fila %d, Columna %d = %f\n", fila + 1, columna + 1, R[fila*N+columna]);
    //     }
    // }

    // PROMEDIO * (RA + RB)
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            R[fila*N+columna] = R[fila*N+columna] * promedio;
        }
    }

    // printf("PROMEDIO\n");
    // for (int fila = 0; fila < N; fila++) {
    //     for (int columna = 0; columna < N; columna++) {
    //         printf("FINAL FILA %d, Columna %d = %f\n", fila + 1, columna + 1, R[fila*N+columna]);
    //     }
    // }

    // T + 𝑎𝑣𝑔𝑅(𝑅𝐴+𝑅𝐵)
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            T[fila*N+columna] = T[fila*N+columna] + R[fila*N+columna];
        }
    }
    // printf("----------------------------------\n");
    // printf("RESULTADO\n");
    // for (int fila = 0; fila < N; fila++) {
    //     for (int columna = 0; columna < N; columna++) {
    //         printf("FINAL FILA %d, Columna %d = %f\n", fila + 1, columna + 1, T[fila*N+columna]);
    //     }
    // }

    timeend = dwalltime();
    printf("Tiempo en segundos %.10lf \n", (timeend - timetick));
}

/* OPTIMIZACIONES POSIBLES
    * Ordenando la suma de A + B por columnas mejora?
    * ES NECESARIO GUARDAR R?
    * Es mejor guardarse T[fila*N+columna] en una variable?
    * Es mejor guardarse M[fila*N+columna] en una variable?
    * No guardar R * (A + B), calcular el promedio directo?
    * Crear una matriz en vez de fila auxiliar es mejor?
*/