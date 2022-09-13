#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//RREF works for wide matrices, meaning that the number of columns must be greater than
//the number of rows, RREF function can be using to find the inverse of a matrix and to
//solve a linear system of equation where the number of unknowns is the same as the number
//of equation in the system.
//computing the RREF of a matrix can be inefficient due to the rounding of computer errors
//thus, this algorithm can be used efficiently for medium sized matrices and for an approximated result.
void RREF(double** Mat, int M, int N)
{
    int i, j, k, l;
    double pivot, factor;
    int above=0;
    int below=0;
    //pivots are the diagonal elements:
    for(i=0; i<M; i++) //iterate over all the elements of the matrix
    {
        for(j=0; j<N; j++)
        {
            if(i==j)
            {
                //we want to know how many elements are above and below the pivot:
                below = M - i-1;
                above = M - below - 1;
                //iterate through the elements above:
                for(k=0; k<above; k++)
                {
                    //know the pivot and the factor
                    pivot = Mat[i][i];
                    factor = Mat[k][i];
                    if((pivot==0)||(factor==0))
                        continue;
                    for(l=0; l<N; l++)
                    {
                        Mat[i][l] = Mat[i][l]*factor;
                        Mat[k][l] = Mat[k][l]*pivot;
                    }
                    for(l=0; l<N; l++)
                    {
                        Mat[k][l] = Mat[k][l] - Mat[i][l];
                    }
                }
                //iterate through the elements below:
                for(k=i+1; k<i+below+1; k++)
                {
                    //know the pivot and the factor
                    pivot = Mat[i][i];
                    factor = Mat[k][i];
                    for(l=0; l<N; l++)
                    {
                        Mat[i][l] = Mat[i][l]*factor;
                        Mat[k][l] = Mat[k][l]*pivot;
                    }
                    for(l=0; l<N; l++)
                    {
                        Mat[k][l] = Mat[k][l] - Mat[i][l];
                    }
                }
            }
        }
    }
    //diagonal must be units ( = 1 )
    double unit;
    if(M<=N)
    {
        for(i=0; i<M; i++)
        {
            unit = Mat[i][i];
            if(unit!=0)
                for(l=0; l<N; l++)
                    Mat[i][l] = Mat[i][l]/unit;
        }
    }
    return;
}

int main()
{
    int M, N;
    int i, j;
    double **Mat;
    printf("Rows: ");
    scanf("%d", &M);
    printf("Columns: ");
    scanf("%d", &N);
    //allocation:
    Mat = (double**)malloc(M*sizeof(double*));
    for(i=0; i<M; i++)
        Mat[i] = (double*)malloc(N*sizeof(double));
    for(i=0; i<M; i++)
        for(j=0; j<N; j++)
        {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &Mat[i][j]);
        }
    RREF(Mat, M, N);
    printf("\n\n__________________________________\n");
    for(i=0; i<M; i++)
    {
        for(j=0; j<N; j++)
        {
            printf("%.3lf\t", Mat[i][j]);
        }
        if(i!=M)
        printf("|\n");
    }
    printf("_________________________________\n");

    for(i=0; i<M; i++)
        free(Mat[i]);
    free(Mat);
    return 0;
}
