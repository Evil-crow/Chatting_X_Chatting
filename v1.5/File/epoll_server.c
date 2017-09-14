/* 文件:epoll_server.c
 *
 * 作用:使用epoll对多个套接字进行管理
 *
 */


#include<stdio.h>
#include<sys/epoll.h>
#include<sys/socket.h>
#include<unistd.h>
#include<pthread.h>
#include<netinet/in.h>
#include<stdlib.h>
#include"epoll_server.h"
#include"main.h"

int epoll_fd;                                //定义epoll注册表,在其他文件中使用extern引用

extern void _error(const char *string,int line);

void epoll_server(int listen_fd)
{
    /*创建epoll实例*/
    int ret;                                     //同样用来处理返回值,epoll_fd为全局变量  
    epoll_fd = epoll_create(256);                //进行注册表的创建,size自从内核2.6.x后并没有实际的意义
    if(epoll_fd < 0)
        _error("epoll_create",__LINE__);

    /*将epoll感兴趣的事件添加进去,此处添加监听套接字,设置为读事件*/
    struct epoll_event ep_ev;                     //设置epoll结构体
    ep_ev.events = EPOLLIN;                       //设置为读事件感兴趣
    ep_ev.data.fd = listen_fd;                    //添加数据为共用体中的fd,暂时不需要void*ptr;
    ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&ep_ev);
    /*将监听套接字以读事件注册入epoll的注册表中*/
    if(ret < 0)
        _error("epoll_ctl",__LINE__);

    /*设置空间用来存储epoll管理的队列*/
    struct epoll_event evs[MAX_EVS];              //设置epoll可以监听的描述符个数
    int maxnum = MAX_EVS;                         //任务队列中的最大数量
    int timeout = TIME_OUT;                       //最大的等待时间

    int epoll_ret = 0;                                //epoll专用返回的事件发生数
    while(1)                                      //在永真循环中,一直用epoll管理
    {
        epoll_ret = epoll_wait(epoll_fd,evs,maxnum,-1);   //epoll_wait获取返回值
        printf("epoll_ret = %d\n",epoll_ret);
        if(epoll_ret > 0)

        switch(epoll_ret)
        {
            case -1:
                printf("epoll_error!\n");
                break;
            case 0:
                printf("epoll_timeout!\n");
                break;
            default:
                for(int i = 0 ; i < epoll_ret ; i++)
                {
                    if((evs[i].data.fd == listen_fd) && (evs[i].events & EPOLLIN))   //判断是否为监听套接字且为读事件
                    {
                        struct sockaddr_in cli_addr;
                        socklen_t          cil_len;
                        cil_len = sizeof(struct sockaddr_in); 
                        /*进行套接字的连接*/
                        int conn_fd = accept(listen_fd,(struct sockaddr *)&cli_addr,&cil_len);
                        if(conn_fd < 0)
                            _error("accept",__LINE__);

                        /*进行新的连接套接字获取,并将其添加进入epoll的注册表*/
                        ep_ev.events = EPOLLIN | EPOLLONESHOT; //epoll对连接套接字感兴趣的是读事件
                        ep_ev.data.fd = conn_fd;               //epoll处理的是连接套接字 
                        ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,conn_fd,&ep_ev);
                        if(ret < 0)
                        {
                            _error("epoll_ctl",__LINE__);
                            exit(0);
                        } 
                    }
                    else                      //如果并非是监听套接字,而是其他的连接套接字
                    {
                        if(evs[i].events & EPOLLIN)                // &运算判断其是否为可读事件
                        {
                            pthread_t thid;                        //线程ID

                            /*创建线程,并且传入连接套接字,进行处理*/
                            pthread_create(&thid,NULL,(void *)menu,(void *)&evs[i].data.fd);

                            pthread_detach(thid);                 //在线程外部调用,回收资源
                        }
                    }   
                }
                break;
        }
    }
}   