//Julian Andrade
//Prompt for Assignment 5 part 1
//Creat a socket based program
//	-Opens a stream socket bound to port 9000
//		-if any connection step fails return -1
//	-logs message to syslog "accepted connection from xxx"
//		-xxx = IP address of connected client
//	-Rx data over the connevtion and appends file to "/var/tmp/aesdsocketdata"
//		-if doesnt exist, create it
//		-make a newline to separate data packets Rx
//			-i.e. packet complete when newline character detected in the input stream
//			-append "/var/tmp/aesdsocketdata"
//			-assume: 
//				-no null char in input data stream
//				-len of packet is shorter than available heap size
//	-Returns full content of "/var/tmp/aesdsocketdata" to client as soon as Rx packet completes
//		-assume total size of all packets will be less than size of root file sys
//	-logs message to the syslog "closed connection from xxx"
//	-Restarts accepting connections from new clients forever in a loop intil SIGNINT or SIGTERM is received
//	-Gracefully exits when SIGINT/SIGTERM is Rx, copmleting any operation, closing open sockets and deleting file from "/var/tmp/aesdsocketdata"
//		Logs message to syslog "Caught signal, exiting" when SIGNINT/SIGTERM Rx
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 9000
#define DATA_FILE_PATH "/var/tmp/aesdsocketdata"

volatile sig_atomic_t sigint_received = 0;

void sigint_handler(int signum) {
    sigint_received = 1;
}

int main() {
    int sockfd, client_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];
    int data_file_fd;

    // Open the data file for appending
    data_file_fd = open(DATA_FILE_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (data_file_fd == -1) {
        perror("Failed to open data file");
        return -1;
    }

    // Set up signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    // Open a stream socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        close(sockfd);
        return -1;
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) == -1) {
        perror("Listen failed");
        close(sockfd);
        return -1;
    }

    // Main loop to accept connections
    while (!sigint_received) {
        // Accept a connection
        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
        if (client_sockfd == -1) {
            perror("Accept failed");
            close(sockfd);
            return -1;
        }

        // Log accepted connection
        syslog(LOG_INFO, "Accepted connection from %s", inet_ntoa(client_addr.sin_addr));

        // Receive data and append to file
        ssize_t bytes_received;
        while ((bytes_received = recv(client_sockfd, buffer, sizeof(buffer), 0)) > 0) {
            write(data_file_fd, buffer, bytes_received);
            // Check for newline character to complete packet
            if (buffer[bytes_received - 1] == '\n') {
                break;
            }
        }

        // Return data file content to client
        lseek(data_file_fd, 0, SEEK_SET);
        while ((bytes_received = read(data_file_fd, buffer, sizeof(buffer))) > 0) {
            send(client_sockfd, buffer, bytes_received, 0);
        }

        // Close client socket
        close(client_sockfd);

        // Log closed connection
        syslog(LOG_INFO, "Closed connection from %s", inet_ntoa(client_addr.sin_addr));
    }

    // Close sockets and file descriptor
    close(sockfd);
    close(data_file_fd);

    // Delete data file
    remove(DATA_FILE_PATH);

    // Log signal received
    syslog(LOG_INFO, "Caught signal, exiting");

    return 0;
}

