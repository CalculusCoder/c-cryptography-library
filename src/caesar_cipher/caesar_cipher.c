//
// Created by jared on 9/23/24.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int caesar_encrypt(char *message, const char* output_file_path, int encryption_shift_key) {
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int alphabetLength = strlen(alphabet);
    int messageLength = strlen(message);

    char *encrypted_message = malloc(messageLength * sizeof(char));

    if (encrypted_message == NULL) {
        printf("Memory Allocation Failure\n");
        return 1;
    }

    //can be refactored to run in o(n) time using a lookup table
    for(int i = 0; i < messageLength; i++) {
        encrypted_message[i] = message[i];

        for (int j = 0; j < alphabetLength; j++) {
            if (tolower(message[i]) == (alphabet[j])) {
                j += encryption_shift_key;

                if (j >= alphabetLength) {
                    j = j % alphabetLength;
                }

                if (isupper(message[i])) {
                    encrypted_message[i] = toupper(alphabet[j]);
                } else {
                    encrypted_message[i] = alphabet[j];
                }

                break;
            }
        }
    }

    encrypted_message[messageLength] = '\0';

    FILE *fptr = fopen(output_file_path, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing\n");
        free(encrypted_message);
        encrypted_message = NULL;
        return 1;
    }

    fprintf(fptr, encrypted_message);
    if (ferror(fptr)) {
        printf("Error writing to file\n");
        fclose(fptr);
        free(encrypted_message);
        encrypted_message = NULL;
        return 1;
    }

    fclose(fptr);

    free(encrypted_message);
    encrypted_message = NULL;

    return 0;
}

int caesar_decrypt(char *message, const char* output_file_path, int decryption_key) {
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int alphabetLength = strlen(alphabet);
    int messageLength = strlen(message);

    char *decrypted_message = malloc(messageLength * sizeof(char));

    if (decrypted_message == NULL) {
        printf("Memory Allocation Failure\n");
        return 1;
    }

    for(int i = 0; i < messageLength; i++) {
        decrypted_message[i] = message[i];

        for (int j = 0; j < alphabetLength; j++) {
            if (tolower(message[i]) == (alphabet[j])) {
                j = j - decryption_key;

                if (j <= -1) {
                    j = j % alphabetLength;
                    j = j + alphabetLength;
                }

                if (isupper(message[i])) {
                    decrypted_message[i] = toupper(alphabet[j]);
                } else {
                    decrypted_message[i] = alphabet[j];
                }

                break;
            }
        }
    }

    decrypted_message[messageLength] = '\0';


    FILE *fptr = fopen(output_file_path, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing\n");
        free(decrypted_message);
        decrypted_message = NULL;
        return 1;
    }



    fprintf(fptr, decrypted_message);
    fclose(fptr);

    free(decrypted_message);
    decrypted_message = NULL;

    return 0;
}