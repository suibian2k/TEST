#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

int fb_init(PFBDEV pFbdev, char *dev)
{
    if(NULL == dev) 
    {
        pFbdev->dev = malloc(sizeof("/dev/fb0"));
        strcpy(pFbdev->dev, "/dev/fb0");
    }

    pFbdev->fb = open(pFbdev->dev, O_RDWR);

    if (-1 == pFbdev->fb)
    {
        printf("open %s error\n", pFbdev->dev);
        return FALSE;
    }

    if (ioctl(pFbdev->fb, FBIOGET_VSCREENINFO, &(pFbdev->fb_var)) == -1)
    {
        printf("ioctl VAR error\n");
        return FALSE;
    }

    if (ioctl(pFbdev->fb, FBIOGET_FSCREENINFO, &(pFbdev->fb_fix)) == -1)
    {
        printf("ioctl FIX error\n");
        return FALSE;
    }
    
    pFbdev->fb_mem_offset = (unsigned long)pFbdev->fb_fix.smem_start
    &(~PAGE_MASK);

    pFbdev->fb_mem = (unsigned long)mmap(NULL, pFbdev->fb_fix.smem_len
    +pFbdev->fb_mem_offset, PROT_READ|PROT_WRITE
    , MAP_SHARED, pFbdev->fb, 0);

    return TRUE;
}

int fb_close(PFBDEV pFbdev)
{
    close(pFbdev->fb);
    pFbdev->fb = -1;
    
    free(pFbdev->dev);
    pFbdev->dev = NULL;

    munmap((void *)pFbdev->fb_mem
    , pFbdev->fb_fix.smem_len + pFbdev->fb_mem_offset);

    return 0;
}

int get_disp_depth(PFBDEV pFbdev)
{
    if(pFbdev->fb<=0) 
    {
        printf("fb dev not open\n");
        return FALSE;
    }
    return pFbdev->fb_var.bits_per_pixel;
}

void fb_memset(void *addr, int c, size_t len)
{
    memset(addr, c, len);
}

int fb_get_width(PFBDEV pFbdev)
{
    return pFbdev->fb_var.xres; 
}

int fb_get_height(PFBDEV pFbdev)
{
    return pFbdev->fb_var.yres; 
}

u32_t fb_get_pixel(PFBDEV pFbdev, int x, int y)
{
    return *((u32_t *)pFbdev->fb_mem+x+y*pFbdev->fb_var.xres);
}

int fb_draw_pixel(PFBDEV pFbdev, int x, int y, u32_t color)
{
    if((x>pFbdev->fb_var.xres)||(y>pFbdev->fb_var.yres)) 
    {
       printf("over the fb_len so can't draw\n");
       return FALSE; 
    }
    else if((x<0)||(y<0)) 
    {
       printf("x<0 or y<0 so can't draw\n");
       return FALSE; 
    }

    u8_t * p = (u8_t *)pFbdev->fb_mem; 
    p = p + x*4 + y*4*pFbdev->fb_var.xres;
    switch(pFbdev->fb_var.bits_per_pixel)
    {
        case 32:
            *(p+3) = color>>24;
        case 24:
            *(p+2) = color>>16;
        case 16:
            *(p+1) = color>>8;
        case 8:
            *p = color; 
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
