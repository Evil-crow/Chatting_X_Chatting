/* 文件:chat_data.c
 *
 * 作用:客户端中的功能选项模块
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termio.h>
#include"chat_data.h"
#include"friends_managment.h"
#include"groups_managment.h"

int getch(void);

void chat_data(int sock_fd)
{
    int ret;                                                //用于处理返回值                                         //设置为信息处理结构体
    int choice;
    char ch;
    system("clear");                                        //进行清屏操作
    while(1)
    {
        system("clear");                                    //清理无用信息
        printf("\t\t\t\t==================================================================\n");
        printf("\t\t\t\t                            主菜单                                 \n");
        printf("\t\t\t\t==================================================================\n\n");
        printf("\t\t\t\t                          1.好友管理                               \n\n");
        printf("\t\t\t\t                          2.群聊管理                               \n\n");
        printf("\t\t\t\t                          3.文件管理                               \n\n");
        printf("\t\t\t\t                          4.消息盒子                               \n\n");
        printf("\t\t\t\t                          0.退出                                  \n\n");
        printf("\t\t\t\t==================================================================\n\n");
        printf("\t\t\t\t请输入你的选项:");
        ch = getch( );
        choice = ch - '0';
        printf("\n");
        switch(choice)
        {
            case 1:
                system("clear");
                friends_managment(sock_fd);
                break;
            case 2:
                system("clear");
                groups_managment(sock_fd);
                break;
            case 3:
                system("clear");
                file_managment(sock_fd);
                break;
            case 4:
                system("clear");
                view_box(sock_fd);
                break;
            case 0:
                close(sock_fd);
                system("clear");
                exit(0);
        }
    }
}

void friends_managment(int sock_fd)
{
    int choice ;
    char ch;
    while(1)
    {
        system("clear");
        printf("\t\t\t\t===================================================================\n");
        printf("\t\t\t\t                          好友管理菜单                               \n");
        printf("\t\t\t\t===================================================================\n\n");
        printf("\t\t\t\t                          1.发起聊天                                \n\n");
        printf("\t\t\t\t                          2.添加好友                                \n\n");
        printf("\t\t\t\t                          3.好友列表                                \n\n");
        printf("\t\t\t\t                          4.删除好友                                \n\n");
        printf("\t\t\t\t                          5.好友状态                                \n\n");
        printf("\t\t\t\t                          6.查看聊天记录                             \n\n");
        printf("\t\t\t\t                          0.返回主菜单                               \n\n");
        printf("\t\t\t\t===================================================================\n\n");
        printf("\t\t\t\t请输入选项:");
        ch = getch( );
        choice = ch - '0';
        printf("\n");
        switch(choice)
        {
            case 1:
                system("clear");
                chatting_with_friend(sock_fd);
                break;
            case 3:
                system("clear");
                print_friend_list(sock_fd);
                break;
            case 2:
                system("clear");
                add_new_friend(sock_fd);
                break;
            case 4:
                system("clear");
                del_friend(sock_fd);
                break;
            case 5:
                system("clear");
                display_friend_status(sock_fd);
                break;
            case 6:
                system("clear");
                view_chat_log(sock_fd);
            case 0:                                                       //返回主菜单
                return ;
        }
    }
}

void groups_managment(int sock_fd)
{
    int choice;
    char ch;
    while(1)
    {
        system("clear");
        printf("\t\t\t\t=====================================================================\n");
        printf("\t\t\t\t                          群组管理菜单                                 \n");
        printf("\t\t\t\t=====================================================================\n\n");
        printf("\t\t\t\t                          1.发起群聊                                   \n\n");
        printf("\t\t\t\t                          2.创建群组                                   \n\n");
        printf("\t\t\t\t                          3.加入群组                                   \n\n");
        printf("\t\t\t\t                          4.群成员列表                                  \n\n");
        printf("\t\t\t\t                          5.群成员状态                                  \n\n");
        printf("\t\t\t\t                          6.查看聊天记录                                \n\n");
        printf("\t\t\t\t                          7.加入的群组列表                               \n\n");
        printf("\t\t\t\t                          8.退出群组                                    \n\n");
        printf("\t\t\t\t                          0.返回主菜单                                  \n\n");
        printf("\t\t\t\t=======================================================================\n\n");
        printf("\t\t\t\t请输入选项:");
        ch = getch( );
        choice = ch - '0';
        printf("\n");
        switch(choice)
        {
            case 1:                                                         //发起群聊函数
                system("clear");
                chatting_with_group(sock_fd);
                break;
            case 2:                                                         //创建群组
                system("clear");    
                create_new_group(sock_fd);
                break;
            case 3:                                                         //加入群组
                system("clear");
                join_group(sock_fd);
                break;
            case 4:                                                         //显示群成员列表
                system("clear");    
                display_group_member(sock_fd);
                break;
            case 5:                                                         //群成员状态
                system("clear");
                display_member_status(sock_fd);
                break;
            case 6:                                                         //聊天记录
                system("clear");
                view_group_chat_log(sock_fd); 
                break;
            case 7:                                                         //加入的群组
                system("clear");
                display_joined_group(sock_fd);                             
                break;
            case 8:                                                         //退出群组
                system("clear");
                del_group(sock_fd);
                break;
            case 0:                                                         //返回上一级菜单
                return;
        }
    }
}

int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;
  
     if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
          return -1;
     }
  
     tm_old = tm;
     cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
          return -1;
     }
  
     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
          return -1;
     }
     
     return ch;
}
