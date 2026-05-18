#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int server_sock, client_sock;

    struct sockaddr_in server, client;

    char buffer[1000];

    socklen_t len;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(server_sock == -1) {
        printf("Socket creation failed\n");
        return 0;
    }

    // Server details
    server.sin_family = AF_INET;
    server.sin_port = htons(2525);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(server_sock,
         (struct sockaddr*)&server,
         sizeof(server));

    // Listen
    listen(server_sock, 5);

    printf("SMTP Server Waiting...\n");

    len = sizeof(client);

    // Accept connection
    client_sock = accept(server_sock,
                         (struct sockaddr*)&client,
                         &len);

    printf("Client Connected\n");

    // Welcome message
    strcpy(buffer, "220 SMTP Server Ready\n");
    send(client_sock, buffer, strlen(buffer), 0);

    while(1) {

        recv(client_sock, buffer, sizeof(buffer), 0);

        printf("Client: %s", buffer);

        // HELO
        if(strncmp(buffer, "HELO", 4) == 0) {

            strcpy(buffer, "250 Hello Client\n");
            send(client_sock, buffer, strlen(buffer), 0);
        }

        // MAIL FROM
        else if(strncmp(buffer, "MAIL FROM", 10) == 0) {

            strcpy(buffer, "250 Sender OK\n");
            send(client_sock, buffer, strlen(buffer), 0);
        }

        // RCPT TO
        else if(strncmp(buffer, "RCPT TO", 7) == 0) {

            strcpy(buffer, "250 Receiver OK\n");
            send(client_sock, buffer, strlen(buffer), 0);
        }

        // DATA
        else if(strncmp(buffer, "DATA", 4) == 0) {

            strcpy(buffer, "354 Enter Mail\n");
            send(client_sock, buffer, strlen(buffer), 0);
        }

        // QUIT
        else if(strncmp(buffer, "QUIT", 4) == 0) {

            strcpy(buffer, "221 Connection Closed\n");
            send(client_sock, buffer, strlen(buffer), 0);

            break;
        }

        // Mail content
        else {

            printf("Mail Received: %s\n", buffer);

            strcpy(buffer, "250 Mail Sent Successfully\n");
            send(client_sock, buffer, strlen(buffer), 0);
        }
    }

    // Close sockets
    close(client_sock);
    close(server_sock);

    return 0;
}