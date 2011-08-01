/*sqlite_error.c*/
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

/*错误处理?*/

int my_sqlite3_open(char *filename,  sqlite3 **ppDb)
{
    int ret;
    ret = sqlite3_open(filename, ppDb);
    return ret;
}

int my_sqlite3_close(sqlite3 *ppDb)
{
    int ret;
    ret =  sqlite3_close(ppDb);
    return ret;
}

int my_sqlite3_exec(sqlite3* ppDb, const char *sql, sqlite3_callback sc, void * e, char **errmsg)
{
    int ret;
    ret =  sqlite3_exec(ppDb, sql,  sc, e, errmsg);
    if(ret != SQLITE_OK) 
    {
        fputs(*errmsg, stderr);
        fputs("\n", stderr);
        sqlite3_close(ppDb);
    }
    
    return ret;
}

