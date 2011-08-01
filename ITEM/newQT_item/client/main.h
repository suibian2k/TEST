/*main.h*/
#ifndef _MAIN_H_
#define _MAIN_H_

#define MAXLINE 1024 //str len
#define MAXNAME 256
#define MAXSTR  256

#define SRV_IP "127.0.0.1"
#define SRV_PORT 8000

#define IMAGE_DIR "./image/"

#define STR_DIR "./db/"
#define STR_LEN 256
#define STR_INSERT "INSERT INTO STR VALUES("

#define TRS_END "."


struct strStruct
{   
   int id;
   char name[MAXNAME];
   char value[MAXLINE];
}*STRSP, STRS;

#endif
