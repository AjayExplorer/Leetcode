#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock_desc;
    struct sockaddr_in server, client;
    char buff[100], result[100];
    socklen_t len;
    int num, square;

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

    // 3. Bind
    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Error in binding\n");
        return 0;
    }

    // 4. Receive data
    len = sizeof(client);
    recvfrom(sock_desc, buff, 100, 0,
             (struct sockaddr*)&client, &len);

    printf("Message from client: %s\n", buff);

    // 5. Process (square calculation)
    num = atoi(buff);
    square = num * num;

    printf("Square is: %d\n", square);

    // 6. Convert to string
    sprintf(result, "%d", square);

    // 7. Send result back
    sendto(sock_desc, result, strlen(result), 0,
           (struct sockaddr*)&client, len);

    printf("Sending...\n");

    // 8. Close socket
    close(sock_desc);

    return 0;
}