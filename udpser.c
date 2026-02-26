#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // 1. Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // 2. Bind to local port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    printf("UDP Server listening on port %d...\n", PORT);

    // 3. Receive message
    int n = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0,
                     (struct sockaddr*)&client_addr, &addr_len);
    buffer[n] = '\0';
    printf("Client says: %s\n", buffer);

    // 4. Send response
    char *response = "Hello from UDP Server!";
    sendto(sock, response, strlen(response), 0,
           (struct sockaddr*)&client_addr, addr_len);

    close(sock);
    return 0;
}
