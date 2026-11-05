#include <iostream>
#include "core/map_file.hpp"

#ifdef _WIN32
#include <windows.h>

state open_file(const char *file_path, map_file &data){
        data.file_mapping = CreateFileA(
        file_path, 
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (data.file_mapping == INVALID_HANDLE_VALUE){
        printf("FAIL WHEN LOAD FILE: %lu\n", GetLastError());
        return MLN_ERR;
    }
    data.mapping = CreateFileMappingA(data.file_mapping, NULL, PAGE_READONLY, 0,0, NULL);
    if (!data.mapping) return MLN_ERR;
    data.file = (const unsigned char*) MapViewOfFile(data.mapping, FILE_MAP_READ, 0,0,0);
    if(data.file == NULL) return MLN_ERR;

    LARGE_INTEGER file_size;
    if (!GetFileSizeEx(data.file_mapping, &file_size)){
        UnmapViewOfFile(data.file);
        CloseHandle(data.mapping);
        CloseHandle(data.file_mapping);
        data.file = nullptr;
        return MLN_ERR;
    }
    data.file_size = (size_t)file_size.QuadPart; 
    return MLN_OK;
}

void drop_file(map_file &data){
    UnmapViewOfFile(data.file);
    CloseHandle(data.mapping);
    CloseHandle(data.file_mapping);
}
#else 
#include <sys/mman.h>
#include <sys/stat.h>
state open_file(const char *file_path, map_file &data){
    data.fd = open(file_path, O_RDONLY);
    if(data.fd == NULL) return MLN_ERR;
    struct stat st;
    if(fstat(fd, &st) == -1) {
        close(data.fd);
        return MLN_ERR;
    }
    data.file = (const unsigned char*) mmap(NULL, st.st_size, 
        PROT_READ, MAP_PRIVATE, fd, data.offset);
    data.file_size = (size_t)st.st_size;   
    
}

void drop_file(map_file &data){
    struct stat st;
    munmap(data.file, st.st_size);
    close(data.fd);
}
#endif

state test_file(map_file &data){
    const unsigned char *data_view = data.file;
    printf("%c\n", data_view[1000]);
    printf("file size is: %zu\n", data.file_size);
    return MLN_OK;
}
