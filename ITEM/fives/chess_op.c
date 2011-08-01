#include <stdio.h>
#include "main.h"

extern int mx;
extern int my;
char flag;
u32_t  current_color = 0;
char chess_board[B_Y*B_X];
int current_player =0;

int check_win(int lx, int ly);
int chess_one(int x, int y);
int chess_do(void)
{
    int x = mx;
    int y = my;

    int lx = 0;
    int ly = 0;

    int  winner ;
    if (0 == flag) 
    {
        print_board();
        flag = 1;
        return 0;
    }
    if (x < ST_X ||x>ST_X+SPACE*(B_X-1)) 
    {
        if ((x>40)&&(x<80)&&(y>80)&&(y<120)) 
        {
            current_color = BLACK;
            current_player = 1;
        }
        else if ((x>40)&&(x<80)&&(y>180)&&(y<220)) 
        {
            current_color = WHITE;
            current_player = 2;
        }
        return 0;
    }
    if (y < ST_Y ||y>ST_Y+SPACE*(B_Y-1)) 
    {
        return 0;
    }

    int dx = (x-ST_X)%SPACE;
    int dy = (y-ST_Y)%SPACE;

    if (dx<INC&&dy<INC) 
    {
        x = x - dx;
        y = y - dy;
    }
    else if((SPACE-dx)<INC&&dy<INC)
    {
        x = x + SPACE - dx;
        y = y - dy;

    }
    else if((SPACE-dy)<INC&&dx<INC)
    {

        x = x - dx;
        y = y + SPACE - dy;

    }
    else if((SPACE-dx)<INC&&(SPACE-dy)<INC)
    {
        x = x + SPACE - dx;
        y = y + SPACE - dy;
    }
    else 
    {
        return 0;
    }

    lx = (x-ST_X)/SPACE;
    ly = (y-ST_Y)/SPACE;

    chess_board [lx+ly*B_X] = current_player;

    fb_circle(x, y, 13,current_color); 
    winner = check_win(lx, ly);

    if (winner>0) 
    {
        printf("player %d win\n", winner);
        return winner;
    }
    return 0;
}

int  check_win(int lx, int ly)
{
    int i = 0;
    int j = 0;
    int winner;

    for (j = 0; j < B_Y; j++)
    {
        for (i = 0; i < B_X; i++)
        {
            winner = chess_one(i, j);
            if (winner > 0)
            {
                return winner;
            }
        }
    }
    return 0;
}

int chess_one(int x, int y)
{
    int i = 0;
    int j = 0;
    int counter = 0;
    int who = 0;
    int m[4] = {1, 0, 1, 1};
    int n[4] = {0, 1, 1, -1};
    int sx = x;
    int sy = y;

    who = chess_board[x+y*B_X];

    if (who == 0)
    {
        return 0;
    }

    for (j = 0; j < 4; j++)
    {
        for (i = 1, counter = 1, x = sx, y = sy; i < 5; i++)
        {
            x += m[j];
            y += n[j];
            if (chess_board[x+y*B_X] == who)
            {
                counter++;
            }
            else
            {
                break;
            }
        }
        if (counter == 5)
        {
            return who;
        }
    }


    return 0;
}
