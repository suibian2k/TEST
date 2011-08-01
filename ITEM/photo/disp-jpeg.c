#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"
#include <time.h>

#define DEBUG 0
#if DEBUG
#endif
typedef struct
{
   int x;
   int y;
}lca;
// 1500*1000
static lca leave[1500*1000];
static int r_count;

int getMin(int a, int b, int c)
{
    if(a<b) 
    {
        if(b<c) 
        {
            return a; 
        }
        else if(a<c)
        {
            return a;
        }
        else
        {
            return c;
        }
    }
    else
    {
        if(b>c) 
        {
            return c; 
        }
        else
        {
            return b;
        }
    }
}
int display_jpeg(char *filename, fb_info fb_inf)
{

    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i, j;

    //// nor_jpeg()

        //for(i = 0; i < fb_inf.h; ++i){
            //for (j = 0; j < fb_inf.w; ++j){
                //fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
            //}
            //usleep(100);
        //}

    ////ltor_jpeg()
        //for (j = 0; j < fb_inf.w; ++j)
        //{
            //for(i = 0; i < fb_inf.h; ++i)
            //{
                //fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
            //}
            //usleep(100);
    //}
    //rol_jpeg()

    //int k;
    //int roller_h, space_h, space_board_w;
    //int rh_tmp;
    //u32_t roller_c;
        //roller_h = 50;
        //space_h = 5;
        //roller_c = 0x00ffffff;
        //space_board_w = 30;

        //for(i = 0; i < fb_inf.h; ++i)
        //{
            //rh_tmp = getMin(roller_h, i/2, (fb_inf.h-i-1)/2);

            //for (j = 0; j < fb_inf.w; ++j)
            //{
                //fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
            //}
            //for (j = 0; j < fb_inf.w; ++j)
            //{
                //for(k = 1; k < rh_tmp+1; k++) 
                //{
                    //fb_pixel(fb_inf, j, i+k, buf32[j + (i+2*rh_tmp-k+1) * fb_inf.w]);
                //}
            //}
            //usleep(100);
        //}
    int k;
    while(1)
    {
        //srand(time(NULL));

        i = rand()%fb_inf.h;
        j = rand()%fb_inf.w;

        fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
        k++;
        //printf("%d %d\n",i,j);

    }

    getchar();
    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}
