#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "main.h"
#include <unistd.h>
#include <string.h>
fbscr_t fb_v;
extern char chess_board[B_X*B_X];
extern char current_player;
extern u32_t current_color;
int init_screen()
{   
    int fd;

    struct fb_var_screeninfo fb_var;
    u32_t *p = NULL;

    fd = open("/dev/fb0", O_RDWR);
    if (-1 == fd) 
    {
        perror("fb1");
        exit(0);
    }

    if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var))
    {
        perror("ioctl\n");
        exit(0);
    } 

    fb_v.w = fb_var.xres;
    fb_v.h = fb_var.yres;
    fb_v.bpp = fb_var.bits_per_pixel;

    printf("c=%d\ty=%d\tbits=%d\n", fb_v.w, fb_v.h, fb_v.bpp);

    p = mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);

    if (MAP_FAILED == p) 
    {
        perror("mmap");
        exit(0);
    }

    fb_v.memo = p;

    memset((u32_t *)fb_v.memo,0,fb_v.w*fb_v.h*fb_v.bpp/8);
    memset(chess_board, 0, B_Y*B_X);
    current_player = 1;
    current_color = BLACK;

    close(fd);
    return 0;

}
int fb_one_pixel(int x, int y, u32_t color)
{
    *((u32_t*)fb_v.memo+x+y*fb_v.w) = color; 
    return 0;
}
