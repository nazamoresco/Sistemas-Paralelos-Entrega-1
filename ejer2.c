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
    double *A,*B,*C,*T,*R,*M,*RESULTADO;
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
    RESULTADO=(double*)malloc(N*N*sizeof(double));

    //Inicializar las matrices
    if(argc > 2) {
        char input[256];

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            A[indice] = strtod(input, NULL);
        }

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            B[indice] = strtod(input, NULL);
        }

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            T[indice] = strtod(input, NULL);
        }

        for (int indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            M[indice] = strtod(input, NULL);
        }

    } else {
        for (int fila = N; fila--;) {
            for (int columna = N; columna--;) {
                A[fila*N+columna] = randFP(0,10);
                B[fila*N+columna] = randFP(0,10);
                M[fila*N+columna] = randFP(0,2*PI);
                T[fila*N+columna] = randFP(0,10);
            }
        }
    }

    timetick = dwalltime();
    printf("----------------------------------\n");
    // Suma A + B, almacenamos el resultado en A
    for (int fila = N; fila--;) {
        for (int columna = N; columna--;) {
            RESULTADO[fila+columna*N] = A[fila*N+columna] + B[fila*N+columna];
        }
    }

    double valorT, valorM;
    // Calculo de R
    for (int fila = N; fila--;) {
        for (int columna = N; columna--;) {
            valorT =T[fila*N+columna];
            valorM =M[fila*N+columna];
            R[fila*N+columna] = (1 - valorT) * (1 - cos(valorM)) +  valorT * sin(valorM);
        }
    }



    //Promedio de R
    double suma = 0.0;
    for (int fila = N; fila--;) {
        for (int columna = N; columna--;) {
            suma += R[fila*N+columna];
        }
    }


    double promedio = suma / (N*N);
    double *RES=(double*)malloc(N*1*sizeof(double));
    // R * (A + B) -> R * A
    for (int fila = N; fila--;) {
        for (int columna = N; columna--;) {
            suma = 0;
            for (int indiceFila = N; indiceFila--;) {
                suma += R[fila*N+indiceFila] * RESULTADO[indiceFila+columna*N];
            }
            RESULTADO[fila+columna*N] = suma;
        }
        // for (int ind = N; ind--; ) {
        //     R[fila*N+ind] = RES[0*N+ind];
        // } // COMERTAR EN LA DOCU
    }

    // PROMEDIO * (RA + RB)
    for (int fila = N; fila--; ) {
        for (int columna = N; columna--; ) {
            R[fila*N+columna] = RESULTADO[fila+columna*N] * promedio;
        }
    }

    // T + 𝑎𝑣𝑔𝑅(𝑅𝐴+𝑅𝐵)
    for (int fila = N; fila--;) {
        for (int columna = N; columna--;) {
            T[fila*N+columna] = T[fila*N+columna] + R[fila*N+columna];
        }
    }

    timeend = dwalltime();
    printf("Tiempo en segundos %.10lf \n", (timeend - timetick));

    // printf("----------------------------------\n");
    // printf("RESULTADO\n");
    // for (int fila = 0; fila < N; fila++) {
    //     for (int columna = 0; columna < N; columna++) {
    //         printf("FINAL FILA %d, Columna %d = %f\n", fila + 1, columna + 1, T[fila*N+columna]);
    //     }
    // }
}