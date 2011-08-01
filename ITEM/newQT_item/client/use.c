/*use.c*/
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include "main.h"

char *my_itoa(int num, char *str, int n)
{
    char *s = (char *)malloc(10);
    switch(n)
    {
        case 10:
            sprintf(s, "%d", num);
    }
    str = s;
    return s;
}

int clear_dir(const char *dir)
{   
    char fs[MAXLINE][256];
    char buf[MAXNAME];
    int fn, i;

    fn = getDir(dir, fs);

    for(i = 0; i < fn; i++) 
    {
        strcpy(buf, dir);
        strcat(buf, fs[i]);
        remove(buf);
#ifdef DEBUG
        printf("%s clear\n",buf);
#endif
    }
    return 0; 
}

int getDir(const char *dir,char (*fs)[256])
{
    struct dirent *dp = NULL;
    DIR *dirp = NULL;
    char buf[MAXNAME];
    int i;

    if(NULL == (dirp = opendir(dir))) 
    {
        trs_error_exit("opendir"); 
    }
    i = 0;
    while(dp = readdir(dirp))
    {
        if((!strcmp(".", dp->d_name))||(!strcmp("..", dp->d_name)))
        {
            continue;
        }
        strcpy(fs[i], dp->d_name);
        i++;
    }
    closedir(dirp);
    return i; 
}
