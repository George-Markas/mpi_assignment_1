cmake_minimum_required(VERSION 3.25)
project(mpi)

set(CMAKE_C_STANDARD 11)

set(SOURCES
    src/main.c
    src/read_int.c
)

set(HEADERS
    include/read_int.h
)

# Add MPI Package to Project
find_package(MPI REQUIRED)

# Include header directory
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link MPI libraries
target_link_libraries(${PROJECT_NAME} PRIVATE MPI::MPI_C)
