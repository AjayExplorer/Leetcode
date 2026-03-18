#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd, port;
    struct sockaddr_in server;
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

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        return 0;
    }

    printf("Connected to server\n");

    // Input file name
    printf("Enter file name: ");
    scanf("%s", filename);

    // Send file name
    send(sockfd, filename, strlen(filename), 0);

    // Create new file
    fp = fopen("received.txt", "w");

    // Receive file data
    while (recv(sockfd, buffer, sizeof(buffer), 0) > 0) {

        if (strcmp(buffer, "ERROR") == 0) {
            printf("File not found on server\n");
            break;
        }

        if (strcmp(buffer, "END") == 0) {
            printf("File received successfully\n");
            break;
        }

        fputs(buffer, fp);
    }

    fclose(fp);
    close(sockfd);

    return 0;
}