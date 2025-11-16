#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fstream>

int main()
{
	sockaddr_in	serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	int	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	int socketfd_client;

	int opt = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));
	
	if (bind(socketfd, (struct sockaddr *)&serverAddress, sizeof(sockaddr_in)) < 0)
		std::cout << "Error : couldn't bind" << std::endl;
	if (listen(socketfd, 2) < 0)
		std::cout << "Error : couldn't listen" << std::endl;
	printf("listening on port 8080\n");
	socketfd_client = accept(socketfd, nullptr, nullptr);
	
	std::ifstream	textfile;
	textfile.open("text.html");
	std::string file_response;
	std::getline(textfile, file_response, '\0');
	std::string response = "HTTP/1.0 200 OK\r\n\r\n" + file_response;
	send(socketfd_client, response.c_str(), response.size(), 0);

	close(socketfd_client);
	close(socketfd);
	return (0);
}