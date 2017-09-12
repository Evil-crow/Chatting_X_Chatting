/* 文件:menu.h
 *
 * 作用:提供menu.c的声明
 *
 */


#ifndef _MENU_H
#define _MENU_H

#define  MAX_STR            30              //宏定义最长的字符串
#define MAX_MESSAGE         45              //宏定义最长的信息长度

void menu(void *sock_fd);

#endif