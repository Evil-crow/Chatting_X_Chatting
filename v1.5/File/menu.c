/* 文件:menu.c
 *
 * 作用:服务器事务处理模块
 *
 */


#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include"menu.h"
#include"main.h"
#include"Linkedlist.h"
#include"struct_node_server.h"

struct epoll_event epoll_ev;            //epoll_event类型结构体,用于注册事件使用

void sign_register(int sock_fd,struct node_server user);

void friend_managment(int conn_fd,struct node_server user);

void group_managment(int conn_fd,struct node_server user);

void file_managment(int conn_fd,struct node_server user);

//void log_out_message(struct node_server user,char *str,char *ptr);            //下线提醒

extern int epoll_fd;                       //在epoll_server中定义,此处为引用

extern void _error(const char *string,int line);

extern char *get_time(void);

extern list *pHead;

void menu(void *sock_fd)
{
    int conn_fd = *(int *)sock_fd;
    struct node_server user;                   //进行接受的结构体
    int ret;                                   //处理返回值
    int sum;                                   //进行接收到的包进行求和
    list *temp;
    char str[30];
    char ptr[30];
    //memset(&user,0,sizeof(user));            //如若置空,以后多次交互不好取出信息 
       
    ret = recv(conn_fd,&user,sizeof(struct node_server),0);
    printf("ret = %d\n",ret);
    sum = ret;
    if(ret <= 0)
    {
        if(ret < 0)                         //表示接受失败
            _error("recv",__LINE__);
        if(ret == 0)                     //表示对方已经关闭连接
        {
            printf("客户端退出,开始删除节点\n");
            if(pHead->next != NULL)
            {
                temp = linkedlist_seek_conn_fd(pHead,conn_fd);
                FILE *sp;
                char str[200];
                strcpy(str,get_time( ));
                sp = fopen("/home/Crow/Public/Information/server_log","a+");
                fprintf(sp,"%s log out : %s\n",temp->name,str);
                fclose(sp);
                epoll_ctl(epoll_fd,EPOLL_CTL_DEL,conn_fd,NULL);      //从epoll注册表中删除该事件,并关闭套接字.
                linkedlist_del(pHead,temp->name);
                close(conn_fd);
            }
            else
            {
                epoll_ctl(epoll_fd,EPOLL_CTL_DEL,conn_fd,NULL);      //从epoll注册表中删除该事件,并关闭套接字.
                close(conn_fd);
            }
        }
    }
    if(ret > 0)
    {
        while(sum != sizeof(struct node_server))         
        {
            ret = recv(conn_fd,&user,sizeof(struct node_server),0);
            sum += ret;
        }
        switch(user.flag)
        {
            case 1:                                       //表示执行登录操作
                sign_register(conn_fd,user);              //进行登录注册的函数
                break;
            case 2:                                       //表示进行好友操作
                friend_managment(conn_fd,user);           //进行数据操作通信的函数
                break;
            case 3:
                group_managment(conn_fd,user);            //进行聊天群的处理
                break;
            case 4:
                file_managment(conn_fd,user);             //进行发送文件的处理
                break;
        }
    }
    
    struct epoll_event ep_ev;                            //在工作任务结束之后,进行再注册,使该事件可以再次被报告
    ep_ev.data.fd = conn_fd;
    ep_ev.events = EPOLLIN | EPOLLONESHOT;
    epoll_ctl(epoll_fd,EPOLL_CTL_MOD,conn_fd,&ep_ev);
}

void file_managment(int conn_fd,struct node_server user)
{
    list *temp;                                                      //进行发送人的查找
    list *Temp;                                                      //进行目标的查找
    int ret;
    temp = linkedlist_seek_conn_fd(pHead,conn_fd);
    strcpy(user.my_firend.friend_message,temp->name);

    //第一步,查找将要接受文件的用户
    Temp = linkedlist_seek_username(pHead,user.my_firend.friends_name);
    if(Temp == NULL)                  //离线模式
    {
        printf("离线模式\n");
        return;
    }
    
    //第二步,如果用户在线,则将信息填入,并且发送过去,发送人填在friend_message中
    printf("%s\n",user.my_file.file_data);
    ret = send(Temp->conn_fd,&user,sizeof(struct node_server),0);              //转发包
    printf("ret = %d\n",ret);
    if(ret < 0)
        _error("recv",__LINE__);
}
