#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>
#include <cstring>

//Set the matrices dimensions, initially 2000
#define DIM 100


//Set the matrices, matrixA and matrixB will be the input matrices
//matrixC will be the multiply result
double matrixA[DIM][DIM];
double matrixB[DIM][DIM];
double matrixC[DIM][DIM];

void fillMatrices (int n);

double multiplyMatrices (int x);

int main(int argc, char *argv[])
{
    fillMatrices(DIM);
    double time = multiplyMatrices(DIM);

    std::cout << "Time elapsed for multiply the matrices was: " << time << " seconds" << std::endl;

    return 0;
}

void fillMatrices (int n)
{
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrixA[i][j] = rand();
            matrixB[i][j] = rand();
        }
    }
}

double  multiplyMatrices (int x)
{
    int i, j, k;

    double totalTime;

    auto t1 = std::chrono::high_resolution_clock::now();

    for (i = 0; i < x; i++)
    {
        for (j = 0; j < x; j++)
        {
            matrixC[i][j] = 0;
            for (k = 0; k < x; k++)
            {
                matrixC[i][j] = matrixC[i][j] + matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    totalTime = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

    return totalTime;
}
