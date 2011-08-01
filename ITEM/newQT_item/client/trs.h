/*trs.h*/
#ifndef _TRS_H_
#define _TRS_H_

int recvImg(int sockfd, struct sockaddr_in servaddr, const char * id);
int recvStr(int sockfd, struct sockaddr_in servaddr, const char * sd);

#endif
