#pragma once

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

typedef struct map_file map_file;

typedef enum {
    MLN_OK,
    MLN_NOT_OK,
    MLN_ERR,
}state;

struct map_file{
    #ifdef _WIN32
    HANDLE mapping;
    HANDLE file_mapping;
    #endif
    const unsigned char *file;
    size_t offset;
    size_t file_size;
    int fd;
    int dim; // row
    int vocab_size; // column
};

state open_file(const char *file_name, map_file &data);
void drop_file(map_file &data);
state test_file(map_file &data);
