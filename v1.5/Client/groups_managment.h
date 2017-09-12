/* 文件:group_managemnt.h
 *
 * 作用:group_managment.c的相关声明
 *
 */


#ifndef _GROUP_MANAGMENT_
#define _GROUP_MANAGMENT_

/******************群聊管理子菜单函数********************/

void chatting_with_group(int sock_fd);

void create_new_group(int sock_fd);

void join_group(int sock_fd);

void display_group_member(int sock_fd);

void display_member_status(int sock_fd);

void view_group_chat_log(int sock_fd);

void display_joined_group(int sock_fd);

void del_group(int sock_fd);

#endif
