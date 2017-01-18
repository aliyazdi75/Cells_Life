#include <winsock.h>
#include <stdio.h>
#include <stdint.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 1373

#define NS_INADDRSZ  4
#define NS_IN6ADDRSZ 16
#define NS_INT16SZ   2

//int inet_pton4(const char *src, char *dst)
//{
//	uint8_t tmp[NS_INADDRSZ], *tp;
//
//	int saw_digit = 0;
//	int octets = 0;
//	*(tp = tmp) = 0;
//
//	int ch;
//	while ((ch = *src++) != '\0') {
//		if (ch >= '0' && ch <= '9') {
//			uint32_t n = *tp * 10 + (ch - '0');
//
//			if (saw_digit && *tp == 0)
//				return 0;
//
//			if (n > 255)
//				return 0;
//
//			*tp = n;
//
//			if (!saw_digit) {
//				if (++octets > 4)
//					return 0;
//				saw_digit = 1;
//			}
//		} else if (ch == '.' && saw_digit) {
//			if (octets == 4)
//				return 0;
//			*++tp = 0;
//			saw_digit = 0;
//		} else {
//			return 0;
//		}
//	}
//	if (octets < 4)
//		return 0;
//
//	memcpy(dst, tmp, NS_INADDRSZ);
//	return 1;
//}
//
//static int socket_fd;
//
//struct cell_position cell_new(struct cell_position your_initial_position)
//{
//	/* Loading winsock dll :) */
//	WSADATA wsaData;
//    	WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//	struct sockaddr_in server_addr;
//	struct sockaddr_in client_addr;
//
//	client_addr.sin_family = AF_INET;
//	client_addr.sin_port = htons(SERVER_PORT);
//	inet_pton4(SERVER_ADDR, &client_addr.sin_addr);
//
//	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//
//	if (!connect(socket_fd, (struct sockaddr *) &client_addr,
//		sizeof(client_addr))) {
//		printf("Starting client ....\n");
//
//		// Solving the problem of initial location....
//		struct cell_position result;
//
//		FILE *sk = fdopen(socket_fd, "w");
//		fprintf(sk, "%d %d\n", your_initial_position.x, your_initial_position.y);
//		fflush(sk);
//
//		sk = fdopen(socket_fd, "r");
//		fscanf(sk, "%d %d", &result.x, &result.y);
//
//		return result;
//	}
//
//	printf("Starting server ....\n");
//
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_port = htons(SERVER_PORT);
//	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//
//	int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//	if (server_socket_fd == -1)
//		perror("socket()");
//
//	if (bind(server_socket_fd, (struct sockaddr *) &server_addr,
//		sizeof(server_addr)) == -1)
//		perror("bind()");
//
//	if (listen(server_socket_fd, 10) == -1)
//		perror("listen()");
//
//	socket_fd = accept(server_socket_fd, NULL, NULL);
//
//	// Solving the problem of initial location....
//	struct cell_position result;
//
//	FILE *sk = fdopen(socket_fd, "w");
//	fprintf(sk, "%d %d\n", your_initial_position.x, your_initial_position.y);
//	fflush(sk);
//
//	sk = fdopen(socket_fd, "r");
//	fscanf(sk, "%d %d", &result.x, &result.y);
//
//	return result;
//
//
//}
//
//
//struct cell_move_data cell_move(struct cell_move_data your_move)
//{
//	FILE *sk = fdopen(socket_fd, "w");
//	fprintf(sk, "%d %d\n", your_move.cell_energy, your_move.move_direction);
//	fflush(sk);
//
//	sk = fdopen(socket_fd, "r");
//	struct cell_move_data result;
//	fscanf(sk, "%d %d", &result.cell_energy, &result.move_direction);
//	return result;
//}
