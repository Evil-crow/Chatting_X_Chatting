/* 文件:sign_register.c
 *
 * 作用:服务器对于登录注册事务的处理
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"Linkedlist.h"
#include"struct_node_server.h"

void send_outline_message(char *str,int conn_fd,struct node_server user);        //发送群离线消息

void log_in_message(struct node_server user,char *str,char *ptr);          //上下线提醒

extern list *pHead;                                                 //主函数中的头节点,此处引用

extern void _error(const char *string,int line);

extern char *get_time(void);                                              //主函数中定义的获取时间函数

int judge(FILE*fp);                                                   //判断文件是否为空

void sign_register(int conn_fd,struct node_server user)
{
    FILE *fp;
    FILE *sp;                                                         //文件指针
    int   ret;
    list *temp;
    char ch;
    char username[MAX_STR];
    char password[MAX_STR];
    char pwd[200];
    char str_name[30];
    fp = fopen("/home/Crow/Public/Information/user","a+");              //以a+方式打开文件
    if(fp == NULL)
        _error("fopen",__LINE__);
    switch(user.consumer.choice_sign)
    {
        case 1:                                                   //进行登录选项
            if(judge(fp))
            {
                fseek(fp,0L,0);
                while(!feof(fp))                                  //当没有读到文件末尾时
                {
                    fscanf(fp,"%s %s\n",username,password);       //读出文件中的用户名和密码
                    if(strcmp(username,user.consumer.username) == 0)          //如果用户名存在
                    {
                        printf("开始检查\n");
                        temp = linkedlist_seek_username(pHead,user.consumer.username);
                        if(temp != NULL)
                        {
                            printf("已经登录\n");
                            user.consumer.result = 1;
                            send(conn_fd,&user,sizeof(struct node_server),0);                      //将处理后的信息包发送回去
                            return ;
                        }
                        if(strcmp(password,user.consumer.passwd1) == 0)
                        {
                            
                            user.consumer.result = 0;              //用户名,密码完全匹配.登录成功
                            char str[200];
                            strcpy(str,get_time( ));
                            sp = fopen("/home/Crow/Public/Information/server_log","a+");
                            fprintf(sp,"%s sign_in : %s\n",user.consumer.username,str);
                            fclose(sp);
                            pHead = linkedlist_add(pHead,conn_fd,user.consumer.username);
                            /*将登录成功的用户,添加进入链表中*/
                            while(ret != sizeof(struct node_server))
                                ret = send(conn_fd,&user,sizeof(struct node_server),0);
                            strcpy(str,"/home/Crow/Public/Information/");
                            strcat(str,user.consumer.username);
                            strcat(str,"/friends_list");
                            log_in_message(user,str,user.consumer.username);        //完成上线提醒
                            /*群聊离线消息*/
                            printf("%s\n",user.consumer.username);
                            send_outline_message(user.consumer.username,conn_fd,user);
                            fp = fopen("/home/Crow/Public/buffer2","r+");
                            if(!judge(fp))
                            return ;                                             //若路径文件为空,则直接返回
                            fscanf(fp,"%s\n",pwd);
                            fclose(fp);
                            fp = fopen("/home/Crow/Public/buffer2","w+");
                            fclose(fp);                                           //清空缓冲区
                            fp = fopen(pwd,"r+");
                            while(!feof(fp))
                            {
                                sleep(1);
                                user.flag = 2;
                                user.my_firend.choice_friend = 1;                //离线期间的私聊消息
                                fscanf(fp,"%s\n%s %s %s\n",user.my_firend.date_time,user.consumer.username,user.my_firend.friends_name,user.my_firend.friend_message);
                                /*填好信息,并发送*/
                                send(conn_fd,&user,sizeof(struct node_server),0);
                            }
                            fclose(fp);
                            fp = fopen(pwd,"w+");
                            fclose(fp);                                           //清空缓冲区
                            
                            return ;
                        }
                        user.consumer.result = 3;                  //登录时.密码错误
                        while(ret != sizeof(struct node_server))
                            ret = send(conn_fd,&user,sizeof(struct node_server),0);                      //将处理后的信息包发送回去
                        return ;
                    }
                }
                user.consumer.result = 2;                          //遍历完成,没有该用户名
                while(ret != sizeof(struct node_server))
                    ret = send(conn_fd,&user,sizeof(struct node_server),0);                      //将处理后的信息包发送回去
                return;
            }
            user.consumer.result = 2;                              //文件为空,用户名不存在
            while(ret != sizeof(struct node_server))
                ret = send(conn_fd,&user,sizeof(struct node_server),0);                      //将处理后的信息包发送回去
            return;
        case 2:                                                  //进行注册选项
            if(judge(fp))
            {
                fseek(fp,0L,0);                                  //使文件指针指向开头
                while(!feof(fp))
                {
                    fscanf(fp,"%s %s\n",username,password);             //从文件中读出用户名及密码
                    if(strcmp(username,user.consumer.username) == 0)    //该用户已经被注册过
                    {
                        user.consumer.result = 1;
                        while(ret != sizeof(struct node_server))
                            ret = send(conn_fd,&user,sizeof(struct node_server),0);                      //将处理后的信息包发送回去
                        return;
                    }      
                }
            }
            fseek(fp,0L,2);                                             //移动文件指针至文件末尾进行追加
            fprintf(fp,"%s %s\n",user.consumer.username,user.consumer.passwd1);      //写入注册用户的信息
            fclose(fp);                                                              //写完记得关闭文件
            char str[200] = "/home/Crow/Public/Information/";
            strcat(str,user.consumer.username);                                      //拼接出路径名
            mkdir(str,0755);
            chdir(str);
            creat("groups_information",0644);
            creat("friends_list",0644);
            mkdir("Friends",0755);
            user.consumer.result = 0;
            while(ret != sizeof(struct node_server))
                ret = send(conn_fd,&user,sizeof(struct node_server),0);                      //将处理后的信息包发送回去
            return;
    }
    /*在switch-case语句之后,进行sign数据包的回馈*/
    
    
}

int judge(FILE *fp)
{
    if(fgetc(fp) == EOF)
    {
        fseek(fp,0L,0);                                        //重新回到文件头
        return 0;                                              //空文件
    }
    fseek(fp,0L,0);
    return 1;                                                  //非空文件
}

void send_outline_message(char *str,int conn_fd,struct node_server user)
{
    FILE *fp;
    char ch;
    fp = fopen(str,"r+");
    printf("temp->name:%s\n",str);
    if(fp != NULL)
    {
        if((ch = fgetc(fp)) != EOF)
        {
            while(!feof(fp))
            {
                sleep(2);
                printf("发送离线消息!\n");
                user.flag = 3;user.my_group.choice_group = 1;
                fscanf(fp,"%s %s %s %s\n",user.my_group.date_time,user.my_group.member_name,user.my_group.group_name,user.my_group.group_message);    
                send(conn_fd,&user,sizeof(struct node_server),0);
            }
        }
        fclose(fp);
        remove(str);
    }
    else
    return ;
}

void log_in_message(struct node_server user,char *str,char *ptr)
{
    FILE *fp;
    char ch;
    list *temp;
    char group[30];
    fp = fopen(str,"r+");
    if((ch = fgetc(fp)) != EOF)
    {
        fseek(fp,0L,0);
        while(!feof(fp))
        {
            user.flag = 2;
            user.my_firend.choice_friend = 8;      //表示是提醒功能
            fscanf(fp,"%s\n",group);
            temp = linkedlist_seek_username(pHead,group);
            strcpy(user.my_firend.friends_name,ptr);
            user.my_firend.friends_status = 1;
            if(temp != NULL) 
            send(temp->conn_fd,&user,sizeof(struct node_server),0);
            break;
        }
    }
    return ;
}
