#include <stdio.h>
#include "main.h"
#include <unistd.h>

int main(int argc, const char *argv[])
{
    
    init_screen();
    //fb_line(0, 0, 1023, 767, 0x0000ff00);
    //fb_line(1023, 767, 0, 0, 0x0000ff00);
    //fb_line(1023, 0, 0, 767, 0x0000ff00);
    //fb_line(0, 767, 1023, 0, 0x0000ff00);
    //fb_circle(512,384,100,0xffffffff);
    //print_board();
    //save_bg(512,367);
    //draw_curser(512,367);
    
    //sleep(3);
    //restore(512,367);
    //draw_curser(300,400);
    mouse_doing();
    return 0;
}
