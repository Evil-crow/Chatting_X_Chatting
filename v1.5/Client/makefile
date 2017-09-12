Client : main.o _recv.o sign_in.o sock_fd_create.o chat_data.o friends_managment.o view_box.o groups_managment.o file_managment.o
	gcc main.o _recv.o sign_in.o sock_fd_create.o chat_data.o friends_managment.o view_box.o groups_managment.o file_managment.o -o Client -lpthread  
main.o : main.c main.h 
	gcc -c main.c main.h  
_recv.o : _recv.c main.h 
	gcc -c _recv.c main.h 
sign_in.o : sign_in.c struct_node_client.h 
	gcc -c sign_in.c struct_node_client.h 
sock_fd_create.o : sock_fd_create.c 
	gcc -c sock_fd_create.c 
chat_data.o : chat_data.c
	gcc -c chat_data.c
friends_managment.o : friends_managment.c struct_node_client.h
	gcc -c friends_managment.c struct_node_client.h
view_box.o : view_box.c struct_node_client.h chat_data.h
	gcc -c view_box.c struct_node_client.h chat_data.h 
groups_managment.o : groups_managment.c struct_node_client.h
	gcc -c groups_managment.c struct_node_client.h
file_managment.o : file_managment.c struct_node_client.h
	gcc -c file_managment.c struct_node_client.h
clean : 
	rm -rf *.o
	rm -rf *.gch