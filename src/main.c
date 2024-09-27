#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caesar_cipher/caesar_cipher.h"
#include "utils//file_utils.h"
#include "columnar_cipher/columnar_cipher.h"



int main(int argc, char *argv[])
{
    if (argc < 6) {
        printf("Argument count error");
        return 1;
    }

    char *file_path = argv[1];
    char *output_file_path = argv[2];
    char* encrypt = argv[4];
    char* cipher = argv[5];


    int file_size = get_file_size(file_path);
    char* message = get_file_message(file_size, file_path);

    if (message == NULL) {
        return 1;
    }

    if (strcmp(cipher, "caesar") == 0) {
        int encryption_decryption_key = atoi(argv[3]);
        if (strcmp(encrypt, "true") == 0) {
            caesar_encrypt(message, output_file_path, encryption_decryption_key);
        } else {
            caesar_decrypt(message, output_file_path, encryption_decryption_key);
        }

    } else if (strcmp(cipher, "columnar") == 0) {
        char* encryption_decryption_key = argv[3];

        if (strcmp(encrypt, "true") == 0) {
            columnar_cipher_encrypt(message, output_file_path, encryption_decryption_key);
        } else {
            columnar_cipher_decrypt(message, output_file_path, encryption_decryption_key);
        }
    }

    free(message);
    message = NULL;


    return 0;
}

