cmake_minimum_required(VERSION 3.29)
project(cryptography_library C)

set(CMAKE_C_STANDARD 11)



add_executable(cryptography_library src/main.c
        src/caesar_cipher/caesar_cipher.c
        src/caesar_cipher/caesar_cipher.h
        src/utils/file_utils.c
        src/utils/file_utils.h
        src/columnar_cipher/columnar_cipher.h
        src/columnar_cipher/columnar_cipher.c)

