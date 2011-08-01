/*client.c*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include "use.h"
#include "trs.h"
#include "main.h"

int main(int argc, const char *argv[])
{
    struct sockaddr_in servaddr;
    int sockfd;
    char trs_buf[MAXLINE];

    sockfd = trs_socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SRV_IP, &servaddr.sin_addr);
    servaddr.sin_port = htons(SRV_PORT);


    /*tell server the address*/
    trs_sendto(sockfd, trs_buf, strlen(trs_buf), 0, (struct sockaddr *)&servaddr , sizeof(servaddr)); 
    
    /*recv ...*/
    recvImg(sockfd, servaddr, IMAGE_DIR);
    recvStr(sockfd, servaddr, STR_DIR);

    trs_close(sockfd);
    return 0;
}
