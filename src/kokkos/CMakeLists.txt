cmake_minimum_required(VERSION 3.16)
project(kokkosMMBench)
include(common.cmake)

add_executable(kokkosMMBench kokkosMMBench.cpp)
target_link_libraries(kokkosMMBench Kokkos::kokkos)