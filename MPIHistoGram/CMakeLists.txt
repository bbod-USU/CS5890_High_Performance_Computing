cmake_minimum_required(VERSION 3.17)
project(MPIHistoGram)

set(CMAKE_CXX_STANDARD 11)
add_executable(MPIHistoGram main.cpp)

find_package(MPI REQUIRED)
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
target_link_libraries(MPIHistoGram PUBLIC MPI::MPI_CXX)