#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>
#include <cstring>

//Set the matrices dimensions, initially 2000
#define DIM 100
unsigned int NUMTIMES = 10;

//Set the matrices, matrixA and matrixB will be the input matrices
//matrixC will be the multiply result
double matrixA[DIM][DIM];
double matrixB[DIM][DIM];
double matrixC[DIM][DIM];

void fillMatrices (int n);
double multiplyMatrices (int n);
void parseArguments(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    std::cout
        << "MMBench (Matrix Multiplication Benchmark)" << std::endl
        << "Test Version" << std::endl;
    
    std::cout 
        << "Matrices dimensions: " << DIM << std::endl;

    int n = NUMTIMES;

    parseArguments(argc, argv);
    fillMatrices(n);
    double time = multiplyMatrices(n);

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

double  multiplyMatrices (int n)
{
    int i, j, k;

    double totalTime;

    auto t1 = std::chrono::high_resolution_clock::now();

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrixC[i][j] = 0;
            for (k = 0; k < n; k++)
            {
                matrixC[i][j] = matrixC[i][j] + matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    totalTime = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

    return totalTime;
}

int parseUInt(const char *str, unsigned int *output)
{
  char *next;
  *output = strtoul(str, &next, 10);
  return !strlen(next);
}

int parseInt(const char *str, int *output)
{
  char *next;
  *output = strtol(str, &next, 10);
  return !strlen(next);
}

void parseArguments(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (!std::string("--dimsize").compare(argv[i]))
        {
            if (++i >= argc || DIM < 0)
            {
                std::cerr << "Invalid dimensions size" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (!std::string("--ntimes").compare(argv[i]))
        {
            if (++i >= argc || !parseUInt(argv[i], &NUMTIMES))
            {
                std::cerr << "Invalid number of times" << std::endl;
                exit(EXIT_FAILURE);
            }
            if (NUMTIMES < 1)
            {
                std::cerr << "Number of times must be  1 or more" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (!std::string("--help").compare(argv[i]))
        {
            std::cout << std::endl;
            std::cout << "Usage of MMBench (Matrix Multiplication Benchmark)" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "   --help                  Print this message" << std::endl;
            std::cout << "   --dimsize    DIM        Use DIM for matrices" << std::endl;
            std::cout << "   --ntimes     NUMTIMES   Run the MMBench NUMTIMES" << std::endl;
            std::cout << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            std::cerr << "Unrecognized argument" << argv[i] << "(try '--help')" << std::endl;
            exit(EXIT_FAILURE);
        }
    }  
}

