/* 文件:sign_register.c
 *
 * 作用:登录注册功能的实现
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<termio.h>
#include"struct_node_client.h"

extern void _error(const char *string,int line);

extern int getch(void);                                          //无缓冲的获取输入的字符

void sign_in(int sock_fd)
{
    struct node_client user;
    int ret;                                              //处理返回值
    char ch;
    user.flag = 1;                                        // 大结构体 中选择标记1 表示为 登录注册操作
    /*打印登录界面的菜单*/
    while(1)
    {
        system("clear");                                      //清屏操作
        printf("\t\t\t\t===================================================================\n");
        printf("\t\t\t\t                     Welcome to Chatting_X_Chatting                \n");
        printf("\t\t\t\t===================================================================\n\n");
        printf("\t\t\t\t                             1.登录账号                             \n\n");
        printf("\t\t\t\t                             2.注册账号                             \n\n");
        printf("\t\t\t\t                             0.退出                                \n\n");
        printf("\t\t\t\t===================================================================\n\n");
        printf("\t\t\t\t请输入你的选择:");
        ch = getch( );
        printf("\n");
        user.consumer.choice_sign = ch - '0';
        switch(user.consumer.choice_sign)
        {
            case 1:                                                         //表示为登录操作
                printf("\t\t\t\t账号:");
                scanf("%s",user.consumer.username);                         //录入用户名
                printf("\t\t\t\t密码:");
                system("stty -echo");                                       //设置不回显
                scanf("%s",user.consumer.passwd1);                          //录入登录密码
                printf("\n");
                system("stty echo");                                        //恢复回显
                ret = send(sock_fd,&user,sizeof(struct node_client),0);
                if(ret < 0)
                {
                    _error("send",__LINE__);
                    exit(0);
                }   
                printf("\t\t\t\t登录中...\n");
                sleep(1);
                return ;
            case 2:                                                         //表示为注册操作
                printf("\t\t\t\t注册账号:");                               
                scanf("%s",user.consumer.username);                        //录入注册用户名
                system("stty -echo");                                      //设置不回显
                printf("\t\t\t\t登录密码:");
                scanf("%s",user.consumer.passwd1);                         //第一次输入密码
                printf("\n");
                printf("\t\t\t\t确认登录密码:");
                scanf("%s",user.consumer.passwd2);                         //第二次确认输入密码
                printf("\n");
                system("stty echo");                                       //恢复回显
                if(strcmp(user.consumer.passwd1,user.consumer.passwd2) == 0)
                {
                    ret = send(sock_fd,&user,sizeof(struct node_client),0);          //发送注册信息包
                    if(ret < 0)
                    {
                        _error("send",__LINE__);
                        exit(0);
                    }
                }
                if(strcmp(user.consumer.passwd1,user.consumer.passwd2) != 0)
                {   
                    printf("\t\t\t\t请保证两次输入的密码一致\n");
                    break;
                }            
                printf("\t\t\t\t注册中...\n");
                sleep(1);
                return ;
            case 0:                                                         //表示为退出,不登入聊天室,与聊天室中的退出不同
                printf("\n\t\t\t\t打开了又不用人家,好桑心啊 ~~ T^T\n");
                getchar( );
                exit(EXIT_SUCCESS);
                break;
        }                                                     //完成客户端登录界面的退出,不需要与服务器发生交互.
    } 
}
