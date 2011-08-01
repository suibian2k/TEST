/*sqlite_error.h*/
#ifdef _SQLITE_ERROR_H_
#define _SQLITE_ERROR_H_
    
int my_sqlite3_open(char *filename,  sqlite3 **ppDb);

int my_sqlite3_close(sqlite3 *ppDb);

int my_sqlite3_exec(sqlite3* ppDb, const char *sql, sqlite_callback sc, void * e, char **errmsg);

#endif
