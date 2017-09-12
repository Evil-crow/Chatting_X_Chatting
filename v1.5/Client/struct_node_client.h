/* 文件:struct_node_client.h
 *
 * 作用:客户端所使用的结构体struct_node_client的声明
 *
 */


#ifndef _STRUCT_CLIENT_H
#define _STRUCT_CLIENT_H

#define MAX_STR           30
#define MAX_MESSAGE       45

struct sign
{
    int choice_sign;                        //进行登录选择
    char username[MAX_STR];
    char passwd1[MAX_STR];                  //登录密码
    char passwd2[MAX_STR];                  //注册密码
    int  result;                            //登录注册包回馈的结果
};
struct friend_
{
    int                         choice_friend;                      //进行好友操作选择
    int                         friends_status;                     //表示好友状态,0/离线,1/在线
    char                        friends_name[MAX_STR];              //想要进行处理的好友姓名
    char                        friend_message[MAX_MESSAGE];        //要发送的消息
    char                        date_time[80];                       //发送消息的日期时间
    char                        log_in_out_message[20];              //上下线提醒
};
struct group
{
    int                         choice_group;                       //进行群聊操作选择
    char                        group_message[MAX_MESSAGE];         //发送群聊消息
    char                        group_name[MAX_STR];                //群组名
    char                        member_name[MAX_STR];               //群成员
    int                         group_result;                       //进行操作的结果,也可以表示状态
    char                        date_time[80];                      //发送消息的时间日期
};
struct file
{
    int                         file_flag;
    char                        file_name[MAX_STR];                 //传输的文件名
    char                        file_data[50];                     //一次读取200字节的内容
};
struct node_client
{
    int                         flag;                               //用于标记是用来进行登录注册还是进行其他操作 1为登录,2为friend,3为group
    int                         decision;                           //表示是否同意请求 1/同意,是,0/不同意,否
    struct sign                 consumer;                           //进行登录的结构体
    struct friend_              my_firend;                          //进行私聊的结构体
    struct group                my_group;                           //进行群聊的结构体
    struct file                 my_file;                            //进行文件传输的结构体
};
#endif
