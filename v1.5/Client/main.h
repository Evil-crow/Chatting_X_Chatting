/* 文件:main.h
 *
 * 作用:mian.c的相关声明
 *
 */


#ifndef _MAIN_H
#define _MAIN_H

int sock_fd_create(void);                       //连接套接字创建函数

void work(int sock_fd);                       //传入连接套接字进行工作

void _recv(void *sosket_fd);                      //一直进行内容获取的线程

void sign_in(int sock_fd);                  //登录操作的函数

void chat_data(int sock_fd);                //登录后进行操作的函数

#endif
