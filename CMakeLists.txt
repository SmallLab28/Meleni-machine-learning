
cmake_minimum_required(VERSION 3.10)
project(meleni)
add_executable(app 
    src/main/main.cpp
    src/core/map_file.cpp
    src/token/vocab.cpp
    src/token/bpe.cpp
    )

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third-party
)


