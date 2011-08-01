#ifndef _MAIN_H_
#define _MAIN_H_

#include <linux/fb.h>

typedef unsigned char   u8_t;
typedef char            s8_t;
typedef unsigned short  u16_t;
typedef unsigned int    u32_t;

/*color*/
#define RED     0x00FF0000
#define GREEN   0x0000FF00
#define BLUE    0x000000FF
#define WHITE   0x00FFFFFF
#define BLACK   0x00000000

/*mouse click*/
#define MOUSE_POP       0
#define LEFT_CLICK      1
#define RIGHT_CLICK     2
#define MIDDLE_CLICK    4

/*mouse disp*/
#define M_W         10
#define M_H         17
#define T___        BLACK
#define BORD        WHITE
#define X___        WHITE

/*read mouse number*/
#define READ_MOUSE 8

/*disp mode*/
#define MAIN_MODE 1
#define SLIDE_MODE 2

/*TURE and FALSE*/
#define TRUE 1
#define FALSE 0

/*fb*/
typedef struct fbdev
{
    int fb;
    unsigned long fb_mem_offset;
    unsigned long fb_mem;
    struct fb_var_screeninfo fb_var;
    struct fb_fix_screeninfo fb_fix;
    char *dev;

}FBDEV, *PFBDEV;
    
/*mouse*/
typedef struct mouse
{
    int fd;
    int w;
    int h;

    int start_x;
    int start_y;
    int start_z;

    int now_x;
    int now_y;
    int now_z;

    u32_t *cursor_pixel;
    u32_t *save_cursor;
    char *dev ;
    
}MOUSE, *PMOUSE;

/*mouse event*/
typedef struct mevent
{
    int dx;
    int dy;
    int dz;     //wheel
    int button;
    int flag;

}MEVENT, *PMEVENT;

/*jpeg*/
typedef struct jpeg
{
    u32_t *pjpeg;
    int h;
    int w;

}JPEG, *PJPEG;

/*jpeg node*/
typedef struct jpeg_node
{
    PJPEG *jpeg; 
    struct jpeg_node *p;
    struct jpeg_node *n;

}JPEG_NODE, *PJPEG_NODE;

/*button*/
typedef struct button
{
    int x;
    int y;
    PJPEG *jpeg;
    char *button_name;

}BUTTON, *PBUTTON;

/*slide message*/
typedef struct slide_mss
{
    JPEG_NODE *headfile;
    PFBDEV pfbdev;
    int second;

}SLIDE_MSS,*PSLIDE_MSS;

/**************************in fb.c*************************************/
int fb_init(PFBDEV pFbdev, char *dev);
int fb_close(PFBDEV pfbdev);
int fb_get_width(PFBDEV pFbdev);
int fb_get_height(PFBDEV pFbdev);
void fb_memset(void *addr, int c, size_t len);
int fb_draw_pixel(PFBDEV pFbdev, int x, int y, u32_t color);
u32_t fb_get_pixel(PFBDEV pFbdev, int x, int y);

/**************************in mouse.c********************************/
int mouse_init(PMOUSE pMouse, const char *dev, u32_t *cursor_pixel
, int m_w, int m_h, int start_x, int start_y, int start_z);
int mouse_draw(PMOUSE pMouse, const PFBDEV pFbdev, int x, int y);
int mouse_get_x(PMOUSE pMouse, PMEVENT pMevent);
int mouse_get_y(PMOUSE pMouse, PMEVENT pMevent);
int mouse_save(PMOUSE pMouse, const PFBDEV pFbdev, int x, int y);
int mouse_restore(PMOUSE pMouse, PFBDEV pFbdev, int x, int y);
int mouse_parse(PMOUSE pMouse, PMEVENT pMevent);

/**************************in thr_mouse.c********************************/
int thr_mouse(const char* dev, PFBDEV pFbdev, PMOUSE pMouse);

/**************************in jpeg_disp.c********************************/
/*JPEG_NODE *jpeg_decode(PFBDEV pfbdev, JPEG_NODE *p, const char *img_file);*/
/*int mouse_main(PFBDEV pfbdev);*/
/*FILE_NODE *load_init(FILE_NODE *head, const char *exname, const char *path);*/
/*int load_destroy(FILE_NODE *head);*/

/*JPEG_NODE *jpeg_create_link(PFBDEV pfbdev, JPEG_NODE *jpeg_head, const char *path);*/

/**//**************************in font.c*************************************/
/*int display_font(const char *code,int *len,int x,int y,PFBDEV pfbdev, u32_t color);*/

/**//**************************in jpeg_disp.c*************************************/
/*JPEG_NODE *jpeg_display_zoom(JPEG_NODE *file, PFBDEV pfbdev, int w, int h);*/
/*int display_jpeg(JPEG_NODE *file, PFBDEV pfbdev, int x, int y, int w, int h);*/
/*int slide_display_jpeg(JPEG_NODE *headfile, PFBDEV pfbdev, int second);*/

/**//*************************in button.c*************************/
/*int button_onclick(PBUTTON button, int x, int y);*/
/*PBUTTON button_create(int x, int y, int w, int h, JPEG_NODE *bj_node, PFBDEV pfbdev);*/
/*void button_destroy(PBUTTON button);*/
/*int button_disp(PBUTTON button, PFBDEV pfbdev);*/


#endif
