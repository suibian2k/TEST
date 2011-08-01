#include <stdio.h>
#include <string.h>
#include "main.h"

int main(int argc, const char *argv[])
{
    FBDEV fbdev; 
    MOUSE mouse;
    int err;


    /*open fb*/
    err = fb_init(&fbdev, NULL);
    if(FALSE == err) 
    {
       return -1; 
    };
    
    thr_mouse(NULL, &fbdev, &mouse);

    /*destroy*/
    fb_close(&fbdev);
    mouse_close(&mouse);

    return 0;
}
