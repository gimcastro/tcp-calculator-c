/*
Giovana Medeiros Castro
To compile: gcc -o server server.c
*/

#include <stdio.h>             
#include <string.h>             
#include <stdlib.h>             
#include <unistd.h>            
#include <arpa/inet.h> 

#define PORT 5001

double math(const char *expr)
{
    double x ,y;
    char operation;

    sscanf(expr, "%lf%c%lf=", &x, &operation, &y);

    switch(operation)
    {
        case '+':
        return x + y;
        case '-':
        return x - y;
        case '/': 
        if(y == 0) return 0;
        return x / y;
        case '*': 
        return x * y;
        default:
        return 0; 
    }
}

int main ()
{
    int server, client;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char buff[64];

    server = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(server, (struct sockaddr *)&addr, sizeof(addr));

    listen(server, 1);

    client = accept(server, (struct sockaddr *)&addr, &addrlen);

    while (1) 
    {
        memset(buff, 0, 64);
        recv(client, buff, 64, 0);

        if (strcmp(buff, "0/0=") == 0) 
        {
            printf("Received question \"0/0=\"; end the server program\n");
            break;
        }

        printf("Received question \"%s\"; ", buff);

        double answer = math(buff);
        char reply[64];
        sprintf(reply, "%.2f", answer);

        printf("send back answer %s \n", reply);

        send(client, reply, strlen(reply), 0);
    }


    close(client);
    close(server);
    return 0;
}