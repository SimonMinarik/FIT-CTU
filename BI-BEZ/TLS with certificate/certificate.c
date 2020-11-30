#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>

#define BUFFER_SIZE 1024
#define ADDR_SIZE 100
//#define HOST "fit.cvut.cz"

int get_host_name(char * domain, char ** addrstr) {
    struct addrinfo *res;
    void *ptr;
    if (getaddrinfo(domain, NULL, NULL, &res)) {
        printf("me1\n");
        return 0;
    }
    while (res)
    {
      inet_ntop (res->ai_family, res->ai_addr->sa_data, *addrstr, 100);
      if (addrstr == NULL) {
          printf("me2\n");
          return 0;
      }
      switch (res->ai_family)
        {
        case AF_INET:
          ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
          break;
        case AF_INET6:
          ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
          break;
        }
      inet_ntop (res->ai_family, ptr, *addrstr, 100);
      if (addrstr == NULL) {
          printf("meme\n");
          return 0;
      }
      res = res->ai_next;
    }
    return 1;
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    int x;
    char * HOST = "fit.cvut.cz";
    if ((sockfd=socket(AF_INET,SOCK_STREAM, IPPROTO_TCP)) == 0) {
        printf("Socket failed\n");
        return 1;
    }
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    char * addrstr = malloc(ADDR_SIZE);
    if (addrstr == NULL) {
        printf("Couldn't allocate memory to variable\n");
        return 1;
    }
    if (!get_host_name(HOST, &addrstr)) {
        printf("Failed getting addr info\n");
        return 1;
    }
    if ((servaddr.sin_addr.s_addr = inet_addr(addrstr)) == -1) {
        printf("Failed converting host address\n");
        return 1;
    }
    servaddr.sin_port = htons(443);
    if (0 != connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        printf("Couldn't connect\n");
        return 1;
    }
    SSL_library_init();
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) {
        printf("Failed creating context\n");
        return 1;
    }

    if (!SSL_CTX_set_default_verify_paths(ctx)) {
        printf("SSL_CTX_set_default_verify_paths failed\n");
        return 1;
    }

    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);
    SSL *ssl = SSL_new(ctx);
    if (ssl == NULL) {
        printf("Failed creating SSL structure\n");
        return 1;
    }

    int i = 0;
    const char * cipher;
    printf("Cipher list:\n");
    while(1) {
        cipher = SSL_get_cipher_list(ssl,i);
        if (cipher == NULL) {
            break;
        }
        printf("%s\n", cipher);
        i++;
    }

    if (!SSL_set_fd(ssl, sockfd)) {
        printf("Failed setting file descriptor\n");
        return 1;
    }
    if (!SSL_set_tlsext_host_name(ssl, HOST)) {
        printf("SNI failed\n");
        return 1;
    }
    
    if (!SSL_set_cipher_list(ssl, "DEAFULT:!ECDHE-ECDSA-AES256-GCM-SHA384")) {
        printf("Couldn't select a cipher for TLS <= 1.2\n");
        return 1;
    }
    if (!SSL_set_ciphersuites(ssl, "TLS_CHACHA20_POLY1305_SHA256:TLS_AES_128_GCM_SHA256")) {
    printf("Couldn't select a cipher for TLS 1.3\n");
        return 1;
    }

    if (SSL_connect(ssl) != 1) {
        printf("TLS/SSL handshake was not successful\n");
        return 1;
    }

    if (SSL_get_verify_result(ssl) != X509_V_OK) {
        printf("SSL_get_verify_result failed\n");
        return 1;
    }

    printf("Current cipher: %s\n",SSL_CIPHER_get_name(SSL_get_current_cipher(ssl)));
    X509 * certificate = SSL_get_peer_certificate(ssl);
    if (certificate == NULL) {
        printf("Failed gettnig a certificate\n");
        return 1;
    }
    FILE * cert_file = fopen("cert.pem", "w");
    if (cert_file == NULL) {
        printf("Failed opening\\creating \"certificate.pem\" file\n");
        return 1;
    }
    if (!PEM_write_X509(cert_file, certificate)) {
        printf("Failed writing the certificate in the file\n");
        return 1;
    }
    if (fclose(cert_file) == EOF) {
        printf("Failed closing the \"certificate.pem\" file\n");
        return 1;
    }

    /**BIO *o = BIO_new_fp(stdout,BIO_NOCLOSE);
    if (o == NULL) {
        printf("BIO_new_fp failed\n");
        return 1;
    }
    if (!X509_print_ex(o, certificate, XN_FLAG_COMPAT, X509_FLAG_COMPAT)) {
        printf("Failed printing the certificate content\n");
        return 1;
    }**/

    const char * request = "GET /student/odkazy HTTP/1.0\r\nHost: fit.cvut.cz\r\n\r\n";
    if (SSL_write(ssl, request, strlen(request)) <= 0) {
        printf("Failed sending SSL request\n");
        return 1;
    }
    FILE *fit_cvut = fopen("fit_cvut", "wb");
    if (fit_cvut == NULL) {
        printf("Failed opening\\creating \"fit_cvut\" file\n");
        return 1;
    }
    char *buffer[BUFFER_SIZE];
    while(1){
        x = SSL_read(ssl, buffer, sizeof(buffer));
        if (!x) break;
        if (x < 0) {
            printf("Error occured while reading while SSL_read\n");
            return 1;
        }
        fwrite(buffer, sizeof(char), x, fit_cvut);
        if (ferror(fit_cvut)) {
            printf("Failed writing in the \"fit_cvut\" file\n");
            return 1;
        }
    }

    if (fclose(fit_cvut) == EOF) {
        printf("Failed closing the \"certificate.pem\" file\n");
        return 1;
    }
    while (1) {
        x = SSL_shutdown(ssl);
        if (x < 0) {
            printf("A fatal error occurred trying to shutdown TLS/SSL connection\n");
            return 1;
        } else if (x == 1) break;
    }
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}