#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	char *addrStr;
	char *portStr;
	char *backlog;
	struct sockaddr_in addr;
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen;
	unsigned int socketFd;
	unsigned int clientSocketFd;
	char banner[] = ">-< TCP Server-Chan says hello 4yu!!\n";
	int i;

	if (argc < 4) {
		fprintf(stderr, "Usage: %s [ADDR] [PORT] [BACKLOG]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	addrStr = argv[1];
	portStr = argv[2];
	backlog = argv[3];

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(portStr));
	if (addr.sin_port == 0) {
		perror("[PORT] must be an UINT16_T greather than 1 value.\n");
		exit(EXIT_FAILURE);
	}
	if (!(inet_aton(addrStr, &addr.sin_addr))) {
		perror("[ADDR] must be a valid IPv4 value.\n");
		exit(EXIT_FAILURE);
	}

	clientAddrLen = sizeof(clientAddr);

	if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "server: socket(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (bind(socketFd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		fprintf(stderr, "server: bind(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (listen(socketFd, atoi(backlog)) == -1) {
		fprintf(stderr, "server: listen(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Ohayo! I'm TCP Server-Chan (%s:%hu)\n", 
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	for (i = 0; i <= atoi(backlog); ++i) {
		memset(&clientAddr, 0, clientAddrLen);
		if ((clientSocketFd = accept(socketFd, (struct sockaddr *)&clientAddr, &clientAddrLen)) == -1) {
			fprintf(stderr, "server: accept(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("Client connected: (%s:%hu)\n", 
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		
		if (write(clientSocketFd, banner, sizeof(banner)) == -1) {
			fprintf(stderr, "server: write(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (close(clientSocketFd) == -1) {
			fprintf(stderr, "client: close(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	if (close(socketFd) == -1) {
		fprintf(stderr, "server: close(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
