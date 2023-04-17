#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#define IP "127.0.0.1"//这个一定要用自己服务器的IP
#define port 8080 //监听端口，可以在范围内自由设定
#define message "HTTP server is ready!"//返回给客户机的信息

int main()
{
	//1.创建一个socket套接字
	int local_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (local_fd == -1)
	{
		std::cout << "socket error!" << std::endl;
		exit(-1);
	}
	std::cout << "socket ready!" << std::endl;

	//2.sockaddr_in结构体：可以存储一套网络地址（包括IP与端口）,此处存储本机IP地址与本地的一个端口
	struct sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);  //绑定6666端口
	local_addr.sin_addr.s_addr = inet_addr(IP); //绑定本机IP地址

	//3.bind()： 将一个网络地址与一个套接字绑定，此处将本地地址绑定到一个套接字上
  std::cout << local_fd << std::endl;
  std::cout << "local_addr.sin_family" << local_addr.sin_family << std::endl;
  std::cout << "local_addr.sin_port" << local_addr.sin_port << std::endl;
  std::cout << "local_addr.sin_addr.s_addr" << local_addr.sin_addr.s_addr<<std::endl;
	int res = bind(local_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (res == -1)
	{
		std::cout << "bind error!" << std::endl;
		exit(-1);
	}
	std::cout << "bind ready!" << std::endl;

	//4.listen()函数：监听试图连接本机的客户端
	//参数二：监听的进程数
	listen(local_fd, 10);
	std::cout << "等待来自客户端的连接...." << std::endl;

	while (true)//循环接收客户端的请求
	{
		//5.创建一个sockaddr_in结构体，用来存储客户机的地址
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		//6.accept()函数：阻塞运行，直到收到某一客户机的连接请求，并返回客户机的描述符
		int client_fd = accept(local_fd, (struct sockaddr *)&client_addr, &len);
		if (client_fd == -1)
		{
			std::cout << "accept错误\n"<< std::endl;
			exit(-1);
		}

		//7.输出客户机的信息
		char *ip = inet_ntoa(client_addr.sin_addr);
		std::cout << "客户机： " << ip << " 连接到本服务器成功!" << std::endl;

		//8.输出客户机请求的信息
		char buff[1024] = {0};
		int size = read(client_fd, buff, sizeof(buff));
		std::cout << "Request information:\n"<< buff << std::endl;
		std::cout << size << " bytes" << std::endl;
		
        // 构建HTTP响应
    std::string response = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/plain\r\n"
                          "Content-Length: 13\r\n"
                          "\r\n"
                          "Hello, world!";
    const char* responseBuffer = response.c_str();
    ssize_t bytesWritten = write(client_fd, responseBuffer, strlen(responseBuffer));
    if (bytesWritten == -1) {
        std::cerr << "Failed to send response." << std::endl;
        close(client_fd);
        close(local_fd);
        return -1;
    }
		//10.关闭sockfd
		close(client_fd);
	}
	close(local_fd);
	return 0;
}