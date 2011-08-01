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

static struct strStruct  str[MAXSTR];
static char str_count = 0;

int sendImg(int sockfd, struct sockaddr_in cliaddr, const char * id)
{
    char trsBuf[MAXLINE];
    char imgDir[MAXNAME];
    int filefd;
    char fs[MAXLINE][256];
    int sn, fn;
    int i;

    fn = getDir(id, fs);

    /*send a file*/
    for(i = 0; i < fn; i++) 
    {
        strcpy(imgDir,id);
        strcat(imgDir,fs[i]);
        filefd = trs_open(imgDir, O_RDONLY);
#ifdef DEBUG
        printf("%s send ...\n", fs[i]);
#endif
        /*send file name*/         
        trs_sendto(sockfd, fs[i], strlen(fs[i]), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

        while(1) 
        {

            /*send file contents*/
            bzero(trsBuf, MAXLINE);
            sn = trs_read(filefd, trsBuf, MAXLINE);
            sendto(sockfd, trsBuf, sn, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
            if(sn < MAXLINE) 
            {
                trs_close(filefd);
                break; 
            }
            usleep(1);
        }
    }
    trs_sendto(sockfd, TRS_END, strlen(TRS_END), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

}

int strCall(void *p, int row, char *value[], char *name[])
{
    /*当数据内容扩充时 ?*/
    int i;
    *(int*)p = 0;

    for(i = 0; i < row; i++) 
    {
        if(!strcmp(name[i], "name")) 
        {   
           strcpy(str[str_count].name, value[i]);
        }
        else if(!strcmp(name[i], "str"))
        {
           strcpy(str[str_count].value, value[i]);
        }
    }
    str_count++;
    str[str_count].id = str_count;
    return SQLITE_OK;
}
int sendStr(int sockfd, struct sockaddr_in cliaddr, const char * sd)
{

    sqlite3 *db = NULL;
    char strDir[MAXNAME];
    char *err = 0;
    int empty = 1;
    int i,ret;
   
    strcpy(strDir, sd);
    strcat(strDir, "str.db");
    ret = my_sqlite3_open(strDir, &db);
    if(SQLITE_OK != ret) 
    {
        return 0; 
    }

    sqlite3_exec(db, "SELECT * FROM STR;", strCall, &empty, &err);
    //printf("%d\n", empty);

    //if(!empty)
    {
        for(i = 0; i < str_count; i++) 
        {
#ifdef DEBUG
        printf("%s send ...\n", str[i].name);
#endif
        trs_sendto(sockfd, (char *)&str[i], sizeof(str[i]), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

        }
        usleep(1);
    }
    my_sqlite3_close(db);

    /*send the end*/
    trs_sendto(sockfd, TRS_END, strlen(TRS_END), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

}
