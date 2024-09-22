#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file(const char *, const char *, int, const char*);
int caesar_encrypt(char*, const char *, int);
int caesar_decrypt(char*, const char *, int);

int main(int argc, char *argv[])
{
    if (argc < 5) {
        printf("Argument count error");
        return 1;
    }

    const char *file_path = argv[1];
    const char *output_file_path = argv[2];
    const int encryption_decryption_key = atoi(argv[3]);
    const char* encrypt = argv[4];

    read_file(file_path, output_file_path, encryption_decryption_key, encrypt);

    return 0;
}



int read_file(const char *file_path, const char *output_file_path, int encryption_decryption_key, const char* encrypt) {
    FILE *fptr = fopen(file_path, "r");
    if (fptr == NULL) {
        printf("Unable to open file");
        return 1;
    }

    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *file_content = malloc((size + 1) *sizeof(char));

    if (file_content == NULL) {
        printf("Memory allocation failure");
        fclose(fptr);
        return 1;
    }




    char *message = malloc((size + 1) *sizeof(char));
    if (message == NULL) {
        printf("Memory allocation failure");
        return 1;
    }

    //read every line and store it in the message variable.
    while (fgets(file_content, size + 1, fptr)) {
        strcat(message, file_content);
    }

    file_content[size] = '\0';

    if (strcmp(encrypt, "true") == 0) {
        caesar_encrypt(message, output_file_path, encryption_decryption_key);
    } else {
        caesar_decrypt(message, output_file_path, encryption_decryption_key);
    }

    fclose(fptr);
    free(file_content);
    free(message);
    message = NULL;
    file_content = NULL;

    return 0;
}



int caesar_encrypt(char *message, const char* output_file_path, int encryption_shift_key) {
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int alphabetLength = strlen(alphabet);
    int messageLength = strlen(message);

    char *encrypted_message = malloc(messageLength * sizeof(char));

    if (encrypted_message == NULL) {
        printf("Memory Allocation Failure\n");
        return 1;
    }


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