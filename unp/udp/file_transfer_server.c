#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>   // open(),read()...
#include <sys/types.h>
#include <string.h>

int main() {
    char buff[20];
    char content[200];
    int sd, connfd, fd, len, nbytes;
    int nmemb = 0; // the member of entry raad;

    struct sockaddr_in servaddr, cliaddr;

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sd == -1) {
        puts("socket not created in server");
        return 1;
    } else {
        puts("socket created in server");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(7802);

    if (bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        puts("Not binded");
        return 1;
    } else {
        puts("Binded");
    }

    len = sizeof(cliaddr);

    recvfrom(sd, buff, 1024, 0, (struct sockaddr *)&cliaddr, &len);

    printf("%s\n", buff);

    fd = open(buff, O_RDONLY);
    if (fd == -1) {
        printf("File does not exist \n");
        return 1;
    }

    while ((nbytes = read(fd, content, sizeof(content))) > 0) {
        sendto(sd, content, sizeof(content), 0, (struct sockaddr*)&cliaddr, len);
        bzero(content, 200);
    }
    strcpy(content, "end");
    sendto(sd, content, sizeof(content), 0, (struct sockaddr*)&cliaddr, len);
    close(fd);
    return 0;
}


