#include <openssl/evp.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("decrypt\n");
    unsigned char buffer[16];
    FILE *fp;
    fp = fopen("encrypted_file", "rb");
    fread(buffer, 4, 1, fp);
    printf("%s\n", buffer);
    if (strcmp("AES", (const char *)buffer)) {
        printf("Sorry, the cipher isn't supported\n");
    }
    fread(buffer, 4, 1, fp);
    if (strcmp("CBC", (const char *)buffer)) {
        printf("Sorry, the mode isn't supported\n");
    }
    memset(buffer,0,16);
    int encrypted_key_len;
    fread(&encrypted_key_len, 4, 1, fp);
    printf("len: %d\n", encrypted_key_len);
    unsigned char * encrypted_key = (unsigned char *) malloc(encrypted_key_len);
    fread(encrypted_key, encrypted_key_len, 1, fp);
    printf("key: %s\n", encrypted_key);
    unsigned char iv[EVP_MAX_IV_LENGTH];
    fread(iv, EVP_MAX_IV_LENGTH, 1, fp);
    printf("iv: %s\n",iv);
    FILE *df;
    df = fopen("decrypted_file", "wb");

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    FILE *pem;
    pem = fopen("privkey.pem", "r");
    EVP_PKEY * priv_key;
    priv_key = PEM_read_PrivateKey(pem, NULL, NULL, NULL);
    fclose(pem);

    unsigned char *plaintext;
    int len;
    memset(buffer, 0, 16);
    EVP_OpenInit(ctx, EVP_aes_256_cbc(), encrypted_key, encrypted_key_len, iv, priv_key);
    while (!feof(fp)) {
        fread(buffer,sizeof(buffer),1,fp);
        printf("funguje\n");
        printf("%s\n", buffer);
        EVP_OpenUpdate(ctx, plaintext, &len, buffer, sizeof(buffer));
        printf("plaintext: %s\n", plaintext);
        fwrite(plaintext, sizeof(plaintext), 1, df);
        memset(buffer, 0, 16);
    }
    fclose(df);
    fclose(fp);
    EVP_CIPHER_CTX_free(ctx);

}