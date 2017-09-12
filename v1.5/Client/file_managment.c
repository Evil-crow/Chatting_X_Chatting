/* 文件:file_managment.c
 *
 * 作用:用于进行文件的传输操作
 *
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"struct_node_client.h"

void __change(char *str);

unsigned long get_file_size(const char *path);

void file_managment(int sock_fd)
{
    int fp;                                               //进行系统调用的文件标识符
    int ret;
    char ch;
    char file_constpath[200];                             //文件的绝对路径
    char file_constpath_copy[200];                        //文件路径的备份
    char friend_name_file[10];                            //暂存好友姓名字符串
    struct node_client user;                              //进行包发送要使用的结构体
    user.flag = 4;                                        //表示进行的是文件传输操作
    user.my_file.file_flag = 1;
    
    printf("\t\t\t\t=====================================================================\n");
    printf("\t\t\t\t                             文件传输\n");
    printf("\t\t\t\t=====================================================================\n");
    printf("\t\t\t\t请输入要发送文件的好友:");
    scanf("%s",friend_name_file);
    printf("\t\t\t\t请输入要传输的文件名:");
    scanf("%s",file_constpath);
    strcpy(file_constpath_copy,file_constpath);                      //复制
    //user.my_file.file_len = get_file_size(file_constpath);           //使用系统调用获取到文件的大小
    __change(file_constpath_copy);                                     //转换
    printf("\t\t\t\t开始传输文件\n");
    fp = open(file_constpath,O_RDONLY);                                 //r打开文件
    if(fp < 0)
    {
        printf("\t\t\t\t该文件不存在,请核实后重新发送!\n");
        return ;
    }
    while(1)
    {
        memset(&user,0,sizeof(struct node_client));
        user.flag = 4;
        strcpy(user.my_firend.friends_name,friend_name_file);
        strcpy(user.my_file.file_name,file_constpath_copy);
        ret = read(fp,user.my_file.file_data,20);
        if(ret != 20)
            break;
        send(sock_fd,&user,sizeof(struct node_client),0);            //进行文件内容的发送
        usleep(15000);
    }
    close(fp);
    printf("\t\t\t\t文件发送完成,接受不接受就不是我能管的了!\n");
    printf("\t\t\t\t按[Enter]键返回\n");
    getchar( );
    if((ch = getchar( )) == '\n')
    return;
}

void __change(char *str)
{
    char ptr[50];
    int i,j;
    j = 0;
    for(i = 0;str[i] != '\0';i++)
    {
	ptr[j++] = str[i];
	if(str[i] == '/')
	{
	    j = 0;
	    continue;
	}
    }
    ptr[j] = '\0';
    strcpy(str,ptr);
}

unsigned long get_file_size(const char *path)  
{  
    unsigned long filesize = -1;      
    struct stat statbuff;  
    if(stat(path, &statbuff) < 0){  
        return filesize;  
    }else{  
        filesize = statbuff.st_size;  
    }  
    return filesize;  
}  
