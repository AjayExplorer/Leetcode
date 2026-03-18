#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock_desc, temp_sock_desc;
    struct sockaddr_in server, client;
    socklen_t len;
    char buff[100];

    // 1. Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        printf("Error in socket creation\n");
        return 0;
    }

    // 2. Set server details
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    // 3. Bind socket
    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Error in binding\n");
        return 0;
    }

    // 4. Listen
    if (listen(sock_desc, 5) == -1) {
        printf("Error in listening\n");
        return 0;
    }

    // 5. Accept connection
    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr*)&client, &len);
    if (temp_sock_desc == -1) {
        printf("Error in accept\n");
        return 0;
    }

    // 6. Receive data
    if (recv(temp_sock_desc, buff, 100, 0) == -1) {
        printf("Error in receiving\n");
        return 0;
    }

    // 7. Display message
    printf("Message from client: %s\n", buff);

    // 8. Close sockets
    close(temp_sock_desc);
    close(sock_desc);

    return 0;
}