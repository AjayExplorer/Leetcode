#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock_desc;
    struct sockaddr_in server;
    char buff[100];
    socklen_t len;

    // 1. Create socket
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1) {
        printf("Error in socket creation\n");
        return 0;
    }

    // 2. Set server details
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3008);

    // 3. Get input
    printf("Enter the number: ");
    fgets(buff, 100, stdin);

    // 4. Send data
    sendto(sock_desc, buff, strlen(buff), 0,
           (struct sockaddr*)&server, sizeof(server));

    printf("Sending...\n");

    // 5. Receive result
    len = sizeof(server);
    recvfrom(sock_desc, buff, 100, 0,
             (struct sockaddr*)&server, &len);

    printf("Message from server: %s\n", buff);

    // 6. Close socket
    close(sock_desc);

    return 0;
}