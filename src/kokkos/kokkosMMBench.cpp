#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>
#include <cstring>
#include <limits>

#include <Kokkos_Core.hpp>

void checkDimensions(int &dim);

int main(int argc, char *argv[])
{
   //Set the matrix dimensions (dim x dim). Default 1000
   int dim = -1;

   //Read command line arguments
   for (int i = 0; i < argc; i++)
   {
        if ((strcmp(argv[i], "-D") == 0 ) || (strcmp(argv[i], "--dimensions") == 0))
        {
            dim = atoi(argv[++i]);
            std::cout << "User dimensions (dim x dim) are " << dim << std::endl;
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

    checkDimensions(dim); 

    Kokkos::initialize(argc, argv);
    {

    int n = dim;

    #ifdef KOKKOS_ENABLE_CUDA
    #define MemSpace Kokkos::CudaSpace
    #endif

    #ifdef KOKKOS_ENABLE_OPENMPTARGET
    #define MemSpace Kokkos::OpenMPTargetSpace
    #endif

    #ifndef MemSpace
    #define MemSpace Kokkos::HostSpace
    #endif

    using ExecSpace = MemSpace::execution_space;
    using range_policy = Kokkos::RangePolicy<ExecSpace>;

    //Allocate A, B and C matrix on device
    typedef Kokkos::View<int**> ViewMatrixType;
    ViewMatrixType d_A("A", n, n);
    ViewMatrixType d_B("B", n, n);
    ViewMatrixType d_C("C", n, n);

    ViewMatrixType::HostMirror h_A = Kokkos::create_mirror_view(d_A);
    ViewMatrixType::HostMirror h_B = Kokkos::create_mirror_view(d_B);
    ViewMatrixType::HostMirror h_C = Kokkos::create_mirror_view(d_C);

    //Matrix A init
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            h_A(i,j) = 1;
        }
    }

    //Matrix B init
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            h_B(i,j) = 1;
        }
    }

    //Matrix C init
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            h_C(i,j) = 0;
        }
    }

    Kokkos::deep_copy(d_A, h_A);
    Kokkos::deep_copy(d_B, h_B);
    Kokkos::deep_copy(d_C, h_C);

    double totalTime;

    auto t1 = std::chrono::high_resolution_clock::now();

    Kokkos::parallel_for("C=A*B", range_policy(0, n), KOKKOS_LAMBDA(int i)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                d_C(i,j) += d_A(i,k) * d_B(k,j);
            }
        }       
    });

    /*
    //Perform the matrix multiplication -> C = A*B
    Kokkos::parallel_for("m_mul", n, KOKKOS_LAMBDA (const int i)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                d_C(i,j) += A(i,k) * B(k,j);
            }
        }
    });
    */

    auto t2 = std::chrono::high_resolution_clock::now();

    totalTime = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

    std::cout << "Time elapsed for multiply the matrices was: " << totalTime << " seconds" << std::endl;

    /*
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << C(i,j) << "";
        }
        std::cout << std::endl;
    }
    */

    }
    Kokkos::finalize();

    return 0;
}

void checkDimensions(int &dim)
{
    if (dim == -1)
    {
        dim = 1000;
        std::cout << "Default dimensions are " << dim << " (dim x dim)" << std::endl;
    }

    if (dim <= 0)
    {
        std::cout << "Dimensions must be greater than 0" << std::endl;
        exit(1);
    }
}