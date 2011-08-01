/*trs.h*/
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sqlite3.h>
#include "use.h"
#include "trs_error.h"
#include "sqlite_error.h"
#include "main.h"

int recvImg(int sockfd, struct sockaddr_in servaddr, const char * id)
{
        
    char trsBuf[MAXLINE];
    char img_dir[MAXNAME];
    int filefd;
    int sn;

    clear_dir(id);
    /*get a file*/
    while(1) 
    {   
        /*get file name and create*/
        bzero(trsBuf, MAXLINE);
        trs_recvfrom(sockfd, trsBuf, MAXLINE, 0, NULL, NULL);
        if(!strcmp(TRS_END, trsBuf))
        {
#ifdef DEBUG
           printf("all file get\n");
#endif
           break; 
        }        

        strcpy(img_dir, id); 
        strcat(img_dir, trsBuf);
        filefd = trs_openm(img_dir, O_RDWR|O_CREAT, 0666);
        if(-1 == filefd) 
        {
            trs_error_exit("open"); 
        }

        /*get file contents and write*/
#ifdef DEBUG
        printf("%s recvfrom ...\n",trsBuf);
#endif
        while(1) 
        {
            bzero(trsBuf, MAXLINE);
            sn = trs_recvfrom(sockfd, trsBuf, MAXLINE, 0, NULL, NULL);

            trs_write(filefd, trsBuf, sn);
            if(sn < MAXLINE) 
            {
                trs_close(filefd);
                break; 
            }
        }

    }
            
}

int recvStr(int sockfd, struct sockaddr_in servaddr, const char * sd)
{
    sqlite3 *db = NULL;

    char strDir[MAXNAME] = STR_DIR;
    char strInsert[MAXLINE];
    char trsBuf[MAXLINE];
    
    struct strStruct str[MAXSTR];

    char *err = NULL;
    int ret = 0;
    int i ,sn;
    char *tp = NULL;

    clear_dir(sd);

    strcat(strDir, "str.db");
    my_sqlite3_open(strDir, &db);
    
#ifdef DEBUG
           printf("create table str\n");
#endif
    my_sqlite3_exec(db, "CREATE TABLE STR(id integer primary key, name text, str text);", NULL, NULL, &err);


    i = 0; 
    while(1) 
    {   
        /*get file name and create*/
        bzero(trsBuf, MAXLINE);
        trs_recvfrom(sockfd, &str[i], MAXLINE, 0, NULL, NULL);

        if(!strcmp(TRS_END, (char *)&str[i]))
        {
#ifdef DEBUG
            printf("all str get\n");
#endif
            break; 
        }        

        strcpy(strInsert, STR_INSERT);
        strcat(strInsert, my_itoa(str[i].id, tp, 10));
        strcat(strInsert, ",'");
        strcat(strInsert, str[i].name);
        strcat(strInsert, "', '");
        strcat(strInsert, str[i].value);
        strcat(strInsert, "');");
#ifdef DEBUG
        printf("%s \n",strInsert);    
#endif        
        my_sqlite3_exec(db, strInsert, NULL, NULL, &err);

        i++;
    }

    sqlite3_close(db);
    return 0;
    
}
