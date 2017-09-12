/* 文件:Linklist.c
 *
 * 作用:自行封装的链表操作
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Linkedlist.h"

extern void _error(const char *string,int line);

list *linkedlist_init(list *pHead)
{
    pHead = (list *)malloc(sizeof(list));                      //为头节点动态分配内存
    if(pHead == NULL)
        _error("malloc",__LINE__);
    pHead->next = NULL;
    return pHead;
}

list *linkedlist_add(list *pHead,int conn_fd,char *name)
{
    list *pNew;
    list *pEnd;
    if(pHead == NULL)
    {
        printf("The list is empty!\n");
        exit(EXIT_SUCCESS);
    }
    pEnd = pHead;
    while(pEnd->next != NULL)
        pEnd = pEnd->next;
    
    pNew = (list *)malloc(sizeof(list));                       //为新节点动态分配内存
    if(pNew == NULL)
        _error("malloc",__LINE__);
    pNew->conn_fd = conn_fd;                                   //进行conn_fd的赋值
    strcpy(pNew->name,name);                                   //保存在新用户的姓名
    pEnd->next = pNew;                                         //进行链表的连接
    pNew->next = NULL;                                         //链表末尾指空
    pEnd = pNew;                                               //保留节点

    return pHead;                                              //最后返回头节点
}

list *linkedlist_seek_username(list *pHead,char *name)
{
    int flag = 0;                                              //用来标记是否找到目标节点
    list *temp;                                                //中继节点
    temp = pHead->next;
    while(temp != NULL)
    {
        if(strcmp(name,temp->name) == 0)
        {
            flag = 1;
            return temp;
        }
        temp = temp->next;
    }
    if(flag == 0)
    return NULL;                                               //返回NULL表示没有找到节点

    return 0;
}

list *linkedlist_seek_conn_fd(list *pHead,int conn_fd)
{
    int flag = 0;                                              //用来标记是否找到目标节点
    list *temp;                                                //中继节点
    temp = pHead->next;
    while(temp != NULL)
    {
        if(temp->conn_fd == conn_fd)
        {
            flag = 1;
            return temp;
        }
        temp = temp->next;
    }
    if(flag == 0)
    return NULL;                                               //返回NULL表示没有找到节点

    return 0;
}

list *linkedlist_del(list *pHead,char *name)
{
    list *cur;                                                 //表示当前节点
    list *prev;                                                //保存上一个节点,用于删除
    list *temp;                                                //要删除的目标节点

    if(pHead == NULL)
        exit(EXIT_SUCCESS);
    cur = pHead;
    prev = cur;
    temp = linkedlist_seek_username(pHead,name);
    while(cur != temp)
    {
        prev = cur;
        cur = cur->next;
    }
    prev->next = cur->next;                                     //进行节点的删除

    return pHead;                                              //返回头节点
}