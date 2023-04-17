#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#define IP "127.0.0.1"
#define port 8080 
#define message "HTTP server is ready!"

int main()
{
	int local_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (local_fd == -1)
	{
		std::cout << "socket error!" << std::endl;
		exit(-1);
	}
	std::cout << "socket ready!" << std::endl;

	struct sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port); 
	local_addr.sin_addr.s_addr = inet_addr(IP);

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

	listen(local_fd, 10);
	std::cout << "wait connecting from client...." << std::endl;

	while (true)
	{
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		int client_fd = accept(local_fd, (struct sockaddr *)&client_addr, &len);
		if (client_fd == -1)
		{
			std::cout << "accept error\n"<< std::endl;
			exit(-1);
		}

		char *ip = inet_ntoa(client_addr.sin_addr);
		std::cout << "client： " << ip << std::endl;

		char buff[1024] = {0};
		int size = read(client_fd, buff, sizeof(buff));
		std::cout << "Request information:\n"<< buff << std::endl;
		std::cout << size << " bytes" << std::endl;
		
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
		close(client_fd);
	}
	close(local_fd);
	return 0;
}
