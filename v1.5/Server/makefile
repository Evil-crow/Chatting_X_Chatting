Server : main.o epoll_server.o listen_fd_creat.o menu.o sign_register.o Linkedlist.o friend_managment.o group_managment.o
	gcc main.o epoll_server.o listen_fd_creat.o menu.o sign_register.o Linkedlist.o friend_managment.o group_managment.o -o Server -lpthread
main.o : main.c main.h Linkedlist.c Linkedlist.h
	gcc -c main.c main.h Linkedlist.h Linkedlist.c -lpthread
epoll_server.o : epoll_server.c epoll_server.h main.h
	gcc -c epoll_server.c epoll_server.h main.h -lpthread
listen_fd_creat.o : listen_fd_creat.c main.h
	gcc -c listen_fd_creat.c main.h
menu.o : menu.c menu.h main.h struct_node_server.h
	gcc -c menu.c menu.h main.h struct_node_server.h
sign_register.o : sign_register.c menu.h Linkedlist.h Linkedlist.c struct_node_server.h  
	gcc -c sign_register.c menu.h Linkedlist.h Linkedlist.c struct_node_server.h 
friend_managment.o : friend_managment.c Linkedlist.c struct_node_server.h 
	gcc -c friend_managment.c Linkedlist.h struct_node_server.h
group_managment.o : group_managment.c struct_node_server.h Linkedlist.c
	gcc -c group_managment.c struct_node_server.h Linkedlist.h
clean : 
	rm -rf *.o
	rm -rf *.gch