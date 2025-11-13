#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main()
{
	sockaddr_in	serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	int	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	int socketfd_client;

	bind(socketfd, (struct sockaddr *)&serverAddress, sizeof(sockaddr_in));
	listen(socketfd, 2);
	printf("listening on port 8080\n");
	socketfd_client = accept(socketfd, nullptr, nullptr);
	
	std::string response = "HTTP/1.0 200 OK\r\n\r\n<html><head>Bonjour depuis ton serveur C !</head><body><h1>On va bien s'amuser sur webserv :)</h1></body></html>";
	send(socketfd_client, response.c_str(), strlen(response.c_str()), 0);

	close(socketfd_client);
	close(socketfd);
	return (0);
}