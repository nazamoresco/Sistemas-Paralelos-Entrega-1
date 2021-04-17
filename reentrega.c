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
    double *A,*B,*C,*T,*R,*M,*RESULTADO, *RES;
    double timetick, timeend, valorT, valorM, promedio;
    double suma = 0.0;
    int N, fila, columna, indice, indiceFila, auxFila, auxColumna;

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
    RES=(double*)malloc(N*1*sizeof(double));

    //Inicializar las matrices
    if(argc > 2) {
        char input[256];

        for (indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            A[indice] = strtod(input, NULL);
        }

        for (indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            B[indice] = strtod(input, NULL);
        }

        for (indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            T[indice] = strtod(input, NULL);
        }

        for (indice = 0; indice < N * N; indice++) {
            scanf("%s",input);
            M[indice] = strtod(input, NULL);
        }

    } else {
        for (fila = 0; fila<N; fila++) {
            for (columna = 0; columna<N; columna++) {
                A[fila+columna*N] = randFP(0,10);
                B[fila+columna*N] = randFP(0,10);
                M[fila*N+columna] = randFP(0,2*PI);
                T[fila*N+columna] = randFP(0,10);
            }
        }
    }

    timetick = dwalltime();
    // Suma A + fila<N;B, almacenmos el resultado en A
    for (fila = 0; fila<N;fila++) {
        for (columna = 0; columna<N ;columna++) {
            auxColumna = columna*N;
            RESULTADO[fila+auxColumna] = A[fila+auxColumna] + B[fila+auxColumna];
        }
    }


    // Calculo de R
    for (fila = 0; fila<N; fila++) {
        auxFila = fila*N;
        for (columna = 0; columna<N; columna++) {
            valorT =T[auxFila+columna];
            valorM =M[auxFila+columna];
            R[auxFila+columna] = (1 - valorT) * (1 - cos(valorM)) +  valorT * sin(valorM);
        }
    }



    //Promedio de R

    for (fila = 0; fila<N; fila++) {
        auxFila = fila*N;
        for (columna = 0; columna<N; columna++) {
            suma += R[auxFila+columna];
        }
    }


    promedio = suma / (N*N);

    // R * (A + B) -> R * A
    for (fila = 0; fila<N; fila++) {
        auxFila = fila*N;
        for (columna = 0; columna<N; columna++) {
            suma = 0;
            auxColumna = columna*N;
            for (indiceFila = 0; indiceFila<N; indiceFila++) {
                suma += R[auxFila+indiceFila] * RESULTADO[indiceFila+auxColumna];
            }
            RESULTADO[fila+auxColumna] = suma;
        }
    }

    // PROMEDIO * (RA + RB)
    for (fila = 0; fila<N; fila++ ) {
        auxFila = fila*N;
        for (columna = 0; columna<N; columna++) {
            R[auxFila+columna] = RESULTADO[fila+columna*N] * promedio;
        }
    }

    // T + 𝑎𝑣𝑔𝑅(𝑅𝐴+𝑅𝐵)
    for (fila = 0; fila<N; fila++) {
        auxFila = fila*N;
        for (columna = 0; columna<N; columna++) {
            T[auxFila+columna] = T[auxFila+columna] + R[auxFila+columna];
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
    free(A);
	free(B);
	free(C);
	free(T);
	free(R);
	free(M);
	free(RES);
	free(RESULTADO);
    return(0);
}