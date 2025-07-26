cmake_minimum_required(VERSION 3.10)
project(InMemoryDB)
set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Database.cpp
    src/Table.cpp
    src/Parser.cpp
)

add_executable(in_memory_db ${SOURCES})