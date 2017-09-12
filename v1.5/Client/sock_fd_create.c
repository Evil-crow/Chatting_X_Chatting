/* 文件:sock_fd_create.c
 *
 * 作用:进行客户端使用的套接字连接
 *
 */


#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>

extern void _error(const char *string,int line);

#define SOCK_PORT            12121                     //设置绑定的主机端口
int sock_fd_create(void)
{
    int                    sock_fd;                    //创建要使用的套接字
    struct sockaddr_in     sock_addr;                  //创建的用于设置sockaddr地址
    int                    ret;                        //用于处理函数的返回值

    sock_fd = socket(AF_INET,SOCK_STREAM,0);           //创建TCP,IPV4的套接字
    if(sock_fd < 0)
        _error("socket",__LINE__);
    
    /*进行sockaddr地址的设置*/
    sock_addr.sin_family = AF_INET;                    //设置为IPV4协议族
    sock_addr.sin_port = htons(SOCK_PORT);             //设置端口为绑定的端口12121
    inet_aton("127.0.0.1",&sock_addr.sin_addr);            //设置IP地址
    printf("\t\t\t\t正在连接服务器.....\n\n");
    sleep(1);
    ret = connect(sock_fd,(struct sockaddr *)&sock_addr,sizeof(struct sockaddr_in));   //进行连接服务器
    if(ret < 0)
    {
        _error("connect",__LINE__);
        exit(EXIT_SUCCESS);
    }

    printf("\t\t\t\t连接成功!\n");
    return sock_fd;                                    //创建好客户端连接用套接字    
}

