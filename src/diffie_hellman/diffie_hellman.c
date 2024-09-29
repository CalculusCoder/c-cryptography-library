//
// Created by jared on 9/28/24.
//
# define PRIME_NUMBER 13
# define PK_GENERATOR_BASE 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int diffie_hellman_generate_public_key(char* output_file_path) {
    srand(time(NULL));
    int random_private_key = rand() % 10 + 1;

    int result = 1;
    for (int i = 0; i < random_private_key; i++) {
        result = result * PK_GENERATOR_BASE;
    }


    int generated_public_key = result % PRIME_NUMBER;
    int length = snprintf(NULL, 0, "%d", generated_public_key) + 1;

    char public_key_str[length];

    sprintf(public_key_str, "%d", generated_public_key);


    FILE *fptr = fopen(output_file_path, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }

    fprintf(fptr, public_key_str);
    if (ferror(fptr)) {
        printf("Error writing to file\n");
        fclose(fptr);
        return 1;
    }

    fclose(fptr);

    return 0;
}

int diffie_hellman_generate_shared_secret(int public_key, char* output_file_path) {

    srand(time(NULL));
    int random_private_key = rand() % 10 + 1;

    int result = 1;
    for (int i = 0; i < random_private_key; i++) {
        result = result * public_key;
    }

    int shared_secret_key = result % PRIME_NUMBER;
    int length = snprintf(NULL, 0, "%d", shared_secret_key) + 1;
    char shared_secret_key_string[length];

    sprintf(shared_secret_key_string, "%d", shared_secret_key);

    FILE *fptr = fopen(output_file_path, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }

    fprintf(fptr, shared_secret_key_string);
    if (ferror(fptr)) {
        printf("Error writing to file\n");
        fclose(fptr);
        return 1;
    }

    fclose(fptr);


    return 0;
}
