//
// Created by jared on 9/23/24.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_file_size(char *file_path) {
    FILE *fptr = fopen(file_path, "r");
    if (fptr == NULL) {
        printf("Unable to open file");
        return 1;
    }

    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    fclose(fptr);
    return size;
}


char* get_file_message(int file_size, char* file_path) {
    FILE *fptr = fopen(file_path, "r");
    if (fptr == NULL) {
        printf("Unable to open file");
        return NULL;
    }

    char *message = malloc((file_size + 1) *sizeof(char));

    if (message == NULL) {
        printf("Memory allocation failure");
        fclose(fptr);
        return NULL;
    }


    fread(message, 1, file_size, fptr);
    fclose(fptr);

    message[file_size] = '\0';

    return message;
}



