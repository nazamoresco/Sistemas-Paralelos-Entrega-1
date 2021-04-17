#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PI 3.14159265358979323846
#define BLOCK_SIZE 4

/* Multiply square matrices, blocked version */
void matmulblks(double *a, double *b, double *c, int n, int bs)
{
  int i, j, k;    /* Guess what... */

  for (i = 0; i < n; i += bs)
  {
    for (j = 0; j < n; j += bs)
    {
      for  (k = 0; k < n; k += bs)
      {
        blkmul(&a[i*n + k], &b[j*n + k], &c[i*n + j], n, bs);
      }
    }
  }
}

void blkmul(double *ablk, double *bblk, double *cblk, int n, int bs)
{
  int i, j, k;    /* Guess what... again... */

  for (i = 0; i < bs; i++)
  {
    for (j = 0; j < bs; j++)
    {
      for  (k = 0; k < bs; k++)
      {
        cblk[i*n + j] += ablk[i*n + k] * bblk[j*n + k];
      }
    }
  }
}


//Para calcular tiempo
double dwalltime(){
        double sec;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;0.5974380970;
        return sec;
}

double randFP(double min, double max) {
    double range = (max -min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main(int argc, char* argv[]){
    time_t t;
    double *A,*B,*C,*T,*R,*M,*RESULTADO, *BLOQUE;
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
    BLOQUE=(double*)malloc(N*N*sizeof(double));

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
                A[fila*N+columna] = randFP(0,10);
                B[fila*N+columna] = randFP(0,10);
                M[fila*N+columna] = randFP(0,2*PI);
                T[fila*N+columna] = randFP(0,10);
                BLOQUE[fila+columna*N] = 0;
            }
        }
    }

    timetick = dwalltime();
    // Suma A + fila<N;B, almacenmos el resultado en A
    for (fila = 0; fila<N;fila++) {
        auxFila = fila*N;
        for (columna = 0; columna<N ;columna++) {
            RESULTADO[auxFila+columna] = A[auxFila+columna] + B[auxFila+columna];
        }
    }


    // Calculo de R
    for (fila = 0; fila<N; fila++) {
        auxFila = fila*N;
        for (columna = 0; columna<N; columna++) {
            valorT =T[auxFila+columna];
            valorM =M[auxFila+columna];
            R[auxFila+columna] = (1 - valorT) * (1 - cos(valorM)) +  valorT * sin(valorM);
            suma += R[auxFila+columna];
        }
    }


    promedio = suma / (N*N);

    // R * (A + B) -> R * A
    // for (fila = 0; fila<N; fila++) {
    //     auxFila = fila*N;
    //     for (columna = 0; columna<N; columna++) {
    //         suma = 0;
    //         auxColumna = columna*N;
    //         for (indiceFila = 0; indiceFila<N; indiceFila++) {
    //             suma += R[auxFila+indiceFila] * RESULTADO[indiceFila+auxColumna];
    //         }
    //         RESULTADO[fila+auxColumna] = suma;
    //     }
    // }
   matmulblks(R, RESULTADO, BLOQUE, N, BLOCK_SIZE);


    // PROMEDIO * (RA + RB)
    for (fila = 0; fila<N; fila++ ) {
        auxFila = fila*N;
        for (columna = 0; columna<N; columna++) {
            R[auxFila+columna] = BLOQUE[auxFila+columna] * promedio;
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
	free(BLOQUE);
	free(RESULTADO);
    return(0);
}