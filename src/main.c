#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "stack_snake.h"

#define HIGH 25
#define WIDTH 80

void press_key(int *step_x, int *step_y);

int move_head(stack_snake *head, int mov_x, int mov_y, int field[HIGH][WIDTH]);
int move_snake(stack_snake *piece, int field[HIGH][WIDTH], int x_head, int y_head);
int smash_wall(int x, int y);
int smash_in_part(stack_snake *part, int head_x, int head_y);

int creat_apple(int *x, int *y, int field[HIGH][WIDTH]);
int eat_apple(int x_apple, int y_apple, stack_snake *head);

void drow(int field[HIGH][WIDTH]);



int main(){

    int field[HIGH][WIDTH] = {0};
    field[HIGH/2][WIDTH/2] = 1;
    
    time_t t;
    srand((unsigned) time(&t));

    int step_x = 0, step_y = 0;

    int update_screan = 100000;

    int y_apple = 0;
    int x_apple = 0;

    stack_snake *head = head_create(WIDTH / 2, HIGH / 2);
    stack_snake *tail = NULL;

    

    int count = 0;

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);

    while (true)
    {
        if(update_screan >= 100000){
            update_screan = 0;
            if(!move_head(head, step_x, step_y, field)){
                break;
            }

            if(x_apple == 0 && y_apple == 0)
                creat_apple(&x_apple, &y_apple, field);

            if(eat_apple(x_apple, y_apple, head))
            {
                x_apple = 0;
                y_apple = 0;

                if(tail == NULL){
                    tail = tail_create(head->x - step_x, head->y - step_y, head);
                    
                }

                else{
                    tail = tail_create(tail->x, tail->y, tail);
                }

            }

            drow(field);

        }

        press_key(&step_x, &step_y);
        fflush(stdin);
        usleep(10000);
        update_screan += 5000;

    }
    usleep(10000000);
    endwin();
    return 0;
}


void press_key(int *step_x, int *step_y){
    int key = getch();
    
    if(key == 'w' && *step_y == 0){
        *step_y = -1;
        *step_x = 0;
    }

    else if(key == 's' && *step_y == 0){
        *step_y = 1;
        *step_x = 0;
    }

    else if(key == 'a' && *step_x == 0){
        *step_y = 0;
        *step_x = -1;
    }

    else if(key == 'd' && *step_x == 0){
        *step_y = 0;
        *step_x = 1;
    }


}



int move_snake(stack_snake *piece, int field[HIGH][WIDTH], int x_head, int y_head){
    int flag = 1;

    if(piece != NULL){
        if(piece->x == x_head && piece->y == y_head){
            flag = 0;
        }
    
        if(flag == 1){
            field[piece->y][piece->x] = 0;
            flag = move_snake(piece->next, field, x_head, y_head);
            piece->y = piece->before->y;
            piece->x = piece->before->x;
            field[piece->y][piece->x] = 1;
        }   
    }

    return flag;
}

int move_head(stack_snake *head, int mov_x, int mov_y, int field[HIGH][WIDTH]){ 
    
    int flag = 1;
    field[head->y][head->x] = 0;
    

    if(smash_wall(head->x + mov_x, head->y + mov_y)){
        flag = move_snake(head->next, field, head->x+mov_x, head->y+mov_y);
        head->x += mov_x;
        head->y += mov_y;
        field[head->y][head->x] = 1;
    }

    else{
        flag = 0;
    }

    return flag;
}

int smash_in_part(stack_snake *part, int head_x, int head_y){
    int flag = 1;

    if(part->x == head_x && part->y == head_y){
        flag = 0;
    }
    
    return flag;
}

int smash_wall(int x, int y){
    int flag = 1;

    if(y == 0 || y == HIGH - 1 || x == 0 || x == WIDTH - 1){
        flag = 0;
    }

    return flag;
}

int creat_apple(int *x, int *y, int field[HIGH][WIDTH]){
    
    *y = rand() % (HIGH - 1) + 1;

    
    int len = 0;
    int massiv[80] = {0};
    for (int j = 1; j < HIGH-1 && len == 0; j++){
        for(int i = 1; i < WIDTH - 1; i++){
            
            if(field[j][i] == 0){
                *x = 1;
                massiv[len] = i;
                len+=1;
            }
        }
        *y = *y % (HIGH - 1) + 1;

    }

    if(len != 0){
        *x = rand() % len;
        field[*y][*x] = 3;
    }

    return len;
}


int eat_apple(int x_apple, int y_apple, stack_snake *head){
    int flag = 0;

    if(x_apple == head->x && y_apple == head->y){
        flag = 1;
    }

    return flag;
}

void drow(int field[HIGH][WIDTH]){

    clear();
    for(int y = 0; y < HIGH; y++){
        for(int x = 0; x < WIDTH; x++){
            if(y == 0 || y == HIGH - 1){
                printw("#");
            }

            else if(x == 0 || x == WIDTH - 1){
                printw("#");
            }

            else if(field[y][x] == 1){
                printw("0");
            }

            else if(field[y][x] == 3){
                printw("@");
            }

            else{
                printw(" ");
            }
        }

        printw("\n");
    }
    refresh();

}
