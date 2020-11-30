#include <openssl/evp.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <string.h>


int encrypt(FILE * file, FILE * key_file) {
    int read_len = 16;
    EVP_PKEY * pubkey;
    EVP_CIPHER_CTX *ctx;
    const EVP_CIPHER *cipher = EVP_aes_256_ctr();
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        exit(0);
        printf("Encryption failed\n");
    }
    unsigned char *ciphertext = (unsigned char *) malloc(EVP_MAX_BLOCK_LENGTH + read_len);
    unsigned char buffer[EVP_MAX_BLOCK_LENGTH + read_len];
    int len;

    pubkey = PEM_read_PUBKEY(key_file, NULL, NULL, NULL);
    if (pubkey == NULL) {
        printf("Public key couldn't be loaded\n");
        return 0;
    }
    unsigned char * my_ek = (unsigned char *) malloc(EVP_PKEY_size(pubkey));
    int my_ekl;
    unsigned char * iv = (unsigned char *) malloc(EVP_CIPHER_iv_length(cipher));

    if (1 != EVP_SealInit( ctx, cipher, &my_ek, &my_ekl, iv, &pubkey, 1)) {
        printf("Encryption failed1\n");
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    FILE *ct;
    ct = fopen("encrypted_file", "wb");
    int cipher_code = 435; //4 - A, 3 - E, 5 - S 
    fwrite(&cipher_code, sizeof(cipher_code),1,ct);
    //int mode_code = 686; //C - 6, B - 8, C - 6
    int mode_code = 679; //C - 6, T - 7, R - 9
    fwrite(&mode_code, sizeof(mode_code),1,ct);
    fwrite(&my_ekl, sizeof(my_ekl), 1, ct);
    fwrite(my_ek, my_ekl, 1, ct);
    fwrite(iv, EVP_CIPHER_iv_length(cipher), 1, ct);
    int x;
    while (1) {
        x = fread(buffer, 1, read_len, file);
        if (!x) break;
        if (1 != EVP_SealUpdate(ctx, ciphertext, &len, buffer, x)) {
            printf("Encryption failed2\n");
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
        fwrite(ciphertext, 1, len, ct);
        //printf("len1: %d\n", len);
        if (ferror(ct)) {
            printf("Couldn't write to file \"encrypted_file\"\n");
            fclose(ct);
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
    }
    if (1 != EVP_SealFinal(ctx, ciphertext, &len)) {
        printf("Encryption failed4\n");
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    fwrite(ciphertext, 1, len, ct);
    //printf("len2: %d\n", len);
    if (ferror(ct)) {
            printf("Couldn't write to file \"encrypted_file\"\n");
            fclose(ct);
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
    fclose(ct);
    free(ciphertext);
    free(iv);
    free(my_ek);
    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

int decrypt(FILE * file, FILE * key_file) {
    int read_len = 16;
    const EVP_CIPHER *cipher;
    unsigned char buffer[EVP_MAX_BLOCK_LENGTH + read_len];
    int x;

    EVP_PKEY * priv_key;
    priv_key = PEM_read_PrivateKey(key_file, NULL, NULL, NULL);
    if (priv_key == NULL) {
        printf("Private key couldn't be loaded\n");
        return 0;
    }

    if (!fread(&x, 4, 1, file)) {
        printf("Data (cipher code) couldn't be loaded\n");
        return 0;
    }
    if (x != 435) {
        printf("Sorry, the cipher isn't supported\n");
        return 0;
    }
    if (!fread(&x, 4, 1, file)) {
        printf("Data (mode code) couldn't be loaded\n");
        return 0;
    }
    if (x == 686) {
        cipher = EVP_aes_256_cbc();
    } else if (x == 679) {
        cipher = EVP_aes_256_ctr();
    } else {
        printf("Sorry, the mode isn't supported\n");
        return 0;
    }

    int encrypted_key_len;
    if (!fread(&encrypted_key_len, 4, 1, file)) {
        printf("Data (key length) couldn't be loaded\n");
        return 0;
    }
    if (encrypted_key_len > EVP_PKEY_size(priv_key)) {
        printf("The key is invalid\n");
        return 0;
    }

    unsigned char * encrypted_key = (unsigned char *) malloc(encrypted_key_len);
    if (!fread(encrypted_key, encrypted_key_len, 1, file)) {
        printf("Data (key) couldn't be loaded\n");
        return 0;
    }

    unsigned char * iv = (unsigned char *) malloc(EVP_CIPHER_iv_length(cipher));
    if (!fread(iv, EVP_CIPHER_iv_length(cipher), 1, file)) {
        printf("Data (iv) couldn't be loaded\n");
        return 0;
    }

    FILE *df;
    df = fopen("decrypted_file", "wb");
    if (!df) {
        printf("Decrypted file couldn't be created\n");
        return 0;
    }

    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        printf("Decryption failed1\n");
        return 0;
    }

    unsigned char * plaintext = (unsigned char *)malloc(EVP_MAX_BLOCK_LENGTH + read_len);
    int len;
    if (1 != EVP_OpenInit(ctx, cipher, encrypted_key, encrypted_key_len, iv, priv_key)) {
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    while (1) {
        x = fread(buffer, 1, read_len, file);
        if (!x) break;
        //printf("x: %d\n", x);
        if (1 != EVP_OpenUpdate(ctx, plaintext, &len, buffer, x)){
            printf("Decryption failed2\n");
            fclose(df);
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
        fwrite(plaintext, 1, len, df);
        if (ferror(df)) {
            printf("Couldn't write to file \"decrypted_file\"\n");
            fclose(df);
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
    }
    //printf("len: %d\n", len);
    if(1 != EVP_OpenFinal(ctx, plaintext, &len)) {
        printf("Decryption failed4\n");
        fclose(df);
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    //printf("len: %d\n", len);
    fwrite(plaintext, 1, len, df);
    if (ferror(df)) {
            printf("Couldn't write to file \"decrypted_file\"\n");
            fclose(df);
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
    fclose(df);
    free(plaintext);
    free(iv);
    free(encrypted_key);
    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Wrong number of arguments.. Example: encrypt file pubkey.pem");
        return 0;
    }
    FILE *text_file = fopen(argv[2], "rb");
    if (!text_file) {
        printf("Text file couldn't be opened\n");
        return 0;
    }
    FILE *key_file = fopen(argv[3], "r");
    if (!key_file) {
        printf("Key file couldn't be opened\n");
        return 0;
    }
    if (!strcmp(argv[1], "encrypt")) {
        encrypt(text_file, key_file);
    } else if (!strcmp(argv[1], "decrypt")) {
        decrypt(text_file, key_file);
    } else {
        printf("Program can only encrypt/decrypt\n");
        return 0;
    }
    fclose(text_file);
    fclose(key_file);
    
    return 0;
}