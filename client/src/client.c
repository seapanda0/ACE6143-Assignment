#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int sock;
struct sockaddr_in dest_addr;
char tx_buffer[128] = {0};
char address[20] ={0};

void exit_program(int sig){
    printf("Shutting Down Socket");
    tx_buffer[0] = '\0';
    sendto(sock, tx_buffer, sizeof(tx_buffer), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    shutdown(sock, SHUT_RDWR);
    exit(0);
}

int main() {

    signal(SIGINT, exit_program);

    uint16_t port;
    
    // Initialize the socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter port: ");
    scanf("%hu", &port);

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("Enter address: ");
    fgets(address, sizeof(address), stdin);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(address);

    while(1){
        printf("You: ");
        fgets(tx_buffer, sizeof(tx_buffer), stdin);

        // Remove newline character
        int len = strlen(tx_buffer);
        if (len > 0 && tx_buffer[len-1] == '\n') {
            tx_buffer[len-1] = '\0';
        }

        sendto(sock, tx_buffer, sizeof(tx_buffer), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
        recvfrom(sock, tx_buffer, sizeof(tx_buffer), 0, NULL, NULL);
        printf("Server: %s\n\n", tx_buffer);            

    }
}