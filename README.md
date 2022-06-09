<!--
 * @Description: 
 * @Version: 1.0
 * @Autor: Yzc258
 * @Date: 2022-06-09 12:28:35
-->
# node_socket

参考[(20条消息) Linux十三（TCP通信流程详解（搭配代码，案例））_幽萌之雨的博客-CSDN博客_linux tcp通信](https://blog.csdn.net/qq_54669536/article/details/120315749)

### 文件读写

```c
#include<stdio.h>
int a;
char b,c[100];
int main(){
    FILE * fp1 = fopen("input.txt", "r");//打开输入文件
    FILE * fp2 = fopen("output.txt", "w");//打开输出文件
    if (fp1==NULL || fp2==NULL) {//若打开文件失败则退出
        puts("不能打开文件！");
        return 0;
    }
    fscanf(fp1,"%d",&a);//从输入文件读取一个整数
    b=fgetc(fp1);//从输入文件读取一个字符
    fgets(c,100,fp1);//从输入文件读取一行字符串
     
    printf("%ld",ftell(fp1));//输出fp1指针当前位置相对于文件首的偏移字节数
     
    fputs(c,fp2);//向输出文件写入一行字符串
    fputc(b,fp2);//向输出文件写入一个字符
    fprintf(fp2,"%d",a);//向输出文件写入一个整数
     
    fclose(fp1);//关闭输入文件
    fclose(fp2);//关闭输出文件，相当于保存
    return 0;
}
```

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
//server
$ ./server或者$ nohup ./server &
使用$ ps aux|grep ./server  $ kill -9 $(pidof ./server)管理进程
//client
$ ./client 192.168.88.131  status
```

