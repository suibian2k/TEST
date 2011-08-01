#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int mouse_init(PMOUSE pMouse, const char *dev, u32_t *cursor_pixel
, int m_w, int m_h, int start_x, int start_y, int start_z)
{
    int i,j;

    if(NULL == dev) 
    {
        pMouse->dev = malloc(sizeof("/dev/input/mice"));
        strcpy(pMouse->dev, "/dev/input/mice");
    }

    pMouse->fd = open(pMouse->dev,O_RDWR|O_NONBLOCK); 
    if(-1 == pMouse->fd) 
    {
       return FALSE; 
    }
    
    pMouse->w = m_w;
    pMouse->h = m_h;

    pMouse->cursor_pixel = malloc(pMouse->w*pMouse->h*4);
    memcpy(pMouse->cursor_pixel, cursor_pixel, pMouse->w*pMouse->h*4);

    pMouse->save_cursor = malloc(pMouse->w*pMouse->h*4);

    pMouse->start_x = start_x;
    pMouse->start_y = start_y;
    pMouse->start_z = start_z;

    pMouse->now_x = start_x;
    pMouse->now_y = start_y;
    pMouse->now_z = start_z;

    return TRUE;
}
int mouse_close(PMOUSE pMouse)
{
    close(pMouse->fd);
    pMouse->fd = -1;

    free(pMouse->dev); 
    pMouse->dev = NULL;

    free(pMouse->cursor_pixel); 
    pMouse->cursor_pixel = NULL;

    free(pMouse->save_cursor); 
    pMouse->save_cursor = NULL;

}
int mouse_draw(PMOUSE pMouse, const PFBDEV pFbdev, int x, int y)
{   
    int i,j;
    for(j = 0; j < pMouse->h; j++) 
    {
        for(i = 0; i < pMouse->w; i++) 
        {
            if(T___ != pMouse->cursor_pixel[i+j*pMouse->w])
            {
                fb_draw_pixel(pFbdev, x+i, y+j
                        , pMouse->cursor_pixel[i+j*pMouse->w]);
            }
        }
    }
    return TRUE;
}

int mouse_get_x(PMOUSE pMouse, PMEVENT pMevent)
{
     return pMouse->now_x;
}

int mouse_get_y(PMOUSE pMouse, PMEVENT pMevent)
{
     return pMouse->now_y;
}

int mouse_get_start_x(PMOUSE pMouse)
{
   return pMouse->start_x; 
}

int mouse_get_start_y(PMOUSE pMouse)
{
   return pMouse->start_y; 
}

int mouse_save(PMOUSE pMouse, PFBDEV pFbdev, int x, int y)
{   
    int i,j;

    for(j = 0; j < pMouse->h; j++) 
    {
        for(i = 0; i < pMouse->w; i++) 
        {
                pMouse->save_cursor[i+j*pMouse->w] = 
                    fb_get_pixel(pFbdev, x+i, y+j);             
        }
    }
    return TRUE;
}

int mouse_restore(PMOUSE pMouse, PFBDEV pFbdev, int x, int y)
{   
    int i,j;

    for(j = 0; j < pMouse->h; j++) 
    {
        for(i = 0; i < pMouse->w; i++) 
        {
                fb_draw_pixel(pFbdev, x+i, y+j
                        , pMouse->save_cursor[i+j*pMouse->w]);
        }
    }
    return TRUE;
}


int mouse_parse(PMOUSE pMouse, PMEVENT pMevent)
{
    s8_t buf[READ_MOUSE];
    int n;

    n = read(pMouse->fd, buf, READ_MOUSE);
    if(-1 != n) 
    {
       pMevent->button = buf[0]&0x07;

       pMevent->dx = buf[1];
       pMevent->dy = -buf[2];
       pMevent->dz = buf[3];
       
       pMouse->now_x += buf[1];
       pMouse->now_y += -buf[2];
       pMouse->now_z += buf[3];
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}
