/* 文件:_recv.c
 *
 * 作用:用于客户端中进行线程接收使用的,_recv线程一直进行资源的接收
 *
 */

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include"struct_node_client.h"
#include"main.h"

struct node_client   recv_user;            //用于recv的结构体

extern int chat_status;                    //表明状态

extern void _error(const char *string,int line);

void _recv(void *socket_fd)
{
    int sock_fd = *(int *)socket_fd;

    int                  ret;             //用来处理返回值
    char                  ch;             //用于判断键位
    int                   sp;             //进行系统调用打开的标识符
    FILE *fp;                             //用于buffer的文件指针
    char  path[100];                      //进行文件的接收
    while(1)
    {
        //while(ret != sizeof(struct node_client))
        ret = recv(sock_fd,&recv_user,sizeof(struct node_client),0);           //收包
        
        /*收包后进行参数的解析*/
        switch(recv_user.flag)                                                //对大标识进行解析
        {
            case 1:                                                      //如果是登录/注册的包
                switch(recv_user.consumer.choice_sign)
                {
                    case 1:                                              //表示是登录包
                        switch(recv_user.consumer.result)
                        {
                            case 0:                                              //表示成功登录信息
                                printf("\t\t\t\t登录成功!(´･_･`)\n");
                                break;
                            case 1:                                              //此用户已在线
                                printf("\t\t\t\t你的帐号已被隔壁练腰的老王提前登录(ಡωಡ)\n");
                                exit(EXIT_SUCCESS);
                                break;
                            case 2:                                              //用户名错误
                                printf("\t\t\t\t没注册用户就想上车,做梦去吧你₍₍ (̨̡ ‾᷄ᗣ‾᷅ )̧̢ ₎₎\n");
                                exit(EXIT_SUCCESS);
                                break;
                            case 3:                                              //密码错误
                                printf("\t\t\t\t自己的密码都记不住,玩锤子(˵¯͒⌢͗¯͒˵)\n");
                                exit(EXIT_SUCCESS);
                                break;
                        }
                        break;
                    case 2:
                        switch(recv_user.consumer.result)
                        {
                            case 0:
                                printf("\t\t\t\t注册成功!(´･_･`)\n");                               
                                break;
                            case 1:
                                printf("\t\t\t\t隔壁老王抢先一步了呢!(ಡωಡ)\n");
                                exit(EXIT_SUCCESS);
                                break;
                        }
                        break;
                }
                break;
            case 2:                                            //flag == 2 表示处理好友相关事件
                switch(recv_user.my_firend.choice_friend)
                {
                    case 1:                                    //choice_friend == 1 表示开始私聊
                        /*私聊收到的消息,分为用户在私聊界面,和不在私聊界面的情况*/
                        if(chat_status == 1)                   //表示在私聊界面
                        {
                            printf("\n");
                            printf("%s[%s]: %s\n",recv_user.my_firend.date_time,recv_user.consumer.username,recv_user.my_firend.friend_message);
                            printf("\n");
                        }
                        if(chat_status == 0)                                   //表示用户不在聊天界面
                        {
                            printf("\n\t\t\t\t您收到%s发来的消息,请及时查看!\n",recv_user.consumer.username);
                            sleep(1);
                            fp = fopen("/home/Crow/Public/buffer1","a+");      //追加信息
                            fprintf(fp,"%s\n%s %s\n",recv_user.my_firend.date_time,recv_user.consumer.username,recv_user.my_firend.friend_message);
                            fclose(fp);                        //写完关闭文件
                        }
                        break;
                    case 2:                                    //表示为添加好友的请求
                        printf("\n您有一条添加好友的系统消息,请及时前往消息盒子查看\n");
                        break;
                    case 3:                                    //不存在有3发回来 
                        break;
                    case 4:                                    //打印好友列表
                        printf("\t\t\t\t%s\n",recv_user.my_firend.friends_name);
                        break;
                    case 5:                                    //删除好友,不存在的
                        break;
                    case 6:                                    //表示显示好友状态
                        if(strcmp(recv_user.my_firend.friends_name,"zero") == 0)
                        {
                            printf("\t\t\t\t暂无好友,快去勾搭小姊姊吧(ಡωಡ)\n");
                            break;
                        }
                        else
                        {
                            if(recv_user.my_firend.friends_status == 0)              //表示用户不在线
                                printf("\t\t\t\t\033[01;31m %s\033[0m\n",recv_user.my_firend.friends_name);
                            else                                                     //则用户在线
                                printf("\t\t\t\t\033[01;32m %s\033[0m\n",recv_user.my_firend.friends_name);
                        }
                        break;
                    case 7:
                        printf("%s\n %s:%s\n",recv_user.my_firend.date_time,recv_user.consumer.username,recv_user.my_firend.friend_message);
                        break;
                    case 8: 
                        if(recv_user.my_firend.friends_status == 0)           //下线提醒
                        printf("\n\t\t\t\t您的好友:%s已下线\n",recv_user.my_firend.friends_name);
                        else 
                        printf("\n\t\t\t\t您的好友:%s已上线\n",recv_user.my_firend.friends_name);
                        break;
                }
                break;
            case 3:                                                                   //表示进行群组的操作
                switch(recv_user.my_group.choice_group)
                {
                    case 1:                                                             //表示群聊/
                        if(chat_status == 1)
                        {
                            printf("%s%s:%s\n",recv_user.my_group.date_time,recv_user.my_group.member_name,recv_user.my_group.group_message);
                        }
                        if(chat_status == 0)
                        {
                            printf("\n\t\t\t\t群组:%s发来消息\n",recv_user.my_group.group_name);
                            sleep(1);
                            fp = fopen("/home/Crow/Public/buffer1","a+");
                            fprintf(fp,"%s\n%s %s\n",recv_user.my_group.date_time,recv_user.my_group.member_name,recv_user.my_group.group_message);
                            fclose(fp);
                        }
                        break;
                    case 2: 
                        //printf("result:%d\n",recv_user.my_group.group_result);                                                            //表示创建群组
                        if(recv_user.my_group.group_result == 0)
                        {
                            printf("\n\t\t\t\t创建群组失败,下次起个diao-diao的名字哟!\n");
                            break;
                        }
                        if(recv_user.my_group.group_result == 1)
                        {
                            printf("\n\t\t\t\t创建群组成功!,快开车啊!\n");
                            break;
                        }
                    case 3:                                                                //表示是加入群组的请求 
                        if(recv_user.my_group.group_result == 0)
                        {
                            printf("\n\t\t\t\t你已经添加过该群组,请重新检查!\n");
                            break;
                        }
                        if(recv_user.my_group.group_result == 1)
                        {
                            printf("\n\t\t\t\t小姊姊,我进来了!快出来玩啊!\n");
                            break;
                        }
                    case 4: 
                        printf("\t\t\t\t%s\n",recv_user.my_group.member_name);
                        break;
                    case 5:                                                      //显示群成员状态的操作
                        if(recv_user.my_group.group_result == 1)
                        printf("\t\t\t\t\033[01;32m %s\033[0m\n",recv_user.my_group.member_name);
                        else
                        printf("\t\t\t\t\033[01;31m %s\033[0m\n",recv_user.my_group.member_name);
                        break;
                    case 6:                                                      //表示查看历史消息
                        if(strcmp(recv_user.my_group.date_time,"zero") != 0)
                        printf("%s %s:%s\n",recv_user.my_group.date_time,recv_user.my_group.member_name,recv_user.my_group.group_message); 
                        else
                        printf("%s\n",recv_user.my_group.group_message);
                        break;
                    case 7: 
                        printf("\t\t\t\t%s\n",recv_user.my_group.group_name);
                        break;
                    case 8:
                        printf("\t\t\t\t%s\n",recv_user.my_group.group_message);
                        break;
                }
                break;
            case 4:                                                              //表示是文件传输的操作
                strcpy(path,"/home/Crow/Public/File/");
                if(recv_user.my_file.file_flag == 1 && chat_status == 4)
                    printf("\n\t\t\t\t%s向您发送文件,请尽快前往消息盒子查收!\n",recv_user.my_firend.friend_message);
                strcat(path,recv_user.my_file.file_name);
                if((sp = open(path,O_RDWR | O_CREAT | O_APPEND,0644) == -1))
                {    
                    fp = fopen(path,"W+");
                    fclose(fp);
                }
                sp = open(path,O_RDWR | O_CREAT | O_APPEND,0644);
                if(sp == -1)
                    _error("open",__LINE__);
                ret = write(sp,recv_user.my_file.file_data,20);
                if(ret == -1)
                    perror("write");
                close(sp);
                break;
        }
    }
}

