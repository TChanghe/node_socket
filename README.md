<!--
 * @Description: 
 * @Version: 1.0
 * @Autor: Yzc258
 * @Date: 2022-06-09 12:28:35
-->
# node_socket


### 添加server端收到消息检测是否为"status"，client端参数增加STATUS

```c
//server
if (*buf == *req)
{
    // printf("rece status\n");
    for (i = 0; i < strlen(tmp); i++)
    {
        sendbuf1[i] = tmp[i];
    }
    send(client_fd, sendbuf1, strlen(sendbuf1), 0);
    close(sockfd);
    printf("reatart socket\n");
}
//client
if (0 == strcmp(argv[2], STATUS))
{
    strcpy(buf, argv[2]);
}
```

### 取消client端循环，增加server自启socket，clien端自动切换PORT

```
char *cmd = "bash restart.sh";
int ret = system(cmd);
close(sockfd);

```

### 运行

```
//server端
$ ./server或者$ nohup ./server &
使用$ ps aux|grep ./server  $ kill -9 $(pidof ./server)管理进程

//client端
$ ./client 192.168.88.131  status
```

