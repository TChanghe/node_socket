/// client.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 512
#define STATUS "status"
#define PORT 4322

int main(int argc, char *argv[])
{

    int sockfd, client_fd;
    int len;
    char buf[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    if (argc < 3)
    {
        printf("USAGE=%s <serv_in> <serv_port>\n", argv[0]);
        exit(-1);
    }

    /*creat socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(-1);
    }
    else
    {
        // printf("socket build success\r\n");
    }

    /*creat sockaddr_in struct data*/
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    /*start connect*/
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (0 == strcmp(argv[2], STATUS))
    {
        strcpy(buf, argv[2]);
    }
    if (send(sockfd, buf, strlen(buf), 0) == -1)
    {
        perror("send");
        exit(-1);
    }
    
    memset(buf, 0, sizeof(buf));
    if (recv(sockfd, buf, BUFFER_SIZE, 0) == -1)
    {
        perror("recv");
        exit(0);
    }
    printf("Received a message:%s\n", buf);
    memset(buf, 0, sizeof(buf));
    close(sockfd);
    exit(0);
}
