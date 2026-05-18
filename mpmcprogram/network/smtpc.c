#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sock_desc;

    struct sockaddr_in server;

    char buffer[1000];

    // Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_desc == -1) {
        printf("Socket creation failed\n");
        return 0;
    }

    // Server details
    server.sin_family = AF_INET;
    server.sin_port = htons(2525);

    // Localhost
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if(connect(sock_desc,
              (struct sockaddr*)&server,
              sizeof(server)) < 0) {

        printf("Connection failed\n");
        return 0;
    }

    printf("Connected to SMTP Server\n");

    // Receive welcome message
    recv(sock_desc, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // HELO
    strcpy(buffer, "HELO\n");
    send(sock_desc, buffer, strlen(buffer), 0);

    recv(sock_desc, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // MAIL FROM
    strcpy(buffer, "MAIL FROM: ajay@gmail.com\n");
    send(sock_desc, buffer, strlen(buffer), 0);

    recv(sock_desc, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // RCPT TO
    strcpy(buffer, "RCPT TO: abc@gmail.com\n");
    send(sock_desc, buffer, strlen(buffer), 0);

    recv(sock_desc, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // DATA
    strcpy(buffer, "DATA\n");
    send(sock_desc, buffer, strlen(buffer), 0);

    recv(sock_desc, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // Message
    strcpy(buffer, "Hello this is SMTP mail\n");
    send(sock_desc, buffer, strlen(buffer), 0);

    recv(sock_desc, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // QUIT
    strcpy(buffer, "QUIT\n");
    send(sock_desc, buffer, strlen(buffer), 0);

    recv(sock_desc, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // Close socket
    close(sock_desc);

    return 0;
}