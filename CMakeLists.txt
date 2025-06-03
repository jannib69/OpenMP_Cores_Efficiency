cmake_minimum_required(VERSION 3.16)
project(OpenMP)

set(CMAKE_CXX_STANDARD 20)

# poti do OpenMP
include_directories(/opt/homebrew/opt/libomp/include)
link_directories(/opt/homebrew/opt/libomp/lib)

# dodaj izvršljivo datoteko
add_executable(OpenMP main.cpp)

# omogoči OpenMP in poveži knjižnico
target_compile_options(OpenMP PRIVATE -Xpreprocessor -fopenmp)
target_link_libraries(OpenMP PRIVATE omp)