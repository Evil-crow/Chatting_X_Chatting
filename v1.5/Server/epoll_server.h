/* 文件:epoll_server.h
 *
 * 作用:epoll_server.c相关的声明
 *
 */


#ifndef _EPOLL_SERVER_H
#define _EPOLL_SERVER_H

#define MAX_EVS               30                 //最大的消息队列
#define TIME_OUT              100                //最大的等待时间

void menu(void *sock_fd);                          //线程调用的函数

void _error(const char *string,int line);

#endif