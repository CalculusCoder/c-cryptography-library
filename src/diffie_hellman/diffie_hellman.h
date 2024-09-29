//
// Created by jared on 9/28/24.
//

#ifndef DIFFIE_HELLMAN_H
#define DIFFIE_HELLMAN_H
int diffie_hellman_generate_public_key(char* output_file_path);
int diffie_hellman_generate_shared_secret(int public_key, char* output_file_path);

#endif //DIFFIE_HELLMAN_H
