#include <stdio.h>
#include <ncurses.h>
#include "stack_snake.h"

#define HIGH 25
#define WIDTH 80

void set_setting();
void press_key(int *step_x, int *step_y);
int move_snake(stack_snake *tail);
void drow();


int main()
{
    int length_snake = 2;

    set_setting();
    
    stack_snake *head = head_create(WIDTH / 2, HIGH / 2);
    stack_snake *tail = tail_create(WIDTH / 2, HIGH / 2 - 1, head);

    while (true)
    {
        /* code */
    }
    


    int move_x, move_y;

}

void set_setting(){
    initscr();
    cbreak();
    noecho();
    nodelay(stdin, true);
}

void press_key(int *step_x, int *step_y){
    int key = getch();
    switch (key)
    {
    case 'w':
        *step_y = 1;
        *step_x = 0;
        break;

    case 's':  
        *step_y =  -1;
        *step_x = 0; 
        break;

    case 'a':
        *step_y =  -1;
        *step_x = 0; 
        break;

    case 'd':
        *step_y =  -1;
        *step_x = 0; 
        break;


    default:
        break;
    }   
}

int move_snake(stack_snake *tail){

    while(tail->next->next != NULL){
        move_snake(tail->next);
    }

    tail->next->x = tail->x;
    tail->next->y = tail->y;


}

void drow(){
        
    refresh();
}
