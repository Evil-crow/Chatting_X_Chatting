/* 文件:listen_fd_creat.c
 *
 * 作用:监听套接字的创建
 *
 */


#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include"main.h"

#define    PORT         12121
#define    LISTENLINE   30

extern void _error(const char *string,int line);

int listen_fd_create(void)
{
    int                     listen_fd;
    int                     optval;                       //setsockopt使用
    int                     ret;                          //作返回值,进行错误判断
    struct sockaddr_in      sock_addr;

    /*创建套接字*/
    listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if(listen_fd < 0)
        _error("socket",__LINE__);

    /*对套接字进行设置*/         
    optval = 1;
    ret = setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int));
    if(ret < 0)
        _error("setsockopt",__LINE__);

    /*对socket地址进行设置*/
    bzero(&sock_addr,sizeof(struct sockaddr_in));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*对套接字进行命名*/
    ret = bind(listen_fd,(struct sockaddr *)&sock_addr,sizeof(struct sockaddr_in));
    if(ret < 0)
        _error("bind",__LINE__);

    /*对套接字进行监听设定*/
    ret = listen(listen_fd,LISTENLINE);
    if(ret < 0)
        _error("listen",__LINE__);

    return listen_fd;                                     //创建监听套接完成
}

