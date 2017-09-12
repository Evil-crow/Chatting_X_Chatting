/* 文件:group_managment.c
 *
 * 作用:进行group相关模块的功能处理
 *
 */


#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include"struct_node_server.h"
#include"Linkedlist.h"

extern list *pHead;                                                //全局的链表

extern void _error(const char *string,int line);                        //自定义判错函数

void group_managment(int conn_fd,struct node_server user)
{
    int ret;
    list *temp;                                //在链表中寻找数据
    char ch;                                   //判断文件是否为空的情况

    FILE *fp,*sp;                                  //文件标识符
    char str[200] = "/home/Crow/Public/Information/";
    char pwd[200];                             //获取路径的字符串
    char group[30];                            //暂存内容
    int temp_fd;                                //中介套套接字

    switch(user.my_group.choice_group)
    {
        case 1:                                //进行群聊
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(user.my_group.member_name,temp->name);                       //存入发消息人的姓名
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            strcat(pwd,"/history");
            fp = fopen(pwd,"a+");
            fprintf(fp,"%s %s %s\n",user.my_group.date_time,user.my_group.member_name,user.my_group.group_message);
            fclose(fp);
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            strcat(pwd,"/members");
            printf("%s\n",pwd);
            fp = fopen(pwd,"r+");
            
            while(!feof(fp))
            {
                fscanf(fp,"%s\n",group);
                printf("%s\n",group);                                         //打印群组成员
                temp = linkedlist_seek_username(pHead,group);
                if(temp == NULL)
                {
                    /*如果离线,则写入指定名称的文件中,使用链表获取用户户名直接读*/
                    sp = fopen(group,"a+");
                    fprintf(sp,"%s %s %s %s\n",user.my_group.date_time,user.my_group.member_name,user.my_group.group_name,user.my_group.group_message);
                    fclose(sp);
                    continue;
                }
                if(temp->conn_fd == conn_fd)
                continue;
                printf("conn_fd:%d,temp->conn_fd:%d\n",conn_fd,temp->conn_fd);    //打印套接字
                printf("group: %s\n",group);                       //打印对应的成员
                temp_fd = temp->conn_fd;
                send(temp_fd,&user,sizeof(struct node_server),0);       //发送给所有在线群组成员
            }
            fclose(fp);
            break;
        case 2:                                //创建群组
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(user.my_group.member_name,temp->name);
            /*先进行群组的创建,及成员的写入*/
            strcpy(pwd,str);
            strcat(pwd,"Groups/");  
            strcat(pwd,"groups");            //准备打开文件
            printf("%s\n",pwd);
            fp = fopen(pwd,"a+");
            fseek(fp,0L,0);
            if((ch = fgetc(fp)) != EOF)
            {
                fseek(fp,0L,0);                       //文件指针回头
                while(!feof(fp))
                {
                    fscanf(fp,"%s\n",group);          //读出成员
                    if(strcmp(group,user.my_group.group_name) == 0)
                    {
                        user.my_group.group_result = 0;         //表示已经创建过
                        send(conn_fd,&user,sizeof(struct node_server),0);
                        return;
                    }
                }
            }
            fprintf(fp,"%s\n",user.my_group.group_name);         //写入新的文件名
            fclose(fp);
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            printf("%s\n",pwd);
            mkdir(pwd,0755);                        //创建群组的目录
            chdir(pwd);                             //进入到新创建的该目录
            creat("history",0644);
            creat("members",0644);                  //创建3个目录下的子文件
            strcat(pwd,"/members");
            fp = fopen(pwd,"a+");
            fprintf(fp,"%s\n",user.my_group.member_name);
            fclose(fp);
            strcpy(pwd,str);
            strcat(pwd,user.my_group.member_name);
            strcat(pwd,"/groups_information");
            printf("%s\n",pwd);
            fp = fopen(pwd,"a+");
            fseek(fp,0L,0);
            fprintf(fp,"%s\n",user.my_group.group_name);
            fclose(fp);
            user.my_group.group_result = 1;           //表示创建群组成功
            send(conn_fd,&user,sizeof(struct node_server),0);
            break;
        case 3:                                                       //表示加入群组操作
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(user.my_group.member_name,temp->name);
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            strcat(pwd,"/members");
            printf("%s\n",pwd);
            fp = fopen(pwd,"r+");
            if((ch = fgetc(fp)) != EOF)
            {
                fseek(fp,0L,0);
                while(!feof(fp))
                {
                    fscanf(fp,"%s\n",group);
                    if(strcmp(group,user.my_group.member_name) == 0)
                    {
                        fclose(fp);
                        user.my_group.group_result = 0;             //证明已经加过该群,
                        send(conn_fd,&user,sizeof(struct node_server),0);
                        return ;
                    }
                }
            }
            fclose(fp);
            fp = fopen(pwd,"a+");
            fprintf(fp,"%s\n",user.my_group.member_name);            //写入成员的名字
            fclose(fp);
            strcpy(pwd,str);
            strcat(pwd,user.my_group.member_name);
            strcat(pwd,"/groups_information");
            printf("%s\n",pwd);
            fp = fopen(pwd,"a+");
            fprintf(fp,"%s\n",user.my_group.group_name);             //将群组写入成员的目录内
            fclose(fp);
            user.my_group.group_result = 1;
            send(conn_fd,&user,sizeof(struct node_server),0);
            break;
        case 4:                                                     //表示查看群组成员
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            strcat(pwd,"/members");
            printf("%s\n",pwd);
            fp = fopen(pwd,"r+");
            if((ch = fgetc(fp)) != EOF)
            {
                fseek(fp,0L,0);
                while(!feof(fp))
                {
                    fscanf(fp,"%s\n",user.my_group.member_name);
                    send(conn_fd,&user,sizeof(struct node_server),0);
                }
                return ;
            }
            strcpy(user.my_group.member_name,"该群组还没有成员哟!");
            send(conn_fd,&user,sizeof(struct node_server),0);
            break;
        case 5:                                                     //表示查看群组成员状态
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            strcat(pwd,"/members");
            printf("%s\n",pwd);
            fp = fopen(pwd,"r+");
            if((ch = fgetc(fp)) != EOF)
            {
                fseek(fp,0L,0);
                while(!feof(fp))
                {
                    fscanf(fp,"%s\n",user.my_group.member_name);
                    temp = linkedlist_seek_username(pHead,user.my_group.member_name);
                    if(temp == NULL)
                    user.my_group.group_result = 0;
                    else
                    user.my_group.group_result = 1;
                    send(conn_fd,&user,sizeof(struct node_server),0);
                }
                break;
            }
            strcpy(user.my_group.member_name,"该群组还没有成员哟!");
            send(conn_fd,&user,sizeof(struct node_server),0);
            break;
        case 6:
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(user.my_group.member_name,temp->name);
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            strcat(pwd,"/history");
            printf("%s\n",pwd);
            fp = fopen(pwd,"r+");
            if((ch = fgetc(fp)) == EOF)
            {
                strcpy(user.my_group.date_time,"zero");
                strcpy(user.my_group.group_message,"暂无历史记录,快去寻找邂逅吧!");
                send(conn_fd,&user,sizeof(struct node_server),0); 
                break;
            }
            fseek(fp,0L,0);
            while(!feof(fp))
            {
                fscanf(fp,"%s %s %s\n",user.my_group.date_time,user.my_group.member_name,user.my_group.group_message);
                send(conn_fd,&user,sizeof(struct node_server),0);
            }
            break;
        case 7:                                                              //显示所有加入群组的操作
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(user.my_group.member_name,temp->name);                      //获取到用户名
            strcpy(pwd,str);
            strcat(pwd,user.my_group.member_name);
            strcat(pwd,"/groups_information");
            fp = fopen(pwd,"r+");
            if((ch = fgetc(fp)) != EOF)
            {
                fseek(fp,0L,0);
                while(!feof(fp))
                {
                    fscanf(fp,"%s\n",user.my_group.group_name);
                    send(conn_fd,&user,sizeof(struct node_server),0);
                }
                fclose(fp);
                return ;
            }
            strcpy(user.my_group.group_name,"目前群组内没有小哥哥,也没有小姊姊哟!\n");
            send(conn_fd,&user,sizeof(struct node_server),0);
            return ;
        case 8:                                                          //表示退出群组的操作
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(user.my_group.member_name,temp->name);
            strcpy(pwd,str);
            strcat(pwd,user.my_group.member_name);
            printf("%s\n",pwd);
            chdir(pwd);                                              //切换目录
            fp = fopen("groups_information","r+");
            sp = fopen("a","w+");
            if((ch = fgetc(fp)) == EOF)
            {
                strcpy(user.my_group.group_message,"没有可以退出的群组");
                send(conn_fd,&user,sizeof(struct node_server),0);
                return;
            }
            fseek(fp,0L,0);
            while(!feof(fp))
            {
                fscanf(fp,"%s\n",group);
                if(strcmp(group,user.my_group.group_name) == 0)
                {
                    continue;
                }
                fprintf(sp,"%s\n",group);
            }
            fclose(fp);
            fclose(sp);
            remove("groups_information");
            rename("a","groups_information");
            strcpy(pwd,str);
            strcat(pwd,"Groups/");
            strcat(pwd,user.my_group.group_name);
            printf("%s\n",pwd);
            chdir(pwd);
            fp = fopen("members","r+");
            sp = fopen("a","w+");
            while(!feof(fp))
            {
                fscanf(fp,"%s\n",group);
                if(strcmp(group,user.my_group.member_name) == 0)
                {
                    continue;
                }
                fprintf(sp,"%s\n",group);
            }
            fclose(fp);
            fclose(sp);
            remove("members");
            rename("a","members");
            strcpy(user.my_group.group_message,"已退出该群组!\n");
            send(conn_fd,&user,sizeof(struct node_server),0);
            break;
    }
}