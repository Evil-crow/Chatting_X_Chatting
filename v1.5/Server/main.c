/* 文件:mian.c
 *
 * 作用:服务器的主函数模块
 *
 */


#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>
#include<signal.h>
#include<string.h>
#include"main.h"
#include"Linkedlist.h"

list *pHead;                                //全局链表头节点

void _error(const char *string,int line);

void change(char *str);                     //进行时间日期格式转换的函数

char *get_time(void);                       //获取时间的函数

int main(int argc,char **argv)
{
    int listen_fd;                              //监听套接字
    FILE *fp;
    char str[200];
    strcpy(str,get_time( ));                    //获取当前主机时间
    fp = fopen("/home/Crow/Public/Information/server_log","a+");
    fprintf(fp,"Server_start:%s\n",str);        //将信息写入日志中
    fclose(fp);                                 //关闭文件
    pHead = linkedlist_init(pHead);             //进行链表的初始化
    listen_fd = listen_fd_create( );             //创建监听套接字
    //signal(SIGPIPE,SIG_IGN);                    //使用epoll,不能忽略此信号,忽略客户端断开连接的情况,保证服务器的稳定性
    epoll_server(listen_fd);                    //epoll+多线程

    return 0;
}

void _error(const char *string,int line)
{
    printf("Error line:%d",line);
    perror(string);
    printf("\n");
}

char *get_time(void)
{
    time_t timenow;
    time(&timenow);
    return ctime(&timenow);
}

