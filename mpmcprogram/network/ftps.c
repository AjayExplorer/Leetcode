#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd, newsockfd, port;
    struct sockaddr_in server, client;
    socklen_t len;
    char filename[100], buffer[1000];
    FILE *fp;

    printf("Enter Port Number: ");
    scanf("%d", &port);

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error creating socket\n");
        return 0;
    }

    // Setup server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind
    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Binding failed\n");
        return 0;
    }

    // Listen
    listen(sockfd, 5);
    printf("Server waiting...\n");

    // Accept connection
    len = sizeof(client);
    newsockfd = accept(sockfd, (struct sockaddr*)&client, &len);

    // Receive file name
    recv(newsockfd, filename, sizeof(filename), 0);

    // Open file
    fp = fopen(filename, "r");

    if (fp == NULL) {
        send(newsockfd, "ERROR", 5, 0);
        printf("File not found\n");
    } else {
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            send(newsockfd, buffer, strlen(buffer), 0);
        }
        send(newsockfd, "END", 3, 0);
        printf("File sent successfully\n");
        fclose(fp);
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}