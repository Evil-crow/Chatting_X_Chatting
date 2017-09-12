/* 文件:friend_managemnt.h
 *
 * 作用:friend_managment.c得相关声明
 *
 */


#ifndef _FRIENDS_MANAGMENT_
#define _FRIENDS_MANAGMENT_

/***************************好友管理的函数***********************************/

void chatting_with_friend(int sock_fd);                         //私聊函数

void print_friend_list(int sock_fd);                            //打印好友列表

void add_new_friend(int sock_fd);                               //添加好友

void del_friend(int sock_fd);                                   //删除好友

void display_friend_status(int sock_fd);                        //显示好友状态

void view_chat_log(int scok_fd);                                //查看聊天记录

#endif
