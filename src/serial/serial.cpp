#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>
#include <cstring>

double matrixMultiply(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   //Set the matrix dimensions (dim x dim)
   int dim = 10;

   //Read command line arguments
   for (int i = 0; i < argc; i++)
   {
        if ((strcmp(argv[i], "-D") == 0 ) || (strcmp(argv[i], "--dimensions") == 0))
        {
            dim = atoi(argv[++i]);
            std::cout << "User dimensions (dim x dim) is " << dim << std::endl;
        }
        else if ((strcmp(argv[i], "-H") == 0) || (strcmp(argv[i], "--help") == 0))
        {
            std::cout << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "--dimensions (-D) [int]   Set the dimensions of matrix (dim x dim)" 
                      << std::endl;
            std::cout << "--help (-H)               Display this message"
                      << std::endl;
            std::cout << std::endl;
            exit(1);
        } 
   } 

   double totalTime = matrixMultiply(argc, argv);

   std::cout << "Time elapsed for multiply the matrices was: " << totalTime << " seconds" << std::endl;

   return 0;
}

double matrixMultiply(int argc, char *argv[])
{
    //Store dimensions argument
    int n = atoi(argv[2]);

    //Define matrices dynamically
    int** A = new int*[n];
    int** B = new int*[n];
    int** C = new int*[n];

    for (int i = 0; i < n; i++)
    {
        A[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        B[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        C[i] = new int[n];
    }

    //Matrix A init
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            //*(A + i*n + j) = 1;
            A[i][j] = 1;
        }
    }

    //Matrix B init
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //*(B + i*n + j) = 1;
            B[i][j] = 1;
        }
    }

    //Matrix C init
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //*(C + i*n + j) = 0;
            C[i][j] = 0;
        }
    }

    double totalTime;

    auto t1 = std::chrono::high_resolution_clock::now();

    //Perform the matrix multiplication -> C = A*B
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    totalTime = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

    for (int i = 0; i < n; i++)
    {
        delete[] A[i];
    }
    delete[] A;

     for (int i = 0; i < n; i++)
    {
        delete[] B[i];
    }
    delete[] B;

     for (int i = 0; i < n; i++)
    {
        delete[] C[i];
    }
    delete[] C;

    return totalTime;
}