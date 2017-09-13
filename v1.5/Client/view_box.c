/* 文件:view_box.c
 *
 * 作用:消息盒子功能的实现
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include"chat_data.h"
#include "struct_node_client.h"

extern struct node_client recv_user;                    //_recv线程所收到的结构体

extern int chat_status;

void view_box(int sock_fd)
{
    chat_status = 4;
    char ch;
    system("clear");
    printf("\t\t\t\t=====================================================================\n");
    printf("\t\t\t\t                              消息盒子\n");
    printf("\t\t\t\t=====================================================================\n");
    if(recv_user.my_firend.choice_friend == 2)                //表明为添加好友请求
    {
        printf("\t\t\t\t收到好友请求!\n\n");
        recv_user.decision = 1;
        recv_user.my_firend.choice_friend = 3;
        printf("\t\t\t\t%s 向您发送添加好友的请求,是否同意(0/1)?  ",recv_user.consumer.username);
        scanf("%d",&recv_user.decision);
        send(sock_fd,&recv_user,sizeof(struct node_client),0);     //反馈包发送
        printf("\t\t\t\t已经发送!\n");
        chat_status = 0;
        memset(&recv_user,0,sizeof(struct node_client));
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }
    if(recv_user.flag == 4)                                   //表明为发送文件的请求
    {
        char path[100] = "/home/Crow/Public/File/";
        printf("\t\t\t\t收到来自%s发送文件的请求\n",recv_user.my_firend.friend_message);
        int choice; 
        printf("\t\t\t\t是否接受?(0/1)");
        scanf("%d",&choice);
        if(choice == 0)
        {
            strcat(path,recv_user.my_file.file_name);
            remove(path);
            printf("\t\t\t\t按[Enter]返回");
            chat_status = 0;
            getchar( );
            if((ch = getchar( )) == '\n')
            return ;
        }
        printf("\t\t\t\t文件接受完成!\n");
        printf("\t\t\t\t按[Enter]返回");
        recv_user.flag = 9;
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }
    else
    {
        memset(&recv_user,0,sizeof(struct node_client));
        printf("\t\t\t\t暂无消息.请稍候再试\n");
        chat_status = 0;
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }
}
