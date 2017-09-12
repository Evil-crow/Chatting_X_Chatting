/* 文件:main.h
 *
 * 作用:提供main.c的声明
 *
 */


#ifndef _MAIN_H
#define _MAIN_H
      
int listen_fd_create(void);                                     //监听套接字的创建

void epoll_server(int listen_fd);                           //epoll+多线程函数

#endif