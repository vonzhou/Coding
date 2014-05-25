#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h> // open(),O_RDWR

int main() {
    int count = 0;
    char buff[20], output[20];
    char file_buffer[200];
    int sockfd, connfd, len, fd, nbytes;

    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1) {
        puts("socket not created in client");
        return 1;
    } else {
        puts("socket created in  client");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; // ANY address or use specific address
    servaddr.sin_port = htons(7802);  // Port address

    puts("Type your UDP client message");
    scanf("%s", buff);
    puts("enter the name of new file to be saved");
    scanf("%s", output);

    // send msg to server
    sendto(sockfd, buff, strlen(buff) + 1, 0,
           (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
    count++;
    printf("%d\n", count);

    fd = open(output, O_RDWR | O_CREAT | O_TRUNC);
    if (fd == -1) {
        printf("error in file handling, %d\n",errno);
        return 1;
    }
    recvfrom(sockfd, file_buffer, sizeof(file_buffer), 0, NULL, NULL);
    while (1) {
        if (strcmp(file_buffer, "end") == 0)
            break;
        printf("%s", file_buffer);
        write(fd, file_buffer, strlen(file_buffer));
        bzero(file_buffer, 200);
        recvfrom(sockfd, file_buffer, sizeof(file_buffer), 0, NULL, NULL);
    }
    close(fd);
    puts("completed");
    return 0;
}
