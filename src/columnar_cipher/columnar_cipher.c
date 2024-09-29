//
// Created by jared on 9/23/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct key_value {
    int key;
    char* value;
};

int compare(const void* a, const void* b) {
    struct key_value* kvA = (struct key_value*)a;
    struct key_value* kvB = (struct key_value*)b;
    return (kvA->key - kvB->key);
}

int find_lowest_key_index(struct key_value kv[], int key_length, int visited[]) {
    int min_key = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < key_length; i++) {
        // Skip keys that have already been visited
        if (!visited[i] && kv[i].key < min_key) {
            min_key = kv[i].key;
            min_index = i;
        }
    }

    return min_index;  // Return the index of the lowest key found
}



void append_letter(struct key_value* kv, int kv_index, char letter) {
    if (kv[kv_index].value == NULL) {
        kv[kv_index].value = malloc(2*sizeof(char));
    } else {
        unsigned int current_length = strlen(kv[kv_index].value);
        kv[kv_index].value = realloc(kv[kv_index].value, (current_length + 2) * sizeof(char));
    }

    unsigned int current_length = strlen(kv[kv_index].value);
    kv[kv_index].value[current_length] = letter;
    kv[kv_index].value[current_length + 1] = '\0';
}


int columnar_cipher_encrypt(char*message, char* output_file_path, char* encryption_decryption_key) {

    int alphabet_lookup[26];
    int key_length = strlen(encryption_decryption_key);
    int letter_index[key_length];
    int messageLength = strlen(message);


    char* new_message = malloc((messageLength + 1) * sizeof(char));
    if (new_message == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int j = 0;
    for (int i = 0; i < messageLength; i++) {
        if (message[i] != '\n' && message[i] != '\r') {
            new_message[j] = message[i];
            j++;
        }
    }

    new_message[j] = '\0';


    for (int i = 0; i < 26; i++) {
        alphabet_lookup[i] = i;
    }

    int number_of_keys = key_length;
    struct key_value *kv = malloc(sizeof(struct key_value) * number_of_keys);
    if (kv == NULL) {
        perror("Malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < key_length; i++) {

        letter_index[i] = alphabet_lookup[encryption_decryption_key[i] - 'a'];
        kv[i].key = letter_index[i];
        kv[i].value = NULL;
    }

    int current_kv_index = 0;
    int current_index = 0;

    for (int start = 0; start < messageLength;) {

        append_letter(kv, current_kv_index, new_message[start]);

        if (start + key_length >= messageLength) {
            current_index++;
            start = current_index;
            current_kv_index++;
        } else {

            start += key_length;
        }

        if (start >= messageLength || current_kv_index >= key_length) {
            break;
        }
    }

    qsort(kv, number_of_keys, sizeof(struct key_value), compare);

    char encrypted_message[messageLength + 1];
    encrypted_message[0] = '\0';



    for (int i = 0; i < number_of_keys; i++) {
        strcat(encrypted_message, kv[i].value);
    }

    printf("Encrypted message: %s", encrypted_message);

    FILE *fptr = fopen(output_file_path, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing\n");
        free(kv);
        free(new_message);
        return 1;
    }

    fprintf(fptr, encrypted_message);

    if (ferror(fptr)) {
        printf("Error writing to file\n");
        fclose(fptr);
        free(kv);
        free(new_message);
        return 1;
    }

    fclose(fptr);




    for (int i = 0; i < key_length; i++) {
        if (kv[i].value != NULL) {
            free(kv[i].value);
            kv[i].value = NULL;
        }
    }


    free(kv);
    free(new_message);
    return 0;
}



int columnar_cipher_decrypt(char*message, char* output_file_path, char* encryption_decryption_key) {

    int alphabet_lookup[26];
    int key_length = strlen(encryption_decryption_key);
    int letter_index[key_length];
    int messageLength = strlen(message);

    char* new_message = malloc((messageLength + 1) * sizeof(char));
    if (new_message == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int j = 0;
    for (int i = 0; i < messageLength; i++) {
        if (message[i] != '\n' && message[i] != '\r') {
            new_message[j] = message[i];
            j++;
        }
    }

    new_message[j] = '\0';

    for (int i = 0; i < 26; i++) {
        alphabet_lookup[i] = i;
    }

    int number_of_keys = key_length;
    struct key_value *kv = malloc(sizeof(struct key_value) * number_of_keys);
    if (kv == NULL) {
        perror("Malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < key_length; i++) {

        letter_index[i] = alphabet_lookup[encryption_decryption_key[i] - 'a'];
        kv[i].key = letter_index[i];
        kv[i].value = NULL;
    }


    // qsort(kv, number_of_keys, sizeof(struct key_value), compare);

    int visited[key_length];  // Array to track visited keys
    for (int i = 0; i < key_length; i++) {
        visited[i] = 0;  // Initialize all as unvisited
    }

    int result = messageLength / key_length;
    int result_duplicate = result;
    int remainder = messageLength % key_length;
    int columns = key_length;
    int current_kv_index = 0;

    for (int start = 0; start < messageLength; start++) {
        int lowest = find_lowest_key_index(kv, key_length, visited);

        if (remainder >= lowest + 1) {
            result+=1; //has result + 1 rows

            for (int j = 0; j < result && current_kv_index < messageLength; j++) {
                append_letter(kv, lowest, new_message[current_kv_index]);
                current_kv_index++;
            }

            result = result_duplicate;

            visited[lowest] = 1;
        } else { //has result rows
            for (int j = 0; j < result && current_kv_index < messageLength; j++) {
                append_letter(kv, lowest, new_message[current_kv_index]);
                current_kv_index++;
            }

            visited[lowest] = 1;

        }

    }

    int decrypted_message_length = 0;

    char decrypted_message[messageLength + 1];
    decrypted_message[0] = '\0';


    int value_letter_index = 0;

    for (int i = 0; decrypted_message_length < messageLength;) {
        decrypted_message[decrypted_message_length] = kv[i].value[value_letter_index];

        decrypted_message_length++;

        if (i + 1 == key_length) {
            value_letter_index++;
            i = 0;

        } else {
            i++;
        }

    }

    decrypted_message[messageLength] = '\0';



    FILE *fptr = fopen(output_file_path, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing\n");
        free(kv);
        free(new_message);
        return 1;
    }

    fprintf(fptr, decrypted_message);

    if (ferror(fptr)) {
        printf("Error writing to file\n");
        fclose(fptr);
        free(kv);
        free(new_message);
        return 1;
    }

    fclose(fptr);


    for (int i = 0; i < key_length; i++) {
        if (kv[i].value != NULL) {
            free(kv[i].value);
            kv[i].value = NULL;
        }
    }


    free(kv);
    free(new_message);
    return 0;
}