# Chatting_X_Chatting项目文档

*暑期的项目文档,也真的是拖了好久才来完成,真的很差劲*

*本项目的内容一切都是可以随意进行学习,使用的,但是切勿用于一切具有商业目的的用途上*

*请于下载内的24小时内迅速删除*

## 0.目录

* [1.引言](#1.引言)
	* [1.1项目综述](#1.1项目综述)
	* [1.2术语表](#1.2术语表)
	* [1.3参考资料](#1.3参考资料)
	* [1.4开发环境及使用工具](#1.4开发环境及使用工具)
	* [1.5使用说明](#1.5使用说明)
* [2.数据结构说明](#2.数据结构)
* [3.模块设计](#2.模块设计)
	* [3.1程序函数调用图及模块分化](#3.1程序函数调用图及模块分化)
	* [3.2功能设计说明](#3.2功能设计说明)
* [4.文件说明](#4.文件说明)
* [5.异常,错误处理](#5.异常,错误处理)
* [6.已经存在的问题及改善方案](#6.已经存在的问题及改善方案)
* [7.运行截图](#7.运行截图)

## 1.引言

### 1.1项目综述
_ _ _

随着网络的发展越来越快,地球越来越小,人与人之间的距离越来越小,**实时通讯**成为必须要实现的一个问题

而在计算机发展史上,也不乏有各种各样的通讯工具的出现**ICQ,MSN,Skype,QQ,Wechat,Yahoo!_Messager.**

此项目是基于一些通讯软件的功能,再结合所学习到的**进程,线程,网络通信**的知识实现的一个通讯软件.

仍然有许多的缺陷,但是已经初步具有实现通讯功能的能力.

### 1.2术语表

_ _ _

|序号  | 术语 |      说明性定义    |
|-----|------|------------------|
|  1  | C/S  | Client/Server模型 |
|  2  | epoll| Linux下处理并发的API|
|  3  | makefile|Linux下进行工程构建的文件|

### 1.3参考资料
_ _ _

在进行该项目的实现时,也查阅了很多的资料

> a.相关类型的书籍

>|书籍|作者|
>|----|---|
> |< Linux_C编程实战 >|董永清|
> |< 高性能Linux服务器构建实战 >|高俊峰|
> |< 鸟哥的Linux私房菜(第三版)|VBird|

> b.查阅的相关的博客,网上资料

> |资料名|作者|
> |-----|---|
> |[Linux-C下C/S架构实例,实现文件传输功能](http://blog.csdn.net/bgylde/article/details/53096739)|bgylde|
> |[IO复用之——epoll](http://2627lounuo.blog.51cto.com/10696599/1784975)|敲完代码好睡觉zzz|

~~事实上,网路上,很多书上的内容都是千篇一律,很废的~~

**但是,我很推荐上面"IO多路复用之---epoll",剖析得很好**

### 1.4开发环境及使用工具

开发环境: Fedora 4.11.12 X86_64

开发工具: Vim及VSCode,gcc编译器

绘图工具: ProcessOn

### 1.5使用说明

如果你曾经有过进行编程的经验,翻一翻目录就会知道该怎么使用了,

但是你如果是初级小白,请按照我接下来的方法进行操作

```
安装说明:
cd ~/Public
git clone https://github.com/Evil-crow/Chatting_X_Chatting.git
cd Chatting_X_Chatting/v1.5/Client
make
make clean
cd ../Server
make
make clean

```

```
使用说明:

Terminal_I

cd Chatting_X_Chatting/v1.5/Server/
./Server

Terminal_II

cd Chatting_X_Chatting/v1.5/Client
./Client

之后,就可以按照提示进行使用

```

此为本机测试方法,若要进行跨机器的通信,请发邮件至我的邮箱

>Evilcrow

>evilcrow486@gmail.com

***

## 2.数据结构说明

本项目中主要是进行线程,进程,网络编程知识的综合运用

所涉及到的数据结构并不是很多,主要是以下两种:

|数据结构|使用之处|
|-------|-------|
|数组|使用数组,主要是在TCP发送包以及各种功能函数实现时所使用的.<br>存储字符串,标识符,各种各样的元素,这样可以使得功能的实现更加便利.<br>但是,在一定情况下,使用数组,并不能很好的提高程序的性能
|链表|链表主要是在Server端使用,使用链表用来存储在线用户.<br>使用C语言不像其他OOP一样,有封装好的类,手动实现,虽然麻烦,但是后面很好使用.<br>,链表基本上,查找上相对慢一点,的那是其他操作很方便.|

## 3.模块设计

### 3.1程序函数调用图及模块分化
___

#### Client

![](https://i.imgur.com/i29cDLM.png)

#### Server

![](https://i.imgur.com/5xhYBPf.png)

### 3.2功能设计说明
___

#### 3.2.1 Client--main模块
_ _ _

##### 功能描述

此模块是进行Client总体控制的main模块

##### 算法和流程图

![](https://i.imgur.com/K3BuFYz.png)

#### 3.2.2 Client--recv模块
_ _ _
##### 功能描述

此模块是Client进行接收包的recv模块

##### 算法和流程图

![](https://i.imgur.com/d78hUjq.png)

#### 3.2.3 Client--chat_data模块
_ _ _
##### 功能描述

此模块是进行Client聊天室的主体控制程序模块

##### 算法与流程图

![](https://i.imgur.com/cyY3fbh.png)

#### 3.2.4 Server--main模块
_ _ _
##### 功能描述

此模块是Server总体控制的main模块

##### 算法与流程图

![](https://i.imgur.com/nUsHYKB.png)

#### 3.2.5 Server--epoll_server模块
_ _ _
##### 功能描述

此模块是Server进行事件管理的重要的epoll模块

##### 算法与流程图

![](https://i.imgur.com/pCzXwPa.png)

### 3.2.6 Server--epoll_menu模块
_ _ _
##### 功能描述

此模块是Server进行事件处理的模块

##### 算法与流程图

![](https://i.imgur.com/hWXdRD5.png)

## 4.文件说明

|文件名|位置|文件描述|
|-----|---|-------|
|buffer1|~/Public/buffer1|存储离线内容|
|buffer2|~/Public/buffer2|存储离线信息位置|
|File目录|~/Public/File|接受发送的文件|
|[用户名]目录|/Public/Information/[用户名]|每一个用户建立一个目录,<br>其中包含了用户的好友目录,群组目录|
|[好友名]目录|~/Public/Information/[用户名]目录/[好友名]目录|其中包含了buffer,history两个文件|
|Groups目录|~/Public/information/Groups目录|其中包含了groups以及members两个文件|

## 5.异常,错误处理

1.关于乱输入引发的错误

解决方案:**使用控制终端的方法进行选项的获取**

```
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
```

2.在其他方面因为操作文件的错误

解决方法:**进行文件打开结果的判断,不合格打印错误提示消息,并且退出**

## 6.已经存在的问题及改善方案

**问题1:不合理的文件结构**

**解决方案:分析实际程序的运行情况,一台主机仅绑定一个客户端,进行合理的文件结构分配**

**问题2:对于不合理的输入**

**解决方案:仍然需要继续进行非法输入的处理**

## 7.运行截图

1.file
![](https://i.imgur.com/soOzFv6.gif)

2.friends
![](https://i.imgur.com/SrQgs4b.gif)

3.groups
![](https://i.imgur.com/vO4ws3m.gif)

4.history
![](https://i.imgur.com/sriJJls.gif)

5.file
![](https://i.imgur.com/m7erd3M.gif)



