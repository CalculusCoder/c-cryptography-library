//
// Created by jared on 9/23/24.
//

#ifndef COLUMNAR_CIPHER_C_H
#define COLUMNAR_CIPHER_C_H

int columnar_cipher_encrypt(char*message, char* output_file_path, char *encryption_decryption_key);
int columnar_cipher_decrypt(char*message, char* output_file_path, char *encryption_decryption_key);

#endif //COLUMNAR_CIPHER_C_H
