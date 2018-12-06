#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

void naive_multiplication(double **A, double **B, double **C, int n, int m, int o)
{ 

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < o; j++)
        {
            for (int k = 0; k < m; k++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void better_multiplication(double **A, double **B, double **C, int n, int m, int o)
{

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m; k++)
        {
            for (int j = 0; j < o; j++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void gsl_multiplication(double *A_ptr, double *B_ptr, double *C_ptr, int n, int m, int o, int p)
{
       
    gsl_matrix_view A = gsl_matrix_view_array(A_ptr, n, m);
    gsl_matrix_view B = gsl_matrix_view_array(B_ptr, o, p);
    gsl_matrix_view C = gsl_matrix_view_array(C_ptr, n, p);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &A.matrix, &B.matrix, 0.0, &C.matrix);
}

int main(int argc, char const *argv[])
{
    clock_t start, end;
    srand(time(NULL));
    printf("Creating csv file\n");
    FILE *fp=fopen("lab3.csv","w+");
	fprintf(fp,"size,naive,better,blas\n");
    
    for(int i = 100; i < 1001; i = i + 100)
    {
        printf("Iteracja: %d\n", i/100);

        double **A = calloc(i, sizeof(double *));
        double **B = calloc(i, sizeof(double *));
        double **C = calloc(i, sizeof(double *));

        double *A_ptr = calloc(i*i, sizeof(double));
        double *B_ptr = calloc(i*i, sizeof(double));
        double *C_ptr = calloc(i*i, sizeof(double));
            
        for(int j =0; j<i; j++)
        {
            A[j] = calloc(i,sizeof(double));
            B[j] = calloc(i,sizeof(double));
            C[j] = calloc(i,sizeof(double));
        }

        for(int j =0; j<i; j++)
        {
            for(int k=0; k<i; k++)
            {
                A[j][k] = (double)rand()/RAND_MAX;
                B[j][k] = (double)rand()/RAND_MAX;
                C[j][k] = 0.0;
            }
        }


        for(int j=0; j<i*i; j++)
        {
            A_ptr[j] = (double)rand()/RAND_MAX;
            B_ptr[j] = (double)rand()/RAND_MAX;
            C_ptr[j] = 0.0;
        }

        start = clock();
        naive_multiplication(A, B, C, i, i, i);
        end = clock();
        fprintf(fp,"%d,%f", i, ((double) (end - start)) / CLOCKS_PER_SEC);
        
        start = clock();
        better_multiplication(A, B, C, i, i, i);
        end = clock();
        fprintf(fp,",%f", ((double) (end - start)) / CLOCKS_PER_SEC);
        
        start = clock();
        gsl_multiplication(A_ptr, B_ptr, C_ptr, i, i, i, i);
        end = clock();
        fprintf(fp,",%f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
        


        for (int j = 0; j < i; j++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }

        free(A);
        free(B);
        free(C);
        free(A_ptr);
        free(B_ptr);
        free(C_ptr);

        printf("Koniec iteracji: %d\n", i/100);
    }

    fclose(fp);

    return 0;
}


