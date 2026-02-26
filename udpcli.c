#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // 1. Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 2. Send message
    char *msg = "Hello from UDP Client!";
    sendto(sock, msg, strlen(msg), 0,
           (struct sockaddr*)&server_addr, addr_len);

    // 3. Receive response
    int n = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0,
                     (struct sockaddr*)&server_addr, &addr_len);
    buffer[n] = '\0';
    printf("Server says: %s\n", buffer);

    close(sock);
    return 0;
}
