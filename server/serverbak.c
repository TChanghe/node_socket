/*
 * @Description:
 * @Version: 1.0
 * @Autor: Yzc258
 * @Date: 2022-06-08 19:34:07
 */
/// server.c
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 4322
#define BUFFER_SIZE 1024
#define MAX 5
#include <pthread.h>
int main()
{
	FILE *fp;
	if ((fp = fopen("msg.txt", "rb")) == NULL)
	{
		exit(0);
	}
	fseek(fp, 0, SEEK_END);
	int fileLen = ftell(fp);
	char *tmp = (char *)malloc(sizeof(char) * fileLen);
	fseek(fp, 0, SEEK_SET);
	fread(tmp, fileLen, sizeof(char), fp);
	fclose(fp);
	// for (int i = 0; i < fileLen; ++i)
	// {
	// 	printf("%c", tmp[i]);
	// }
	printf("\n");

	if ((fp = fopen("example.txt", "wb")) == NULL)
	{
		printf("error");
		exit(0);
	}
	rewind(fp);
	fwrite(tmp, fileLen, sizeof(char), fp);
	fclose(fp);
	//	free(tmp);

	struct sockaddr_in servaddr;
	int sockfd, client_fd;
	char buf[BUFFER_SIZE];
	char req[] = "status";
	char sendbuf[] = "received data";
	char sendbuf1[100] = "";
	/*建立socket连接*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	printf("socket id=%d\n", sockfd);
	/*设置sockaddr_in结构体中相关参数*/
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	int i = 1; /*允许重复使用本地址与套接字进行绑定*/
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

	/*绑定函数bind()*/
	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	printf("Bind success!\n");
	/*调用listen函数，创建未处理请求的队列*/
	if (listen(sockfd, MAX) == -1)
	{
		perror("listen");
		exit(1);
	}

	printf("Listen...\n");

	/*调用accept函数，等待客户端连接*/
	if ((client_fd = accept(sockfd, NULL, NULL)) == -1)
	{
		perror("accept");
		exit(0);
	}

	while (1)
	{
		if (recv(client_fd, buf, BUFFER_SIZE, 0) == -1)
		{
			perror("recv");
			exit(0);
		}
		else
		{
			printf("Received a message:%s\n", buf);
			if (*buf == *req)
			{
				//printf("111\n");
				for (i = 0; i < strlen(tmp); i++)
				{
					sendbuf1[i] = tmp[i];
					//	printf("%c+%c", sendbuf1[i], tmp[i]);
				}
				send(client_fd, sendbuf1, strlen(sendbuf1), 0);
				close(sockfd);
				printf("reatart socket\n");
			}
			memset(buf, 0, sizeof(buf));
			if (send(client_fd, sendbuf, strlen(sendbuf), 0) == -1)
			{
				perror("send");
				exit(-1);
			}
			memset(buf, 0, sizeof(buf));
			//printf("aaa");
		}
		//printf("bbb");
		char *cmd = "bash restartbak.sh";
		int ret = system(cmd);
		if (ret != 0)
		{
			printf("execute result is %d\n", ret);
		}
		close(sockfd);
		exit(0);
		return 0;
	}
}