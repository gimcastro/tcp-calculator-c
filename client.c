/*
Giovana Medeiros Castro
To compile: gcc -o client client.c 
*/

#include <stdio.h>             
#include <string.h>             
#include <stdlib.h>             
#include <unistd.h>            
#include <arpa/inet.h> 

#define PORT 5001

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char buff[64], reply[64];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Connected with server on %s\n", inet_ntoa(server_addr.sin_addr));

    while (1)
    {
        memset(buff, 0, 64);
        printf("Enter: ");
        fflush(stdout);

        fgets(buff, 64, stdin);
        buff[strcspn(buff, "\n")] = '\0'; 

        send(sock, buff, strlen(buff), 0);

        if (strcmp(buff, "0/0=") == 0)
        {
            printf("User input ends; end the client program\n");
            break;
        }

        memset(reply, 0, 64);
        recv(sock, reply, 64, 0);

        printf("Answer from server: %s\n", reply);
    }

    close(sock);
    return 0;
}
