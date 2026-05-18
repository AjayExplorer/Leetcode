#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    char buf[3][100] = {
        "I am Batman.",
        "I am the protector of Gotham.",
        "I am Walter White."
    };

    char ack[2];

    int i = 1, k;
    socklen_t len;

    int sock_desc;

    struct sockaddr_in client;
//Socket creation
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_desc < 0)
        printf("Error in socket.\n");
// set server address
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(3003);

    len = sizeof(client);

    while(i < 4) {

        printf("\nSending packet %d\n", i);

        sendto(sock_desc,buf[i-1],100,0,(struct sockaddr*)&client,len);

        printf("Waiting for ACK...\n");

        recvfrom(sock_desc, ack, sizeof(ack),0,(struct sockaddr*)&client,&len);

        printf("ACK received: %s\n", ack);

        if(strcmp(ack, "1") == 0)
            i++;

        else
            printf("Resend needed for packet %d\n", i);
    }

    close(sock_desc);

    return 0;
}