#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {

    char buf[3][100];
    char ack[2];

    int i = 1, k;

    socklen_t len;

    int sock_desc;

    struct sockaddr_in server, client;
//Socket creation
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_desc < 0)
        printf("Error in socket creation.\n");
// set server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    k = bind(sock_desc,
             (struct sockaddr*)&server,
             sizeof(server));

    if(k < 0)
        printf("Error in binding.\n");

    len = sizeof(client);

    while(i < 4) {

        printf("\nReceiving packet %d\n", i);

        recvfrom(sock_desc,buf[i-1],100,0,(struct sockaddr*)&client,&len);

        printf("Packet received: %s\n", buf[i-1]);

        printf("ACK for packet %d: ", i);

        scanf("%s", ack);

        if(strcmp(ack, "1") == 0)
            i++;

        sendto(sock_desc,ack,strlen(ack)+1, 0,(struct sockaddr*)&client, len);

        printf("Sending ACK...\n");
    }

    printf("\nPackets received:\n");

    for(i = 1; i < 4; i++)
        printf("%s\n", buf[i-1]);

    close(sock_desc);

    return 0;
}