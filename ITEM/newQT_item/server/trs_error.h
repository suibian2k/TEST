/*trs_error.h*/
#ifndef _TRS_ERROR_H_
#define _TRS_ERROR_H_

#include <sys/types.h>
#include <sys/socket.h>

/*trs_error.c*/
void trs_error_exit(const char *s);
int trs_socket(int domain, int type, int protocol);
int trs_bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
int trs_listen(int sockfd, int backlog);
int trs_connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
int trs_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
ssize_t trs_read(int fd, void *buf, size_t count);
ssize_t trs_write(int fd, void *buf, size_t count);
size_t trs_recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);
size_t trs_sendto(int sockfd, void *buf, size_t len, int flags,
        struct sockaddr *dest_addr, socklen_t addrlen);
int trs_open(const char *pathname, int flags);
int trs_openm(const char *pathname, int flags, mode_t mode);
size_t trs_close(int fd);

#endif
