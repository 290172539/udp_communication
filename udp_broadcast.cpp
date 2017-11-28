/*
 *文件名字:udp_broadcast.cpp
 */

 #include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h> 

 int main(int argc, char *argv[])  
{  
    unsigned short port = 60000; 				//服务器端口  
    //char *server_ip = "192.168.1.255";   		//服务器ip地址,广播地址
 	char *server_ip = "127.0.0.1";   		//服务器ip地址,广播地址  
      
    if( argc > 1 )   							// main函数传参，服务器ip地址  
    {     
        server_ip = argv[1];  
    }  
      
    if( argc > 2 )   							// main函数传参，服务器端口  
    {  
        port = atoi(argv[2]);  
    }  
  
    int sockfd;  
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);   	//创建UDP套接字  
    if(sockfd < 0)  
    {  
        perror("socket");  
        exit(-1);  
    }  
      
    // 套接字地址  
    struct sockaddr_in dest_addr;  
    bzero(&dest_addr, sizeof(dest_addr));   	// 清空内容  
    dest_addr.sin_family = AF_INET;     		// ipv4  
    dest_addr.sin_port   = htons(port); 		// 端口转换  
    inet_pton(AF_INET, server_ip,
			 &dest_addr.sin_addr); 				// ip地址转换 
     
	/*设置广播模式*/
  	int opt = 1;
  	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&opt,sizeof(opt));
    printf("send data to UDP server %s:%d!\n", server_ip, port);  
      
    while(1)  
    {  
        char send_buf[512] = "son,ee,12,111,222,22*ff";  
	
       // fgets(send_buf, sizeof(send_buf), stdin);//获取输入  
        send_buf[strlen(send_buf)-1] = '\0'; 
 
        //发送数据  
        int len = sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));  
        printf("len = %d\n", len);  
		sleep(1);
    }  
      
    close(sockfd);  
    return 0;  
}  
