/* 文件:chat_data.h
 *
 * 作用:chat_data.c的声明之类
 *
 */


#ifndef _CHAT_DATA_H
#define _CHAT_DATA_H

/***********************4个子菜单函数*********************/

void friends_managment(int sock_fd);

void groups_managment(int scoka_fd);

void file_managment(int sock_fd);

void view_box(int sock_fd);

#endif
