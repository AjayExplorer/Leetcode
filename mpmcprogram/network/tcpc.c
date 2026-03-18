#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock_desc;
    struct sockaddr_in client;
    char buff[100];

    // 1. Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        printf("Error in socket creation\n");
        return 0;
    }

    // 2. Set server details
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(3003);

    // 3. Connect to server
    if (connect(sock_desc, (struct sockaddr*)&client, sizeof(client)) == -1) {
        printf("Error in connection\n");
        return 0;
    }

    // 4. Send data
    printf("Enter the data: ");
    fgets(buff, 100, stdin);

    send(sock_desc, buff, strlen(buff), 0);

    printf("Sending...\n");

    // 5. Close socket
    close(sock_desc);

    return 0;
}