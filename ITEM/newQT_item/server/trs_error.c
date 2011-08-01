/*trs_error.c*/

//#define DEBUG
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void trs_error_exit(const char *s)
{
    perror(s); 
    exit(1);
}

int trs_socket(int domain, int type, int protocol)
{
    int ret;
    while(1) 
    {
        ret = socket(domain, type, protocol);
        if(-1 == ret) 
        {
            if(EINTR == errno) 
            {
#ifdef DEBUG
                printf("socket faild ...\n");
                printf("socket will again ...\n");
#endif
                continue;  
            }
            else
            {
                trs_error_exit("socket error");
            
            }
        }
#ifdef DEBUG
        printf("socket sucess\n");
#endif
        return ret;
    }
}

int trs_bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen)
{
    int ret;
    while(1) 
    {
        ret = bind(sockfd, addr, addrlen);
        if(-1 == ret) 
        {
            if(EINTR == errno) 
            {
#ifdef DEBUG
                printf("bind faild ...\n");
                printf("bind will again ...\n");
#endif
                continue;  
            }
            else
            {
                trs_error_exit("bind error");
            }
        }
#ifdef DEBUG
        printf("bind sucess\n");
#endif
        return ret;
    }
}

int trs_listen(int sockfd, int backlog)
{
    int ret;
    while(1) 
    {
        ret = listen(sockfd, backlog);
        if(-1 == ret) 
        {
            if(EINTR == errno) 
            {
#ifdef DEBUG
                printf("listen faild ...\n");
                printf("listen will again ...\n");
#endif
                continue;  
            }
            else
            {
                trs_error_exit("listen error");
            }
        }
#ifdef DEBUG
        printf("listen sucess\n");
#endif
        return ret;
    }
}

int trs_connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen)
{
    int n;
    while(1) 
    {
        n = connect(sockfd, addr, addrlen);
        if(-1 == n) 
        {
            //if(EINTR == errno) 
            //{
//#ifdef DEBUG
                //printf("connect faild ...\n");
                //printf("sleep 1 ...\n");
                //sleep(1)
                //printf("connect will again ...\n");
                //#endif
            continue;  
                //}
            /* client conncting...*/
            //else
            //{
                //trs_error_exit("connect error");
            //}
        }
#ifdef DEBUG
        printf("connect sucess\n");
#endif
        return n;
    }
}
int trs_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int n;
    while(1) 
    {
        n = accept(sockfd, addr, addrlen);
        if(-1 == n) 
        {
            if((EINTR == errno)||(ECONNABORTED == errno))
            {
#ifdef DEBUG
                printf("accept faild ...\n");
                printf("accept will again ...\n");
#endif
                continue;  
            }
            else
            {
                trs_error_exit("accept error");
            }
        }
#ifdef DEBUG
        printf("accept sucess\n");
#endif
        return n;
    }
}
ssize_t trs_read(int fd, void *buf, size_t count)
{
    ssize_t n ;
    while(1) 
    {
        n = read(fd, buf, count);
        if(-1 == n) 
        {
            if(EINTR == errno) 
            {
#ifdef DEBUG
                printf("read faild ...\n");
                printf("read will again ...\n");
#endif
                continue;  
            }
            else
            {
                trs_error_exit("read error");
            }
        }
#ifdef DEBUG
        printf("read sucess\n");
#endif
        return n;
    }
}
ssize_t trs_write(int fd, void *buf, size_t count)
{
    ssize_t n ;
    while(1) 
    {
        n = write(fd, buf, count);
        if(-1 == n) 
        {
            if(EINTR == errno) 
            {
#ifdef DEBUG
                printf("write faild ...\n");
                printf("write will again ...\n");
#endif
                continue;  
            }
            else
            {
                trs_error_exit("write error");
            }
        }
#ifdef DEBUG
        printf("wirte sucess\n");
#endif
        return n;
    }
}

ssize_t trs_recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen)
{
    ssize_t n;    
    n = recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
    if(-1 == n) 
    {
       trs_error_exit("recvfrom error"); 
    }
    return n;
   
}

ssize_t trs_sendto(int sockfd, void *buf, size_t len, int flags,
        struct sockaddr *dest_addr, socklen_t addrlen)
{
    ssize_t n;    
    n = sendto(sockfd, buf, len, flags, dest_addr, addrlen);
    if(-1 == n) 
    {
       trs_error_exit("sendto error"); 
    }
    return n;

}
int trs_open(const char *pathname, int flags)
{
    int n;    
    n = open(pathname, flags);
    if(-1 == n) 
    {
       trs_error_exit("open error"); 
    }
    return n;
}
int trs_openm(const char *pathname, int flags, mode_t mode)
{
    int n;    
    n = open(pathname, flags, mode);
    if(-1 == n) 
    {
       trs_error_exit("open error"); 
    }
    return n;
}

int trs_close(int fd)
{
    int n;    
    n = close(fd);
    if(-1 == n) 
    {
       trs_error_exit("close error"); 
    }
    return n;
}
