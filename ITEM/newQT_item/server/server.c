/*srver.c*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "trs.h"
#include "main.h"

int main(int argc, const char *argv[])
{
    int fd, i;
    pid_t pid;
    char *str = "this is a demon";

    pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
        exit(1);
    }
    else if(pid > 0)
    {
        exit(0);
    }

    setsid();
    chdir("/");
    umask(0);

    for(i = 0; i < getdtablesize(); i++)
    {
        close(i);
    }

    while(1)
    {
        server_main(argc, argv);
    }

    return 0;
} 
//#define DEBUG

int server_main(int argc, const char *argv[])
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    char trs_buf[MAXLINE];
    int sockfd, filefd;
    sockfd = trs_socket(AF_INET, SOCK_DGRAM, 0);
    int n;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SRV_PORT);

    trs_bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

#ifdef DEBUG
    printf("server start ...\n");
#endif
    while(1) 
    {
        cliaddr_len = sizeof(cliaddr);

        /*get client address*/
        trs_recvfrom(sockfd, trs_buf, MAXLINE, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
        n = fork();
        if(-1 == n) 
        {
            trs_error_exit("call to fork"); 
        }
        else if(0 == n) 
        {
#ifdef DEBUG

            printf("%s already connect\n", inet_ntoa(cliaddr.sin_addr));
#endif

            /*send ...*/
            sendImg(sockfd, cliaddr, IMAGE_DIR);
            sendStr(sockfd, cliaddr, STR_DIR);

#ifdef DEBUG
            printf("%s already close\n", inet_ntoa(cliaddr.sin_addr));
#endif
            exit(0);
        }
    }
    return 0;
}
