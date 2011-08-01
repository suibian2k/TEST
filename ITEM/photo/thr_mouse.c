#include <stdio.h>
#include "main.h"

int thr_mouse(const char* dev, PFBDEV pFbdev, PMOUSE pMouse)
{
    int err;   
    int x, y;

    u32_t cursor_pixel[10*17] = 
    {
        BORD,T___,T___,T___,T___,T___,T___,T___,T___,T___,
        BORD,BORD,T___,T___,T___,T___,T___,T___,T___,T___, 
        BORD,X___,BORD,T___,T___,T___,T___,T___,T___,T___,
        BORD,X___,X___,BORD,T___,T___,T___,T___,T___,T___,
        BORD,X___,X___,X___,BORD,T___,T___,T___,T___,T___,
        BORD,X___,X___,X___,X___,BORD,T___,T___,T___,T___,
        BORD,X___,X___,X___,X___,X___,BORD,T___,T___,T___,
        BORD,X___,X___,X___,X___,X___,X___,BORD,T___,T___,
        BORD,X___,X___,X___,X___,X___,X___,X___,BORD,T___,
        BORD,X___,X___,X___,X___,X___,X___,X___,X___,BORD,
        BORD,X___,X___,X___,X___,X___,BORD,BORD,BORD,BORD,
        BORD,X___,X___,BORD,X___,X___,BORD,T___,T___,T___,
        BORD,X___,BORD,T___,BORD,X___,X___,BORD,T___,T___,
        BORD,BORD,T___,T___,BORD,X___,X___,BORD,T___,T___,
        T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
        T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
        T___,T___,T___,T___,T___,T___,BORD,BORD,T___,T___
    };

    MEVENT mevent;

    /*init the mouse*/
    x = fb_get_width(pFbdev);
    y = fb_get_height(pFbdev);

    err = mouse_init(pMouse, dev, cursor_pixel, 10, 17, x/2, y/2,0);
    if(FALSE == err) 
    {
        printf("mouse init error\n");
        return FALSE; 
    }
    x = mouse_get_start_x(pMouse);
    y = mouse_get_start_y(pMouse);
    mouse_save(pMouse, pFbdev, x, y); 
    mouse_draw(pMouse, pFbdev, x, y);

    /*response the mouse*/
    while(1) 
    {
        err = mouse_parse(pMouse, &mevent);
        if(FALSE == err) 
        {
            continue; 
        }

        mouse_restore(pMouse, pFbdev, x, y);
        
        /*mouse x y*/
        x = mouse_get_x(pMouse, &mevent);
        y = mouse_get_y(pMouse, &mevent);
        if(x<0) 
        {
            x = 0; 
        }
        else if((x+pMouse->w)>fb_get_width(pFbdev))
        {
            x = fb_get_width(pFbdev)-pMouse->w; 
        }
        if(y<0) 
        {
            y = 0; 
        }
        else if((y+pMouse->h)>fb_get_height(pFbdev))
        {
            y = fb_get_height(pFbdev)-pMouse->h; 
        }
        
        /*mouse button*/
        
        switch(mevent.button)
        {
            case 1:
                break;
            case 2:
                break;
            case 4:
                break;
            default:
                break;
        }
        mouse_save(pMouse, pFbdev, x, y); 
        mouse_draw(pMouse, pFbdev, x, y); 
    }

    return TRUE;

}
